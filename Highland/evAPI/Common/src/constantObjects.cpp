/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       constantObjects.cpp                                       */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      15 Aug 2023                                               */
/*    Description:  Constant objects used by the evAPI.                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/constantObjects.h"

namespace evAPI
{
  vex::controller primaryController = vex::controller(vex::primary);
  vex::controller secondaryController = vex::controller(vex::partner);
  vex::competition Competition = vex::competition();
}