/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controllerUI.h                                            */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 24, 2023                                              */
/*    Description:  Class for the UI on each of the controllers. It pairs     */
/*                  with the vexUI class, and should not have any objects     */
/*                  created outside of it.                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef CONTROLLERUI_H
#define CONTROLLERUI_H

#include <vector>
#include <sys/types.h>
#include "vex.h"
#include "../evAPI/Common/include/evErrorTypes.h"
#include "../../Common/include/UIData.h"

namespace evAPI
{
  /**
   * @brief Class for the UI on each of the controllers. It pairs with the vexUI class, 
   *        and should not have any objects created outside of it.
  */
  class controllerUI
  {
    private:
      //The controller screen the UI controls
      vex::controller::lcd *parentController = nullptr;

      //Each line on the controller
      std::vector<UIData *> displayLines;

      //The ID of the line at the top of the screen
      uint currentLine = 0;

      //True is the screen is being updated
      bool updatingScreen = false;

            /**
       * @brief Updates all the data points on the controller screen if their values have changed.
       * @param exitIfUpdating Optional. Set to true if the function should just exit if the screen is
       *                       being updated.
       * @returns An evError.
       *          Object_State_Is_Changing: If the screen is being updated and exitIfUpdating if true.
       *          No_Data_Defined: If there is no currently defined values to display.
       *          No_Error: The screen is updated successfully.
      */
      evError updateScreenData(bool exitIfUpdating = false);

      /**
       * @brief Redraws the entire controller screen.
       * @param exitIfUpdating Optional. Set to true if the function should just exit if the screen is
       *                       being updated.
       * @returns An evError.
       *          Object_State_Is_Changing: If the screen is being updated and exitIfUpdating if true.
       *          No_Data_Defined: If there is no currently defined values to display.
       *          No_Error: The screen is updated successfully.
      */
      evError updateScreen(bool exitIfUpdating = false);

      /**
       * @brief A function that acts as a thread for both controller UIs.
       * @param UIClass A pointer to a vexUI object.
       * @returns 0
      */
      friend int controllerThread(void *UIClass);

    public:
      controllerUI(vex::controller::lcd &controller);
      ~controllerUI();

      /**
       * @brief Scrolls down the screen by one if possible.
       * @returns An evError.
       *          Range_Limit_Reached: If there is no more room to scroll down.
       *          No_Data_Defined: If there is no currently defined values to display.
       *          No_Error: If the screen scrolled down successfully.
      */
      evError scrollDown();

      /**
       * @brief Scrolls up the screen by one if possible.
       * @returns An evError.
       *          Range_Limit_Reached: If there is no more room to scroll up.
       *          No_Data_Defined: If there is no currently defined values to display.
       *          No_Error: If the screen scrolled up successfully.
      */
      evError scrollUp();

      /**
       * @brief Scrolls the screen to a certain line if possible. The line will appear at the to of th screen.
       * @param lineNumber The ID of the line to scroll to.
       * @returns An evError.
       *          Index_Out_Of_Range: If lineNumber is an invalid ID,
       *          drawing invalid data. The screen will still be scrolled to the last possible line.
       *          No_Data_Defined: If there is no currently defined values to display.
       *          No_Error: If the screen scrolled up successfully.
      */
      evError setScreenLine(uint lineNumber);

      /**
       * @returns An evErrorUInt object containing the line number in "data", and any errors in "evErrorData".
       *          Errors: No_Data_Defined: If there is no currently defined values to display.
       *          No_Error: If the screen scrolled up successfully.
      */
      evErrorUInt getLineNumber();

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
        //Make sure the vector has size for the new data point.
        if(displayLines.size() < id+1)
        {
          displayLines.resize(id+1);
        }

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

        //Create the new data point.
        displayLines[id] = new UIData;

        //Set the parameters for the data point.
        displayLines[id]->setData<T>(name, &displayData);

        return evError::No_Error;
      }

      /**
       * @brief Adds a new line to display text on the controller.
       * @param id The ID of the
       *  line.
       * @param name The text displayed on the line. Can be a max of 19 characters.
       * @returns An evError.
       *          Data_Already_Exists: If a line already exists with that ID.
       *          Invalid_Argument_Data: If the name is invalid.
       *          No_Error: If the line was added successfully.
      */
      evError addData(uint id, const char name[20]);
  };
  
} // namespace evAPI

#endif // CONTROLLERUI_H