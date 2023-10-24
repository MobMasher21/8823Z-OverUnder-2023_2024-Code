#!SRC made data for compiling the evAPI
#*Common data
SRC_C += $(wildcard evAPI/Common/src/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*.c)
SRC_C += $(wildcard evAPI/Common/src/*/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*/*.c)

#?LVGL
#*LVGL Setup
SRC_C += $(wildcard evAPI/LVGL/LVGLInit/src/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/LVGLInit/src/*.c)
SRC_C += $(wildcard evAPI/LVGL/LVGLInit/src/*/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/LVGLInit/src/*/*.c)

#*LVGL UI
SRC_C += $(wildcard evAPI/LVGL/lvglUI/coreUI/src/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/coreUI/src/*.c)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/coreUI/src/*/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/coreUI/src/*/*.c)

SRC_C += $(wildcard evAPI/LVGL/lvglUI/preautoUI/src/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/preautoUI/src/*.c)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/preautoUI/src/*/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/preautoUI/src/*/*.c)

SRC_C += $(wildcard evAPI/LVGL/lvglUI/matchUI/src/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/matchUI/src/*.c)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/matchUI/src/*/*.cpp)
SRC_C += $(wildcard evAPI/LVGL/lvglUI/matchUI/src/*/*.c)

SRC_C += $(wildcard evAPI/LVGL/lvglUI/Assets/src/*.c)

#SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*.cpp)
#SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*.c)
#SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*/*.cpp)
#SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*/*.c)
#
#SRC_C += $(wildcard evAPI/robotControl/Flywheel/src/*.cpp)
#SRC_C += $(wildcard evAPI/robotControl/Flywheel/src/*.c)
#SRC_C += $(wildcard evAPI/robotControl/Flywheel/src/*/*.cpp)
#SRC_C += $(wildcard evAPI/robotControl/Flywheel/src/*/*.c)
#
#SRC_C += $(wildcard evAPI/robotControl/Intake/src/*.cpp)
#SRC_C += $(wildcard evAPI/robotControl/Intake/src/*.c)
#SRC_C += $(wildcard evAPI/robotControl/Intake/src/*/*.cpp)
#SRC_C += $(wildcard evAPI/robotControl/Intake/src/*/*.c)
#
#SRC_C += $(wildcard evAPI/vexUI/src/*.cpp)
#SRC_C += $(wildcard evAPI/vexUI/src/*.c)
#SRC_C += $(wildcard evAPI/vexUI/src/*/*.cpp)
#SRC_C += $(wildcard evAPI/vexUI/src/*/*.c)