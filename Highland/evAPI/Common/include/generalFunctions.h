#ifndef __GENERALFUNCTIONS_H__
#define __GENERALFUNCTIONS_H__

#include "evNamespace.h"

//https://www.arduino.cc/reference/en/

namespace evAPI
{
  #define DEG_TO_RAD 0.017453292519943295769236907684886
  #define RAD_TO_DEG 57.295779513082320876798154814105

  /**
   * @brief Constrains a number between two other numbers.
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
  //#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

  /**
   * @brief Converts an input from degrees to radians.
   * @param deg The angle in degrees.
   * @returns The angle in radians.
  */
  template <typename T> inline T radians(T deg)
  { return deg * DEG_TO_RAD; }
  //#define radians(deg) ((deg)*DEG_TO_RAD)

  /**
   * @brief Converts an input from radians to degrees.
   * @param rad The angle in radians.
   * @returns The angle in degrees.
  */
  template <typename T> inline T degrees(T rad)
  { return rad * RAD_TO_DEG; }
  //#define degrees(rad) ((rad)*RAD_TO_DEG)

  /**
   * @brief Calculates the square of a number: the number multiplied by itself.
   * @param x The number.
   * @returns The square of the number.
   * @author Arduino
   * @link https://reference.arduino.cc/reference/en/language/functions/math/sq/
  */
  template <typename T> inline T sq(T x)
  { return x * x; }
  //#define sq(x) ((x)*(x))

  /**
   * @brief Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow,
   *  a value of fromHigh to toHigh, values in-between to values in-between, etc.
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
}

#endif // __GENERALFUNCTIONS_H__