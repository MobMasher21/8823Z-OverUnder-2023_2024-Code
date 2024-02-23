#ifndef __GENERALFUNCTIONS_H__
#define __GENERALFUNCTIONS_H__

#include "evNamespace.h"
#include "evErrorTypes.h"
#include <string>
#include <type_traits>

//https://www.arduino.cc/reference/en/

namespace evAPI
{
  #define DEG_TO_RAD 0.017453292519943295769236907684886
  #define RAD_TO_DEG 57.295779513082320876798154814105

  /**
   * @brief Constrains a number between two other numbers.
   * @tparam T The type of data the function will take in and return.
   * @param amt The number that is being constrained.
   * @param low The lowest value the input can be.
   * @param high The highest value the input can be.
   * @returns "amt" if it is between the two constraining values. "low" if it is less than "low".
   * "high" if it is greater than "high".
  */
  template <typename T> T constrain(T amt, T low, T high)
  {
    if(amt < low)
    { return low; }

    else if(amt > high)
    { return high; }

    return amt;
  }

  /**
   * @brief Converts an input from degrees to radians.
   * @tparam T The type of data the function will take in and return.
   * @param deg The angle in degrees.
   * @returns The angle in radians.
  */
  template <typename T> inline T toRadians(T deg)
  { return deg * DEG_TO_RAD; }

  /**
   * @brief Converts an input from radians to degrees.
   * @tparam T The type of data the function will take in and return.
   * @param rad The angle in radians.
   * @returns The angle in degrees.
  */
  template <typename T> inline T toDegrees(T rad)
  { return rad * RAD_TO_DEG; }

  /**
   * @brief Calculates the square of a number: the number multiplied by itself.
   * @tparam T The type of data the function will take in and return.
   * @param x The number.
   * @returns The square of the number.
   * @author Arduino
   * @link https://reference.arduino.cc/reference/en/language/functions/math/sq/
  */
  template <typename T> inline T sq(T x)
  { return x * x; }

  /**
   * @brief Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow,
   *  a value of fromHigh to toHigh, values in-between to values in-between, etc.
   * @tparam T The type of data the function will take in and return.
   * @param value The number to map.
   * @param fromLow The lower bound of the value’s current range.
   * @param fromHigh The upper bound of the value’s current range.
   * @param toLow The lower bound of the value’s target range.
   * @param toHigh The upper bound of the value’s target range.
   * @author Arduino
   * @link https://reference.arduino.cc/reference/en/language/functions/math/map/
  */
  template <typename T> inline T map(T value, T fromLow, T fromHigh, T toLow, T toHigh)
  { return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow; }

  /**
   * @brief Gets the current status of the competition.
   * @returns The status of the competition as evAPI::robotMode.
  */
  robotMode getCompetitionStatus();

  /**
   * @returns True if te robot is connected to competition controller.
  */
  bool isConnectToField();

  /**
   * @brief Returns a reference to a controller depending on the input type.
   * @param type The type of controller to get.
   * @returns A reference to a controller.
  */
  controller& typeToController(controllerType type);

  /**
   * @brief Returns the state of a button on a controller.
   * @param type The controller the desired button is on.
   * @param targetButton The button to check.
   * @returns The status of the button.
  */
  buttonStatus getButtonStatus(controllerType type, controllerButtons targetButton);

  /**
   * @brief Converts an evError into a std::string.
   * @param error The error to convert.
   * @returns a std::string containing the error. 
  */
  std::string evErrorToString(evError error);

  /**
   * @brief Check if the device in a port is the correct one.
   * @param port The port to check.
   * @param type The device type.
   * @returns An evErrorBool. Its "data" parameter will be true if the correct device type is detected.
   *          Incorrect_Device_In_Port if the device type doesn't match what is in the port.
   *          No_Device_In_Port if there isn't anything in the port.
   *          Invalid_Device_In_Port if an unknown device is in the port.
   *          No_Error if the device type matches what is in the port.
   * @warning This function can only check for the type of device in a port, not if it is the correct
   *          one on the robot. If the port is supposed to have a left side base motor, and actually
   *          has a right side base motor, the function will return true with No_Error.
  */
  evErrorBool isCorrectDeviceInPort(int32_t port, V5_DeviceType type);

  /**
   * @brief Check if the device in a port is the correct one.
   * @tparam T The type of the "device" parameter. It must inherit from the vex::device class.
   * @param device The device to check for.
   * @returns An evErrorBool. Its "data" parameter will be true if the correct device type is detected.
   *          Incorrect_Device_In_Port if the device type doesn't match what is in the port.
   *          No_Device_In_Port if there isn't anything in the port.
   *          Invalid_Device_In_Port if an unknown device is in the port.
   *          No_Error if the device type matches what is in the port.
   * @warning This function can only check for the type of device in a port, not if it is the correct
   *          one on the robot. If the port is supposed to have a left side base motor, and actually
   *          has a right side base motor, the function will return true with No_Error.
  */
  template<typename T> evErrorBool isCorrectDeviceInPort(T device)
  {
    static_assert(std::is_base_of<vex::device, T>::value, "T must be a vex object that inherits vex::device");

    //Return data
    evErrorBool returnValue;
    returnValue.data = false;

    //*Get return data depending on the type of device in the port.
    if(device.installed())
    {
      returnValue.errorData = evError::No_Error;
      returnValue.data = true;
    }

    else if(device.type() == kDeviceTypeNoSensor)
    {
      returnValue.errorData = evError::No_Device_In_Port;
    }

    else if(device.type() == kDeviceTypeUndefinedSensor)
    {
      returnValue.errorData = evError::Invalid_Device_In_Port;
    }

    else
    {
      returnValue.errorData = evError::Incorrect_Device_In_Port;
    }

    return returnValue;
  }
}

#endif // __GENERALFUNCTIONS_H__