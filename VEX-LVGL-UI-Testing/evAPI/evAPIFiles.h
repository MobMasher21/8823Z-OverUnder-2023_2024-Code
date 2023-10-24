#ifndef EVAPIFILES_H
#define EVAPIFILES_H

//Format Year/Month/Day
#define EVAPI_VERSION 20231014

#include "evAPISettings.h"

#include "../evAPI/Common/include/colors.h"
#include "../evAPI/Common/include/generalFunctions.h"
#include "../evAPI/Common/include/evNamespace.h"
//#include "../evAPI/Common/include/PID.h"
#include "../evAPI/Common/include/evColor.h"
#include "../evAPI/Common/include/constantObjects.h"
#include "../evAPI/Common/include/evPatch.h"
#include "../evAPI/Common/include/dualPneumatics.h"
#include "../evAPI/Common/include/vexPrivateRebuild.h"
#include "../evAPI/Common/include/evErrorTypes.hpp"

#ifdef __has_include
  #if FORCE_UI_VERSION == 0
    #if __has_include("lvgl.h")
      #include "../evAPI/LVGL/lvglUI/coreUI/include/coreUI.hpp"
      #include "../evAPI/LVGL/LVGLInit/include/vexLVGL.hpp"
    #else
      #include "../evAPI/vexUI/include/UserInterface.h"
    #endif
  #elif FORCE_UI_VERSION == 1
    #if __has_include("../evAPI/vexUI/include/UserInterface.h")
      #include "../evAPI/vexUI/include/UserInterface.h"
    #else
      #error Standard evAPI UI can't be found! Please make sure all of the evAPI is installed!
    #endif
  #else
    #if __has_include("lvgl.h")
      #include "../evAPI/LVGL/lvglUI/coreUI/include/coreUI.hpp"
      #include "../evAPI/LVGL/LVGLInit/include/vexLVGL.hpp"
    #else
      #error LVGL is not present in project!
    #endif
  #endif
#else
  #if FORCE_UI_VERSION == 0
    #include "../evAPI/LVGL/lvglUI/coreUI/include/coreUI.hpp"
    #include "../evAPI/LVGL/LVGLInit/include/vexLVGL.hpp"
  #else
    #include "../evAPI/vexUI/include/UserInterface.h"
  #endif
#endif

//#include "../evAPI/robotControl/Drivetrain/include/Drive.h"
//#include "../evAPI/robotControl/Flywheel/include/Flywheel.h"
//#include "../evAPI/robotControl/Intake/include/Intake.h"

#endif // EVAPIFILES_H
