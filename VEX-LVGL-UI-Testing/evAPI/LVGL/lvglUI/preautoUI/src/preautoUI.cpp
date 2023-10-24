/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       preautoUI.hpp                                             */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 12, 2023                                              */
/*    Description:  Class for the preauto UI.                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <limits.h>
#include "../include/preautoUI.hpp"
#include "../../coreUI/include/coreUI.hpp"
#include "../evAPI/LVGL/LVGLInit/include/vexLVGL.hpp"

namespace evAPI
{
  //A vector of all the buttons
  preautoButton *buttonList[MAX_AUTO_BUTTON_COUNT];

  //ID of the button that was previously pressed
  uint prevTriggeredButtonID = UINT_MAX;

  //Button info box
  lv_obj_t *buttonInfoBox;

  //Timer used to automatically delete the button info box
  timer buttonInfoBoxTimer = timer();

  /**
   * Stores the status of the button info box. Needed because checking for nullptr doesn't work
   * with LVGL objects
  */
  bool buttonInfoBoxExists = false;

  /**
   * @brief Closes the button info box.
  */
  void closeInfoButtonBox()
  {
    //Don't delete the button info box if it doesn't exist.
    if(buttonInfoBoxExists)
    {
      buttonInfoBoxExists = false;
      lv_msgbox_close(buttonInfoBox);
    }
  }

  /**
   * @brief A function to be run by the close button on the button info box.
   * @param event Unused. Only here so the function can be tied to the button in LVGL.
  */
  static void closeButtonPressed(lv_event_t *event)
  {
    //Extract the event code from the event
    lv_event_code_t eventCode = lv_event_get_code(event);

    //Only run if the button was pressed
    if(eventCode == LV_EVENT_PRESSING)
    {
      buttonInfoBoxExists = false;
    }
  }

  /**
   * @brief The function that is run whenever a button in the preauto UI is pressed.
   * It stores the button that was pressed, changes the UI to show the new button that was pressed,
   * and creates the button info box.
   * @param event An LVGL event that is tied to the button that was pressed.
  */
  static void autoButtonPressFunc(lv_event_t *event)
  {
    //Extract the event code from the event
    lv_event_code_t eventCode = lv_event_get_code(event);

    //Use the event code to get the LVGL object that was pressed
    lv_obj_t *triggeredButton = lv_event_get_target(event);

    //Only run if the button was pressed
    if(eventCode == LV_EVENT_CLICKED)
    {
      //Get the first child of triggeredButton, which is its LVGLButtonID
      lv_obj_t *LVGLButtonID = lv_obj_get_child(triggeredButton, 0);

      //Extract the ID from LVGLButtonID
      int buttonID = strtol(lv_label_get_text(LVGLButtonID), nullptr, 10);

      //Select the button and display the button info box.
      UI.autoSelector.selectButton(buttonID, false);
    }
  }

  evError preautoUI::addButtonCore(uint id)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if a button already exists with that ID
    if(buttonList[id] != nullptr)
    {
      return evError::Data_Already_Exists;
    }

    //!Determine where the button should be located on screen and what tab it is on

    //ID of the button relative to the page it is on. 0-7
    uint localID = id;

    //ID of tab the button is on
    uint buttonTabID = 0;

    //Multipliers that control the button location
    uint8_t verticalOffsetMultiplier = 0;
    uint8_t horizontalOffsetMultiplier = 0;

    //Position of the button
    uint buttonX;
    uint buttonY;

    //*Create the offsets used to calculate the position

    //Reduce the ID to be between 0-7 and find the tab the button is on
    while(localID > 7)
    {
      localID -= 8;
      buttonTabID++;
    }

    //If the button is in the bottom row of buttons
    if(localID > 3)
    {
      //Move the ID to be in the top row for calculating the horizontal offset
      localID -= 4;
      verticalOffsetMultiplier = 1;
    }

    //Get the horizontal offset
    horizontalOffsetMultiplier = localID;

    //*Calculate the position with the offsets
    buttonX = ((AUTO_BUTTON_SIZE + AUTO_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier)) + AUTO_BUTTON_X_OFFSET;
    buttonY = ((AUTO_BUTTON_SIZE + AUTO_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier)) + AUTO_BUTTON_Y_OFFSET;

    //Create the button
    buttonList[id] = new preautoButton(id, buttonX, buttonY, pageTabs[buttonTabID], autoButtonPressFunc);

    return evError::No_Error;
  }

  preautoUI::preautoUI()
  {}
  
  preautoUI::~preautoUI()
  {}

  bool preautoUI::addAutoTab(const char Name[SELECTOR_TAB_NAME_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Store the name
    addTab(Name);

    return false;
  }

  evErrorUInt preautoUI::addButton(uint id, int r, int g, int b)
  {
    //Data to return
    evErrorUInt returnData;

    //Create the button and store any errors
    returnData.errorData = addButtonCore(id);

    if(returnData.errorData != evError::No_Error)
    {
      return returnData;
    }

    //*Set the button color
    evColor buttonColor;

    buttonColor.rgb(r, g, b);

    buttonList[id]->setButtonColor(buttonColor);

    //Store the amount of created buttons;
    returnData.data = buttonCount;

    return returnData;
  }
  
  evErrorUInt preautoUI::addButton(uint id, evColor buttonColor)
  {
    //Data to return
    evErrorUInt returnData;

    //Create the button and store any errors
    returnData.errorData = addButtonCore(id);

    if(returnData.errorData != evError::No_Error)
    {
      return returnData;
    }

    //Set the button color
    buttonList[id]->setButtonColor(buttonColor);

    returnData.data = buttonCount;

    return returnData;
  }

  evErrorUInt preautoUI::addButton(uint id, allianceType alliance)
  {
    //Data to return
    evErrorUInt returnData;

    //Create the button and store any errors
    returnData.errorData = addButtonCore(id);

    if(returnData.errorData != evError::No_Error)
    {
      return returnData;
    }

    //Set the button alliance and color
    buttonList[id]->setButtonColor(alliance);

    returnData.data = buttonCount;

    return returnData;
  }

  evError preautoUI::addIcon(uint id, iconType iconID, evColor iconColor)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //The error returned by the setIcon function
    evError returnError;

    //Add the icon
    returnError = buttonList[id]->setIcon(iconID, iconColor);

    //Return any errors from setIcon
    if(returnError != evError::No_Error)
    {
      return returnError;
    }

    return evError::No_Error;
  }

  evError preautoUI::addIcon(uint id, const lv_img_dsc_t *icon, evColor iconColor)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //The error returned by the setIcon function;
    evError returnError;

    //Add the custom icon to the button
    returnError = buttonList[id]->setIcon(icon, iconColor);

    //Return any errors from setIcon
    if(returnError != evError::No_Error)
    {
      return returnError;
    }

    return evError::No_Error;
  }

  evError preautoUI::changeIconColor(uint id, int r, int g, int b)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Convert the rgb values to an evColor
    evColor newColor;

    newColor.rgb(r, g, b);

    //The error returned by the setIcon function;
    evError returnError;

    //Change the icon color
    returnError = buttonList[id]->changeIconColor(newColor);

    //Return any errors from changeIconColor
    if(returnError != evError::No_Error)
    {
      return returnError;
    }

    return evError::No_Error;
  }

  evError preautoUI::changeIconColor(uint id, evColor iconColor)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }
    
    //Change the icon color
    buttonList[id]->changeIconColor(iconColor);

    return evError::No_Error;
  }

  evError preautoUI::addCallbackFunc(uint id, void (*callback)(uint))
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Add the callback function to the button and return its output
    return buttonList[id]->setCallbackFunction(callback);
  }

  evError preautoUI::addTitle(uint id, const char Title[MAX_AUTO_TITLE_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Store title
    buttonList[id]->setTitle(Title);

    return evError::No_Error;
  }

  evError preautoUI::addDescription(uint id, const char Description[MAX_AUTO_DESCRIPTION_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Store Description
    buttonList[id]->setDescription(Description);

    return evError::No_Error;
  }

  evError preautoUI::addAlliance(uint id, allianceType alliance)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Store the alliance of the button
    buttonList[id]->setAlliance(alliance);

    return evError::No_Error;
  }

  evError preautoUI::changeButtonColor(uint id, int r, int g, int b)
  {
    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    evColor newColor;

    newColor.rgb(r, g, b);

    //Change the color of the button
    buttonList[id]->setButtonColor(newColor);

    return evError::No_Error;
  }

  evError preautoUI::changeButtonColor(uint id, color buttonColor)
  {
    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Change the color of the button
    buttonList[id]->setButtonColor(buttonColor);

    return evError::No_Error;
  }

  evError preautoUI::selectButton(uint id, bool doNotShowSettings)
  {
    //Static variable for the close button
    static lv_obj_t *closeButton;

    //Exit if the id corresponds to an out of range value.
    if(id > MAX_AUTO_BUTTON_COUNT)
    {
      return evError::Invalid_Argument_Data;
    }

    //Exit if the UI hasn't been created yet
    if(pageTabView == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Run button callback
    buttonList[id]->selectButton();
    
    //Change the selected ID to the ID of the button
    selectedButtonID = id;
    
    //Deselect the previous button if there was one
    if((id != prevTriggeredButtonID) && prevTriggeredButtonID != UINT_MAX)
    {
      buttonList[prevTriggeredButtonID]->deselectButton();
    }

    //Get the title and description data
    auto titleData = buttonList[id]->getTitle();
    auto descriptionData = buttonList[id]->getDescription();

    //*Display the button info box

    //Clear the button info box timer
    buttonInfoBoxTimer.reset();

    //Create the button info box if there is data to display
    if((descriptionData.errorData == evError::No_Error) && !doNotShowSettings)
    {
      //Get title and description
      std::string Title = *titleData.data;
      std::string Description = *descriptionData.data;

      //Create the button info box with the title and description data
      buttonInfoBox = lv_msgbox_create(NULL, Title.c_str(), Description.c_str(), NULL, true);
      buttonInfoBoxExists = true;

      //Get the close button
      closeButton = lv_msgbox_get_close_btn(buttonInfoBox);

      //Add an event to the button to mark the button info box as closed when pressed
      lv_obj_add_event_cb(closeButton, closeButtonPressed, LV_EVENT_ALL, NULL);

      //Center the button info box on the screen
      lv_obj_center(buttonInfoBox);

      /* Create an event on the button info box timer that will delete the box after
      the user specified time */
      buttonInfoBoxTimer.event(closeInfoButtonBox, UI.autoSelector.getDisplayTime());
    }

    //Force the screen to redraw
    lv_obj_invalidate(pageTabView);

    //Store the button ID as the previously triggered button ID
    prevTriggeredButtonID = id;

    return evError::No_Error;
  }

  evError preautoUI::selectTab(uint id)
  {
    //*Make sure the tab exists
    if(pageTabs.size() > id+1)
    {
      return evError::Invalid_Argument_Data;
    }

    if(pageTabs[id] == nullptr)
    {
      return evError::Object_Does_Not_Exist;
    }

    //Select the tab
    lv_tabview_set_act(pageTabView, id, LV_ANIM_ON);

    return evError::No_Error;
  }

  void preautoUI::setDisplayTime(uint32_t time)
  {
    //Make sure LVGL has started
    startLVGL();

    buttonInfoDisplayTime = time;
  }

  uint32_t preautoUI::getDisplayTime()
  {
    return buttonInfoDisplayTime;
  }

  uint preautoUI::getProgNumber()
  {
    return selectedButtonID;
  }

  uint preautoUI::getButtonCount()
  {
    return buttonCount;
  }

  void preautoUI::showPreautoUI(bool status)
  {
    //Show or hide the UI based on the input
    if(status)
    {
      lv_obj_clear_flag(pageTabView, LV_OBJ_FLAG_HIDDEN);
    }

    else
    {
      lv_obj_add_flag(pageTabView, LV_OBJ_FLAG_HIDDEN);
    }
  }
} // namespace evAPI