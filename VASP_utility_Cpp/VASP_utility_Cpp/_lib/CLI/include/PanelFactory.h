/*
  @author Andrei-KS
  created at the 2025
*/
#ifndef __PANEL_FACTORY_H__
#define __PANEL_FACTORY_H__

#include "PanelType.h"
#include "IPanel.h"
#include <memory>

namespace CLI {
  class PanelFactory {
  public:
    static std::shared_ptr<IPanel> getPanel(PanelType type, const char* panelName);
  };
}

#endif // !__PANEL_FACTORY_H__