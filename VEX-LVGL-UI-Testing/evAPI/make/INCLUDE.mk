#!Include made data for compiling the evAPI
SRC_H += $(wildcard evAPI/*.h)
SRC_H += $(wildcard evAPI/Common/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Drivetrain/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Flywheel/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Intake/include/*.h)

#?LVGL
#*LVGL Setup
SRC_H += $(wildcard evAPI/LVGL/LVGLInit/include/*.h)
SRC_H += $(wildcard evAPI/LVGL/LVGLInit/include/*.hpp)

#*LVGL UI
SRC_H += $(wildcard evAPI/LVGL/lvglUI/coreUI/include/*.h)
SRC_H += $(wildcard evAPI/LVGL/lvglUI/coreUI/include/*.hpp)

SRC_H += $(wildcard evAPI/LVGL/lvglUI/preautoUI/include/*.h)
SRC_H += $(wildcard evAPI/LVGL/lvglUI/preautoUI/include/*.hpp)

SRC_H += $(wildcard evAPI/LVGL/lvglUI/matchUI/include/*.h)
SRC_H += $(wildcard evAPI/LVGL/lvglUI/matchUI/include/*.hpp)

SRC_H += $(wildcard evAPI/LVGL/lvglUI/controllerUI/include/*.h)
SRC_H += $(wildcard evAPI/LVGL/lvglUI/controllerUI/include/*.hpp)

SRC_H += $(wildcard evAPI/LVGL/lvglUI/Common/include/*.h)
SRC_H += $(wildcard evAPI/LVGL/lvglUI/Common/include/*.hpp)

SRC_H += $(wildcard evAPI/LVGL/lvglUI/Assets/include/*.h)

#SRC_H += $(wildcard evAPI/vexUI/include/*.h)