#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "vex.h"
#include "Rollers.h"
#include "evAPI.h"

class Robot {
  public:
    const gearSetting red = ratio36_1;
    const gearSetting green = ratio18_1;
    const gearSetting blue = ratio6_1;
    evAPI::Drive drive;
    Rollers rollers;
    evAPI::Flywheel flywheel;

  private:

};

extern Robot robot;

#endif // __ROBOT_H__