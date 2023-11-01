/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       coreUI.hpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 20, 2023                                              */
/*    Description:  Class that consolidates and controls all the UIs from     */
/*                  the evAPI.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/coreUI.hpp"
#include "../evAPI/Common/include/constantObjects.h"
#include "../evAPI/Common/include/generalFunctions.h"

namespace evAPI
{
  coreUI UI;
  
  coreUI::coreUI()
  {}
  
  coreUI::~coreUI()
  {}

  int brainUIUpdateFunc()
  {
    //Initalize the controller UIs
    UI.primaryControllerUI.updateScreen();
    UI.secondaryControllerUI.updateScreen();
  
    while(true)
    {
      //Update the UI mode if manual control is off
      if(!UI.getManualControlStatus())
      {
        switch(getCompetitionStatus())
        {
          case robotMode::driverControl:
            UI.setUIMode(UIStates::Match_UI);
            break;

          case robotMode::autonomousControl:
            UI.setUIMode(UIStates::Match_UI);
            break;

          case robotMode::disabled:
            UI.setUIMode(UIStates::Preauto_UI);
            break;
        }
      }

      //Show the correct UI on the brain
      switch(UI.getUIMode())
      {
        case UIStates::Preauto_UI:
          //Show the correct brain UI
          UI.autoSelector.showPreautoUI(true);
          //UI.matchDisplays.showMatchUI(false);
          break;

        case UIStates::Match_UI:
          //Show the correct brain UI
          UI.autoSelector.showPreautoUI(false);
          //UI.matchDisplays.showMatchUI(true);

          //Update the match displays
          //matchDisplays.updateDisplays();
          break;

        default: //UIStates::Disabled
          //Hide both UIs
          UI.autoSelector.showPreautoUI(false);
          //UI.matchDisplays.showMatchUI(false);
          break;
      }

      //Update controller UIs
      UI.primaryControllerUI.updateScreenData();
      //UI.secondaryControllerUI.updateScreenData();
      
      this_thread::sleep_for(10);
    }
    
    return 0;
  }

  evError coreUI::startUI()
  {
    //Return if the auto selector UI hasn't been created
    /* if(autoSelector.getButtonCount() == 0)
    {
      return evError::Object_Property_Not_Specified;
    } */

    //Exit if the thread has already been created
    if(brainUIThread != nullptr)
    {
      return evError::Device_Already_Exists;
    }

    //Start the thread
    brainUIThread = new vex::thread(brainUIUpdateFunc);

    return evError::No_Error;
  }

  void coreUI::setManualControl(bool status)
  {
    brainUIManualControl = status;
  }

  void coreUI::setUIMode(UIStates mode)
  {
    brainUIMode = mode;
  }

  UIStates coreUI::getUIMode()
  {
    return brainUIMode;
  }

  bool coreUI::getManualControlStatus()
  {
    return brainUIManualControl;
  }


} // namespace evAPI