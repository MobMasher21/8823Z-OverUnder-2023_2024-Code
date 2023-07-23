/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Jayden                                           */
/*    Created:      Sun Jul 23 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex; 

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Motor1.spin(reverse, 100, pct);
  Motor2.spin(reverse, 100, pct);
  Motor3.spin(reverse, 50, pct);
  Motor4.spin(reverse, 50, pct);
  
}
