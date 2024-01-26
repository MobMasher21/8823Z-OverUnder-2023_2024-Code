#include "../include/vexUI.h"

namespace evAPI
{
  //vexUI UI = vexUI();

  int controllerThread(void *UIClass)
  {
    //Get the thread input and store it as a copy of the UI
    vexUI *UI = (vexUI*)UIClass;

    //Stores if the controllers were previously installed
    bool prevPrimaryControllerInstalled = false;
    bool prevSecondaryControllerInstalled = false;

    bool primaryControllerInstalled = false;
    bool secondaryControllerInstalled = false;
    
    //*Main thread loop
    while(true)
    {
      //Get current conenction status of controllers
      primaryControllerInstalled = primaryController.installed();
      secondaryControllerInstalled = secondaryController.installed();

      //*Primary Controller
      if(primaryControllerInstalled && !prevPrimaryControllerInstalled)
      {
        UI->primaryControllerUI.updateScreen();
      }

      else if(primaryControllerInstalled)
      {
        UI->primaryControllerUI.updateScreenData();
      }

      //*Secondary Controller
      if(secondaryControllerInstalled && !prevSecondaryControllerInstalled)
      {
        UI->secondaryControllerUI.updateScreen();
      }

      else if(secondaryControllerInstalled)
      {
        UI->secondaryControllerUI.updateScreenData();
      }

      //Store current connection status of controllers
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

    controllerUIThread = new thread(controllerThread, this);

    autoSelectorUI.startThread();

    return evError::No_Error;
  }

} // namespace evAPI