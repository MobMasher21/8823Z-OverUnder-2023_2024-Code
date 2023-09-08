# SRC made data for compiling the evAPI

SRC_C += $(wildcard evAPI/*.cpp)
SRC_C += $(wildcard evAPI/*.c)
SRC_C += $(wildcard evAPI/*/*.cpp)
SRC_C += $(wildcard evAPI/*/*.c)

SRC_C += $(wildcard evAPI/Common/src/*.cpp)
SRC_C += $(wildcard evAPI/Common/src/*.c)
SRC_C += $(wildcard evAPI/Common/src*/*.cpp)
SRC_C += $(wildcard evAPI/Common/src*/*.c)

SRC_C += $(wildcard evAPI/customVexDevices/Control/src/*.cpp)
SRC_C += $(wildcard evAPI/customVexDevices/Control/src/*.c)
SRC_C += $(wildcard evAPI/customVexDevices/Control/src*/*.cpp)
SRC_C += $(wildcard evAPI/customVexDevices/Control/src*/*.c)

SRC_C += $(wildcard evAPI/customVexDevices/Sensors/src*.cpp)
SRC_C += $(wildcard evAPI/customVexDevices/Sensors/src*.c)
SRC_C += $(wildcard evAPI/customVexDevices/Sensors/src*/*.cpp)
SRC_C += $(wildcard evAPI/customVexDevices/Sensors/src*/*.c)

SRC_C += $(wildcard evAPI/odomSupport/src/*.cpp)
SRC_C += $(wildcard evAPI/odomSupport/src/*.c)
SRC_C += $(wildcard evAPI/odomSupport/src/*/*.cpp)
SRC_C += $(wildcard evAPI/odomSupport/src/*/*.c)

SRC_C += $(wildcard evAPI/robotControl/src/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/src/*.c)
SRC_C += $(wildcard evAPI/robotControl/src/*/*.cpp)
SRC_C += $(wildcard evAPI/robotControl/src/*/*.c)

SRC_C += $(wildcard evAPI/vexUI/src/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/src/*.c)
SRC_C += $(wildcard evAPI/vexUI/src/*/*.cpp)
SRC_C += $(wildcard evAPI/vexUI/src/*/*.c)