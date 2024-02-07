/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.h                                                     */
/*    Author:       Jackson Area Robotics                                     */
/*    Description:  PID class.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef PID_H
#define PID_H

namespace evAPI {
  class PID {
    public:
      /**
       * @brief Sets constants used for the PID function.
       * @param kp The KP factor.
       * @param ki The KI factor.
       * @param kd The KD factor.
      */
      void setConstants(double kp, double ki, double kd);
      /**
       * @brief Set the values for when the PID will stop
       * 
       * @param settleErrorIN The error that is good enough
       * @param settleTimeIN The the cycle count that it needs to be settled
       * @param timeoutIN The timeout cycle count before it gives up
       */
      void setStoppings(double settleErrorIN, double settleTimeIN, double timeoutIN);
      void setStoppings(double settleErrorIN, double settleTimeIN);
      
      /**
       * @brief Set the starti of the PID
       * 
       * @param startiIN
       */
      void setStarti(int startiIN);
  
      /**
       * @brief Set the accumulated error
       * 
       * @param totalErrorIN 
       */
      void setTotalError(long totalErrorIN);
  
      /**
       * @brief Returns if the PID is done
       * 
       * @return true The PID is settled
       * @return false The PID is still running
       */
      bool isSettled();

      /**
       * @brief Resets the timeout for the PID
       * 
       */
      void resetTimeout();
  
      /**
       * @brief Does all the PID math
       * 
       * @param error The new error for the PID function
       * @return double Output powers of the PID
       */
      double compute(double error);
    
    private:
      double KP = 0;
      double KI = 0;
      double KD = 0;
      double starti = 0;  // Error must be above this for it to be added to the accumulator
      double settleError = 0;  // Error to be considered done moving
      double settleTime = 0;  // Cycles the robot must be settled to be done
      double timeout = 0;  // Max cycles the PID will run for
      long accumulatedError = 0;
      double previousError = 0;
      double cyclesSpentSettled = 0;
      double cyclesSpentRunning = 0;
  };
}

#endif // PID_H