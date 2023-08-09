/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       greatUI.h                                                 */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Aug 5 2023                                            */
/*    Description:  Header file for the UI system using LVGL.                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef GREATUI_H
#define GREATUI_H

#include "vex.h"
#include "..\include\button.h"
#include "..\..\..\Common\include\colors.h"
#include "..\..\..\Common\include\evNamespace.h"

//! Define icon IDs here!
#define SKILLS_ICON 0
#define LEFT_ARROW 1
#define RIGHT_ARROW 2

#define MAX_TAB_COUNT 5

#define MAX_BUTTON_COUNT (MAX_TAB_COUNT * 8)
#define MAX_BRAIN_GRAPH_COUNT 32 
#define MAX_BRAIN_NAME_LENGTH 22
#define MAX_CONTROLLER_GRAPH_COUNT 6
#define MAX_CONTROLLER_NAME_LENGTH 20

#define MAX_TITLE_LENGTH 16
#define MAX_TAB_NAME_LENGTH 6
#define MAX_DESCRIPTION_LENGTH 240

namespace evAPI
{
  class greatUI
  {
    private:
      thread * matchUIThread;
      thread * controllerUIThread;

      uint finalButtonID = 0;
      uint buttonCount = 0;
      uint buttonInfoDisplayTime = 2000;

      int progMode = 0;

      void addButtonCore(int id);
      
    public:
      greatUI(/* args */);
      ~greatUI();

      /**
       * @brief Starts the UI thread handling screen updates and touch detection.
      */
      void startUIThreads();

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param r The red value for the color of the button.
       * @param g The green value for the color of the button.
       * @param b The blue value for the color of the button.
       * @returns The total number of buttons created.
      */
      int addButton(int id, int r, int g, int b);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param buttonColor A color object that contains the color of the button.
       * @returns The total number of buttons created.
      */
      int addButton(int id, color buttonColor);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param alliance The alliance the robot will be part of when this button is selected.
       * It's color will match that of the alliance, with no alliance producing a grey button.
       * @returns The total number of buttons created.
      */
      int addButton(int id, allianceType alliance);
      
      /**
       * @brief Adds an icon to the button.
       * @param id The ID of the button.
       * @param iconInput An ID of the icon.
       * @returns False if the icon is added successfully.
      */
      bool addIcon(int id, int iconID);

      /**
       * @brief Changes the color of an icon on a button.
       * @param id The ID of the button.
       * @param r The red value for the color of the icon.
       * @param g The green value for the color of the icon.
       * @param b The blue value for the color of the icon.
       * @returns False if the icon is added successfully.
      */
      bool setIconColor(int id, int r, int g, int b);

      /**
       * @brief Changes the color of an icon on a button.
       * @param id The ID of the button.
       * @param iconColor A color object containing the color of the icon.
       * @returns False if the icon is added successfully.
      */
      bool setIconColor(int id, color iconColor);

      /**
       * @brief Adds a function to be called when the button is pressed.
       * @param id The ID of the button.
       * @param callback The function to be run.
      */
      bool addCallbackFunc(int id, void (*callback)(int));

      /**
       * @brief Adds a title to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Title An array of characters that contains the title.
      */
      bool addTitle(int id, const char Title[MAX_TITLE_LENGTH]);

      /**
       * @brief Adds a description to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Title An array of characters that contains the description.
       * @returns False if it successfully adds the data.
      */
      bool addDescription(int id, const char Description[MAX_DESCRIPTION_LENGTH]);

      /**
       * @brief Changes the name of a tab.
       * @param id The ID of the tab.
       * @param Title An array of characters that contains the name.
       * @returns False if it successfully adds the data.
      */
      bool setTabName(int id, const char Name[MAX_TAB_NAME_LENGTH]);

      /**
       * @brief Maps a button to a specific alliance. This will not change the color of the button.
       * @param id The ID of the button.
       * @param alliance The alliance the robot will be part of when this button is selected.
      */
      bool addAlliance(int id, allianceType alliance);

      /**
       * @brief Changes the color of a button. THIS FUNCTION CAN ONLY BE RUN AFTER THE UI HAS BEEN STARTED!
       * @param id The ID of the button.
       * @param r The red value for the color of the button.
       * @param g The green value for the color of the button.
       * @param b The blue value for the color of the button.
      */
      bool changeButtonColor(int id, int r, int g, int b);

      /**
       * @brief Changes the color of a button. THIS FUNCTION CAN ONLY BE RUN AFTER THE UI HAS BEEN STARTED!
       * @param id The ID of the button.
       * @param buttonColor A color object that contains the color of the button.
      */
      bool changeButtonColor(int id, color buttonColor);

      /**
       * @brief Changes the selected button. THIS FUNCTION CAN ONLY BE RUN AFTER THE UI HAS BEEN STARTED!
       * @param id The button that will be selected.
       * @param doNotShowSettings Optional. Allows the user to change the program showing the name on the screen.
      */
      void selectButton(int id, bool doNotShowSettings = false);

      /**
       * @brief Sets the time the button info box will be displayed on the Brain.
       * @param time The time in ms.
      */
      void setDisplayTime(int time);
      
      /**
       * @returns The time in ms the button info box will be displayed for.
      */
      int getDisplayTime();

      /**
       * @returns The ID of the selected button.
      */
      int getProgNumber();

      /**
       * @returns The total amount of buttons.
      */
      uint getButtonCount();

      /**
       * @returns The ID of the final button created.
      */
      uint getFinalButtonID();
  };

  extern greatUI UI;
  
} // namespace evAPI

#endif // GREATUI_H