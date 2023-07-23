#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor1 = motor(PORT17, ratio6_1, false);
motor Motor2 = motor(PORT19, ratio6_1, true);
motor Motor3 = motor(PORT20, ratio6_1, false);
motor Motor4 = motor(PORT21, ratio6_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}