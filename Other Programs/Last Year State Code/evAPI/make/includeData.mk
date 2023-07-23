# Include made data for compiling the evAPI

SRC_H += $(wildcard evAPI/*.h)
SRC_H += $(wildcard evAPI/Common/include/*.h)
SRC_H += $(wildcard evAPI/customVexDevices/Control/include/*.h)
SRC_H += $(wildcard evAPI/customVexDevices/Sensors/include*/.h)
SRC_H += $(wildcard evAPI/odomSupport/include/*.h)
SRC_H += $(wildcard evAPI/robotControl/include/*.h)
SRC_H += $(wildcard evAPI/vexUI/include/*.h)