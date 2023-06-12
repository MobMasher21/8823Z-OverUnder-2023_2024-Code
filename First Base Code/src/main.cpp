// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// trigger              digital_out   B               
// stringLauncher       digital_out   A               
// rollerDistance       distance      17              
// ---- END VEXCODE CONFIGURED DEVICES ----

// --- Start EVAPI CONFIGURED DEVICES -------
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// primaryController    Controller
// secondaryController  Controller             
// ---- END EVAPI CONFIGURED DEVICES ------

/** code ideas
* write automatic controller debouncing code as a class
*/

#include "vex.h"

using namespace vex;

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

  // Run the pre-autonomous function.
  pre_auton();

  while (true) {
    this_thread::sleep_for(50);
  }
}