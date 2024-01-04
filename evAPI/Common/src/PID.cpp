/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.cpp                                                   */
/*    Author:       Jackson Area Robotics                                     */
/*    Created:      ???                                                       */
/*    Description:  PID class.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <math.h>
#include "../../Common/include/PID.h"

namespace evAPI {
  /**
   * @brief Sets constants used for the PID function.
   * @param kp The KP factor.
   * @param ki The KI factor.
   * @param kd The KD factor.
   */
  void PID::setConstants(double kp, double ki, double kd) {
    KP = kp;
    KI = ki;
    KD = kd;
  }

  /**
   * @brief Set the values for when the PID will stop
   * 
   * @param settleErrorIN The error that is good enough
   * @param settleTimeIN The the cycle count that it needs to be settled
   * @param timeoutIN The timeout cycle count before it gives up
   */
  void PID::setStoppings(double settleErrorIN, double settleTimeIN, double timeoutIN) {
    settleError = settleErrorIN;
    settleTime = settleTimeIN;
    timeout = timeoutIN;
  }
  void PID::setStoppings(double settleErrorIN, double settleTimeIN) {
    settleError = settleErrorIN;
    settleTime = settleTimeIN;
  }

  /**
   * @brief Set the starti of the PID
   * 
   * @param startiIN
   */
  void PID::setStarti(int startiIN) {
    starti = startiIN;
  }

  /**
   * @brief Set the accumulated error
   * 
   * @param totalErrorIN 
   */
  void PID::setTotalError(long totalErrorIN) {
    accumulatedError = totalErrorIN;
  }

  /**
   * @brief Returns if the PID is done
   * 
   * @return true The PID is settled
   * @return false The PID is still running
   */
  bool PID::isSettled() {
    //if (the PID has been running longer than the max time) or (the error has been acceptable for long enough)
    if((cyclesSpentRunning > timeout && timeout != 0) || (cyclesSpentSettled > settleTime)) {
      return(true);
    } else {
      return(false);
    }
  }

  /**
   * @brief Resets the timeout for the PID
   * 
   */
  void PID::resetTimeout() {
    cyclesSpentRunning = 0;
  }

  /**
   * @brief Does all the PID math
   * 
   * @param error The new error for the PID function
   * @return double Output powers of the PID
   */
  double PID::compute(double error){
    double output;

    //adds the error to the accumulator if it is large enough
    if(fabs(error) < starti) {
      accumulatedError+=error;
    }

    //resets the accumulated error if the robot passes the wanted location
    if((error>0 && previousError<0)||(error<0 && previousError>0)) { 
      accumulatedError = 0; 
    }

    output = KP * error + KI * accumulatedError + KD * (error-previousError);  //the core PID math
    previousError=error;

    if(fabs(error) < settleError) {  //if the error is in the ok range
      cyclesSpentSettled++;  //add 1 to the cycles that it has been
    } else {  //if it's not in the ok range
      cyclesSpentSettled = 0;  //reset the counter
    }

    cyclesSpentRunning++;
    return output;
  }
}