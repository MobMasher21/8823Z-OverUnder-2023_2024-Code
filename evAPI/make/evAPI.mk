# SRC made data for compiling the evAPI

SRC_C += $(wildcard evAPI/Common/src/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*.c)
SRC_C += $(wildcard evAPI/Common/src/*/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*/*.c)

SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*.c)
SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*/*.c)

SRC_C += $(wildcard evAPI/robotControl/DriverBaseControl/src/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/DriverBaseControl/src/*.c)
SRC_C += $(wildcard evAPI/robotControl/DriverBaseControl/src/*/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/DriverBaseControl/src/*/*.c)

SRC_C += $(wildcard evAPI/VisionTracker/src/*.cpp)
SRC_C += $(wildcard evAPI/VisionTracker/src/*.c)
SRC_C += $(wildcard evAPI/VisionTracker/src/*/*.cpp)
SRC_C += $(wildcard evAPI/VisionTracker/src/*/*.c)

SRC_C += $(wildcard evAPI/vexUI/AutoSelector/src/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/AutoSelector/src/*.c)
SRC_C += $(wildcard evAPI/vexUI/AutoSelector/src/*/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/AutoSelector/src/*/*.c)

SRC_C += $(wildcard evAPI/vexUI/BrainDataDisplay/src/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/BrainDataDisplay/src/*.c)
SRC_C += $(wildcard evAPI/vexUI/BrainDataDisplay/src/*/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/BrainDataDisplay/src/*/*.c)

# Include made data for compiling the evAPI

SRC_H += $(wildcard evAPI/*.h)
SRC_H += $(wildcard evAPI/Common/include/*.h)

SRC_H += $(wildcard evAPI/robotControl/Drivetrain/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/DriverBaseControl/include/*.h)

SRC_H += $(wildcard evAPI/VisionTracker/include/*.h)

SRC_H += $(wildcard evAPI/vexUI/AutoSelector/include/*.h)
SRC_H += $(wildcard evAPI/vexUI/BrainDataDisplay/include/*.h)