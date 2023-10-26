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
#include "evErrorTypes.hpp"
#include "evPatch.h"

namespace evAPI
{
  /**
   * @brief An accessor class used for storing all the data as a vector or array. Should be created with
   *        a templateData object with the desired type.
  */
  class templateDataCore
  {
    public:
      virtual evError setData(const char *nameIn, void *dataIn);
      virtual std::string &getName();
      virtual evErrorString getData();
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
      T *data;
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
       * @returns A std::string object containing the name.
      */
      std::string &getName();

      /**
       * @returns The data as an evErrorData structure with the std::string type.
       *          Object_Property_Not_Specified: If there is no data to print out.
       *          No_Error: If the data was returned successfully + A string containing the data to display.
      */
      evErrorString getData();
  };

  #include "../src/templateData.tpp"
  
} // namespace evAPI

#endif // TEMPLATEDATA_HPP