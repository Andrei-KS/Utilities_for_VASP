// VASP_utility_Cpp.cpp : Defines the entry point for the application.
//

#include "PanelFactory.h"
#include <iostream>
#include "EIGENVALFileConvertingHandler.h"
#include "StringProcessingUtilits.h"
#include <unordered_map>
#include <stdexcept>
#include "PanelManger.h"

namespace VASP_utility {
  inline void KeepWindowOpen()
  {
    std::cin.clear();
    std::cout << "Please enter a character to exit\n";
    char ch;
    std::cin >> ch;
    return;
  }

  void SkipToNomber()
  {
    std::cout << "Sorry, that was not a number; please try again\n";
    if (std::cin.fail())
    { // we found something that wasn’t an integer
      std::cin.clear(); // we’d like to look at the characters
      for (char ch; std::cin >> ch; )
      { // throw away non - digits
        if (isdigit(ch) || ch == '-')
        {
          std::cin.unget(); // put the digit back, so that we can read the number
          return;
        }
      }
    }
    throw std::exception("no input"); // eof or bad: give up
  }

  int GetInt(const std::function<bool(int)> check = [](int) {return true; })
  {
    int n = 0;
    while (true)
    {
      if (std::cin >> n)
      {
        if (check(n))
        {
          return n;
        }
        else
        {
          continue;
        }
      }
      SkipToNomber();
    }
  }

  double GetDouble(const std::function<bool(int)> check = [](int) {return true; })
  {
    double n = 0;
    while (true)
    {
      if (std::cin >> n)
      {
        if (check(n))
        {
          return n;
        }
        else
        {
          continue;
        }
      }
      SkipToNomber();
    }
  }


  void clear_screen()
  {
#if defined(WIN32)||defined(_WIN32)
    std::system("cls");
#else
    std::system("clear");
#endif
  }

  FileProcessing::EIGENVALFileConvertingHandler* eigenvalFileConvertingHandler = nullptr;
  double* eigenvalFermiLevel = nullptr;
  std::string GetPromEIGENVAL(std::shared_ptr<CLI::IPanel> panel)
  {
    std::string result;
    if (panel.get())
    {
      result = panel->GetTitel() +
        "\n EIGENVAL path : " + (eigenvalFileConvertingHandler == nullptr ? "not found" : eigenvalFileConvertingHandler->getFullFileName()) +
        "\n FermiLevel    : " + std::to_string(*eigenvalFermiLevel);
    }
    return result;
  }

  void createMenu()
  {
    std::shared_ptr<CLI::IPanel> mainMenupanel = CLI::PanelFactory::getPanel({ CLI::PanelType::DEFUALT, "MainMenu" });
    mainMenupanel->ChangePromMessage(mainMenupanel->GetTitel());

    std::shared_ptr<CLI::IPanel> eigenvalPanel = CLI::PanelFactory::getPanel({ CLI::PanelType::DEFUALT, "EIGENVALPanel" });
    eigenvalPanel->ChangePromMessage(GetPromEIGENVAL(eigenvalPanel));

    std::weak_ptr<CLI::IPanel> wpEigenvalPanel = eigenvalPanel;
    CLI::OptionSetting runConvertOptionSetting{ "Run Convert", [wpEigenvalPanel]()->void
      {
        auto panel = wpEigenvalPanel.lock();
        std::cout << "Please wait...";
        eigenvalFileConvertingHandler->Convert(*eigenvalFermiLevel);
      }
    };
    eigenvalPanel->AddOption(runConvertOptionSetting);

    CLI::OptionSetting setEIGENVALPathOptionSetting{ "Set new EIGENVAL path", [wpEigenvalPanel]()->void
      {
        auto panel = wpEigenvalPanel.lock();
        std::string nameFile;
        // TODO: Andrei-KS 2025:
        // need to resolve issue with twice calling getline,
        // because if it is deleted, we will skip the required input string.
        // I think we need to rid of buffer content of cin.
        std::getline(std::cin, nameFile);
        while (true)
        {
          std::cout << "please enter new EIGENVAL path(or !back if you want return to panel):";
          std::cin.clear();
          std::getline(std::cin, nameFile);

          if(nameFile == "!back")
          {
            break;
          }

          nameFile = nameFile + StringProcessingUtilits::getPathSeparate() + "EIGENVAL";
          try
          {
            FileProcessing::EIGENVALFileConvertingHandler* newEigenvalFileConvertingHandler = new FileProcessing::EIGENVALFileConvertingHandler(nameFile);
            delete eigenvalFileConvertingHandler;
            eigenvalFileConvertingHandler = newEigenvalFileConvertingHandler;
            break;
          }
          catch (std::exception e)
          {
            std::cout << e.what() << "\n";
          }
        }
        panel->ChangePromMessage(GetPromEIGENVAL(panel));
      }
    };
    eigenvalPanel->AddOption(setEIGENVALPathOptionSetting);

    CLI::OptionSetting setFermiLevelOptionSetting{ "Set new FermiLevel", [wpEigenvalPanel]()->void
      {
        auto panel = wpEigenvalPanel.lock();
        std::cout << "please enter new Fermi level:";
        *eigenvalFermiLevel = GetDouble();
        panel->ChangePromMessage(GetPromEIGENVAL(panel));
      }
    };
    eigenvalPanel->AddOption(setFermiLevelOptionSetting);

    std::shared_ptr<CLI::IPanel> exitPanel = CLI::PanelFactory::getPanel({ CLI::PanelType::DEFUALT, "EXIT" });
    exitPanel->ChangePromMessage(exitPanel->GetTitel());

    CLI::PanelManger* pm = CLI::PanelManger::GetPanelManger();
    pm->AddNewPanel(mainMenupanel);
    pm->AddNewPanel(eigenvalPanel);
    pm->AddNewPanel(exitPanel);
    
    pm->SetNextPanel(mainMenupanel);

    pm->SetTransition(mainMenupanel, eigenvalPanel);
    pm->SetTransition(mainMenupanel, exitPanel);
  }
}

int main()
{
  VASP_utility::eigenvalFermiLevel = new double(0);
  try
  {
    std::string nameEIGENVAL = "EIGENVAL";
    VASP_utility::eigenvalFileConvertingHandler = new FileProcessing::EIGENVALFileConvertingHandler(nameEIGENVAL);
  }
  catch (std::exception e)
  {
    std::cout << e.what();
  }
  VASP_utility::createMenu();


//#ifdef DEBUG_BUILD
//	std::string nameFile = "exempl";
//	ShowContentTextFileFunction* ShowContentFunction = new ShowContentTextFileFunction(nameFile);
//	mainPanel.AddItem("Show content " + nameFile, ShowContentFunction);
//#endif

	//std::string nameEIGENVAL = "EIGENVAL";
	//EIGENVALFileConvertingHandler efch(nameEIGENVAL);
	//efch.Convert("_OUTPUT_EIGNVAL", 3.81811261);
	//efch.GetFermiSurface("_OUTPUT_FERMISURFACE", 3.81811261);

  CLI::PanelManger* pm = CLI::PanelManger::GetPanelManger();
  while (true)
  {
    std::shared_ptr<CLI::IPanel> panel = pm->GetNextPanel();
    if (!panel.get())
    {
      throw std::logic_error("panel doesn't exist");
    }
    if (panel->GetTitel() == "EXIT")
    {
      break;
    }
    VASP_utility::clear_screen();
    panel->ShowPanel();
    int choice = VASP_utility::GetInt([panel](int choice)
      {
        if (choice < 0 || choice >= panel->GetOptionNumber())
        {
          std::cout << "Sorry, that is incorrect option; please try again\n";
          return false;
        }
        return true;
      }
    );
    panel->SelectOption(choice);
  }

  VASP_utility::clear_screen();
  VASP_utility::KeepWindowOpen();

  delete VASP_utility::eigenvalFermiLevel;
	return 0;
}
