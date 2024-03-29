﻿// VASP_utility_Cpp.cpp : Defines the entry point for the application.
//

#include "Panel.h"
#include "ToggleFunction.h"
#include "ShowContentTextFileFunction.h"
#include <iostream>
#include "EIGENVALFileConvertingHandler.h"

int main()
{
	Panel mainPanel("MainMenu");
	mainPanel.ChangeTextMessage("Main menu:");

	
#ifdef DEBUG_BUILD
	std::string nameFile = "exempl";
	ShowContentTextFileFunction* ShowContentFunction = new ShowContentTextFileFunction(nameFile);
	mainPanel.AddItem("Show content " + nameFile, ShowContentFunction);
#endif

	std::string nameEIGENVAL = "EIGENVAL";
	EIGENVALFileConvertingHandler efch(nameEIGENVAL);
	efch.Convert("_OUTPUT_EIGNVAL", 3.81811261);
	efch.GetFermiSurface("_OUTPUT_FERMISURFACE", 3.81811261);

#ifdef DEBUG_BUILD
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
#endif

	return 0;
}
