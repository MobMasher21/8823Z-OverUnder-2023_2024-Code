# SRC made data for compiling the evAPI

SRC_C += $(wildcard evAPI/Common/src/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*.c)
SRC_C += $(wildcard evAPI/Common/src/*/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*/*.c)

SRC_C += $(wildcard evAPI/vexUI/src/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/src/*.c)
SRC_C += $(wildcard evAPI/vexUI/src/*/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/src/*/*.c)

# Include made data for compiling the evAPI

SRC_H += $(wildcard evAPI/*.h)
SRC_H += $(wildcard evAPI/Common/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Drivetrain/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Flywheel/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Intake/include/*.h)
SRC_H += $(wildcard evAPI/vexUI/include/*.h)