/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       coreUI.hpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 20, 2023                                              */
/*    Description:  Class that consolidates and controls all the UIs from     */
/*                  the evAPI.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef COREUI_HPP
#define COREUI_HPP

#include "vex_thread.h"
#include "../../preautoUI/include/preautoUI.hpp"
#include "../evAPI/Common/include/evErrorTypes.hpp"

namespace evAPI
{
  enum class UIStates
  {
    Disabled,
    Preauto_UI,
    Match_UI
  };

  class coreUI
  {
    private:
      //Thread for updating the brain UI
      vex::thread *brainUIThread = nullptr;

      //Status of the brain UI
      UIStates brainUIMode = UIStates::Disabled;

      //If the brain UI is in manual control
      bool brainUIManualControl = false;
      
    public:
      coreUI();
      ~coreUI();

      /**
       * @brief The UI for the auto selector. By default, it will appear when the robot is in the
       * disabled period of a competition.
      */
      preautoUI autoSelector;
      //matchUI matchDisplays;
      //controllerUI primaryControllerUI;
      //controllerUI secondaryControllerUI;

      /**
       * @brief Starts the UI if it hasn't already been started.
       * @returns An evError.
       *          Object_Property_Not_Specified: If neither brain UI has been configured.
       *          Device_Already_Exists: If the UI has already been started.
       *          No_Error: If the UI thread has been successfully started.
     */
      evError startUI();

      /**
       * @brief Sets the status of manual control for the UI. Setting this to true will prevent
       *        the UI from automatically changing screens when the competition mode changes.
       * @param status The status of manual control.
      */
      void setManualControl(bool status);

      /**
       * @brief Sets the state of the brain UI.
       * @param mode The mode for the brain UI.
       * @warning This function will not have any affect if manual control for the brain UI is disabled.
       *          Make sure the brain UI is disabled before calling this function.
      */
      void setUIMode(UIStates mode);

      /**
       * @returns The current mode for the brain UI.
      */
      UIStates getUIMode();

      /**
       * @returns True if the brain UI is in manual control mode.
      */
      bool getManualControlStatus();
  };

  extern coreUI UI;
  
} // namespace evAPI


#endif // COREUI_HPP