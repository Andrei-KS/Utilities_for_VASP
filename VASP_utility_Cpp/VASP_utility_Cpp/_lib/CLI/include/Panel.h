#ifndef __PANEL_H__
#define __PANEL_H__

#include <string>
#include <vector>

class CalledPanelFunction;

/**
* @author Andrei-KS
*/
class Panel
{
public:
	/**
	* 
	*/
	Panel(const std::string& titel);

	/**
	* 
	*/
	void ChangeTextMessage(const std::string& textMessage);
	
	/**
	* 
	*/
	void ShowPanel() const;

	/**
	* 
	*/
	void ShowTextMessage() const;

	/**
	* 
	*/
	void ShowItems() const;

	/**
	* 
	*/
	void AddItem(const std::string& textInItems, CalledPanelFunction* cpfunction);

	/**
	* 
	*/
	void RemoveItem(size_t indexItem);

	/**
	* 
	*/
	void ChangeItem(size_t indexItem, const std::string& textInItems, CalledPanelFunction* cpfunction);

	/**
	* 
	*/
	void ExecuteItemFunction(size_t indexItem);

	/**
	* 
	*/
	const std::string& GetTitel() const;

	/**
	* 
	*/
	const std::string& GetTextMessage() const;
	
	/**
	* 
	*/
	const std::vector<std::pair<std::string, CalledPanelFunction*>>& GetItems() const;

	/**
	* 
	*/
	const std::pair<std::string, CalledPanelFunction*>& GetItem(size_t indexItem) const;

private:
	/** contains name this panel */
	std::string itsTitel;
	
	/** contains text that will display on screen */
	std::string itsTextMessage;

	/** contains items that will display on screen at items dashboard*/
	std::vector<std::pair<std::string, CalledPanelFunction*>> itsItems;
};

#endif // !__PANEL_H__