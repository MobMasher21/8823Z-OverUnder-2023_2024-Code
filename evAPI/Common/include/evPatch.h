/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       evPatch.h                                                 */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 25, 2023                                          */
/*    Description:  Patches to reimplement C++ features missing from the C++  */
/*                  variant VEX ships.                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef EVPATCH_H
#define EVPATCH_H

#include <string>
#include <sstream>

namespace evAPI::evPatch
{
  /**
   * @brief Converts a value to a std::string object.
   * @param n The data to convert.
   * @returns A std::string object containing the data.
  */
  template <typename T> std::string to_string(const T& n)
  {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

#endif // EVPATCH_H