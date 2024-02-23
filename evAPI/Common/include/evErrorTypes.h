/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       evErrorTypes.h                                            */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 2, 2023                                               */
/*    Description:  All types of errors the evAPI can report.                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef EVERRORTYPES_H
#define EVERRORTYPES_H

#include <string>

namespace evAPI
{
  /**
   * @brief A collections of various errors functions in the evAPI can output.
  */
  enum class evError
  {
    //!Unhandled_Error : Only used by evErrorToString when it gets an evError it doesn't know
    
    No_Error = 0,

    //*Hardware Device config errors
    No_Motors_Defined,
    No_Sensor_Defined,
    No_Device_Defined, //General use cases.
    No_Device_In_Port,
    Incorrect_Device_In_Port,
    Invalid_Device_In_Port,

    //*Software Device config errors
    No_Data_Defined,
    Device_Already_Exists,
    Data_Already_Exists,
    Calibration_Already_Complete,
    Invalid_Argument_Data,
    Object_Does_Not_Exist,
    Object_Property_Not_Specified,
    Range_Limit_Reached,
    Index_Out_Of_Range,
    Object_State_Is_Changing,

    Unknown_Error
  };

  /**
   * @brief A structure that is returned when a function needs to output an error and regular data.
  */
  template<typename T> struct evErrorData
  {
    //The error data
    evError errorData = evError::No_Error;

    //The normal data being returned
    T data;
  };

  //Typedefs of evErrorData for various common types
  typedef evErrorData<int> evErrorInt;
  typedef evErrorData<unsigned int> evErrorUInt;
  typedef evErrorData<float> evErrorFloat;
  typedef evErrorData<double> evErrorDouble;
  typedef evErrorData<bool> evErrorBool;
  typedef evErrorData<std::string> evErrorString;

} // namespace evAPI

#endif // EVERRORTYPES_H 