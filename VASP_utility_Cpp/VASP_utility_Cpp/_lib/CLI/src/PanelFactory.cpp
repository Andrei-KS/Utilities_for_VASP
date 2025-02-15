

#include "PanelFactory.h"
#include "Panel.h"

namespace CLI {
  std::shared_ptr<IPanel> PanelFactory::getPanel(PanelType type, const char* panelName)
  {
    IPanel* panel = nullptr;
    switch (type)
    {
    case PanelType::DEFUALT:
      panel = new Panel(std::string(panelName));
      break;
    }
    return std::shared_ptr<IPanel>(panel);
  }
}
