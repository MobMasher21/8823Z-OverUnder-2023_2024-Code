/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Controllers.cpp                                           */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      ?? Feb 2023                                               */
/*    Description:  Creates the controller objects used in the evAPI.         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/Controllers.h"

namespace evAPI
{
  vex::controller primaryController = vex::controller(vex::primary);
  vex::controller secondaryController = vex::controller(vex::partner);
}