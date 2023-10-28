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
  controller primaryController = controller(primary);
  controller secondaryController = controller(partner);
}