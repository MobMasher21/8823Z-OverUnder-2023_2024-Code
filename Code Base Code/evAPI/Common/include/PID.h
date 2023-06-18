/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.h                                                     */
/*    Author:       Jackson Area Robotics                                     */
/*    Created:      ???                                                       */
/*    Description:  PID class.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef PID_H
#define PID_H

#include <math.h>

namespace evAPI
{
  class PID
  {
    public:

      /**
       * @brief Creates a PID object.
       * 
       * @param error Starting error
       * @param kp KP Value
       * @param ki KI Value
       * @param kd KD Value
       * @param settleErrorIn
       * @param settleCyclesIn
       * @param timeoutIn
      */
      PID(double kp, double ki, double kd, double settleErrorIn, int settleCyclesIn, int timeoutIn);

      PID(double kp, double ki, double kd);

      double compute(double error);

      bool is_settled();

      /**
       * @brief Sets constants used for the PID function.
       * 
       * @param kp The KP factor.
       * @param ki The KI factor.
       * @param kd The KD factor.
      */
      void setConstants(double kp, double ki, double kd);

      /**
       * @brief Set the settle error and time as well as timeout
       * 
       * @param settleErrorIn
       * @param settleCyclesIn
       * @param timeoutIn
       */
      void setSettle(int settleErrorIn, int settleCyclesIn, int timeoutIn);

      /**
       * @brief Set the total error
       * 
       * @param iIn what the total error is
       */
      void setTotalError(long iIn);

    private:
      double KP = 0;
      double KI = 0;
      double KD = 0;
      double settleError = 0;
      int settleCycles = 0;
      int timeout = 0;
      long totalError = 0;
      double previousError = 0;
      double output = 0;
      int cyclesSpentSettled = 0;
      int cyclesSpentRunning = 0;
   
  };
}

#endif // PID_H