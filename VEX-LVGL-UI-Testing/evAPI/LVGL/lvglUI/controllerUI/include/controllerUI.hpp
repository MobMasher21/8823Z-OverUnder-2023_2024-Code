/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controllerUI.hpp                                          */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 24, 2023                                              */
/*    Description:  Class for the UI on each of the controllers.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef CONTROLLERUI_HPP
#define CONTROLLERUI_HPP

#include <vector>
#include <sys/types.h>
#include "vex_controller.h"
#include "../evAPI/Common/include/evErrorTypes.hpp"
#include "../evAPI/Common/include/templateData.hpp"

namespace evAPI
{
  class controllerUI
  {
    private:
      //The controller screen the UI controls
      vex::controller::lcd *parentController;

      //Each line on the controller
      std::vector<templateDataCore *> displayLines;

      //The ID of the line at the top of the screen
      uint currentLine = 0;

      bool isDisabled = false;

    public:
      controllerUI(vex::controller::lcd *controller);
      ~controllerUI();

      /**
       * @brief Updates all the data points on the controller screen if their values have changed.
       * @returns An evError.
       *          
      */
      evError updateScreenData();

      /**
       * @brief Redraws the entire controller screen.
       * @returns An evError.
       *          
      */
      evError updateScreen();

      /**
       * @brief Scrolls down the screen by one if possible.
       * @returns An evError.
       *          Range_Limit_Reached: If there is no more room to scroll down.
       *          No_Error: If the screen scrolled down successfully.
      */
      evError scrollDown();

      /**
       * @brief Scrolls up the screen by one if possible.
       * @returns An evError.
       *          Range_Limit_Reached: If there is no more room to scroll up.
       *          No_Error: If the screen scrolled up successfully.
      */
      evError scrollUp();

      /**
       * @brief Scrolls the screen to a certain line if possible. The line will appear at the to of th screen.
       * @param lineNumber The ID of the line to scroll to.
       * @returns An evError.
       *          Index_Out_Of_Range: If lineNumber is an invalid ID,
       *          Index_Out_Of_Range_Non_Critical: If scrolling to the ID would result in parts of te screen
       *          drawing invalid data. The screen will still be scrolled to the last possible line.
       *          No_Error: If the screen scrolled up successfully.
      */
      evError setScreenLine(uint lineNumber);

      /**
       * @returns The line number of the line at the top of the screen.
      */
      uint getLineNumber();

      /**
       * @brief Adds a new line to display data on the controller.
       * @param id The ID of the line.
       * @param name The name of the line. Can be a max of 19 characters.
       * @param displayData The data to be displayed on the screen. Can be any type that can be converted
       *        to a character array natively.
       * @returns An evError.
       *          Data_Already_Exists: If a line already exists with that ID.
       *          Invalid_Argument_Data: If the name is invalid.
       *          No_Error: If the line was added successfully.
      */
      template<typename T> evError addData(uint id, const char name[20], T &displayData)
      {
        //Exit if a line already exists with that ID.
        if(displayLines[id] != nullptr)
        {
          return evError::Data_Already_Exists;
        }

        //Return if the name data is invalid.
        if(name == nullptr)
        {
          return evError::Invalid_Argument_Data;
        }

        //Make sure the vector has size for the new data point.
        if(displayLines.size() < id+1)
        {
          //Create new null data points until the size is correct.
          for(size_t i = 0; i < (id+1) - displayLines.size(); i++)
          {
            displayLines.push_back(nullptr);
          }
        }

        //Create the new data point.
        displayLines[id] = new templateData<T>;

        //Set the parameters for the data point.
        displayLines[id]->setData(name, displayData);

        return evError::No_Error;
      }

      /**
       * @brief Adds a new line to display text on the controller.
       * @param id The ID of the line.
       * @param name The text displayed on the line. Can be a max of 19 characters.
       * @returns An evError.
       *          Data_Already_Exists: If a line already exists with that ID.
       *          Invalid_Argument_Data: If the name is invalid.
       *          No_Error: If the line was added successfully.
      */
      evError addData(uint id, const char name[20]);
  };
  
} // namespace evAPI

#endif // CONTROLLERUI_HPP