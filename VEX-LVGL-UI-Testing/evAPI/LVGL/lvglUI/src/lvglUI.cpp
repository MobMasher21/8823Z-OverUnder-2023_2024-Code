/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       lvglUI.cpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Backend code for the UI.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <vector>
#include "../include/lvglUI.h"
#include "../include/preautoButton.h"
#include "../include/tabGroup.h"
#include "../../../Common/include/evNamespace.h"
#include "../../../Common/include/generalFunctions.h"
#include "../../../Common/include/constantObjects.h"
#include "../../../Common/include/evPatch.h"

LV_IMG_DECLARE(Skills_Icon)
LV_IMG_DECLARE(Left_Arrow)
LV_IMG_DECLARE(Right_Arrow)
LV_IMG_DECLARE(Exclamation_Points)

namespace evAPI
{
  /**
   * @brief The core LVGL UI object. All user actions run through it.
  */
  lvglUI UI = lvglUI();

  //!AUTO SELECTOR
  //*Preauto UI objects
  //Tab group that houses the preauto UI
  tabGroup autoTab;

  //Buttons
  preautoButton *buttonList[MAX_AUTO_BUTTON_COUNT]; //evAPI button objects

  //ID of the previous button that was pressed
  int prevTriggeredButtonID = -1;

  //Button info box
  lv_obj_t *buttonInfoBox;

  //Timer used to automatically delete the button info box
  timer buttonInfoBoxTime = timer();

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
      lv_msgbox_close(buttonInfoBox);
      buttonInfoBoxExists = false;
    }
  }

  /**
   * @brief The function that is run whenever a button in the preauto UI is pressed.
   * It stores the button that was pressed, changes the UI to show the new button that was pressed,
   * and creates the button info box.
   * @param event An LVGL event that is tied to the button that was pressed.
  */
  static void autoButtonPressFunc(lv_event_t * event)
  {
    //Get info about the button that was interacted with
    lv_event_code_t eventCode = lv_event_get_code(event);
    lv_obj_t * triggeredButton = lv_event_get_target(event);

    //Only run if the button was pressed
    if(eventCode == LV_EVENT_CLICKED)
    {
      //Get ID from button text.
      lv_obj_t * buttonIDLabel = lv_obj_get_child(triggeredButton, 0);
      int buttonID = strtol(lv_label_get_text(buttonIDLabel), nullptr, 10);

      //Select the button and display the button info box.
      UI.selectButton(buttonID, false);
    }
  }

  void lvglUI::autoSelectorSetup()
  {
    //The amount of tabs needed for the preauto UI
    uint tabCount = floor(finalMatchDisplayID / 8) + 1;

    //The amount of tabs the user has created
    uint userCreatedTabCount = autoTab.getTabCount();

    //If there weren't enough tabs created by the user, create enough to fit all the buttons
    if(tabCount > userCreatedTabCount)
    {
      for(size_t i = 0; i < (tabCount - userCreatedTabCount); i++)
      {
        autoTab.addTab();
      }
    }
    
    //*Create the buttons
    //Parameters for the button placement in its tab
    int verticalOffsetMultiplier = 1;
    int horizontalOffsetMultiplier = 1;
    int buttonTab = 0;

    //Create button loop
    for(uint currentButton = 0; currentButton < (UI.getFinalButtonID() + 1); currentButton++)
    {
      //Create a button if its ID contains data
      if(buttonList[currentButton] != nullptr)
      {
        //*Create the button
        buttonList[currentButton]->LVGLButton = lv_btn_create(autoTab.pageTabs[buttonTab]);

        //Give the buttons a size
        lv_obj_set_width(buttonList[currentButton]->LVGLButton, AUTO_BUTTON_SIZE);
        lv_obj_set_height(buttonList[currentButton]->LVGLButton, AUTO_BUTTON_SIZE);

        //Set the location of each button
        lv_obj_set_x(buttonList[currentButton]->LVGLButton, ((AUTO_BUTTON_SIZE + AUTO_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + AUTO_BUTTON_X_OFFSET);
        lv_obj_set_y(buttonList[currentButton]->LVGLButton, ((AUTO_BUTTON_SIZE + AUTO_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + AUTO_BUTTON_Y_OFFSET);

        //Create a label object on the button to store the ID of the button
        buttonList[currentButton]->LVGLButtonID = lv_label_create(buttonList[currentButton]->LVGLButton);
        lv_label_set_text_fmt(buttonList[currentButton]->LVGLButtonID, "%d", currentButton);
        lv_obj_add_flag(buttonList[currentButton]->LVGLButtonID, LV_OBJ_FLAG_HIDDEN);

        //Add an event to run the button pressing code when the button is touched
        lv_obj_add_event_cb(buttonList[currentButton]->LVGLButton, autoButtonPressFunc, LV_EVENT_ALL, NULL);

        //*Create a color for the button
        lv_color_t buttonColorLVGL = lv_color_hex(buttonList[currentButton]->buttonColor.rgb());

        //Create a style for the button with that color
        lv_style_init(&buttonList[currentButton]->LVGLButtonStyle);
        lv_style_set_bg_opa(&buttonList[currentButton]->LVGLButtonStyle, LV_OPA_100);
        lv_style_set_bg_color(&buttonList[currentButton]->LVGLButtonStyle, buttonColorLVGL);
        lv_style_set_outline_width(&buttonList[currentButton]->LVGLButtonStyle, 2);
        lv_style_set_outline_opa(&buttonList[currentButton]->LVGLButtonStyle, 0);

        //Set the outline color of the button
        #if REDEFINE_COLORS
          lv_style_set_outline_color(&buttonList[currentButton]->LVGLButtonStyle, lv_color_hex(ClrLightGrey.rgb()));
        #else
          lv_style_set_outline_color(&buttonList[currentButton]->LVGLButtonStyle, lv_color_hex(vexClrLightGrey.rgb()));
        #endif

        //Apply that style to the button
        lv_obj_add_style(buttonList[currentButton]->LVGLButton, &buttonList[currentButton]->LVGLButtonStyle, LV_PART_MAIN);
        
        //*Add title to button
        if(buttonList[currentButton]->Title.length() > 0) 
        {
          //Create a label to store the title for the button
          buttonList[currentButton]->LVGLButtonTitle = lv_label_create(buttonList[currentButton]->LVGLButton);
          lv_label_set_text_fmt(buttonList[currentButton]->LVGLButtonTitle, "%s", buttonList[currentButton]->Title.c_str());
          lv_obj_add_flag(buttonList[currentButton]->LVGLButton, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
          lv_obj_align_to(buttonList[currentButton]->LVGLButtonTitle, buttonList[currentButton]->LVGLButton,  LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
        }

        //*Add an icon to the button
        //-2 is custom icon. -1 is no icon. 0 or greater is builtin icons.

        //Add a custom icon to the button
        if(buttonList[currentButton]->iconID == -2)
        {
          //Create an image object
          buttonList[currentButton]->LVGLButtonIcon = lv_img_create(buttonList[currentButton]->LVGLButton);
          buttonList[currentButton]->LVGLButtonIconColor = lv_color_hex(buttonList[currentButton]->iconColor.rgb());

          //Set the image data on the button
          lv_img_set_src(buttonList[currentButton]->LVGLButtonIcon, &buttonList[currentButton]->buttonIconCustom);

          //Align the image with the button
          lv_obj_align_to(buttonList[currentButton]->LVGLButtonIcon, buttonList[currentButton]->LVGLButton, LV_ALIGN_CENTER, 0, 0);

          //Set color parameters for the icon.
          lv_obj_set_style_img_recolor_opa(buttonList[currentButton]->LVGLButtonIcon, LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonList[currentButton]->LVGLButtonIcon, buttonList[currentButton]->LVGLButtonIconColor, 0);
        }

        //Add a builtin icon to the button.
        else if(buttonList[currentButton]->iconID > -1)
        {
          //Create an image object
          buttonList[currentButton]->LVGLButtonIcon = lv_img_create(buttonList[currentButton]->LVGLButton);
          buttonList[currentButton]->LVGLButtonIconColor = lv_color_hex(buttonList[currentButton]->iconColor.rgb());

          //Apply the builtin icon to the button
          switch(buttonList[currentButton]->iconID)
          {
            case SKILLS_ICON:
              lv_img_set_src(buttonList[currentButton]->LVGLButtonIcon, &Skills_Icon);
              break;
            
            case LEFT_ARROW:
              lv_img_set_src(buttonList[currentButton]->LVGLButtonIcon, &Left_Arrow);
              break;

            case RIGHT_ARROW:
              lv_img_set_src(buttonList[currentButton]->LVGLButtonIcon, &Right_Arrow);
              break;

            case EXCLAMATION_POINTS:
              lv_img_set_src(buttonList[currentButton]->LVGLButtonIcon, &Exclamation_Points);
              break;
          }

          //Align the icon with the button
          lv_obj_align_to(buttonList[currentButton]->LVGLButtonIcon, buttonList[currentButton]->LVGLButton, LV_ALIGN_CENTER, 0, 0);

          //Set color parameters for the icon
          lv_obj_set_style_img_recolor_opa(buttonList[currentButton]->LVGLButtonIcon, LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonList[currentButton]->LVGLButtonIcon, buttonList[currentButton]->LVGLButtonIconColor, 0);
        }
      }

      //*Select the next position for a button
      //Go to the next row
      if(horizontalOffsetMultiplier >= 4)
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier++;
      }

      //Go to the next colum
      else
      {
        horizontalOffsetMultiplier++;
      }

      //Go to the next tab
      if(verticalOffsetMultiplier > 2)
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier = 1;
        buttonTab++;
      }
    }

    //Force a redraw of the auto selection UI to make sure all assets show up.
    lv_obj_invalidate(autoTab.pageTabView);
    this_thread::sleep_for(50);
  }

  lvglUI::lvglUI()
  {}
  
  lvglUI::~lvglUI()
  {}

  void lvglUI::addButtonCore(int id)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if a button already exists at that ID
    if(buttonList[id] != nullptr)
    {
      return;
    }

    //Create a new button
    buttonList[id] = new preautoButton;
    buttonList[id]->buttonCallback = NULL;
    buttonCount++;

    //Set the the id of the final button to this buttons ID if it is greater
    if(id > finalButtonID)
    {
      finalButtonID = id;
    }
  }

  int lvglUI::addButton(int id, int r, int g, int b)
  {
    addButtonCore(id);
    buttonList[id]->buttonColor.rgb(r, g, b);
    return buttonCount;
  }
  
  int lvglUI::addButton(int id, color buttonColor)
  {
    addButtonCore(id);
    buttonList[id]->buttonColor = buttonColor;
    return buttonCount;
  }

  int lvglUI::addButton(int id, allianceType alliance)
  {
    addButtonCore(id);
    buttonList[id]->buttonAlliance = alliance;

    //Add a color based on the robot alliance
    switch(alliance)
    {
      case redAlliance:
        buttonList[id]->buttonColor = red;
        break;
      
      case blueAlliance:
        buttonList[id]->buttonColor = blue;
        break;

      #if REDEFINE_COLORS
        default:
          buttonList[id]->buttonColor = ClrGray;
          break;
      #else
        default:
          buttonList[id]->buttonColor = vexClrGray;
          break;
      #endif
    }

    return buttonCount;
  }

  bool lvglUI::addIcon(int id, int iconID)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Add the icon
    buttonList[id]->iconID = iconID;

    return 0;
  }

  bool lvglUI::addIcon(int id, const lv_img_dsc_t icon)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Add the custom icon to the button
    buttonList[id]->buttonIconCustom = icon;
    buttonList[id]->iconID = -2;

    return 0;
  }

  bool lvglUI::changeIconColor(int id, int r, int g, int b)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Change the icon color
    buttonList[id]->iconColor.rgb(r, g, b);

    return 0;
  }

  bool lvglUI::changeIconColor(int id, color iconColor)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }
    
    //Change the icon color
    buttonList[id]->iconColor = iconColor;

    return 0;
  }

  bool lvglUI::addCallbackFunc(int id, void (*callback)(int))
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Add the callback function to the button
    buttonList[id]->buttonCallback = callback;

    return false;
  }

  bool lvglUI::addTitle(int id, const char Title[MAX_AUTO_TITLE_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Store title
    buttonList[id]->Title = Title;

    return false;
  }

  bool lvglUI::addDescription(int id, const char Description[MAX_AUTO_DESCRIPTION_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Store Description
    buttonList[id]->Description = Description;

    return false;
  }

  bool lvglUI::addAutoTab(const char Name[SELECTOR_TAB_NAME_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Store the name
    autoTab.addTab(Name);

    return false;
  }

  bool lvglUI::addAlliance(int id, allianceType alliance)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Store the alliance of the button
    buttonList[id]->buttonAlliance = alliance;

    return 0;
  }

  bool lvglUI::changeButtonColor(int id, int r, int g, int b)
  {
    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Change the color of the button
    lv_style_set_bg_color(&buttonList[id]->LVGLButtonStyle, lv_color_make(r, g, b));

    //Force the UI to redraw
    lv_obj_invalidate(autoTab.pageTabView);

    return 0;
  }

  bool lvglUI::changeButtonColor(int id, color buttonColor)
  {
    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Change the color of the button
    lv_style_set_bg_color(&buttonList[id]->LVGLButtonStyle, lv_color_hex(buttonColor.rgb()));

    //Force the UI to redraw
    lv_obj_invalidate(autoTab.pageTabView);
    
    return 0;
  }

  void lvglUI::selectButton(int id, bool doNotShowSettings)
  {
    //Exit if there the UI hasn't been created yet
    if(autoTab.pageTabView == nullptr)
    {
      return;
    }

    //Run button callback
    if(buttonList[id]->buttonCallback != nullptr)
    {
      buttonList[id]->buttonCallback(id);
    }
    
    //Change the selected ID to the ID of the button
    selectedButtonID = id;

    //Clear the button info box timer
    buttonInfoBoxTime = 0;
    
    //*Highlight the button if it isn't already highlighted
    if(id != prevTriggeredButtonID)
    {
      //Show the boarder for the button
      lv_style_set_outline_opa(&buttonList[id]->LVGLButtonStyle, 255);

      //Remove the boarder on the previously selected button.
      if(prevTriggeredButtonID != -1)
      {
        lv_style_set_outline_opa(&buttonList[prevTriggeredButtonID]->LVGLButtonStyle, 0);
      }
    }

    //*Display the button info box
    if(buttonList[id]->Description.length() > 0 && !doNotShowSettings)
    {
      //Create the button info box with the title and description data
      buttonInfoBox = lv_msgbox_create(NULL, buttonList[id]->Title.c_str(), buttonList[id]->Description.c_str(), NULL, false);
      buttonInfoBoxExists = true;

      //Center the button info box on the screen
      lv_obj_center(buttonInfoBox);

      //Create an event on the button info box timer that will delete the box after
      //the user specified time
      buttonInfoBoxTime.event(closeInfoButtonBox, UI.getDisplayTime());
    }

    //Set the robot alliance if it is supposed to change
    if(buttonList[id]->buttonAlliance != noChange)
    {
      robotAlliance = buttonList[id]->buttonAlliance;
    }

    //Force the screen to redraw
    lv_obj_invalidate(autoTab.pageTabView);

    //Store the button ID as the previously triggered button ID
    prevTriggeredButtonID = id;
  }

  void lvglUI::selectTab(int id)
  {
    lv_tabview_set_act(autoTab.pageTabView, id, LV_ANIM_ON);
  }

  void lvglUI::setDisplayTime(int time)
  {
    //Make sure LVGL has started
    startLVGL();

    buttonInfoDisplayTime = time;
  }

  int lvglUI::getDisplayTime()
  {
    return buttonInfoDisplayTime;
  }

  int lvglUI::getProgNumber()
  {
    return selectedButtonID;
  }

  uint lvglUI::getButtonCount()
  {
    return buttonCount;
  }

  uint lvglUI::getFinalButtonID()
  {
    return finalButtonID;
  }

  //!Brain Display Setup
  //*Match UI objects
  matchDisplay *matchDisplays[MAX_MATCH_DATA_COUNT];

  //Match UI tab objects
  tabGroup matchTab;

  //Data on what objects have data that needs to be updated
  uint8_t matchDisplaysWithData[MAX_MATCH_DATA_COUNT];
  uint8_t lastMatchDisplayWithData = 0;

  void lvglUI::matchUISetup()
  {
    //The amount of tabs needed for the match UI
    uint8_t tabCount = floor(finalMatchDisplayID / 8) + 1;

    //The amount of tabs the user has created
    uint userCreatedTabCount = matchTab.getTabCount();

    //If there weren't enough tabs created by the user, create enough to fit all the match displays
    if(tabCount > userCreatedTabCount)
    {
      for(size_t i = 0; i < (tabCount - userCreatedTabCount); i++)
      {
        matchTab.addTab();
      }
    }

    //Data on where each brain display should be put
    int verticalOffsetMultiplier = 1;
    int horizontalOffsetMultiplier = 1;
    int buttonTab = 0;
    uint matchDisplayUpdateID = 0;

    //*Create the brain displays
    for(uint currentDisplay = 0; currentDisplay < (finalMatchDisplayID + 1); currentDisplay++)
    {
      //Create brain display if there is data
      if(matchDisplays[currentDisplay] != nullptr)
      {
        //Create the brain display
        matchDisplays[currentDisplay]->LVGLMatchDisplay = lv_btn_create(matchTab.pageTabs[buttonTab]);
        lv_obj_clear_flag(matchDisplays[currentDisplay]->LVGLMatchDisplay, LV_OBJ_FLAG_CLICKABLE);

        //Set the size of for the brain display
        lv_obj_set_width(matchDisplays[currentDisplay]->LVGLMatchDisplay, MATCH_BUTTON_X_SIZE);
        lv_obj_set_height(matchDisplays[currentDisplay]->LVGLMatchDisplay, MATCH_BUTTON_Y_SIZE);

        //Set the location of the brain display
        lv_obj_set_x(matchDisplays[currentDisplay]->LVGLMatchDisplay, ((MATCH_BUTTON_X_SIZE + MATCH_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + MATCH_BUTTON_X_OFFSET);
        lv_obj_set_y(matchDisplays[currentDisplay]->LVGLMatchDisplay, ((MATCH_BUTTON_Y_SIZE + MATCH_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + MATCH_BUTTON_Y_OFFSET);
        
        //Create a label to store the ID of the brain display
        matchDisplays[currentDisplay]->LVGLMatchDisplayIDLabel = lv_label_create(matchDisplays[currentDisplay]->LVGLMatchDisplay);
        lv_label_set_text_fmt(matchDisplays[currentDisplay]->LVGLMatchDisplayIDLabel, "%d", currentDisplay);
        lv_obj_add_flag(matchDisplays[currentDisplay]->LVGLMatchDisplayIDLabel, LV_OBJ_FLAG_HIDDEN);

        //*Create a color for the brain display
        lv_color_t matchDisplayLVGL = lv_color_hex(matchDisplays[currentDisplay]->graphColor.rgb());

        //Set the style of the brain display with that color
        lv_style_init(&matchDisplays[currentDisplay]->LVGLMatchDisplayStyle);
        lv_style_set_bg_opa(&matchDisplays[currentDisplay]->LVGLMatchDisplayStyle, LV_OPA_100);
        lv_style_set_bg_color(&matchDisplays[currentDisplay]->LVGLMatchDisplayStyle, matchDisplayLVGL);

        //Apply the style
        lv_obj_add_style(matchDisplays[currentDisplay]->LVGLMatchDisplay, &matchDisplays[currentDisplay]->LVGLMatchDisplayStyle, LV_PART_MAIN);

        //Create a label to store text on the brain display
        matchDisplays[currentDisplay]->LVGLMatchDisplayTitle = lv_label_create(matchDisplays[currentDisplay]->LVGLMatchDisplay);
        lv_obj_add_flag(matchDisplays[currentDisplay]->LVGLMatchDisplay, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_align_to(matchDisplays[currentDisplay]->LVGLMatchDisplayTitle, matchDisplays[currentDisplay]->LVGLMatchDisplay,  LV_ALIGN_LEFT_MID, -7, 0);

        //*Add text to the brain display
        //String to store data for the brain display if it is a floating point number
        std::string dataString;
        
        //Select the type of data the is being displayed and print out its data
        switch(matchDisplays[currentDisplay]->dataType)
        {
          default:
            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s",
              matchDisplays[currentDisplay]->Name.c_str()
            );
            break;

          case matchDisplayDataType::INT:
            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%i",
              matchDisplays[currentDisplay]->Name.c_str(),
              *(int*)matchDisplays[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case matchDisplayDataType::UINT:
            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%i",
              matchDisplays[currentDisplay]->Name.c_str(),
              *(uint*)matchDisplays[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case matchDisplayDataType::LONG:
            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%lu",
              matchDisplays[currentDisplay]->Name.c_str(),
              *(long*)matchDisplays[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case matchDisplayDataType::ULONG:
            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%lu",
              matchDisplays[currentDisplay]->Name.c_str(),
              *(ulong*)matchDisplays[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case matchDisplayDataType::FLOAT:
            dataString = evPatch::to_string(*(float*)matchDisplays[currentDisplay]->displayData);

            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%s",
              matchDisplays[currentDisplay]->Name.c_str(),
              dataString.c_str()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case matchDisplayDataType::DOUBLE:
            dataString = evPatch::to_string(*(double*)matchDisplays[currentDisplay]->displayData);

            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%s",
              matchDisplays[currentDisplay]->Name.c_str(),
              dataString.c_str()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case matchDisplayDataType::FUNC_INT:
            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%i",
              matchDisplays[currentDisplay]->Name.c_str(),
              (*matchDisplays[currentDisplay]->funcInt)()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case matchDisplayDataType::FUNC_DOUBLE:
            dataString = evPatch::to_string((*matchDisplays[currentDisplay]->funcDouble)());

            lv_label_set_text_fmt(
              matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
              "%s%s",
              matchDisplays[currentDisplay]->Name.c_str(),
              dataString.c_str()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
        }

        matchDisplayUpdateID++;
      }

      //*Select the next position for the brain display
      //Move to the next row
      if(horizontalOffsetMultiplier >= 2)
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier++;
      }

      //Move to the next colum
      else
      {
        horizontalOffsetMultiplier++;
      }

      //Move to the next tab
      if(verticalOffsetMultiplier > 4)
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier = 1;
        buttonTab++;
      }
    }
    
    lastMatchDisplayWithData = matchDisplayUpdateID;
  }

  bool lvglUI::createBrainDisplay(int id, const char name[MAX_MATCH_DATA_NAME_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a brain display at the selected ID
    if(matchDisplays[id] != nullptr)
    {
      return 1;
    }

    //Create the brain display
    matchDisplays[id] = new matchDisplay;

    //Store the name
    matchDisplays[id]->Name = name;

    matchDisplayCount++;

    //Keep track of the largest brain display ID
    if(id > finalMatchDisplayID)
    {
      finalMatchDisplayID = id;
    }

    return 0;
  }

  bool lvglUI::setBrainDisplayColor(int id, int r, int g, int b)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a brain display at the selected ID
    if(matchDisplays[id] == nullptr)
    {
      return 1;
    }

    //Set the color of the brain display
    matchDisplays[id]->graphColor.rgb(r, g, b);

    return 0;
  }

  bool lvglUI::setBrainDisplayColor(int id, color Color)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a brain display at the selected ID
    if(matchDisplays[id] == nullptr)
    {
      return 1;
    }

    //Set the color of the brain display
    matchDisplays[id]->graphColor = Color;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, void *data, matchDisplayDataType inputDataType)
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a brain display at the selected ID
    if(matchDisplays[id] == nullptr)
    {
      return 1;
    }

    //Store a pointer to the data and the type of data
    matchDisplays[id]->displayData = data;
    matchDisplays[id]->dataType = inputDataType;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, int (*callback)())
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a brain display at the selected ID
    if(matchDisplays[id] == nullptr)
    {
      return 1;
    }

    //Store a pointer to the function and the type the function returns
    matchDisplays[id]->funcInt = callback;
    matchDisplays[id]->dataType = matchDisplayDataType::FUNC_INT;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, double (*callback)())
  {
    //Make sure LVGL has started
    startLVGL();

    //Exit if there isn't a brain display at the selected ID
    if(matchDisplays[id] == nullptr)
    {
      return 1;
    }

    //Store a pointer to the function and the type the function returns
    matchDisplays[id]->funcDouble = callback;
    matchDisplays[id]->dataType = matchDisplayDataType::FUNC_DOUBLE;

    return 0;
  }

  bool lvglUI::addMatchTab(const char Name[SELECTOR_TAB_NAME_LENGTH])
  {
    //Make sure LVGL has started
    startLVGL();

    //Store the name
    matchTab.addTab(Name);
    
    return false;
  }

  uint lvglUI::getMatchDisplayCount()
  {
    return matchDisplayCount;
  }

  uint lvglUI::getFinalMatchDisplayID()
  {
    return finalMatchDisplayID;
  }

  int UIThreadFunc()
  {
    //Store the current mode of the competition
    uint8_t compMode = disabled;

    //Make sure the thread updates the screen on the first go by initialising this value to an invalid one
    uint8_t prevCompMode = 4; 

    //String object used for converting floating point numbers to strings for LVGL to display 
    std::string dataString;

    //*Main loop in thread
    while(true)
    {
      //*Set the mode of the UI if manual control is disabled
      if(!UI.isManualControl())
      {
        //Store the competition mode
        compMode = getCompetitionStatus();

        //Update what UI is shown if the competition mode changes
        if(compMode != prevCompMode)
        {
          //Show preauto UI
          if(compMode == disabled)
          {
            UI.setUIMode(UIStates::Preauto_UI);
          }

          //Show Match UI
          else
          {
            UI.setUIMode(UIStates::Match_UI);
          }
        }

        //Store the competition mode to be used as the previous competition mode.
        prevCompMode = compMode;
      }

      //Make sure the UI will update if manual control is disabled
      else
      {
        prevCompMode = 4;
      }

      //*Update the brain displays in the Match UI
      if(UI.getUIMode() == UIStates::Match_UI)
      {
        //The current brain display being worked on
        uint currentDisplay;
        
        //*Loop for all the brain displays with data
        for(uint8_t i = 0; i < lastMatchDisplayWithData-1; i++)
        {
          //Store the ID of the display being processed
          currentDisplay = matchDisplaysWithData[i];

          //*Refresh the text on the brain display
          switch(matchDisplays[currentDisplay]->dataType)
          {
            //No data, just a name
            default:
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s",
                matchDisplays[currentDisplay]->Name.c_str()
              );
              break;

            //Data as an int
            case matchDisplayDataType::INT:
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%i",
                matchDisplays[currentDisplay]->Name.c_str(),
                *(int*)matchDisplays[currentDisplay]->displayData
              );
              break;
            
            //Data as a uint
            case matchDisplayDataType::UINT:
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%i",
                matchDisplays[currentDisplay]->Name.c_str(),
                *(uint*)matchDisplays[currentDisplay]->displayData
              );
              break;
            
            //Data as a long
            case matchDisplayDataType::LONG:
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%lu",
                matchDisplays[currentDisplay]->Name.c_str(),
                *(long*)matchDisplays[currentDisplay]->displayData
              );
              break;

            //Data as a ulong
            case matchDisplayDataType::ULONG:
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%lu",
                matchDisplays[currentDisplay]->Name.c_str(),
                *(ulong*)matchDisplays[currentDisplay]->displayData
              );
              break;
            
            //Data as a float
            case matchDisplayDataType::FLOAT:
              //Convert data to a string. LVGL can't display floating point numbers
              dataString = evPatch::to_string(*(float*)matchDisplays[currentDisplay]->displayData);

              //Refresh data
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%s",
                matchDisplays[currentDisplay]->Name.c_str(),
                dataString.c_str()
              );
              break;

            //Data as a double
            case matchDisplayDataType::DOUBLE:
              //Convert data to a string. LVGL can't display floating point numbers
              dataString = evPatch::to_string(*(double*)matchDisplays[currentDisplay]->displayData);

              //Refresh data
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%s",
                matchDisplays[currentDisplay]->Name.c_str(),
                dataString.c_str()
              );
              break;

            //Data from a function returning an int
            case matchDisplayDataType::FUNC_INT:
              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%i",
                matchDisplays[currentDisplay]->Name.c_str(),
                (*matchDisplays[currentDisplay]->funcInt)()
              );
              break;

            //Data from a function returning a double
            case matchDisplayDataType::FUNC_DOUBLE:
              //Convert data to a string. LVGL can't display floating point numbers
              dataString = evPatch::to_string((*matchDisplays[currentDisplay]->funcDouble)());

              lv_label_set_text_fmt(
                matchDisplays[currentDisplay]->LVGLMatchDisplayTitle,
                "%s%s",
                matchDisplays[currentDisplay]->Name.c_str(),
                dataString.c_str()
              );
              break;
          }
        }
      }
      
      //Sleep to allow the brain to do other tasks
      this_thread::sleep_for(20);
    }

    return 0;
  }

  void lvglUI::startUIThreads()
  {
    //Make sure LVGL has started
    startLVGL();

    //Create the preauto UI
    autoSelectorSetup();

    //Create the match UI
    matchUISetup();

    //Start the UI with the preauto UI enabled.
    UI.setUIMode(UIStates::Preauto_UI);

    //Start the UI thread
    UIThread = new thread(UIThreadFunc);

    //Allow for some time for the UI to initialise
    this_thread::sleep_for(10);
  }

  UIStates lvglUI::getUIMode()
  {
    return UIMode;
  }

  void lvglUI::setUIMode(UIStates mode)
  {
    //Set the UI mode
    UIMode = mode;

    //*Select what elements of the UI are shown or hidden
    switch(mode)
    {
      //Preauto UI
      case UIStates::Preauto_UI:
        //Hide the match UI and enable the preauto UI
        lv_obj_add_flag(matchTab.pageTabView, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(autoTab.pageTabView, LV_OBJ_FLAG_HIDDEN);
        break;

      //Match UI
      case UIStates::Match_UI:
        //Enable the match UI and hide the preauto UI
        lv_obj_clear_flag(matchTab.pageTabView, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(autoTab.pageTabView, LV_OBJ_FLAG_HIDDEN);
        
        //Close the button info box
        closeInfoButtonBox();
        break;

      //Disabled
      default:
        //Hide both the match UI and the preauto UI
        lv_obj_clear_flag(matchTab.pageTabView, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(autoTab.pageTabView, LV_OBJ_FLAG_HIDDEN);

        //Close the button info box
        closeInfoButtonBox();
        break;
    }

    //lv_obj_invalidate(matchTab.pageTabView);
    //lv_obj_invalidate(autoTab.pageTabView);
  }

  void lvglUI::enableManualUIControl(bool value)
  {
    manualUIControlEnabled = value;
  }

  bool lvglUI::isManualControl()
  {
    return manualUIControlEnabled;
  }
} // namespace evAPI