/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Jayden                                           */
/*    Created:      Sun Jul 23 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         17              
// Motor2               motor         19              
// Motor3               motor         20              
// Motor4               motor         21              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Motor1.spin(fwd, 100, pct);
  Motor2.spin(fwd, 100, pct);
  Motor3.spin(fwd, 100, pct);
  Motor4.spin(fwd, 100, pct);
}
