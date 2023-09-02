#ifndef __GENERALFUNCTIONS_H__
#define __GENERALFUNCTIONS_H__

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
  #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

  /**
   * @brief Converts an input from degrees to radians.
   * @param deg The angle in degrees.
   * @returns The angle in radians.
  */
  #define radians(deg) ((deg)*DEG_TO_RAD)

  /**
   * @brief Converts an input from radians to degrees.
   * @param rad The angle in radians.
   * @returns The angle in degrees.
  */
  #define degrees(rad) ((rad)*RAD_TO_DEG)

  /**
   * @brief Calculates the square of a number: the number multiplied by itself.
   * @param x The number.
   * @returns The square of the number.
   * @author Arduino
   * @link https://reference.arduino.cc/reference/en/language/functions/math/sq/
  */
  #define sq(x) ((x)*(x))

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
  long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);

  /**
   * @brief Reduces and angle to be between 0 and 360 degrees.
   * @param angle The angle to reduce.
   * @returns The reduced angle.
  */
  float reduce_0_to_360(float angle);
  
  /**
   * @brief Reduces and angle to be between -180 and 180 degrees.
   * @param angle The angle to reduce.
   * @returns The reduced angle.
  */
  float reduce_negative_180_to_180(float angle);
  
  /**
   * @brief Reduces and angle to be between -90 and 90 degrees.
   * @param angle The angle to reduce.
   * @returns The reduced angle.
  */
  float reduce_negative_90_to_90(float angle);
  
  /**
   * @brief Converts a motor power value in percentage to one in volts.
   * @param percent The percentage getting converted to voltage.
   * @returns The corresponding value in voltage.
  */
  float to_volt(float percent);
}

#endif // __GENERALFUNCTIONS_H__