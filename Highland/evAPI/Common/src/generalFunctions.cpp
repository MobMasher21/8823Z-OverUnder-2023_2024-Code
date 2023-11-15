#include <math.h>
#include "../include/constantObjects.hpp"
#include "../include/generalFunctions.hpp"

namespace evAPI
{
  robotMode getCompetitionStatus()
  {
    if(!Competition.isEnabled())
    {
      return robotMode::disabled;
    }

    else if(Competition.isDriverControl())
    {
      return robotMode::driverControl;
    }

    return robotMode::autonomousControl;
  }

  bool isConnectToField()
  {
    return Competition.isCompetitionSwitch() || Competition.isFieldControl();
  }
}