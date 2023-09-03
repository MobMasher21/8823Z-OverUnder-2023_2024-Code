/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       lvglUI.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Aug 5 2023                                            */
/*    Description:  Header file for the UI system using LVGL.                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef GREATUI_H
#define GREATUI_H

#include "vex.h"
#include "v5lvgl.h"
#include "evAPISettings.h"
#include "../include/matchUICore.h"
#include "../include/UITheme.h"
#include "../../../Common/include/colors.h"
#include "../../../Common/include/evNamespace.h"

namespace evAPI
{
  class lvglUI
  {
    private:
      thread * UIThread;

      //!AUTO SELECTOR

      uint finalButtonID = 0;
      uint buttonCount = 0;
      uint buttonInfoDisplayTime = 2000;

      int progMode = 0;

      void addButtonCore(int id);

      void autoSelectorSetup();

      //!MATCH UI

      uint finalMatchDisplayID = 0;
      uint matchDisplayCount = 0;

      void matchUISetup();
      
    public:
      lvglUI();
      ~lvglUI();

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
       * @brief Adds a custom icon to the button.
       * @param id The ID of the button.
       * @param icon A custom icon from LVGL. 
       * @returns False if the icon is added successfully.
      */
      bool addIcon(int id, const lv_img_dsc_t icon);

      /**
       * @brief Changes the color of an icon on a button.
       * @param id The ID of the button.
       * @param r The red value for the color of the icon.
       * @param g The green value for the color of the icon.
       * @param b The blue value for the color of the icon.
       * @returns False if the icon is added successfully.
      */
      bool changeIconColor(int id, int r, int g, int b);

      /**
       * @brief Changes the color of an icon on a button.
       * @param id The ID of the button.
       * @param iconColor A color object containing the color of the icon.
       * @returns False if the icon is added successfully.
      */
      bool changeIconColor(int id, color iconColor);

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
      bool addTitle(int id, const char Title[MAX_AUTO_TITLE_LENGTH]);

      /**
       * @brief Adds a description to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Description An array of characters that contains the description.
       * @returns False if it successfully adds the data.
      */
      bool addDescription(int id, const char Description[MAX_AUTO_DESCRIPTION_LENGTH]);

      /**
       * @brief Changes the name of a tab in the auto selector.
       * @param id The ID of the tab.
       * @param Title An array of characters that contains the name.
       * @returns False if it successfully adds the data.
      */
      bool setAutoTabName(int id, const char Name[MAX_AUTO_TAB_NAME_LENGTH]);

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
       * @brief Changes the selected tab. THIS FUNCTION CAN ONLY BE RUN AFTER THE UI HAS BEEN STARTED!
       * @param id The tab that will be selected.
      */
      void selectTab(int id);

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

      //!Brain Display Setup

      /**
       * @brief Creates the field display. NOTE: USING THIS WILL REMOVE 4 SLOTS FOR GRAPHS ON THE
       *  BRAIN SCREEN.
       * @param side Which side of the brain's screen the field will be displayed on.
      */
      //void createFieldDisplay(turnType side);

      /**
       * @param Sets a tile's color on the field display.
       * @param tileID The numerical ID of the tile. Ranges from 0-35, with 0 being the top left,
       * and 35 being the bottom right. The value goes up by one for each tile to he right.
       * @param tileColor The color the tile will be set too.
      */
      void setTileColor(uint8_t tileID, color tileColor);

      /**
       * @param Sets a tile's color on the field display.
       * @param tileID The numerical ID of the tile. Ranges from 0-35, with 0 being the top left,
       * and 35 being the bottom right. The value goes up by one for each tile to he right.
       * @param tileColor The color the tile will be set too.
      */
      void setTileColor(uint8_t tileID, int tileColor);

      /**
       * @brief Creates text to display on the Brain.
       * @param name An array of characters containing the name of the data.
      */
      bool createBrainDisplay(int id, const char name[MAX_MATCH_DATA_NAME_LENGTH]);

      /**
       * @brief Sets the color of a brain display with the specified id.
       * @param id The ID of the brian display.
       * @param r The red value for the color of the brian display.
       * @param g The green value for the color of the brian display.
       * @param b The blue value for the color of the brian display.
       * @return False if the operation completed successfully.
      */
      bool setBrainDisplayColor(int id, int r, int g, int b);
      
      /**
       * @brief Sets the color of a brain display with the specified id.
       * @param id The ID of the brian display.
       * @param Color The color of the brain display.
       * @return False if the operation completed successfully.
      */
      bool setBrainDisplayColor(int id, color Color);

      /**
       * @brief Sets the value to be displayed on the brain display.
       * @param id The ID of the brian display.
       * @param *data The address of a variable that contains the data to be displayed.
       * @param inputDataType The type of the variable being displayed.
      */
      bool setBrainDisplayData(int id, void *data, brainDataType inputDataType);

      /**
       * @brief Sets the value to be displayed on the brain display.
       * @param id The ID of the brian display.
       * @param callback The a function that returns the data to be displayed.
      */
      bool setBrainDisplayData(int id, int (*callback)());

      /**
       * @brief Sets the value to be displayed on the brain display.
       * @param id The ID of the brian display.
       * @param callback The a function that returns the data to be displayed.
      */
      bool setBrainDisplayData(int id, double (*callback)());

      /**
       * @brief Changes the name of a tab in the auto selector.
       * @param id The ID of the tab.
       * @param Title An array of characters that contains the name.
       * @returns False if it successfully adds the data.
      */
      bool setMatchTabName(int id, const char Name[MAX_MATCH_TAB_NAME_LENGTH]);

      /**
       * @returns The total amount of match display outputs.
      */
      uint getMatchDisplayCount();

      /**
       * @returns The ID of the final match display created.
      */
      uint getFinalMatchDisplayID();

      /**
       * @brief Starts the UI thread handling screen updates and touch detection.
      */
      void startUIThreads();
  };

  extern lvglUI UI;
  
} // namespace evAPI

#endif // GREATUI_H