#include "../include/Drive.h"

namespace evAPI
{
  bool Drive::isMoving()
  {
    return leftMotor1->isSpinning() || rightMotor1->isSpinning();
  }

} // namespace evAPI