/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vexUI.h                                                   */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Dec 19, 2023                                              */
/*    Description:  Core classes used to control all aspects of the UI.       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef VEXUI_H
#define VEXUI_H

#include "../evAPI/Common/include/evAPIBasicConfig.h"
#include "../../AutoSelector/include/AutoSelector.h"
#include "../../controllerUI/include/controllerUI.h"

namespace evAPI
{
  class vexUI
  {
    private:
      //*Threads used for updating the UIs
      //vex::thread *brainUIThread = nullptr;
      vex::thread *controllerUIThread = nullptr;

    public:
      vexUI(/* args */);
      ~vexUI();

      evError startThreads();

      //UI objects
      controllerUI primaryControllerUI = controllerUI(&primaryController.Screen);
      controllerUI secondaryControllerUI = controllerUI(&secondaryController.Screen);
      AutoSelector autoSelectorUI = AutoSelector();

  };

  extern vexUI UI;
  
} // namespace evAPI

#endif // VEXUI_H