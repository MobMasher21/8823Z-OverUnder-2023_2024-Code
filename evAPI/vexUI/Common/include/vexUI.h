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
      vex::thread *controllerUIThread = nullptr;

    public:
      vexUI();
      ~vexUI();

      /**
       * @brief Starts all the threads for the UI.
       * @returns An evError.
       *          Data_Already_Exists: If the threads have already been created.
       *          No_Error: If there is no error.
      */
      evError startThreads();

      //*UI objects
      /**
       * @brief The UI for the primary controller. Displays three lines of data at a time, but can scroll to display different lines.
      */
      controllerUI primaryControllerUI = controllerUI(primaryController.Screen);

      /**
       * @brief The UI for the secondary controller. Displays three lines of data at a time, but can scroll to display different lines.
      */
      controllerUI secondaryControllerUI = controllerUI(secondaryController.Screen);

      /**
       * @brief The UI for the auto selector. Consists of pages that each contain 8 customizable buttons. Pages can be switched
       *        by pressing arrow buttons at the bottom of the screen.
      */
      AutoSelector autoSelectorUI = AutoSelector();

  };
  
} // namespace evAPI

#endif // VEXUI_H