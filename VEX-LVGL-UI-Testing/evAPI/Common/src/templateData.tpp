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

template<typename T> std::string &templateData<T>::getName()
{
  return name;
}

template<typename T> evErrorString templateData<T>::getData()
{
  //Data to be returned
  evErrorString returnData;

  //Check if the data exists and return Object_Property_Not_Specified if it doesn't
  if(data == nullptr)
  {
    returnData.errorData = evError::Object_Property_Not_Specified;
    return returnData;
  }

  //Store the data
  returnData.data = evPatch::to_string(*data);

  //Return the data
  return returnData;
}