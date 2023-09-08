/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomTimer.cpp                                             */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      01 Jan 2023                                               */
/*    Description:  The timer subclass used in evAPI's odometry.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../../odomSupport/include/odomTimer.h"

namespace evAPI
{
  void odomTimer::resetTimer()
  { odomTime.reset(); }
  
  uint32_t odomTimer::getCurrentTime()
  { return odomTime.time(); }
  
  bool odomTimer::isOverTime()
  {
    if(getCurrentTime() > maxTime)
    { return true; }
  
    return false;
  }
  
  void odomTimer::setMaxTime(int time)
  { maxTime = time; }
}