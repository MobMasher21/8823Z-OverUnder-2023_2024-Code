/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       templateData.hpp                                          */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 24, 2023                                              */
/*    Description:  Template Class for holding data of a desired type and     */
/*                  outputting that data as a string.                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef TEMPLATEDATA_HPP
#define TEMPLATEDATA_HPP

#include "string"
#include "../evAPI/Common/include/evErrorTypes.hpp"
#include "../evAPI/Common/include/evPatch.hpp"

namespace evAPI
{
  /**
   * @brief An object that is returned when getting the data from a templateData object
  */
  struct templateDataReturn
  {
    /**
     * @brief Any errors associated with getting the data.
    */
    evError errorData = evError::No_Error;

    /**
     * @brief A name associated with the data.
    */
    std::string dataName;

    /**
     * @brief A string containing the data.
    */
    std::string dataOut;

    /**
     * @brief True if the data has changed from the last time it was read.
    */
    bool dataChanged = false;
  };

  /**
   * @brief An accessor class used for storing all the data as a vector or array. Should be created with
   *        a templateData object with the desired type.
  */
  class templateDataCore
  {
    public:
      virtual evError setData(const char *nameIn, void *dataIn) = 0;
      virtual templateDataReturn &getData() = 0;
  };

  /**
   * @brief A template class that can store data of the specified type and output it as a std::string object.
   *        If a templateDataCore object pointer is created, it can be set to a templateData object of the
   *        desired type. This can be useful if you need to store data of varying types.
   * @param T The type this instance of the class will be associated with.
   * @example templateDataCore *data = templateData<int>;
  */
  template<typename T> class templateData : public templateDataCore
  {
    private:
      //Pointer to the data the object holds
      T *data;

      //The previous value of the data
      std::string prevData;

      //The name of the object used for displaying information on a screen
      std::string name;

    public:

      /**
       * @brief Stores the name and data pointer.
       * @param nameIn The name for the data.
       * @param dataIn A pointer that stores the variable used for the data to display.
       * @returns An evError.
       *          Invalid_Argument_Data: If the name data is null.
       *          No_Error: If the title and name were stored successfully.
      */
      evError setData(const char *nameIn, void *dataIn);

      /**
       * @brief Returns the data with a templateDataReturn object.
       * @returns A reference to a templateDataReturn object.
       *          errorData: Object_Property_Not_Specified if there is no data attached to the object.
       *          dataName: The name of the object.
       *          dataOut: The data as a std::string object.
       *          dataChanged: True if the data has changed since the last time it was read.
      */
      templateDataReturn &getData();
  };

  //Include the function code for templateDataCore
  #include "../src/templateData.tpp"
  
} // namespace evAPI

#endif // TEMPLATEDATA_HPP