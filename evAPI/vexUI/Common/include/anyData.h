/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       anyData.h                                                 */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Dec 13, 2023                                              */
/*    Description:  Template class that allows for storing any type of data   */
/*                  that can be converted to a string                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef ANYDATA_H
#define ANYDATA_H

#include "../evAPI/Common/include/evPatch.h"
#include "../evAPI/Common/include/evErrorTypes.h"

namespace evAPI
{
  /**
   * @brief An accessor class used for storing all the data as a vector or array. Should be created with
   *        a anyData object with the desired type.
   * @example anyDataCore *data = anyData<int>;
  */
  class anyDataCore
  {
    public:
      virtual ~anyDataCore() = default;
      virtual evError setData(void *newData) = 0;
      virtual evErrorString getData() = 0;
  };

  /**
   * @brief A template class used to store a pointer to a variable, and return its values
   *        as a string. Should be created with an anyDataCore 
   * @tparam T The type of data that will be stored in the anyData object.
   * @example anyDataCore *data = anyData<int>; 
  */
  template<typename T> class anyData: public anyDataCore
  {
    private:
      T *data = nullptr;

    public:
      /**
       * @brief Creates a new anyData object that points to the set data.
       * @param data A pointer to the data to store.
       * @returns An evError. Object_Property_Not_Specified if data is invalid.
       *          No_Error if their aren't any errors.
      */
      evError setData(void *newData);

      /**
       * @returns An evErrorData object containing a std::string. If the data isn't null, the string will 
       * containing the data from setData(). If it is, the error will be Object_Property_Not_Specified.
      */
      evErrorString getData();
  };
  
  template<typename T> evError anyData<T>::setData(void *newData)
  {
    //Only set the data if it isn't null
    if(newData != nullptr)
    {
      data = (T*)newData;
    }
    
    else
    {
      data = nullptr;
      return evError::Object_Property_Not_Specified;
    }

    return evError::No_Error;
  }

  template<typename T> evErrorString anyData<T>::getData()
  {
    evErrorString dataString;

    //Get data if data exists
    if(data != nullptr)
    {
      dataString.data = evPatch::to_string(*data);
    }

    //Report an error if the data isn't found
    else
    {
      dataString.data = std::string("");
      dataString.errorData = evError::Object_Property_Not_Specified;
    }

    return dataString;
  }
  
} // namespace evAPI

#endif // ANYDATA_H