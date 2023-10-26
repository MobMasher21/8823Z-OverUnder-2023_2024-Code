/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controllerUI.cpp                                          */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 24, 2023                                              */
/*    Description:  Class for the UI on each of the controllers.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/controllerUI.hpp"

namespace evAPI
{
  controllerUI::controllerUI(vex::controller::lcd *controller)
  {
    parentController = controller;
  }
  
  controllerUI::~controllerUI()
  {
  }

  evError controllerUI::updateScreenData()
  {


    return evError::No_Error;
  }

  evError controllerUI::updateScreen()
  {


    return evError::No_Error;
  }

  evError controllerUI::scrollDown()
  {
    //The number of lines remaining before the final line
    uint validLinesRemaining;

    //Get the amount of lines remaining
    validLinesRemaining = displayLines.size() - currentLine - 3;

    //Check if increasing currentLine will cause an out of bounds error
    if(validLinesRemaining != 0)
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
      //Create new null data points until the size is correct.
      for(size_t i = 0; i < (id+1) - displayLines.size(); i++)
      {
        displayLines.push_back(nullptr);
      }
    }

    //Create the new data point.
    displayLines[id] = new templateData<uint8_t>;

    //Set the parameters for the data point.
    displayLines[id]->setData(name, nullptr);

    return evError::No_Error;
  }

} // namespace evAPI