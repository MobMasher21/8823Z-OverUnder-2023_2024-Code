#include "../include/vexUI.h"

namespace evAPI
{
  vexUI UI = vexUI();

  int controllerThread()
  {
    //Stores if the controllers were previously installed
    bool prevPrimaryControllerInstalled = false;
    bool prevSecondaryControllerInstalled = false;

    bool primaryControllerInstalled;
    bool secondaryControllerInstalled;
    
    //*Main thread loop
    while(true)
    {
      primaryControllerInstalled = primaryController.installed();
      secondaryControllerInstalled = secondaryController.installed();

      //*Update the controller screens if they were just connected
      if(primaryControllerInstalled && !prevPrimaryControllerInstalled)
      {
        UI.primaryControllerUI.updateScreen();
      }

      if(secondaryControllerInstalled && !prevSecondaryControllerInstalled)
      {
        UI.secondaryControllerUI.updateScreen();
      }

      //*Update the screen data on the controllers if they are currently connected
      if(primaryControllerInstalled)
      {
        UI.primaryControllerUI.updateScreenData();
      }

      if(secondaryControllerInstalled)
      {
        UI.secondaryControllerUI.updateScreenData();
      }

      prevPrimaryControllerInstalled = primaryControllerInstalled;
      prevSecondaryControllerInstalled = secondaryControllerInstalled;

      this_thread::sleep_for(10);
    }

    return 0;
  }

  vexUI::vexUI(/* args */)
  {}
  
  vexUI::~vexUI()
  {
    delete controllerUIThread;
  }

  evError vexUI::startThreads()
  {
    //Exit if the controller thread already exists
    if(controllerUIThread != nullptr)
    {
      return evError::Data_Already_Exists;
    }

    controllerUIThread = new thread(controllerThread);

    UI.autoSelectorUI.startThread();

    return evError::No_Error;
  }

} // namespace evAPI