/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomMain.h                                                */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      ?? Feb 2023                                               */
/*    Description:  Creates the odometry class used in the evAPI.             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __ODOMMAIN_H__
#define __ODOMMAIN_H__

#include "../../odomSupport/include/odomCore.h"
#include "../../odomSupport/include/odomPoint.h"
#include "../../odomSupport/include/odomInertial.h"
#include "../../odomSupport/include/odomTimer.h"
#include "../../odomSupport/include/autonPathArrays.h"

namespace evAPI
{
  /**
   * @brief Main class for odometry.
  */
  class odomMain
  {
    private:

    public:
      odomCore Core;
      odomPoint Points;
      odomInertial Inertial;
      odomTimer Timer;
      autonPathArrays Paths;

  };

  extern odomMain Odometry;
}

#endif // __ODOMMAIN_H__