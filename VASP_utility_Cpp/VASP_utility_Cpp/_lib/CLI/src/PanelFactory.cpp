

#include "PanelFactory.h"
#include "Panel.h"

namespace CLI {
  std::shared_ptr<IPanel> PanelFactory::getPanel(const PanelSetting& setting)
  {
    IPanel* panel = nullptr;
    switch (setting.mType)
    {
    case PanelType::DEFUALT:
      panel = new Panel(std::string(setting.mName));
      break;
    }
    return std::shared_ptr<IPanel>(panel);
  }
}
