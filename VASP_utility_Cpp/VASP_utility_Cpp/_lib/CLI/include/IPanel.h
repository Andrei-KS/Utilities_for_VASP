/*
  @author Andrei-KS
  created at the 2025
*/
#ifndef __IPANEL_H__
#define __IPANEL_H__

#include <string>
#include <vector>
#include "PanelType.h"

namespace CLI {
  /**
  * 
  * Title
  * Prom text
  * option1
  * option2
  * ...
  * optinN
  *
  * When we select option we will call bonded to it function
  *
  */
  class IPanel
  {
  public:
    /**
    *
    */
    IPanel() {};

    /**
     *
     */
    virtual ~IPanel() {};

    /**
    *
    */
    virtual const std::string& GetTitel() const = 0;

    /**
    *
    */
    virtual const std::string& GetPromMessage() const = 0;

    /**
    *
    */
    virtual const size_t GetOptionNumber() const = 0;

    /**
    *
    */
    virtual const OptionSetting& GetOption(size_t optionIndex) const = 0;

    /**
    *
    */
    virtual void ChangePromMessage(const std::string& text) = 0;

    /**
    *
    */
    virtual void ChangeOption(size_t optionIndex, const OptionSetting& optionSetting) = 0;

    /**
    *
    */
    virtual void AddOption(const OptionSetting& optionSetting) = 0;

    /**
    *
    */
    virtual void RemoveOption(size_t optionIndexItem) = 0;

    /**
    *
    */
    virtual void SelectOption(size_t optionIndex) = 0;

    /**
    *
    */
    virtual void ShowPromMessage() const = 0;

    /**
    *
    */
    virtual void ShowOptions() const = 0;

    /**
    *
    */
    virtual void ShowPanel() const = 0;

    /**
    * 
    */
    virtual bool IsPendingClose() const = 0;

    /**
    * 
    */
    virtual void ClosePanel() = 0;
  };
}

#endif // !__IPANEL_H__