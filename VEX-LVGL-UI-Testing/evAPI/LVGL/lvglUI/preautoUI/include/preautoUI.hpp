/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       preautoUI.hpp                                             */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 12, 2023                                              */
/*    Description:  Class for the preauto UI.                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef PREAUTOUI_HPP
#define PREAUTOUI_HPP

#include "preautoButton.hpp"
#include "../evAPI/Common/include/evErrorTypes.hpp"
#include "../../Common/include/tabGroup.hpp"

#define SKILLS_ICON iconType::Skills_Icon
#define LEFT_ARROW iconType::Left_Arrow
#define RIGHT_ARROW iconType::Right_Arrow
#define EXCLAMATION_POINTS iconType::Exclamation_Points

namespace evAPI
{
  class preautoUI : private tabGroup
  {
    private:
      //The amount of buttons created
      uint buttonCount;

      //The amount of time in ms the button info display will be up
      uint32_t buttonInfoDisplayTime = 2000;

      //The ID of the currently selected button
      uint selectedButtonID;

      /**
       * @brief The core function behind all the addButton functions.
       * @param id The ID of the button
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: IF the button is created successfully.
      */
      evError addButtonCore(uint id);

    public:
      preautoUI();
      ~preautoUI();

      /**
       * @brief Creates a tab in the auto selector.
       * @param Title An array of characters that contains the name.
       * @returns False if it successfully adds the data.
      */
      bool addAutoTab(const char Name[SELECTOR_TAB_NAME_LENGTH]);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param r The red value for the color of the button.
       * @param g The green value for the color of the button.
       * @param b The blue value for the color of the button.
       * @returns An evErrorData object.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error + Button ID: IF the button is created successfully.
      */
      evErrorUInt addButton(uint id, int r, int g, int b);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param buttonColor A color object that contains the color of the button.
       * @returns An evErrorData object.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error + Button ID: IF the button is created successfully.
      */
      evErrorUInt addButton(uint id, evColor buttonColor);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param alliance The alliance the robot will be part of when this button is selected.
       *                 It's color will match that of the alliance, with no alliance producing
       *                 a grey button.
       * @returns An evErrorData object.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error + Button ID: IF the button is created successfully.
      */
      evErrorUInt addButton(uint id, allianceType alliance);
      
      /**
       * @brief Adds an icon to the button.
       * @param id The ID of the button.
       * @param iconInput An ID of the icon.
       * @param iconColor Optional. The color of the icon.
       * @returns An evError.
       *          Object_Does_Not_Exist: If there isn't a button with the ID.
       *          Invalid_Argument_Data: If the icon type is Custom_Icon or if the ID is greater 
       *                                 than the maximum amount of buttons.
       *          No_Error: IF the functions adds the icon successfully.
      */
      evError addIcon(uint id, iconType iconID, evColor iconColor = vex::color::white);

      /**
       * @brief Adds a custom icon to the button.
       * @param id The ID of the button.
       * @param icon The address of a custom icon from LVGL. 
       * @param iconColor Optional. The color of the icon.
       * @returns An evError.
       *          Object_Does_Not_Exist: If there isn't a button with the ID.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          No_Error: IF the functions adds the icon successfully.
      */
      evError addIcon(uint id, const lv_img_dsc_t &icon, evColor iconColor = vex::color::white);

      /**
       * @brief Changes the color of an icon on a button.
       * @param id The ID of the button.
       * @param r The red value for the color of the icon.
       * @param g The green value for the color of the icon.
       * @param b The blue value for the color of the icon.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          Object_Property_Not_Specified: If the button doesn't have an icon.
       *          No_Error: If the icon color is changed successfully.
      */
      evError changeIconColor(uint id, int r, int g, int b);

      /**
       * @brief Changes the color of an icon on a button.
       * @param id The ID of the button.
       * @param iconColor A color object containing the color of the icon.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          Object_Property_Not_Specified: If the button doesn't have an icon.
       *          No_Error: If the icon color is changed successfully.
      */
      evError changeIconColor(uint id, evColor iconColor);

      /**
       * @brief Adds a function to be called when the button is pressed.
       * @param id The ID of the button.
       * @param callback The function to be run.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons or if the 
       *                                 callback function is invalid.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the callback was set correctly.
      */
      evError addCallbackFunc(uint id, void (*callback)(uint));

      /**
       * @brief Adds a title to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Title An array of characters that contains the title.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the title is added successfully.
      */
      evError addTitle(uint id, const char Title[MAX_AUTO_TITLE_LENGTH]);

      /**
       * @brief Adds a description to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Description An array of characters that contains the description.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the description is added successfully.
      */
      evError addDescription(uint id, const char Description[MAX_AUTO_DESCRIPTION_LENGTH]);

      /**
       * @brief Maps a button to a specific alliance. This will not change the color of the button.
       * @param id The ID of the button.
       * @param alliance The alliance the robot will be part of when this button is selected.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the alliance was added successfully.
      */
      evError addAlliance(uint id, allianceType alliance);

      /**
       * @brief Changes the color of a button.
       * @param id The ID of the button.
       * @param r The red value for the color of the button.
       * @param g The green value for the color of the button.
       * @param b The blue value for the color of the button.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the button color was changed successfully.
      */
      evError changeButtonColor(uint id, int r, int g, int b);

      /**
       * @brief Changes the color of a button.
       * @param id The ID of the button.
       * @param buttonColor A color object that contains the color of the button.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the button color was changed successfully.
      */
      evError changeButtonColor(uint id, color buttonColor);

      /**
       * @brief Changes the selected button.
       * @param id The button that will be selected.
       * @param doNotShowSettings Optional. Prevents the button info box from appearing.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the maximum amount of buttons.
       *          Data_Already_Exists: If a button has already been created with that ID.
       *          No_Error: If the button was selected successfully.
      */
      evError selectButton(uint id, bool doNotShowSettings = false);

      /**
       * @brief Changes the selected tab.
       * @param id The tab that will be selected.
       * @returns An evError.
       *          Invalid_Argument_Data: If the ID is greater than the amount of tabs.
       *          Data_Already_Exists: If a tab doesn't exist with that ID.
       *          No_Error: If the tab was selected successfully.
      */
      evError selectTab(uint id);

      /**
       * @brief Sets the time the button info box will be displayed on the Brain.
       * @param time The time in ms.
      */
      void setDisplayTime(uint32_t time);
      
      /**
       * @returns The time in ms the button info box will be displayed for.
      */
      uint32_t getDisplayTime();

      /**
       * @returns The ID of the selected button.
      */
      uint getProgNumber();

      /**
       * @returns The total amount of buttons.
      */
      uint getButtonCount();

      /**
       * @returns The ID of the final button created.
      */
      uint getFinalButtonID();

      /**
       * @brief Shows or hides the preauto UI.
       * @param status True if the UI is shown. False i it isn't.
       * @warning Function is used by the Core UI for automatically switching the displayed UI
       *          to the Match UI. Calling this function is not recommended.
      */
      void showPreautoUI(bool status);
  };
  
} // namespace evAPI

#endif // PREAUTOUI_HPP