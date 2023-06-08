/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robotStatus.h                                             */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      16 Jan 2023                                               */
/*    Description:  Defines and other bits if information used for            */
/*                  configuring the program for different robots.             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __ROBOTSTATUS_H__
#define __ROBOTSTATUS_H__

#include "vex.h"
#include "evNamespace.h"

namespace evAPI
{
  class robotStatus
  {
    private:
      robotAlliance currentAlliance;
      uint8_t controllerAmount;

      timer compTimer = timer();

      int compMode;

    public:

      robotStatus();

      competition Competition;

      void setAlliance(robotAlliance alliance);

      int getAlliance();

      uint8_t controllerCount();

      void driverStart();

      void autonStart();

      void disabledStart();

      double getCompetitionTime();
  };

  extern robotStatus robotInfo;

}

#endif // __ROBOTSTATUS_H__