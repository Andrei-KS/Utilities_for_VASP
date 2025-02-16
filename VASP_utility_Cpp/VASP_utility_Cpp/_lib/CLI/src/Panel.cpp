

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

  void Panel::swapOption(const size_t firstOptionIndex, const size_t secondOptionIndex)
  {
    if (firstOptionIndex > mOptions.size())
    {
      throw std::out_of_range(std::string("Panel::swapOption firstOptionIndex [" + std::to_string(firstOptionIndex) + "] bigger than mOptions.size()"));
    }
    if (secondOptionIndex > mOptions.size())
    {
      throw std::out_of_range(std::string("Panel::swapOption secondOptionIndex [" + std::to_string(secondOptionIndex) + "] bigger than mOptions.size()"));
    }
    OptionSetting temp = mOptions[firstOptionIndex];
    mOptions[firstOptionIndex] = mOptions[secondOptionIndex];
    mOptions[secondOptionIndex] = temp;
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
    const std::string seporator(40, '-');
    std::cout << seporator << std::endl;
    ShowPromMessage();
    ShowOptions();
    std::cout << seporator << std::endl;
  }
}