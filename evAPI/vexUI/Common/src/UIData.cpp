/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UIData.cpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Dec 13, 2023                                              */
/*    Description:  Class that is used to store data for the UIs.             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/UIData.h"

namespace evAPI
{
  UIData::UIData()
  {}
  
  UIData::~UIData()
  {
    if(data != nullptr)
    {
      delete data;
    }
  }

  UIDataReturn UIData::getData()
  {
    //Get data to return
    UIDataReturn dataOut;

    //Data stored by the user
    evErrorData<std::string> objectData;

    //*Get needed data and return it
    objectData = data->getData();

    //Store the needed data being outputted
    dataOut.label = label;
    dataOut.errorData = objectData.errorData;
    dataOut.data = objectData.data;
    
    //Check if data has changed
    if(objectData.data != prevData)
    {
      dataOut.hasChanged = true;
    }

    prevData = objectData.data;

    //*Return the data
    return dataOut;
  }

} // namespace evAPI