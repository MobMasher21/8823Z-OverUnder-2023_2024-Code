#include <math.h>
#include "../include/evAPIBasicConfig.h"
#include "../include/generalFunctions.h"

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