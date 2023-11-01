/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       tabGroup.hpp                                              */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 6, 2023                                               */
/*    Description:  Class that holds data for the selector tabs.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef SELECTORTABDATA_H
#define SELECTORTABDATA_H

#include <string>
#include <vector>
#include <sys/types.h>
#include "lvgl.h"
#include "evAPISettings.h"

namespace evAPI
{
  class tabGroup
  {
    private:
      //Stores if the tab view has been created or not
      bool tabViewInit = false;

      /**
       * @brief Creates the tabview object and defines its parameters.
      */
      void createTabView();

    public:

      /**
       * @brief Adds a tab to the tab group.
       *        The name will be "Tab: " followed by the number of the tab.
      */
      void addTab();

      /**
       * @brief Adds a tab to the tab group.
       * @param Name The name of the tab.
      */
      void addTab(const char *Name);

      /**
       * @returns The amount of tabs in the tab group.
      */
      size_t getTabCount();

      //!LVGL objects need to be exposed in order for the UI to work with them
      //Main tabview object. Holds all the other tabs
      lv_obj_t *pageTabView;

      //All the tabs associated with this tab group
      std::vector<lv_obj_t *> pageTabs;
  };
  
} // namespace evAPI

#endif // SELECTORTABDATA_H