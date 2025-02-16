/*
  @author Andrei-KS
  created at the 2021
*/
#ifndef __PANEL_H__
#define __PANEL_H__

#include "IPanel.h"
#include <string>

namespace CLI {
  /**
  * 
  */
  class Panel : public IPanel
  {
  public:
    /**
    *
    */
    Panel(const std::string& titel);

    /*
    * 
    */
    ~Panel();

    /**
    *
    */
    virtual const std::string& GetTitel() const override { return mTitel; }

    /**
    *
    */
    virtual const std::string& GetPromMessage() const override { return mPromMessage; }

    /**
    *
    */
    virtual const size_t GetOptionNumber() const override { return mOptions.size(); }

    /**
    *
    */
    virtual const OptionSetting& GetOption(size_t optionIndex) const override;

    /**
    *
    */
    virtual void ChangePromMessage(const std::string& text) override { mPromMessage = text; }

    /**
    *
    */
    virtual void ChangeOption(size_t optionIndex, const OptionSetting& optionSetting) override;

    /**
    *
    */
    virtual void AddOption(const OptionSetting& optionSetting) override;

    /**
    *
    */
    virtual void swapOption(const size_t firstOptionIndex, const size_t secondOptionIndex) override;

    /**
    *
    */
    virtual void RemoveOption(size_t optionIndex) override;

    /**
    *
    */
    virtual void SelectOption(size_t optionIndex) override;

    /**
    *
    */
    virtual void ShowPromMessage() const override;

    /**
    *
    */
    virtual void ShowOptions() const override;

    /**
    *
    */
    virtual void ShowPanel() const override;

    /**
    *
    */
    virtual bool IsPendingClose() const override { return mIsPendingClose; }

    /**
    *
    */
    virtual void ClosePanel() override { mIsPendingClose = true; }

  private:
	  /** contains name this panel */
	  std::string mTitel;
	
	  /** contains text that will display on screen */
	  std::string mPromMessage;

	  /** contains options that will display on screen*/
	  std::vector<OptionSetting> mOptions;

    /** */
    bool mIsPendingClose;
  };
}

#endif // !__PANEL_H__