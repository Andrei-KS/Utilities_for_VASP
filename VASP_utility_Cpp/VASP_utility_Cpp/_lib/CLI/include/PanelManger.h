/*
  @author Andrei-KS
  created at the 2025
*/
#ifndef __PANEL_MANGER_H__
#define __PANEL_MANGER_H__

#include "PanelType.h"
#include "IPanel.h"
#include <unordered_map>
#include <memory>

namespace CLI
{
  /**
  * 
  */
  class PanelManger
  {
  public:
    /**
    * 
    */
    static PanelManger* const  GetPanelManger();

    /**
    * 
    */
    std::shared_ptr<IPanel> GetNextPanel();

    /**
    * 
    */
    void AddNewPanel(std::shared_ptr<IPanel> panel);

    /**
    * 
    */
    void SetTransition(std::shared_ptr<IPanel> srcPanel, std::shared_ptr<IPanel>& distPanel);

    /**
    * 
    */
    void SetNextPanel(std::shared_ptr<IPanel> panel);

  private:
    /**
    * 
    */
    PanelManger();

    /**
    * 
    */
    static PanelManger* mPanelManger;
    
    /** */
    std::unordered_map<std::string, std::shared_ptr<CLI::IPanel>> mPanelMap;

    /** */
    std::string mNextPanel;
  };
}

#endif // !__PANEL_MANGER_H__