#ifndef AUTODATA_H_
#define AUTODATA_H_

#include "../../../Common/include/evAPIBasicConfig.h"
#include "../../../Common/include/evNamespace.h"
#include <string>

#define MAX_TITLE_LENGTH 15
#define MAX_DESCRIPTION_LENGTH 188
#define PER_LINE_MAX 47

namespace evAPI {
  class AutoData {
    public:
      void setTitle(char titleIN[MAX_TITLE_LENGTH]);  // Set the auto title
      void setDescription(char descriptionIN[MAX_DESCRIPTION_LENGTH]);  // Set the auto description
      bool printButtonData();  // Prints all the data to the screen

      /**
       * @returns The title of the data as a std::string.
      */
      std::string getTitle();

      /**
       * @returns The description of the data as a std::string.
      */
      std::string getDescription();
  
    private:
      char title[MAX_TITLE_LENGTH+1];
      bool hasTitle;
      char description[MAX_DESCRIPTION_LENGTH+1];
      bool hasDescription;
      
  };
}

#endif // AUTODATA_H_