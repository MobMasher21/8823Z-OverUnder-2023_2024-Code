/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       selectorTabData.cpp                                       */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 6, 2023                                               */
/*    Description:  Class that holds data for the selector tabs.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include "../include/tabGroup.hpp"

namespace evAPI
{
  void tabGroup::createTabView()
  {
    //Create the core tabview object if it doesn't exist
    if(!tabViewInit)
    {
      pageTabView = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 35);
      tabViewInit = true;
    }
  }

  tabGroup::tabGroup()
  {}

  void tabGroup::addTab()
  {
    //Make sure the core tabview object has been created
    createTabView();

    //LVGL object for te tab
    lv_obj_t *tempTab;

    //Create a name for the tab
    char *temporaryName;
    asprintf(&temporaryName, "Tab: %i", tabCount+1);

    //Create the tab and give it the created name
    tempTab = lv_tabview_add_tab(pageTabView, temporaryName);

    //Add the tab to the vector
    pageTabs.push_back(tempTab);

    //Increase the amount of tabs
    tabCount++;
  }

  void tabGroup::addTab(const char *Name)
  {
    //Make sure the core tabview object has been created
    createTabView();

    //LVGL object for the tab
    lv_obj_t *tempTab;

    //Create the tab and give it a name
    tempTab = lv_tabview_add_tab(pageTabView, Name);

    //Add the tab to the vector
    pageTabs.push_back(tempTab);

    //Increase the amount of tabs
    tabCount++;
  }

  size_t tabGroup::getTabCount()
  {
    return tabCount;
  }

} // namespace evAPI