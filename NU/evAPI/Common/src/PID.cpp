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

namespace evAPI
{
  PID::PID(double error, double kp, double ki, double kd, double starti) :
    //error(error),
    KP(kp),
    KI(ki),
    KD(kd),
    starti(starti)
  {};

  PID::PID(double error, double kp, double ki, double kd, double starti, double settle_error, double settle_time, double timeout) :
    //error(error),
    KP(kp),
    KI(ki),
    KD(kd),
    starti(starti),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout)
  {};

  double PID::compute(double error){
    if (fabs(error) < starti){
      accumulated_error+=error;
    }
    if ((error>0 && previous_error<0)||(error<0 && previous_error>0)){ 
      accumulated_error = 0; 
    }
    output = KP*error + KI*accumulated_error + KD*(error-previous_error);

    previous_error=error;

    if(fabs(error)<settle_error){
      time_spent_settled+=10;
    } else {
      time_spent_settled = 0;
    }

    time_spent_running+=10;

    return output;
  }

  bool PID::is_settled()
  {
    if((time_spent_running > timeout && timeout != 0) || (time_spent_settled > settle_time))
    { return(true); }
    
    return(false);
  }

  void PID::setConstants(double kp, double ki, double kd)
  {
    KP = kp;
    KI = ki;
    KD = kd;
  }
}