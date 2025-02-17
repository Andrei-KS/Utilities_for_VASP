

#include "PanelManger.h"
#include <stdexcept>

namespace CLI
{
  PanelManger* PanelManger::mPanelManger = nullptr;

  PanelManger::PanelManger()
    : mPanelMap(std::unordered_map<std::string, std::shared_ptr<CLI::IPanel>>())
  {
  }

  PanelManger * const PanelManger::GetPanelManger()
  {
    if (mPanelManger == nullptr)
    {
      mPanelManger = new PanelManger();
    }
    return mPanelManger;
  }

  std::shared_ptr<IPanel> PanelManger::GetNextPanel()
  {
    auto it = mPanelMap.find(mNextPanel);
    if (it == mPanelMap.end())
    {
      throw std::logic_error(std::string(mNextPanel) + "has not found in VASP_utility::panelMap");
    }
    return it->second;
  }

  void PanelManger::AddNewPanel(std::shared_ptr<IPanel> panel)
  {
    if (!panel.get())
    {
      throw std::logic_error("panel is nullptr");
    }

    auto it = mPanelMap.find(panel->GetTitel());
    if (it != mPanelMap.end())
    {
      throw std::logic_error(std::string(panel->GetTitel()) + " was already added");
    }
    mPanelMap.insert({ panel->GetTitel(), panel });
  }

  void PanelManger::SetTransition(std::shared_ptr<IPanel> srcPanel, std::shared_ptr<IPanel>& distPanel)
  {
    if (!(srcPanel.get() && distPanel.get()))
    {
      throw std::logic_error("srcPanel or distPanel is nullptr");
    }

    auto it = mPanelMap.find(srcPanel->GetTitel());
    if (it == mPanelMap.end())
    {
      throw std::logic_error("srcPanel" + std::string(srcPanel->GetTitel()) + " isn't added to PanelManager");
    }
    it = mPanelMap.find(distPanel->GetTitel());
    if (it == mPanelMap.end())
    {
      throw std::logic_error("distPanel" + std::string(distPanel->GetTitel()) + " isn't added to PanelManager");
    }

    std::weak_ptr<CLI::IPanel> wpSrcPanel = srcPanel;
    CLI::OptionSetting backOptionSetting{ "Back to " + srcPanel->GetTitel(), [this,wpSrcPanel]()->void
      {
        auto panel = wpSrcPanel.lock();
        mNextPanel = panel->GetTitel();
      }
    };
    distPanel->AddOption(backOptionSetting);

    std::weak_ptr<CLI::IPanel> wpDistPanel = distPanel;
    CLI::OptionSetting goToOptionSetting{ "Go to " + distPanel->GetTitel(), [this,wpDistPanel]()->void
      {
        auto panel = wpDistPanel.lock();
        mNextPanel = panel->GetTitel();
      }
    };
    srcPanel->AddOption(goToOptionSetting);
  }

  void PanelManger::SetNextPanel(std::shared_ptr<IPanel> panel)
  {
    if (!panel.get())
    {
      throw std::logic_error("panel is nullptr");
    }
    auto it = mPanelMap.find(panel->GetTitel());
    if (it == mPanelMap.end())
    {
      throw std::logic_error("srcPanel" + std::string(panel->GetTitel()) + " isn't added to PanelManager");
    }

    mNextPanel = panel->GetTitel();
  }
}