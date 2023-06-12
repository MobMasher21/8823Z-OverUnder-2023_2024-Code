#ifndef __ROBOTSYSTEM_H__
#define __ROBOTSYSTEM_H__

#include "..\..\..\include\vex.h"

namespace evAPI
{
  class robotSystem
  {
    public:

      /**
       * @brief Exits the current program.
      */
      void exitProgram();

      /**
       * @brief Dumps the current memory.
      */
      void dumpMemory();

      /**
       * @returns The time sense the brain first powered up.
      */
      uint64_t timeFromPowerUp();

      devices Devices;
  };

  extern robotSystem robotCore;
}

#endif // __ROBOTSYSTEM_H__