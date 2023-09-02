/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       constantObjects.h                                         */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      15 Aug 2023                                               */
/*    Description:  Constant objects used by the evAPI.                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __CONSTANTOBJECTS_H__
#define __CONSTANTOBJECTS_H__

#include "evNamespace.h"

namespace evAPI
{
  extern vex::controller primaryController;
  extern vex::controller secondaryController;
  extern vex::competition Competition;
  extern evAPI::allianceType robotAlliance;
}

#endif // __CONSTANTOBJECTS_H__