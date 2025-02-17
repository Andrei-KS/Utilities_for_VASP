// VASP_utility_Cpp.cpp : Defines the entry point for the application.
//

#include "PanelFactory.h"
#include <iostream>
#include "EIGENVALFileConvertingHandler.h"
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

  void SkipToInt()
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
      SkipToInt();
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

  void createMenu()
  {
    std::shared_ptr<CLI::IPanel> mainMenupanel = CLI::PanelFactory::getPanel({ CLI::PanelType::DEFUALT, "MainMenu" });
    mainMenupanel->ChangePromMessage(mainMenupanel->GetTitel());

    std::shared_ptr<CLI::IPanel> eigenvalPanel = CLI::PanelFactory::getPanel({ CLI::PanelType::DEFUALT, "EIGENVALPanel" });
    eigenvalPanel->ChangePromMessage(eigenvalPanel->GetTitel());

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
	return 0;
}
