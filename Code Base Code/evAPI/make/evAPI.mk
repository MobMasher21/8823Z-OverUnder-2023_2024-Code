# SRC made data for compiling the evAPI

SRC_C += $(wildcard evAPI/*.cpp)
SRC_C += $(wildcard evAPI/*.c)
SRC_C += $(wildcard evAPI/*/*.cpp)
SRC_C += $(wildcard evAPI/*/*.c)

SRC_C += $(wildcard evAPI/robotControl/src/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/src/*.c)
SRC_C += $(wildcard evAPI/robotControl/src/*/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/src/*/*.c)

SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*.c)
SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/Drivetrain/src/*/*.c)

# Include made data for compiling the evAPI

SRC_H += $(wildcard evAPI/*.h)
SRC_H += $(wildcard evAPI/robotControl/include/*.h)
SRC_H += $(wildcard evAPI/Common/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/Drivetrain/include/*.h)