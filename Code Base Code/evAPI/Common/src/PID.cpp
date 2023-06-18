/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.cpp                                                   */
/*    Author:       Jackson Area Robotics                                     */
/*    Created:      ???                                                       */
/*    Description:  PID class.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../../Common/include/PID.h"

namespace evAPI
{
  PID::PID(double kp, double ki, double kd, double settleErrorIn, int settleCyclesIn, int timeoutIn) {
    KP = kp;
    KI = ki;
    KD = kd;
    settleError = settleErrorIn;
    settleCycles = settleCyclesIn;
    timeout = timeoutIn;
  }

  PID::PID(double kp, double ki, double kd) {
    KP = kp;
    KI = ki;
    KD = kd;
  }

  double PID::compute(double error){
    totalError+=error;

    output = KP * error + KI * totalError + KD * (error-previousError);

    previousError=error;

    if(fabs(error) < settleError) {
      cyclesSpentSettled += 1;
    } else {
      cyclesSpentSettled = 0;
    }

    cyclesSpentRunning += 1;

    return output;
  }

  bool PID::is_settled()
  {
    if((cyclesSpentRunning > timeout && timeout != 0) || (cyclesSpentSettled > settleCycles))
    { return(true); }
    
    return(false);
  }

  void PID::setConstants(double kp, double ki, double kd)
  {
    KP = kp;
    KI = ki;
    KD = kd;
  }

  void PID::setSettle(int settleErrorIn, int settleCyclesIn, int timeoutIn) {
    settleError = settleErrorIn;
    settleCycles = settleCyclesIn;
    timeout = timeoutIn;
  }

  void PID::setTotalError(long iIn) {
    totalError = iIn;
  }
}