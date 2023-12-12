/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cameron Barclay, Jayden Liffick, Teo Carrion              */
/*    Created:      12/6/2023, 10:45:31 PM                                    */
/*    Description:  Main Code for 8823Z Team robot                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "../evAPI/evAPIFiles.h"
#include "global.h"

using namespace vex;
using namespace evAPI;


/*---------------------------------------------------------------------------------*/
/*                             Pre-Autonomous Functions                            */
/*---------------------------------------------------------------------------------*/
void pre_auton(void) {

  //* Setup for auto selection UI ============================================
  // Add all the buttons
  UI.addButton(0, Lime);
  UI.addButton(2, 0xff, 0x10, 0xa0);  //color is 0xff10a0
  UI.addButton(3, blue);
  UI.addButton(7, blue);

  // Set all the titles
  UI.setButtonTitle(0, "Push in simp");
  UI.setButtonTitle(2, "Skills");
  UI.setButtonTitle(3, "Push In");
  UI.setButtonTitle(7, "Load");

  // Set all the descriptions
  UI.setButtonDescription(0, "Ram backward, then go forward");
  UI.setButtonDescription(2, "Shoots all the match loads into the field");
  UI.setButtonDescription(3, "Auto for pushing in a nugget in on either side");
  UI.setButtonDescription(7, "Auto for a robot on the loading side of the field");

  // Select all the icons
  UI.setButtonIcon(0, UI.icons.number0);
  UI.setButtonIcon(2, UI.icons.skills);
  UI.setButtonIcon(3, UI.icons.leftArrow);
  UI.setButtonIcon(7, UI.icons.rightArrow);

  // Print all buttons and start thread
  UI.printButtons();
  UI.startThread();


  //* Setup for smart drive ==================================================
  // Setup motor settings
  driveBase.leftPortSetup(1, 2, 3);
  driveBase.rightPortSetup(4, 5, 6);
  driveBase.leftReverseSetup(true, true, true);
  driveBase.rightReverseSetup(false, false, false);
  
  // Setup inertial sensor settings
  driveBase.setupInertialSensor(7);

  // Set default speeds
  driveBase.setDriveSpeed(20);
  driveBase.setTurnSpeed(20);

  // Setup PID
  driveBase.setupDrivePID(1, 0, 0, 5, 5, 100);  // p, i, d, error, error time, timeout
  driveBase.setupTurnPID(1, 0, 0, 1, 5, 100);  // p, i, d, error, error time, timeout


  //* Setup for base driver contorl ==========================================
  driveContorl.setPrimaryStick(leftStick);
  driveContorl.setHandicaps(1, 1);  // main drive, turning

  //* Setup for controller functions when pressed/released ===================
  primaryContorller.WINGs_BUTTON.pressed(tglWings);
  primaryContorller.CATA_SPEED_INC.pressed(cataInc);
  primaryContorller.CATA_SPEED_DEC.pressed(cataDec);

}


/*---------------------------------------------------------------------------------*/
/*                                 Autonomous Task                                 */
/*---------------------------------------------------------------------------------*/
void autonomous(void) {

  switch (UI.getSelectedButton()) {
    case 0:
      break;
  }
}

/*---------------------------------------------------------------------------------*/
/*                                 User Control Task                               */
/*---------------------------------------------------------------------------------*/
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    //=========== All drivercontrol code goes between the lines ==============

    //* Control the base code -----------------------------
    driveContorl.driverLoop();

    //========================================================================

    vex::task::sleep(20); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::task::sleep(100);
  }
}
