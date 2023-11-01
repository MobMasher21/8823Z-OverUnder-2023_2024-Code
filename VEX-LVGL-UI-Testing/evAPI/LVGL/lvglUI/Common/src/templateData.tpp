/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       templateData.tpp                                          */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 24, 2023                                              */
/*    Description:  Template Class for holding data of a desired type and     */
/*                  outputting that data as a string.                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

template<typename T> evError templateData<T>::setData(const char *nameIn, void *dataIn)
{
  //Check if the name is invalid
  if(nameIn == nullptr)
  {
    return evError::Invalid_Argument_Data;
  }

  //Store the name
  name = nameIn;

  //Store the data if it is valid
  if(dataIn != nullptr)
  {
    data = (T*)dataIn;
  }

  return evError::No_Error;
}

template<typename T> templateDataReturn &templateData<T>::getData()
{
  //Data to be returned
  static templateDataReturn returnData;

  //Store the name of the data
  returnData.dataName = name;

  //Check if the data exists and return Object_Property_Not_Specified if it doesn't
  if(data == nullptr)
  {
    returnData.errorData = evError::Object_Property_Not_Specified;
    returnData.dataOut = "";
    returnData.dataChanged = false;
    return returnData;
  }

  //Store the data
  returnData.dataOut = evPatch::to_string(*data);

  //Store true if the data is different from when it was last read/
  if(strcmp(returnData.dataOut.c_str(), prevData.c_str()))
  {
    returnData.dataChanged = true;
  }

  else
  {
    returnData.dataChanged = false;
  }

  //Store the current data
  prevData = returnData.dataOut;

  //Return the data
  return returnData;
}