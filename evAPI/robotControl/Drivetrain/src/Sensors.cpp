#include "../include/Drive.h"

namespace evAPI
{
  bool Drive::isMoving()
  {
    return leftMotor1->isSpinning() || rightMotor1->isSpinning();
  }

  double Drive::getBaseSpeed(turnType side)
  {
    double wheelVelocity;

    if(side == turnType::left)
    {
      wheelVelocity = leftMotor1->velocity(pct);
    }

    else
    {
      wheelVelocity = rightMotor1->velocity(pct);
    }

    //TODO: Fix this crap
    //Convert the motor velocity to the wheel velocity
    //wheelVelocity *= (gearInput / gearOutput)/*  * (2 * M_PI * wheelSize) */;

    return wheelVelocity;
  }

} // namespace evAPI