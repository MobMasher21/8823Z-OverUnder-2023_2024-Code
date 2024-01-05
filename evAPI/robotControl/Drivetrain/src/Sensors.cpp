#include "../include/Drive.h"

namespace evAPI
{
  bool Drive::isMoving()
  {
    return leftMotor1->isSpinning() || rightMotor1->isSpinning();
  }

  bool Drive::getBaseSpeed(turnType side)
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

    //TODO: Add code to return the wheel speed, not the motor speed

    return wheelVelocity;
  }

} // namespace evAPI