// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          Controller    
// ---- END VEXCODE CONFIGURED DEVICES ----

/** code ideas
* write automatic controller debouncing code as a class
*/

#include "vex.h"
#include "../include/evAPI.h"

using namespace vex;
using namespace evAPI;

competition Competition;

Drive codeBase;

int leftSpeed;
int rightSpeed;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  codeBase.leftPortSetup(7, 8);
  codeBase.rightPortSetup(9, 10);
  codeBase.leftReverseSetup(true, true);
  codeBase.rightReverseSetup(false, false);
  codeBase.leftEncoderSetup(1, 2.75, false);
  codeBase.rightEncoderSetup(2, 2.75, false);
  codeBase.backEncoderSetup(6, 2.75, false);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  while(1) {
    //=================================================================================

    leftSpeed = (Controller1.Axis3.position(pct) + Controller1.Axis1.position(pct));
    rightSpeed = (Controller1.Axis3.position(pct) - Controller1.Axis1.position(pct));
    codeBase.spinBase(leftSpeed, rightSpeed);

    //=================================================================================
    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  //! Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  while (true) {
    this_thread::sleep_for(50);
  }
}