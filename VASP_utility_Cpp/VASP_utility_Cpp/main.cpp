// VASP_utility_Cpp.cpp : Defines the entry point for the application.
//

#include "PanelFactory.h"
#include <iostream>
#include "EIGENVALFileConvertingHandler.h"

namespace VASP_utility {
  std::shared_ptr<CLI::IPanel> createMainPanel()
  {
    std::shared_ptr<CLI::IPanel> pMainPanel = CLI::PanelFactory::getPanel(CLI::PanelType::DEFUALT, "MainMenu");
    pMainPanel->ChangePromMessage(pMainPanel->GetTitel());

    CLI::OptionSetting exitOptionSetting{ "Exit", [pMainPanel]()->void {pMainPanel->ClosePanel(); } };
    pMainPanel->AddOption(exitOptionSetting);

    return pMainPanel;
  }
}

int main()
{
	std::shared_ptr<CLI::IPanel> pMainPanel = VASP_utility::createMainPanel();

//#ifdef DEBUG_BUILD
//	std::string nameFile = "exempl";
//	ShowContentTextFileFunction* ShowContentFunction = new ShowContentTextFileFunction(nameFile);
//	mainPanel.AddItem("Show content " + nameFile, ShowContentFunction);
//#endif

	//std::string nameEIGENVAL = "EIGENVAL";
	//EIGENVALFileConvertingHandler efch(nameEIGENVAL);
	//efch.Convert("_OUTPUT_EIGNVAL", 3.81811261);
	//efch.GetFermiSurface("_OUTPUT_FERMISURFACE", 3.81811261);

	while (!pMainPanel->IsPendingClose())
	{
		int choice;
    pMainPanel->ShowPanel();
		std::cin >> choice;
    pMainPanel->SelectOption(choice);
	}


	return 0;
}
