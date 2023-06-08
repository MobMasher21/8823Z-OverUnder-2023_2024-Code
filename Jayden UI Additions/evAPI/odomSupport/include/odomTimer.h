/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomTimer.h                                               */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      01 Jan 2023                                               */
/*    Description:  The timer subclass used in evAPI's odometry.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __ODOMTIMER_H__
#define __ODOMTIMER_H__

#include "vex.h"

namespace evAPI
{
  #define MAX_MOVING_TIME 7000 //Maximum time it takes to complete a movement in ms
  
  class odomTimer
  {
    private:
  
      timer odomTime = timer();
  
      int maxTime = MAX_MOVING_TIME;
  
    public:
  
      /**
       * @brief Resets the timer for the odometry.
      */
      void resetTimer();
  
      /**
       * @returns The current time in ms of the timer.
      */
      uint32_t getCurrentTime();
  
      /**
       * @returns True if the timer has passed the maximum time value.
      */
      bool isOverTime();
  
      /**
       * @brief Sets the time value the timer needs to reach in order to trigger isOverTime();
       * @param time The time value in ms.
      */
      void setMaxTime(int time);
  };
}

#endif // __ODOMTIMER_H__