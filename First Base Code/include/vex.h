/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

const int32_t smartPortLookupTable[] = 
{ 0     , PORT1 , PORT2 , PORT3 , PORT4 , PORT5 , PORT6 , PORT7 , 
  PORT8 , PORT9 , PORT10, PORT11, PORT12, PORT13, PORT14, PORT15, 
  PORT16, PORT17, PORT18, PORT19, PORT20, PORT21                };