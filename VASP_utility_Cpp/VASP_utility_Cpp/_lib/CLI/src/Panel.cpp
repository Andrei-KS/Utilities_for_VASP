

#include "Panel.h"
#include "CalledPanelFunction.h"
#include <iostream>
#include <exception>

Panel::Panel(const std::string& titel)
	: itsTitel(titel)
	, itsTextMessage(std::string())
	, itsItems(std::vector<std::pair<std::string, CalledPanelFunction*>>())
{
}

void Panel::ChangeTextMessage(const std::string& textMessage)
{
	itsTextMessage = textMessage;
}

void Panel::ShowPanel() const
{
	ShowTextMessage();
	ShowItems();
}

void Panel::ShowTextMessage() const
{
	std::cout << itsTextMessage << std::endl;
}

void Panel::ShowItems() const
{
	for(size_t it = 0; it < itsItems.size(); it++)
	{
		std::cout << it << ".\t" << itsItems[it].first << std::endl;
	}
}

void Panel::AddItem(const std::string& textInItems, CalledPanelFunction* cpfunction)
{
	itsItems.push_back(std::pair<std::string, CalledPanelFunction*>(textInItems, cpfunction));
}

void Panel::RemoveItem(size_t indexItem)
{
	itsItems.erase(itsItems.begin() + indexItem);
}

void Panel::ChangeItem(size_t indexItem, const std::string& textInItems, CalledPanelFunction* cpfunction)
{
	try
	{
		itsItems.at(indexItem).first = textInItems;
		itsItems.at(indexItem).second = cpfunction;

	}
	catch (const std::exception& e)
	{
		std::cout << "Error:\tPanel::ChangeItem(size_t indexItem, const std::string& textInItems, CalledPanelFunction* cpfunction):\t" << e.what() << std::endl;
		throw e;
	}
}

void Panel::ExecuteItemFunction(size_t indexItem)
{
	CalledPanelFunction* cpfunction = nullptr;
	try
	{
		cpfunction = itsItems.at(indexItem).second;
	}
	catch (const std::exception& e)
	{
#ifdef DEBUG_BUILD
		std::cout << "Error:\tPanel::ExecuteItemFunction(size_t indexItem):\t" << e.what() << std::endl;
#endif
		std::cout << "This value is not valid" << std::endl;
		return;
	}

	if (cpfunction == nullptr)
	{
		return;
	}

	cpfunction->execute();
}

const std::string& Panel::GetTitel() const
{
	return itsTitel;
}

const std::string& Panel::GetTextMessage() const
{
	return itsTextMessage;
}

const std::vector<std::pair<std::string, CalledPanelFunction*>>& Panel::GetItems() const
{
	return itsItems;
}

const std::pair<std::string, CalledPanelFunction*>& Panel::GetItem(size_t indexItem) const
{
	return itsItems.at(indexItem);
}