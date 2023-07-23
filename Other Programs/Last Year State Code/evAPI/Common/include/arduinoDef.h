#ifndef __ARDUINODEF_H__
#define __ARDUINODEF_H__

//https://www.arduino.cc/reference/en/

namespace evAPI
{
  #define DEG_TO_RAD 0.017453292519943295769236907684886
  #define RAD_TO_DEG 57.295779513082320876798154814105

  /**
   * @brief An arduino function that returns the lowest input provided.
   * @param a Input #1
   * @param b Input #2
   * @returns The lowest of the two inputs.
  */
  #define min(a,b) ((a)<(b)?(a):(b))

  /**
   * @brief An arduino function that returns the largest input provided.
   * @param a Input #1
   * @param b Input #2
   * @returns The larger of the two inputs.
  */
  #define max(a,b) ((a)>(b)?(a):(b))

  /**
   * @brief An arduino function that returns the absolute value of the input. It supports more types
   *  than just int.
   * @param x The input
   * @returns The absolute value of the input.
  */
  #define absf(x) ((x)>0?(x):-(x))

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
   * @brief Squares a number.
   * @param x The number being squared.
   * @returns The squared number.
  */
  #define sq(x) ((x)*(x))
}

#endif // __ARDUINODEF_H__