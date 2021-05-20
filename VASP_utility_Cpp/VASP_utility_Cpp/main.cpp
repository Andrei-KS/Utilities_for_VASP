// VASP_utility_Cpp.cpp : Defines the entry point for the application.
//

#include "Panel.h"
#include "ToggleFunction.h"
#include "ShowContentTextFileFunction.h"
#include <iostream>

int main()
{
	Panel mainPanel("MainMenu");
	mainPanel.ChangeTextMessage("Main menu:");

	
#ifdef DEBUG_BUILD
	std::string nameFile = "exempl";
	ShowContentTextFileFunction* ShowContentFunction = new ShowContentTextFileFunction(nameFile);
	mainPanel.AddItem("Show content " + nameFile, ShowContentFunction);
#endif

	bool ExitFlag = false;
	ToggleFunction * ExitFunction = new ToggleFunction(&ExitFlag);
	mainPanel.AddItem("Exit", ExitFunction);
	while (!ExitFlag)
	{
		int choice;
		mainPanel.ShowPanel();
		std::cin >> choice;
		mainPanel.ExecuteItemFunction(choice);
	}
	return 0;
}
