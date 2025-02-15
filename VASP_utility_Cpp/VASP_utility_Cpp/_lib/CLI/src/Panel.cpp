

#include "Panel.h"
#include <iostream>
#include <stdexcept>


namespace CLI {
  Panel::Panel(const std::string& titel)
    : mTitel(titel)
    , mPromMessage(std::string())
    , mOptions(std::vector<OptionSetting>())
    , mIsPendingClose(false)
  {
  }

  Panel::~Panel()
  {
  }

  const OptionSetting& Panel::GetOption(size_t optionIndex) const
  {
    if (optionIndex > mOptions.size())
    {
      throw std::out_of_range(std::string("Panel::GetOption get ") + std::to_string(optionIndex));
    }
    return mOptions[optionIndex];
  }

  void Panel::ChangeOption(size_t optionIndex, const OptionSetting& optionSetting)
  {
    if (optionIndex > mOptions.size())
    {
      throw std::out_of_range(std::string("Panel::ChangeOption get ") + std::to_string(optionIndex));
    }
    mOptions[optionIndex] = optionSetting;
  }

  void Panel::AddOption(const OptionSetting& optionSetting)
  {
    mOptions.push_back(optionSetting);
  }

  void Panel::RemoveOption(size_t optionIndex)
  {
    if (optionIndex > mOptions.size())
    {
      throw std::out_of_range(std::string("Panel::ChangeOption get ") + std::to_string(optionIndex));
    }
    mOptions.erase(mOptions.begin() + optionIndex);
  }

  void Panel::SelectOption(size_t optionIndex)
  {
    if (optionIndex > mOptions.size())
    {
      throw std::out_of_range(std::string("Panel::ChangeOption get ") + std::to_string(optionIndex));
    }
    mOptions[optionIndex].mFunction();
  }

  void Panel::ShowPromMessage() const
  {
    std::cout << mPromMessage << std::endl;
  }

  void Panel::ShowOptions() const
  {
    for(size_t optionIndex = 0; optionIndex < mOptions.size(); ++optionIndex)
    {
      std::cout << optionIndex << ".\t" << mOptions[optionIndex].mName << std::endl;
    }
  }

  void Panel::ShowPanel() const
  {
    ShowPromMessage();
    ShowOptions();
  }
}