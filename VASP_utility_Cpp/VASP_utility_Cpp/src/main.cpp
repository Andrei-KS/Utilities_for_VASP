// VASP_utility_Cpp.cpp : Defines the entry point for the application.
//

#include "PanelFactory.h"
#include <iostream>
#include "EIGENVALFileConvertingHandler.h"
#include <unordered_map>
#include <stdexcept>

namespace VASP_utility {
  std::unordered_map<std::string, std::shared_ptr<CLI::IPanel>> panelMap = std::unordered_map<std::string, std::shared_ptr<CLI::IPanel>>();
  std::string nextPanel;

  void clear_screen()
  {
#if defined(WIN32)||defined(_WIN32)
    std::system("cls");
#else
    std::system("clear");
#endif
  }

  std::shared_ptr<CLI::IPanel> createMainPanel()
  {
    std::shared_ptr<CLI::IPanel> spPanel = CLI::PanelFactory::getPanel(CLI::PanelType::DEFUALT, "MainMenu");
    spPanel->ChangePromMessage(spPanel->GetTitel());
    std::weak_ptr<CLI::IPanel> wpPanel = spPanel;
    CLI::OptionSetting exitOptionSetting{ "Exit", [wpPanel]()->void
      {
        if (auto panel = wpPanel.lock())
        {
          panel->ClosePanel();
        }
        nextPanel.clear();
      }
    };
    spPanel->AddOption(exitOptionSetting);

    return spPanel;
  }

  std::shared_ptr<CLI::IPanel> createEIGENVALPanel(std::shared_ptr<CLI::IPanel> parent)
  {
    std::shared_ptr<CLI::IPanel> spPanel = CLI::PanelFactory::getPanel(CLI::PanelType::DEFUALT, "EIGENVALPanel");
    spPanel->ChangePromMessage(spPanel->GetTitel());
    
    std::weak_ptr<CLI::IPanel> wpPanel = spPanel;
    std::weak_ptr<CLI::IPanel> wpParent = parent;
    CLI::OptionSetting backOptionSetting{ "Back to " + parent->GetTitel(), [wpPanel,wpParent]()->void
      {
        auto panel = wpPanel.lock();
        auto parent = wpParent.lock();
        if (panel && parent)
        {
          nextPanel = parent->GetTitel();
        }
        else
        {
          nextPanel.clear();
        }
      }
    };
    spPanel->AddOption(backOptionSetting);

    CLI::OptionSetting goToOptionSetting{ "Go to "+ spPanel->GetTitel(), [wpPanel]()->void
      {
        auto panel = wpPanel.lock();
        if (panel)
        {
          nextPanel = panel->GetTitel();
        }
      }
    };
    parent->AddOption(goToOptionSetting);

    parent->swapOption(parent->GetOptionNumber() - 1, parent->GetOptionNumber() - 2);

    return spPanel;
  }
}

int main()
{
	std::shared_ptr<CLI::IPanel> pMainPanel = VASP_utility::createMainPanel();
  std::shared_ptr<CLI::IPanel> pEIGENVALPanel = VASP_utility::createEIGENVALPanel(pMainPanel);
  VASP_utility::panelMap.insert({ pMainPanel->GetTitel(), pMainPanel });
  VASP_utility::panelMap.insert({ pEIGENVALPanel->GetTitel(), pEIGENVALPanel });
  VASP_utility::nextPanel = pMainPanel->GetTitel();

//#ifdef DEBUG_BUILD
//	std::string nameFile = "exempl";
//	ShowContentTextFileFunction* ShowContentFunction = new ShowContentTextFileFunction(nameFile);
//	mainPanel.AddItem("Show content " + nameFile, ShowContentFunction);
//#endif

	//std::string nameEIGENVAL = "EIGENVAL";
	//EIGENVALFileConvertingHandler efch(nameEIGENVAL);
	//efch.Convert("_OUTPUT_EIGNVAL", 3.81811261);
	//efch.GetFermiSurface("_OUTPUT_FERMISURFACE", 3.81811261);

	while (!VASP_utility::nextPanel.empty())
	{
    auto it = VASP_utility::panelMap.find(VASP_utility::nextPanel);
    if (it == VASP_utility::panelMap.end())
    {
      throw std::logic_error(std::string(VASP_utility::nextPanel) + "has not found in VASP_utility::panelMap");
    }
    std::shared_ptr<CLI::IPanel> currentPanel = it->second;
    VASP_utility::clear_screen();
    currentPanel->ShowPanel();
		int choice;
		std::cin >> choice;

    currentPanel->SelectOption(choice);
	}


	return 0;
}
