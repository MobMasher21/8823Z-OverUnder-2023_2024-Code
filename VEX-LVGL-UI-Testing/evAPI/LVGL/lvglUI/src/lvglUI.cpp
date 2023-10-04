/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       lvglUI.cpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Backend code for the UI.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/lvglUI.h"
#include "../include/button.h"
#include "../../../Common/include/evNamespace.h"
#include "../../../Common/include/constantObjects.h"
#include "../../../Common/include/evPatch.h"
#include "../../../Common/include/vexPrivateRebuild.h"

LV_IMG_DECLARE(Skills_Icon)
LV_IMG_DECLARE(Left_Arrow)
LV_IMG_DECLARE(Right_Arrow)
LV_IMG_DECLARE(Exclamation_Points)

namespace evAPI
{
  lvglUI UI = lvglUI();

  //!AUTO SELECTOR

  button * buttonList[MAX_AUTO_BUTTON_COUNT];

  int selectedButtonID = 0;

  //*Preauto UI objects
  //Page tabs
  lv_obj_t * autoPageTabs;
  lv_obj_t * autoTabObjects[MAX_AUTO_TAB_COUNT];
  char autoTabNames[MAX_AUTO_TAB_NAME_LENGTH][MAX_AUTO_TAB_COUNT];
  uint autoTabNameLength[MAX_AUTO_TAB_COUNT];

  //Buttons
  lv_obj_t * selectorButtons[MAX_AUTO_BUTTON_COUNT];
  lv_obj_t * selectorButtonIDLabel[MAX_AUTO_BUTTON_COUNT];
  lv_obj_t * selectorButtonTitle[MAX_AUTO_BUTTON_COUNT];
  lv_style_t buttonStyle[MAX_AUTO_BUTTON_COUNT];

  //Icons
  lv_obj_t * buttonIconObject[MAX_AUTO_BUTTON_COUNT];
  lv_color_t buttonIconColor[MAX_AUTO_BUTTON_COUNT];

  int prevTriggeredButtonID = -1;

  //Button info box
  lv_obj_t * buttonInfoBox;
  timer buttonInfoBoxTime = timer();

  void closeInfoButtonBox()
  {
    lv_msgbox_close(buttonInfoBox);
  }

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
    //Get the amount of tabs needed.
    uint8_t tabCount = floor(UI.getFinalButtonID() / 8);

    //Create the tabview object that stores all the tabs
    autoPageTabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 35);

    //*Create the tabs
    for(uint8_t i = 0; i < (tabCount + 1); i++)
    {
      //If no name is  for the tab
      if(autoTabNameLength[i] == 0)
      {
        char * name;
        asprintf(&name, "Tab %d", (i+1));
        autoTabObjects[i] = lv_tabview_add_tab(autoPageTabs, name);
      }

      //If the tab has a custom name
      else
      {
        char singleTabName[MAX_AUTO_TAB_NAME_LENGTH];

        //Copy over the tab name
        for(uint ii = 0; ii < autoTabNameLength[i]+1; ii++)
        {
          singleTabName[ii] = autoTabNames[ii][i];
        }

        autoTabObjects[i] = lv_tabview_add_tab(autoPageTabs, singleTabName);
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
        selectorButtons[currentButton] = lv_btn_create(autoTabObjects[buttonTab]);

        //Give the buttons a size
        lv_obj_set_width(selectorButtons[currentButton], AUTO_BUTTON_SIZE);
        lv_obj_set_height(selectorButtons[currentButton], AUTO_BUTTON_SIZE);

        //Set the location of each button
        lv_obj_set_x(selectorButtons[currentButton], ((AUTO_BUTTON_SIZE + AUTO_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + AUTO_BUTTON_X_OFFSET);
        lv_obj_set_y(selectorButtons[currentButton], ((AUTO_BUTTON_SIZE + AUTO_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + AUTO_BUTTON_Y_OFFSET);
        
        //Create a label object on the button to store the ID of the button
        selectorButtonIDLabel[currentButton] = lv_label_create(selectorButtons[currentButton]);
        lv_label_set_text_fmt(selectorButtonIDLabel[currentButton], "%d", currentButton);
        lv_obj_add_flag(selectorButtonIDLabel[currentButton], LV_OBJ_FLAG_HIDDEN);

        //Add an event to run the button pressing code when the button is touched
        lv_obj_add_event_cb(selectorButtons[currentButton], autoButtonPressFunc, LV_EVENT_ALL, NULL);

        //*Create a color for the button
        lv_color_t buttonColorLVGL = lv_color_hex(buttonList[currentButton]->buttonColor.rgb());

        //Create a style for the button with that color
        lv_style_init(&buttonStyle[currentButton]);
        lv_style_set_bg_opa(&buttonStyle[currentButton], LV_OPA_100);
        lv_style_set_bg_color(&buttonStyle[currentButton], buttonColorLVGL);
        lv_style_set_outline_width(&buttonStyle[currentButton], 2);
        lv_style_set_outline_opa(&buttonStyle[currentButton], 0);

        //Set the outline color of the button
        #if REDEFINE_COLORS
          lv_style_set_outline_color(&buttonStyle[currentButton], lv_color_hex(ClrLightGrey.rgb()));
        #else
          lv_style_set_outline_color(&buttonStyle[currentButton], lv_color_hex(vexClrLightGrey.rgb()));
        #endif

        //Apply that style to the button
        lv_obj_add_style(selectorButtons[currentButton], &buttonStyle[currentButton], LV_PART_MAIN);

        //*Add title to button
        if(buttonList[currentButton]->titleLength > 0) 
        {
          //Create a label to store the title for the button
          selectorButtonTitle[currentButton] = lv_label_create(selectorButtons[currentButton]);
          lv_label_set_text_fmt(selectorButtonTitle[currentButton], "%s", buttonList[currentButton]->Title);
          lv_obj_add_flag(selectorButtons[currentButton], LV_OBJ_FLAG_OVERFLOW_VISIBLE);
          lv_obj_align_to(selectorButtonTitle[currentButton], selectorButtons[currentButton],  LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
        }

        //*Add an icon to the button
        //-2 is custom icon. -1 is no icon. 0 or greater is builtin icons.

        //Add a custom icon to the button
        if(buttonList[currentButton]->iconID == -2)
        {
          //Create an image object
          buttonIconObject[currentButton] = lv_img_create(selectorButtons[currentButton]);
          buttonIconColor[currentButton] = lv_color_hex(buttonList[currentButton]->iconColor.rgb());

          //Set the image data on the button
          lv_img_set_src(buttonIconObject[currentButton], &buttonList[currentButton]->buttonIconCustom);

          //Align the image with the button
          lv_obj_align_to(buttonIconObject[currentButton], selectorButtons[currentButton], LV_ALIGN_CENTER, 0, 0);

          //Set color parameters for the icon.
          lv_obj_set_style_img_recolor_opa(buttonIconObject[currentButton], LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonIconObject[currentButton], buttonIconColor[currentButton], 0);
        }

        //Add a builtin icon to the button.
        else if(buttonList[currentButton]->iconID > -1)
        {
          //Create an image object
          buttonIconObject[currentButton] = lv_img_create(selectorButtons[currentButton]);
          buttonIconColor[currentButton] = lv_color_hex(buttonList[currentButton]->iconColor.rgb());

          //Apply the builtin icon to the button
          switch(buttonList[currentButton]->iconID)
          {
            case SKILLS_ICON:
              lv_img_set_src(buttonIconObject[currentButton], &Skills_Icon);
              break;
            
            case LEFT_ARROW:
              lv_img_set_src(buttonIconObject[currentButton], &Left_Arrow);
              break;

            case RIGHT_ARROW:
              lv_img_set_src(buttonIconObject[currentButton], &Right_Arrow);
              break;

            case EXCLAMATION_POINTS:
              lv_img_set_src(buttonIconObject[currentButton], &Exclamation_Points);
              break;
          }

          //Align the icon with the button
          lv_obj_align_to(buttonIconObject[currentButton], selectorButtons[currentButton], LV_ALIGN_CENTER, 0, 0);

          //Set color parameters for the icon
          lv_obj_set_style_img_recolor_opa(buttonIconObject[currentButton], LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonIconObject[currentButton], buttonIconColor[currentButton], 0);
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
    lv_obj_invalidate(autoPageTabs); 
    this_thread::sleep_for(50);
  }

  lvglUI::lvglUI()
  {
    //Make sure the name length for each tab is 0
    for(uint i = 0; i < MAX_AUTO_TAB_COUNT; i++)
    {
      autoTabNameLength[i] = 0;
    }
  }
  
  lvglUI::~lvglUI()
  {}

  void lvglUI::addButtonCore(int id)
  {
    //Exit if a button already exists at that ID
    if(buttonList[id] != nullptr)
    {
      return;
    }

    //Create a new button
    buttonList[id] = new button;
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
    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Store the length of the title
    buttonList[id]->titleLength = strlen(Title);

    //Store the title
    for(uint i = 0; i < strlen(Title); i++)
    {
      buttonList[id]->Title[i] = Title[i];
    }

    return false;
  }

  bool lvglUI::addDescription(int id, const char Description[MAX_AUTO_DESCRIPTION_LENGTH])
  {
    //Exit if there isn't a button at the selected ID
    if(buttonList[id] == nullptr)
    {
      return true;
    }

    //Store the length of the description
    buttonList[id]->descriptionLength = strlen(Description);

    //Store the description
    for(uint i = 0; i < strlen(Description); i++)
    {
      buttonList[id]->Description[i] = Description[i];
    }

    return false;
  }

  bool lvglUI::setAutoTabName(int id, const char Name[MAX_AUTO_TAB_NAME_LENGTH])
  {
    //Store the length of the name
    int nameLength = strlen(Name);
    autoTabNameLength[id] = nameLength;

    //Store the name
    for(uint i = 0; i < nameLength; i++)
    {
      autoTabNames[i][id] = Name[i];
    }
    
    return false;
  }

  bool lvglUI::addAlliance(int id, allianceType alliance)
  {
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
    lv_style_set_bg_color(&buttonStyle[id], lv_color_make(r, g, b));

    //Force the UI to redraw
    lv_obj_invalidate(autoPageTabs);

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
    lv_style_set_bg_color(&buttonStyle[id], lv_color_hex(buttonColor.rgb()));

    //Force the UI to redraw
    lv_obj_invalidate(autoPageTabs);
    
    return 0;
  }

  void lvglUI::selectButton(int id, bool doNotShowSettings)
  {
    //Exit if there the UI hasn't been created yet
    if(autoPageTabs == nullptr)
    {
      return;
    }

    //Run button callback
    if(buttonList[id]->buttonCallback != nullptr)
    {
      buttonList[id]->buttonCallback(id);
    }
    
    //Change the selected ID to the ID of the button
    progMode = id;

    //Clear the button info box timer
    buttonInfoBoxTime = 0;
    
    //*Highlight the button if it isn't already highlighted
    if(id != prevTriggeredButtonID)
    {
      //Show the boarder for the button
      lv_style_set_outline_opa(&buttonStyle[id], 255);

      //Remove the boarder on the previously selected button.
      if(prevTriggeredButtonID != -1)
      {
        lv_style_set_outline_opa(&buttonStyle[prevTriggeredButtonID], 0);
      }
    }

    //*Display the button info box
    if(buttonList[id]->descriptionLength > 0 && !doNotShowSettings)
    {
      //Create the button info box with the title and description data
      buttonInfoBox = lv_msgbox_create(NULL, buttonList[id]->Title, buttonList[id]->Description, NULL, false);

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
    lv_obj_invalidate(autoPageTabs);

    //Store the button ID as the previously triggered button ID
    prevTriggeredButtonID = id;
  }

  void lvglUI::selectTab(int id)
  {
    lv_tabview_set_act(autoPageTabs, id, LV_ANIM_ON);
  }

  void lvglUI::setDisplayTime(int time)
  {
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
  brainReadOut * matchDisplayData[MAX_MATCH_DATA_COUNT];

  //Match UI tab objects
  lv_obj_t * matchPageTabs;
  lv_obj_t * matchTabObjects[MAX_MATCH_TAB_COUNT];
  char matchTabNames[MAX_MATCH_TAB_NAME_LENGTH][MAX_MATCH_TAB_COUNT];
  uint matchTabNameLength[MAX_MATCH_TAB_COUNT];

  //Match display objects
  lv_obj_t * matchDisplays[MAX_MATCH_DATA_COUNT];
  lv_obj_t * matchDisplayIDLabel[MAX_MATCH_DATA_COUNT];
  lv_obj_t * matchDisplayTitle[MAX_MATCH_DATA_COUNT];
  lv_style_t matchDisplayStyle[MAX_MATCH_DATA_COUNT];

  //Data on what objects have data that needs to be updated
  uint8_t matchDisplaysWithData[MAX_MATCH_DATA_COUNT];
  uint8_t lastMatchDisplayWithData = 0;

  void lvglUI::matchUISetup()
  {
    //The amount of tabs needed for the match UI
    uint8_t tabCount = floor(finalMatchDisplayID / 8);

    //Create the match UI tabview
    matchPageTabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 35);

    //*Create Match UI Tabs
    for(uint8_t i = 0; i < (tabCount + 1); i++)
    {
      //No name
      if(matchTabNameLength[i] == 0)
      {
        char * name;
        asprintf(&name, "Tab %d", (i+1));
        matchTabObjects[i] = lv_tabview_add_tab(matchPageTabs, name);
      }

      //Custom name
      else
      {
        char singleTabName[MAX_MATCH_TAB_NAME_LENGTH];

        //Copy the name data
        for(uint ii = 0; ii < matchTabNameLength[i]+1; ii++)
        {
          singleTabName[ii] = matchTabNames[ii][i];
        }

        matchTabObjects[i] = lv_tabview_add_tab(matchPageTabs, singleTabName);
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
      if(matchDisplayData[currentDisplay] != nullptr)
      {
        //Create the brain display
        matchDisplays[currentDisplay] = lv_btn_create(matchTabObjects[buttonTab]);
        lv_obj_clear_flag(matchDisplays[currentDisplay], LV_OBJ_FLAG_CLICKABLE);

        //Set the size of for the brain display
        lv_obj_set_width(matchDisplays[currentDisplay], MATCH_BUTTON_X_SIZE);
        lv_obj_set_height(matchDisplays[currentDisplay], MATCH_BUTTON_Y_SIZE);

        //Set the location of the brain display
        lv_obj_set_x(matchDisplays[currentDisplay], ((MATCH_BUTTON_X_SIZE + MATCH_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + MATCH_BUTTON_X_OFFSET);
        lv_obj_set_y(matchDisplays[currentDisplay], ((MATCH_BUTTON_Y_SIZE + MATCH_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + MATCH_BUTTON_Y_OFFSET);
        
        //Create a label to store the ID of the brain display
        matchDisplayIDLabel[currentDisplay] = lv_label_create(matchDisplays[currentDisplay]);
        lv_label_set_text_fmt(matchDisplayIDLabel[currentDisplay], "%d", currentDisplay);
        lv_obj_add_flag(matchDisplayIDLabel[currentDisplay], LV_OBJ_FLAG_HIDDEN);

        //*Create a color for the brain display
        lv_color_t matchDisplayLVGL = lv_color_hex(matchDisplayData[currentDisplay]->graphColor.rgb());

        //Set the style of the brain display with that color
        lv_style_init(&matchDisplayStyle[currentDisplay]);
        lv_style_set_bg_opa(&matchDisplayStyle[currentDisplay], LV_OPA_100);
        lv_style_set_bg_color(&matchDisplayStyle[currentDisplay], matchDisplayLVGL);

        //Apply the style
        lv_obj_add_style(matchDisplays[currentDisplay], &matchDisplayStyle[currentDisplay], LV_PART_MAIN);

        //Create a label to store text on the brain display
        matchDisplayTitle[currentDisplay] = lv_label_create(matchDisplays[currentDisplay]);
        lv_obj_add_flag(matchDisplays[currentDisplay], LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_align_to(matchDisplayTitle[currentDisplay], matchDisplays[currentDisplay],  LV_ALIGN_LEFT_MID, -7, 0);

        //*Add text to the brain display
        //String to store data for the brain display if it is a floating point number
        std::string dataString;
        
        //Select the type of data the is being displayed and print out its data
        switch(matchDisplayData[currentDisplay]->dataType)
        {
          default:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s",
              matchDisplayData[currentDisplay]->Name
            );
            break;

          case brainDataType::INT:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%i",
              matchDisplayData[currentDisplay]->Name,
              *(int*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case brainDataType::UINT:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%i",
              matchDisplayData[currentDisplay]->Name,
              *(uint*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case brainDataType::LONG:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%lu",
              matchDisplayData[currentDisplay]->Name,
              *(long*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::ULONG:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%lu",
              matchDisplayData[currentDisplay]->Name,
              *(ulong*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case brainDataType::FLOAT:
            dataString = evPatch::to_string(*(float*)matchDisplayData[currentDisplay]->displayData);

            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%s",
              matchDisplayData[currentDisplay]->Name,
              dataString.c_str()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::DOUBLE:
            dataString = evPatch::to_string(*(double*)matchDisplayData[currentDisplay]->displayData);

            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%s",
              matchDisplayData[currentDisplay]->Name,
              dataString.c_str()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::FUNC_INT:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%i",
              matchDisplayData[currentDisplay]->Name,
              (*matchDisplayData[currentDisplay]->funcInt)()
            );
            matchDisplaysWithData[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::FUNC_DOUBLE:
            dataString = evPatch::to_string((*matchDisplayData[currentDisplay]->funcDouble)());

            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%s",
              matchDisplayData[currentDisplay]->Name,
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
    //Exit if there isn't a brain display at the selected ID
    if(matchDisplayData[id] != nullptr)
    {
      return 1;
    }

    //Create the brain display
    matchDisplayData[id] = new brainReadOut;

    //Store the length of the name
    matchDisplayData[id]->nameLength = strlen(name);

    //Store the name
    for(uint8_t i = 0; i < matchDisplayData[id]->nameLength; i++)
    {
      matchDisplayData[id]->Name[i] = name[i];
    }

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
    //Exit if there isn't a brain display at the selected ID
    if(matchDisplayData[id] == nullptr)
    {
      return 1;
    }

    //Set the color of the brain display
    matchDisplayData[id]->graphColor.rgb(r, g, b);

    return 0;
  }

  bool lvglUI::setBrainDisplayColor(int id, color Color)
  {
    //Exit if there isn't a brain display at the selected ID
    if(matchDisplayData[id] == nullptr)
    {
      return 1;
    }

    //Set the color of the brain display
    matchDisplayData[id]->graphColor = Color;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, void *data, brainDataType inputDataType)
  {
    //Exit if there isn't a brain display at the selected ID
    if(matchDisplayData[id] == nullptr)
    {
      return 1;
    }

    //Store a pointer to the data and the type of data
    matchDisplayData[id]->displayData = data;
    matchDisplayData[id]->dataType = inputDataType;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, int (*callback)())
  {
    //Exit if there isn't a brain display at the selected ID
    if(matchDisplayData[id] == nullptr)
    {
      return 1;
    }

    //Store a pointer to the function and the type the function returns
    matchDisplayData[id]->funcInt = callback;
    matchDisplayData[id]->dataType = brainDataType::FUNC_INT;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, double (*callback)())
  {
    //Exit if there isn't a brain display at the selected ID
    if(matchDisplayData[id] == nullptr)
    {
      return 1;
    }

    //Store a pointer to the function and the type the function returns
    matchDisplayData[id]->funcDouble = callback;
    matchDisplayData[id]->dataType = brainDataType::FUNC_DOUBLE;

    return 0;
  }

  bool lvglUI::setMatchTabName(int id, const char Name[MAX_MATCH_TAB_NAME_LENGTH])
  {
    //Get the length of the name
    int nameLength = strlen(Name);

    //Store the length of the name
    matchTabNameLength[id] = nameLength;

    //Store the name
    for(uint i = 0; i < nameLength; i++)
    {
      matchTabNames[i][id] = Name[i];
    }
    
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
      //*Store the competition mode
      if(!Competition.isEnabled())
      {
        compMode = disabled;
      }

      else if(Competition.isDriverControl())
      {
        compMode = driverControl;
      }

      else
      {
        compMode = autonomousControl;
      }

      //*Update what UI is shown if the competition mode changes
      if(compMode != prevCompMode)
      {
        //Show preauto UI
        if(compMode == disabled)
        {
          lv_obj_add_flag(matchPageTabs, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(autoPageTabs, LV_OBJ_FLAG_HIDDEN);
        }

        //Show Match UI
        else
        {
          lv_obj_add_flag(autoPageTabs, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(matchPageTabs, LV_OBJ_FLAG_HIDDEN);
        }
      }

      //*Update the brain displays in the Match UI
      if(compMode == driverControl)
      {
        //The current brain display being worked on
        uint currentDisplay;
        
        //*Loop for all the brain displays with data
        for(uint8_t i = 0; i < lastMatchDisplayWithData-1; i++)
        {
          //Store the ID of the display being processed
          currentDisplay = matchDisplaysWithData[i];

          //*Refresh the text on the brain display
          switch(matchDisplayData[currentDisplay]->dataType)
          {
            //No data, just a name
            default:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s",
                matchDisplayData[currentDisplay]->Name
              );
              break;

            //Data as an int
            case brainDataType::INT:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%i",
                matchDisplayData[currentDisplay]->Name,
                *(int*)matchDisplayData[currentDisplay]->displayData
              );
              break;
            
            //Data as a uint
            case brainDataType::UINT:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%i",
                matchDisplayData[currentDisplay]->Name,
                *(uint*)matchDisplayData[currentDisplay]->displayData
              );
              break;
            
            //Data as a long
            case brainDataType::LONG:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%lu",
                matchDisplayData[currentDisplay]->Name,
                *(long*)matchDisplayData[currentDisplay]->displayData
              );
              break;

            //Data as a ulong
            case brainDataType::ULONG:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%lu",
                matchDisplayData[currentDisplay]->Name,
                *(ulong*)matchDisplayData[currentDisplay]->displayData
              );
              break;
            
            //Data as a float
            case brainDataType::FLOAT:
              //Convert data to a string. LVGL can't display floating point numbers
              dataString = evPatch::to_string(*(float*)matchDisplayData[currentDisplay]->displayData);

              //Refresh data
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%s",
                matchDisplayData[currentDisplay]->Name,
                dataString.c_str()
              );
              break;

            //Data as a double
            case brainDataType::DOUBLE:
              //Convert data to a string. LVGL can't display float point numbers
              dataString = evPatch::to_string(*(double*)matchDisplayData[currentDisplay]->displayData);

              //Refresh data
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%s",
                matchDisplayData[currentDisplay]->Name,
                dataString.c_str()
              );
              break;

            //Data from a function returning an int
            case brainDataType::FUNC_INT:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%i",
                matchDisplayData[currentDisplay]->Name,
                (*matchDisplayData[currentDisplay]->funcInt)()
              );
              break;

            //Data from a function returning a double
            case brainDataType::FUNC_DOUBLE:
              //Convert data to a string. LVGL can't display floating point numbers
              dataString = evPatch::to_string((*matchDisplayData[currentDisplay]->funcDouble)());

              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%s",
                matchDisplayData[currentDisplay]->Name,
                dataString.c_str()
              );
              break;
          }
        }
      }

      //Store the competition mode to be used as the previous competition mode.
      prevCompMode = compMode;
      
      //Sleep to allow the brain to do other tasks
      this_thread::sleep_for(20);
    }

    return 0;
  }

  //extern lv_disp_t * lvglDisplay;

  void lvglUI::startUIThreads()
  {
    vex_lvgl_init();
    autoSelectorSetup();
    //matchUISetup();

    UIThread = new thread(UIThreadFunc);
  }
} // namespace evAPI