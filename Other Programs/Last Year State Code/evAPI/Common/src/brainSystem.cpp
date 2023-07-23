#include "..\include\robotSystem.h"

namespace evAPI
{
  robotSystem robotCore;
  
  void robotSystem::exitProgram()
  { vexSystemExitRequest(); }
  
  void robotSystem::dumpMemory()
  { vexSystemMemoryDump(); }
  
  uint64_t robotSystem::timeFromPowerUp()
  { return vexSystemPowerupTimeGet(); }
}