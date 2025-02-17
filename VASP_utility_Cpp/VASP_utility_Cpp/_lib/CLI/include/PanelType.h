/*
* @author Andrei-KS
* created at the 2025
*/

#ifndef __PANEL_TYPE_H__
#define __PANEL_TYPE_H__

#include <string>
#include <functional>

namespace CLI
{
  /**
  *
  */
  struct OptionSetting
  {
    std::string mName;
    std::function<void()> mFunction;
  };

  /**
  * 
  */
  enum class PanelType
  {
    DEFUALT = 0,
    NUM_PANEL_TYPE,
  };
}

#endif // !__PANEL_TYPE_H__