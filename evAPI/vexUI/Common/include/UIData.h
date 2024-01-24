/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UIData.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Dec 13, 2023                                              */
/*    Description:  Class that is used to store data for the UIs.             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef UIDATA_H
#define UIDATA_H

#include "anyData.h"

namespace evAPI
{
  struct UIDataReturn
  {
    std::string label;
    std::string data;
    bool hasChanged = false;
    evError errorData = evError::No_Error;
  };

  class UIData
  {
    private:
      //Data the object stores
      anyDataCore *data = nullptr;

      //Data from the previous time it was read out
      std::string prevData;

      //Name of the object
      std::string label;

    public:
      UIData();
      ~UIData();

      /**
       * @brief Sets the data and name stored in the object
      */
      template<typename T> evError setData(const char *labelIn, T *dataIn);

      UIDataReturn getData();
  };

  template<typename T> evError UIData::setData(const char *labelIn, T *dataIn)
  {
    //Make sure the name is valid
    if(labelIn == nullptr)
    {
      return evError::Invalid_Argument_Data;
    }

    //Store the name
    label = labelIn;

    //Delete data if it already exists
    if(data != nullptr)
    {
      delete data;
    }

    //Create and set the data object
    data = new anyData<T>;
    data->setData(dataIn);
    
    return evError::No_Error;
  }
  
} // namespace evAPI

#endif // UIDATA_H