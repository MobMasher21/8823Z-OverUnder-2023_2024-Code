/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controllerUI.cpp                                          */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 24, 2023                                              */
/*    Description:  Class for the UI on each of the controllers.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/controllerUI.hpp"
#include "vex_global.h"

namespace evAPI
{
  controllerUI::controllerUI(vex::controller::lcd *controller)
  {
    parentController = controller;
  }
  
  controllerUI::~controllerUI()
  {
  }

  evError controllerUI::updateScreenData(bool exitIfUpdating)
  {
    //Decide what to do if the screen is bing updated
    if(updatingScreen)
    {
      if(exitIfUpdating)
      {
        //Return
        return evError::Object_State_Is_Changing;
      }

      else
      {
        //Wait until the screen stops updating
        while(updatingScreen)
        {
          vex::this_thread::sleep_for(10);
        }
      }
    }

    //Store the fact that the screen is updating
    updatingScreen = true;

    //The current line on the screen
    uint8_t currentScreenLine = 1;

    //The amount of lines to draw
    uint8_t lineDrawCount = 3;

    if(displayLines.size() < 3)
    {
      lineDrawCount = displayLines.size();
    }

    //*Update the data on the screen
    for(size_t i = currentLine; i < (currentLine + lineDrawCount); i++)
    {
      //Only draw data if there is data to draw.
      if(displayLines[i] != nullptr)
      {
        //Get the data for the row
        templateDataReturn screenData = displayLines[i]->getData();

        //*Draw the new data if it has changed
        if(screenData.dataChanged)
        {
          //Set the cursor to tbe point where the data starts
          parentController->setCursor(currentScreenLine, screenData.dataName.length()+1);

          //Print the new data in place of the old data
          parentController->print(screenData.dataOut.c_str());

          //*Clear the remainder of the row
          for(size_t ii = parentController->column(); ii < 19; ii++)
          {
            parentController->setCursor(currentScreenLine, ii);
            parentController->print(" ");
          }
        }
      }
      
      currentScreenLine++;
    }

    //The screen is no longer updating
    updatingScreen = false;
    
    return evError::No_Error;
  }

  evError controllerUI::updateScreen(bool exitIfUpdating)
  {
    //Decide what to do if the screen is bing updated
    if(updatingScreen)
    {
      if(exitIfUpdating)
      {
        //Return
        return evError::Object_State_Is_Changing;
      }

      else
      {
        //Wait until the screen stops updating
        while(updatingScreen)
        {
          vex::this_thread::sleep_for(10);
        }
      }
    }

    //Store the fact that the screen is updating
    updatingScreen = true;

    //Clear the screen
    parentController->clearScreen();

    //The current line on the screen
    uint8_t currentScreenLine = 1;

    //The amount of lines to draw
    uint8_t lineDrawCount = 3;

    if(displayLines.size() < 3)
    {
      lineDrawCount = displayLines.size();
    }

    //*Draw the new data to the screen.
    for(size_t i = currentLine; i < (currentLine + lineDrawCount); i++)
    {
      //Only draw data if there is data to draw.
      if(displayLines[i] != nullptr)
      {
        //Set the cursor
        parentController->setCursor(currentScreenLine, 1);

        //Get the data for the row
        templateDataReturn screenData = displayLines[i]->getData();

        //Print the name
        parentController->print(screenData.dataName.c_str());

        //Print the data if applicable
        if(screenData.errorData == evError::No_Error)
        {
          parentController->print(screenData.dataOut.c_str());
        }
      }

      currentScreenLine++;
    }

    //The screen is no longer updating
    updatingScreen = false;

    return evError::No_Error;
  }

  evError controllerUI::scrollDown()
  {
    //The number of lines remaining before the final line
    long validLinesRemaining;

    //Get the amount of lines remaining
    validLinesRemaining = displayLines.size() - currentLine - 3;

    //Check if increasing currentLine will cause an out of bounds error
    if(validLinesRemaining <= 0)
    {
      return evError::Range_Limit_Reached;
    }

    //Scroll down one line
    currentLine++;

    //Refresh the controller screen
    updateScreen();

    return evError::No_Error;
  }

  evError controllerUI::scrollUp()
  {
    //Exit if the line index is at the first line
    if(currentLine == 0)
    {
      return evError::Range_Limit_Reached;
    }

    //Scroll up one line
    currentLine--;

    //Refresh the controller screen
    updateScreen();

    return evError::No_Error;
  }

  evError controllerUI::setScreenLine(uint lineNumber)
  {
    //Exit if lineNumber is an invalid index.
    if(lineNumber+1 > displayLines.size())
    {
      return evError::Index_Out_Of_Range;
    }

    //The number of lines remaining before the final line
    uint validLinesRemaining;

    //Get the amount of lines remaining
    validLinesRemaining = displayLines.size() - currentLine - 3;

    //If there aren't enough lines to fully scroll to the location
    if(lineNumber > validLinesRemaining)
    {
      //Set the line index to the last valid point
      currentLine = validLinesRemaining;

      //Refresh the controller screen
      updateScreen();
      return evError::Index_Out_Of_Range_Non_Critical;
    }

    //Set the line index to the line number
    currentLine = lineNumber;

    //Refresh the controller screen
    updateScreen();

    return evError::No_Error;
  }

  uint controllerUI::getLineNumber()
  {
    return currentLine;
  }

  evError controllerUI::addData(uint id, const char name[20])
  {
    //Return if the name data is invalid.
    if(name == nullptr)
    {
      return evError::Invalid_Argument_Data;
    }

    //Make sure the vector has size for the new data point.
    if(displayLines.size() < id+1)
    {
      displayLines.resize(id+1);
    }

    //Create the new data point.
    displayLines[id] = new templateData<uint8_t>;

    //Set the parameters for the data point.
    displayLines[id]->setData(name, nullptr);

    return evError::No_Error;
  }

} // namespace evAPI