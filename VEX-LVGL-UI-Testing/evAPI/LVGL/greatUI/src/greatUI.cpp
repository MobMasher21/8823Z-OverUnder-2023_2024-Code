/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       lvglUI.cpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Backend code for the UI.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/greatUI.h"
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

  lv_obj_t * autoPageTabs;
  lv_style_t autoTabStyle;
  lv_obj_t * autoTabObjects[MAX_AUTO_TAB_COUNT];
  char autoTabNames[MAX_AUTO_TAB_NAME_LENGTH][MAX_AUTO_TAB_COUNT];
  uint autoTabNameLength[MAX_AUTO_TAB_COUNT];

  lv_obj_t * selectorButtons[MAX_AUTO_BUTTON_COUNT];
  lv_obj_t * selectorButtonIDLabel[MAX_AUTO_BUTTON_COUNT];
  lv_obj_t * selectorButtonTitle[MAX_AUTO_BUTTON_COUNT];
  lv_style_t buttonStyle[MAX_AUTO_BUTTON_COUNT];

  lv_obj_t * buttonIconObject[MAX_AUTO_BUTTON_COUNT];
  lv_color_t buttonIconColor[MAX_AUTO_BUTTON_COUNT];

  int prevTriggeredButtonID = -1;

  lv_obj_t * buttonInfoBox;
  timer buttonInfoBoxTime = timer();

  UITheme * basicTheme = nullptr;

  void closeInfoButtonBox()
  { lv_msgbox_close(buttonInfoBox); }

  static void autoButtonPressFunc(lv_event_t * event)
  {
    lv_event_code_t eventCode = lv_event_get_code(event);
    lv_obj_t * triggeredButton = lv_event_get_target(event);

    if(eventCode == LV_EVENT_CLICKED)
    {
      lv_obj_t * buttonIDLabel = lv_obj_get_child(triggeredButton, 0); //Get ID from button text.
      int buttonID = strtol(lv_label_get_text(buttonIDLabel), nullptr, 10);

      UI.selectButton(buttonID, false);
    }
  }

  void lvglUI::autoSelectorSetup()
  {
    uint8_t tabCount = floor(UI.getFinalButtonID() / 8);

    autoPageTabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 35);

    if(vexDisplayThemeIdGet()) //Select style for UI
    { autoTabStyle = lightModeStyle.getThemeData(themeData::BackgroundTheme); }

    else
    { autoTabStyle = darkModeStyle.getThemeData(themeData::BackgroundTheme); }
    
    //lv_obj_add_style(autoPageTabs, &autoTabStyle, LV_PART_MAIN);

    for(uint8_t i = 0; i < (tabCount + 1); i++)
    {
      if(autoTabNameLength[i] == 0) //If no name is set
      {
        char * name;
        asprintf(&name, "Tab %d", (i+1));
        autoTabObjects[i] = lv_tabview_add_tab(autoPageTabs, name);
      }

      else
      {
        char singleTabName[MAX_AUTO_TAB_NAME_LENGTH];

        for(uint ii = 0; ii < autoTabNameLength[i]+1; ii++)
        { singleTabName[ii] = autoTabNames[ii][i]; }

        autoTabObjects[i] = lv_tabview_add_tab(autoPageTabs, singleTabName);
      }
    }

    lv_obj_t * tabButtons = lv_tabview_get_tab_btns(autoPageTabs);
    //lv_obj_add_style(tabButtons, &autoTabStyle, LV_PART_MAIN);
    
    int verticalOffsetMultiplier = 1;
    int horizontalOffsetMultiplier = 1;
    int buttonTab = 0;

    for(uint currentButton = 0; currentButton < (UI.getFinalButtonID() + 1); currentButton++)
    {
      if(buttonList[currentButton] != nullptr) //Create the button
      {
        selectorButtons[currentButton] = lv_btn_create(autoTabObjects[buttonTab]);
        lv_obj_set_width(selectorButtons[currentButton], AUTO_BUTTON_SIZE);
        lv_obj_set_height(selectorButtons[currentButton], AUTO_BUTTON_SIZE);

        lv_obj_set_x(selectorButtons[currentButton], ((AUTO_BUTTON_SIZE + AUTO_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + AUTO_BUTTON_X_OFFSET);
        lv_obj_set_y(selectorButtons[currentButton], ((AUTO_BUTTON_SIZE + AUTO_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + AUTO_BUTTON_Y_OFFSET);
        
        selectorButtonIDLabel[currentButton] = lv_label_create(selectorButtons[currentButton]); //Create label to store ID.
        lv_label_set_text_fmt(selectorButtonIDLabel[currentButton], "%d", currentButton);
        lv_obj_add_flag(selectorButtonIDLabel[currentButton], LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_event_cb(selectorButtons[currentButton], autoButtonPressFunc, LV_EVENT_ALL, NULL);

        lv_color_t buttonColorLVGL = lv_color_hex(buttonList[currentButton]->buttonColor.rgb());

        lv_style_init(&buttonStyle[currentButton]);
        lv_style_set_bg_opa(&buttonStyle[currentButton], LV_OPA_100);
        lv_style_set_bg_color(&buttonStyle[currentButton], buttonColorLVGL);

        lv_obj_add_style(selectorButtons[currentButton], &buttonStyle[currentButton], LV_PART_MAIN);
        lv_style_set_outline_width(&buttonStyle[currentButton], 2);
        lv_style_set_outline_opa(&buttonStyle[currentButton], 0);

        #if REDEFINE_COLORS
          lv_style_set_outline_color(&buttonStyle[currentButton], lv_color_hex(ClrLightGrey.rgb()));
        #else
          lv_style_set_outline_color(&buttonStyle[currentButton], lv_color_hex(vexClrLightGrey.rgb()));
        #endif

        if(buttonList[currentButton]->titleLength > 0) //Add title to button
        {
          selectorButtonTitle[currentButton] = lv_label_create(selectorButtons[currentButton]); //Create label to store ID.
          lv_label_set_text_fmt(selectorButtonTitle[currentButton], "%s", buttonList[currentButton]->Title);
          lv_obj_add_flag(selectorButtons[currentButton], LV_OBJ_FLAG_OVERFLOW_VISIBLE);
          lv_obj_align_to(selectorButtonTitle[currentButton], selectorButtons[currentButton],  LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
        }

        //-2 is custom icon. -1 is no icon. 0 or greater is builtin icons.
        if(buttonList[currentButton]->iconID == -2) //Add custom icon to button.
        {
          buttonIconObject[currentButton] = lv_img_create(selectorButtons[currentButton]);
          buttonIconColor[currentButton] = lv_color_hex(buttonList[currentButton]->iconColor.rgb());
          //buttonIconOpacity[currentButton] = 255;

          lv_img_set_src(buttonIconObject[currentButton], &buttonList[currentButton]->buttonIconCustom);

          lv_obj_align_to(buttonIconObject[currentButton], selectorButtons[currentButton], LV_ALIGN_CENTER, 0, 0);

          lv_obj_set_style_img_recolor_opa(buttonIconObject[currentButton], LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonIconObject[currentButton], buttonIconColor[currentButton], 0);
        }

        else if(buttonList[currentButton]->iconID > -1) //Add builtin icon
        {
          buttonIconObject[currentButton] = lv_img_create(selectorButtons[currentButton]);
          buttonIconColor[currentButton] = lv_color_hex(buttonList[currentButton]->iconColor.rgb());
          //buttonIconOpacity[currentButton] = 255;

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

          lv_obj_align_to(buttonIconObject[currentButton], selectorButtons[currentButton], LV_ALIGN_CENTER, 0, 0);

          lv_obj_set_style_img_recolor_opa(buttonIconObject[currentButton], LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonIconObject[currentButton], buttonIconColor[currentButton], 0);
        }
      }

      if(horizontalOffsetMultiplier >= 4) //Create next button position
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier++;
      }

      else
      { horizontalOffsetMultiplier++; }

      if(verticalOffsetMultiplier > 2)
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier = 1;
        buttonTab++;
      }
    }

    lv_obj_invalidate(autoPageTabs); //Force a redraw of the auto selection UI to make sure all assets show up.
    this_thread::sleep_for(50);
  }

  lvglUI::lvglUI()
  {
    for(uint i = 0; i < MAX_AUTO_TAB_COUNT; i++)
    { autoTabNameLength[i] = 0; }
  }
  
  lvglUI::~lvglUI()
  {}

  void lvglUI::addButtonCore(int id)
  {
    if(buttonList[id] != nullptr)
    { return; }

    buttonList[id] = new button;
    buttonList[id]->buttonCallback = NULL;
    buttonCount++;

    if(id > finalButtonID)
    { finalButtonID = id; }
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
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->iconID = iconID;

    return 0;
  }

  bool lvglUI::addIcon(int id, const lv_img_dsc_t icon)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->buttonIconCustom = icon;
    buttonList[id]->iconID = -2;

    return 0;
  }

  bool lvglUI::changeIconColor(int id, int r, int g, int b)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->iconColor.rgb(r, g, b);

    return 0;
  }

  bool lvglUI::changeIconColor(int id, color iconColor)
  {
    if(buttonList[id] == nullptr)
    { return true;}
    
    buttonList[id]->iconColor = iconColor;

    return 0;
  }

  bool lvglUI::addCallbackFunc(int id, void (*callback)(int))
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->buttonCallback = callback;
    return false;
  }

  bool lvglUI::addTitle(int id, const char Title[MAX_AUTO_TITLE_LENGTH])
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->titleLength = strlen(Title);

    for(uint i = 0; i < strlen(Title); i++)
    { buttonList[id]->Title[i] = Title[i]; }

    return false;
  }

  bool lvglUI::addDescription(int id, const char Description[MAX_AUTO_DESCRIPTION_LENGTH])
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->descriptionLength = strlen(Description);

    for(uint i = 0; i < strlen(Description); i++)
    { buttonList[id]->Description[i] = Description[i]; }

    return false;
  }

  bool lvglUI::setAutoTabName(int id, const char Name[MAX_AUTO_TAB_NAME_LENGTH])
  {
    int nameLength = strlen(Name);

    autoTabNameLength[id] = nameLength;

    for(uint i = 0; i < nameLength; i++)
    { autoTabNames[i][id] = Name[i]; }
    
    return false;
  }

  bool lvglUI::addAlliance(int id, allianceType alliance)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->buttonAlliance = alliance;
    return 0;
  }

  bool lvglUI::changeButtonColor(int id, int r, int g, int b)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    lv_style_set_bg_color(&buttonStyle[id], lv_color_make(r, g, b));
    lv_obj_invalidate(autoPageTabs);

    return 0;
  }

  bool lvglUI::changeButtonColor(int id, color buttonColor)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    lv_style_set_bg_color(&buttonStyle[id], lv_color_hex(buttonColor.rgb()));
    lv_obj_invalidate(autoPageTabs);
    
    return 0;
  }

  void lvglUI::selectButton(int id, bool doNotShowSettings)
  {
    if(autoPageTabs == nullptr)
    { return; }

    if(buttonList[id]->buttonCallback != nullptr) //Run button callback
    { buttonList[id]->buttonCallback(id); }
    
    progMode = id;
    buttonInfoBoxTime.operator=(0);

      if(id != prevTriggeredButtonID) //Enable selection border
      {
        lv_style_set_outline_opa(&buttonStyle[id], 255);

        if(prevTriggeredButtonID != -1)
        { lv_style_set_outline_opa(&buttonStyle[prevTriggeredButtonID], 0); }
      }

      if(buttonList[id]->descriptionLength > 0 && !doNotShowSettings) //Print button info.
      {
        buttonInfoBox = lv_msgbox_create(NULL, buttonList[id]->Title, buttonList[id]->Description, NULL, false);
        lv_obj_center(buttonInfoBox);
        buttonInfoBoxTime.event(closeInfoButtonBox, UI.getDisplayTime());
      }

      if(buttonList[id]->buttonAlliance != noChange) //Set robot alliance
      { robotAlliance = buttonList[id]->buttonAlliance; }

      lv_obj_invalidate(autoPageTabs);

      prevTriggeredButtonID = id;
  }

  void lvglUI::selectTab(int id)
  { lv_tabview_set_act(autoPageTabs, id, LV_ANIM_ON); }

  void lvglUI::setDisplayTime(int time)
  { buttonInfoDisplayTime = time; }

  int lvglUI::getDisplayTime()
  { return buttonInfoDisplayTime; }

  int lvglUI::getProgNumber()
  { return selectedButtonID; }

  uint lvglUI::getButtonCount()
  { return buttonCount; }

  uint lvglUI::getFinalButtonID()
  { return finalButtonID; }

  //!Brain Display Setup

  #define MATCH_BUTTON_X_SIZE 210
  #define MATCH_BUTTON_Y_SIZE 35
  #define MATCH_BUTTON_X_OFFSET 0
  #define MATCH_BUTTON_Y_OFFSET -7
  #define MATCH_BUTTON_X_SPACING_DISTANCE 26
  #define MATCH_BUTTON_Y_SPACING_DISTANCE 12

  brainReadOut * matchDisplayData[MAX_MATCH_DATA_COUNT];

  lv_obj_t * matchPageTabs;
  lv_obj_t * matchTabObjects[MAX_MATCH_TAB_COUNT];
  char matchTabNames[MAX_MATCH_TAB_NAME_LENGTH][MAX_MATCH_TAB_COUNT];
  uint matchTabNameLength[MAX_MATCH_TAB_COUNT];

  lv_obj_t * matchDisplays[MAX_MATCH_DATA_COUNT];
  lv_obj_t * matchDisplayIDLabel[MAX_MATCH_DATA_COUNT];
  lv_obj_t * matchDisplayTitle[MAX_MATCH_DATA_COUNT];
  lv_style_t matchDisplayStyle[MAX_MATCH_DATA_COUNT];

  uint8_t matchDisplayUpdateList[MAX_MATCH_DATA_COUNT];
  uint8_t matchDisplaysWithData = 0;

  void lvglUI::matchUISetup()
  {
    uint8_t tabCount = floor(finalMatchDisplayID / 8);

    matchPageTabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 35);

    for(uint8_t i = 0; i < (tabCount + 1); i++)
    {
      if(matchTabNameLength[i] == 0) //If no name is set
      {
        char * name;
        asprintf(&name, "Tab %d", (i+1));
        matchTabObjects[i] = lv_tabview_add_tab(matchPageTabs, name);
      }

      else
      {
        char singleTabName[MAX_MATCH_TAB_NAME_LENGTH];

        for(uint ii = 0; ii < matchTabNameLength[i]+1; ii++)
        { singleTabName[ii] = matchTabNames[ii][i]; }

        matchTabObjects[i] = lv_tabview_add_tab(matchPageTabs, singleTabName);
      }
    }

    int verticalOffsetMultiplier = 1;
    int horizontalOffsetMultiplier = 1;
    int buttonTab = 0;
    uint matchDisplayUpdateID = 0;

    for(uint currentDisplay = 0; currentDisplay < (finalMatchDisplayID + 1); currentDisplay++)
    {
      if(matchDisplayData[currentDisplay] != nullptr)
      {
        matchDisplays[currentDisplay] = lv_btn_create(matchTabObjects[buttonTab]);
        lv_obj_clear_flag(matchDisplays[currentDisplay], LV_OBJ_FLAG_CLICKABLE);

        lv_obj_set_width(matchDisplays[currentDisplay], MATCH_BUTTON_X_SIZE);
        lv_obj_set_height(matchDisplays[currentDisplay], MATCH_BUTTON_Y_SIZE);

        lv_obj_set_x(matchDisplays[currentDisplay], ((MATCH_BUTTON_X_SIZE + MATCH_BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + MATCH_BUTTON_X_OFFSET);
        lv_obj_set_y(matchDisplays[currentDisplay], ((MATCH_BUTTON_Y_SIZE + MATCH_BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + MATCH_BUTTON_Y_OFFSET);
        
        matchDisplayIDLabel[currentDisplay] = lv_label_create(matchDisplays[currentDisplay]); //Create label to store ID.
        lv_label_set_text_fmt(matchDisplayIDLabel[currentDisplay], "%d", currentDisplay);
        lv_obj_add_flag(matchDisplayIDLabel[currentDisplay], LV_OBJ_FLAG_HIDDEN);

        lv_color_t matchDisplayLVGL = lv_color_hex(matchDisplayData[currentDisplay]->graphColor.rgb());

        lv_style_init(&matchDisplayStyle[currentDisplay]);
        lv_style_set_bg_opa(&matchDisplayStyle[currentDisplay], LV_OPA_100);
        lv_style_set_bg_color(&matchDisplayStyle[currentDisplay], matchDisplayLVGL);

        lv_obj_add_style(matchDisplays[currentDisplay], &matchDisplayStyle[currentDisplay], LV_PART_MAIN);

        matchDisplayTitle[currentDisplay] = lv_label_create(matchDisplays[currentDisplay]); //Create label to store ID.
        lv_obj_add_flag(matchDisplays[currentDisplay], LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_align_to(matchDisplayTitle[currentDisplay], matchDisplays[currentDisplay],  LV_ALIGN_LEFT_MID, -7, 0);

        std::string dataString;
        
        switch(matchDisplayData[currentDisplay]->dataType) //Add title to display
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
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case brainDataType::UINT:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%i",
              matchDisplayData[currentDisplay]->Name,
              *(uint*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case brainDataType::LONG:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%lu",
              matchDisplayData[currentDisplay]->Name,
              *(long*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::ULONG:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%lu",
              matchDisplayData[currentDisplay]->Name,
              *(ulong*)matchDisplayData[currentDisplay]->displayData
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;
            
          case brainDataType::FLOAT:
            dataString = evPatch::to_string(*(float*)matchDisplayData[currentDisplay]->displayData);

            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%s",
              matchDisplayData[currentDisplay]->Name,
              dataString.c_str()
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::DOUBLE:
            dataString = evPatch::to_string(*(double*)matchDisplayData[currentDisplay]->displayData);

            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%s",
              matchDisplayData[currentDisplay]->Name,
              dataString.c_str()
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::FUNC_INT:
            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%i",
              matchDisplayData[currentDisplay]->Name,
              (*matchDisplayData[currentDisplay]->funcInt)()
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;

          case brainDataType::FUNC_DOUBLE:
            dataString = evPatch::to_string((*matchDisplayData[currentDisplay]->funcDouble)());

            lv_label_set_text_fmt(
              matchDisplayTitle[currentDisplay],
              "%s%s",
              matchDisplayData[currentDisplay]->Name,
              dataString.c_str()
            );
            matchDisplayUpdateList[matchDisplayUpdateID] = currentDisplay;
            break;
        }

        matchDisplayUpdateID++;
      }

      if(horizontalOffsetMultiplier >= 2) //Create next display position
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier++;
      }

      else
      { horizontalOffsetMultiplier++; }

      if(verticalOffsetMultiplier > 4)
      {
        horizontalOffsetMultiplier = 1;
        verticalOffsetMultiplier = 1;
        buttonTab++;
      }
    }
    
    matchDisplaysWithData = matchDisplayUpdateID;
  }

  bool lvglUI::createBrainDisplay(int id, const char name[MAX_MATCH_DATA_NAME_LENGTH])
  {
    if(matchDisplayData[id] != nullptr)
    { return 1; }

    matchDisplayData[id] = new brainReadOut;
    matchDisplayData[id]->nameLength = strlen(name);

    for(uint8_t i = 0; i < matchDisplayData[id]->nameLength; i++)
    { matchDisplayData[id]->Name[i] = name[i]; }

    matchDisplayCount++;

    if(id > finalMatchDisplayID)
    { finalMatchDisplayID = id; }

    return 0;
  }

  bool lvglUI::setBrainDisplayColor(int id, int r, int g, int b)
  {
    if(matchDisplayData[id] == nullptr)
    { return 1; }

    matchDisplayData[id]->graphColor.rgb(r, g, b);

    return 0;
  }

  bool lvglUI::setBrainDisplayColor(int id, color Color)
  {
    if(matchDisplayData[id] == nullptr)
    { return 1; }

    matchDisplayData[id]->graphColor = Color;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, void *data, brainDataType inputDataType)
  {
    if(matchDisplayData[id] == nullptr)
    { return 1; }

    matchDisplayData[id]->displayData = data;
    matchDisplayData[id]->dataType = inputDataType;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, int (*callback)())
  {
    if(matchDisplayData[id] == nullptr)
    { return 1; }

    matchDisplayData[id]->funcInt = callback;
    matchDisplayData[id]->dataType = brainDataType::FUNC_INT;

    return 0;
  }

  bool lvglUI::setBrainDisplayData(int id, double (*callback)())
  {
    if(matchDisplayData[id] == nullptr)
    { return 1; }

    matchDisplayData[id]->funcDouble = callback;
    matchDisplayData[id]->dataType = brainDataType::FUNC_DOUBLE;

    return 0;
  }

  bool lvglUI::setMatchTabName(int id, const char Name[MAX_MATCH_TAB_NAME_LENGTH])
  {
    int nameLength = strlen(Name);

    matchTabNameLength[id] = nameLength;

    for(uint i = 0; i < nameLength; i++)
    { matchTabNames[i][id] = Name[i]; }
    
    return false;
  }

  uint lvglUI::getMatchDisplayCount()
  { return matchDisplayCount; }

  uint lvglUI::getFinalMatchDisplayID()
  { return finalMatchDisplayID; }

  int UIThreadFunc()
  {
    uint8_t compMode = 0;
    uint8_t prevCompMode = 4;

    std::string dataString;

    while(true)
    {
      if(!Competition.isEnabled()) //Get state of competition.
      { compMode = disabled; }

      else if(Competition.isDriverControl())
      { compMode = driverControl; }

      else
      { compMode = autonomousControl; }

      /* if(compMode != prevCompMode) //Change UI state if competition has changed.
      {
        if(compMode == disabled)
        {
          lv_obj_add_flag(matchPageTabs, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(autoPageTabs, LV_OBJ_FLAG_HIDDEN);
        }

        else
        {
          lv_obj_add_flag(autoPageTabs, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(matchPageTabs, LV_OBJ_FLAG_HIDDEN);
        }
      } */

      /* if(compMode == driverControl) //Match UI update
      { */
        uint currentDisplay;
        for(uint8_t i = 0; i < matchDisplaysWithData-1; i++)
        {
          currentDisplay = matchDisplayUpdateList[i];
          switch(matchDisplayData[currentDisplay]->dataType) //Add title to display
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
              break;
            
            case brainDataType::UINT:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%i",
                matchDisplayData[currentDisplay]->Name,
                *(uint*)matchDisplayData[currentDisplay]->displayData
              );
              break;
            
            case brainDataType::LONG:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%lu",
                matchDisplayData[currentDisplay]->Name,
                *(long*)matchDisplayData[currentDisplay]->displayData
              );
              break;

            case brainDataType::ULONG:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%lu",
                matchDisplayData[currentDisplay]->Name,
                *(ulong*)matchDisplayData[currentDisplay]->displayData
              );
              break;
            
            case brainDataType::FLOAT:
              dataString = evPatch::to_string(*(float*)matchDisplayData[currentDisplay]->displayData);

              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%s",
                matchDisplayData[currentDisplay]->Name,
                dataString.c_str()
              );
              break;

            case brainDataType::DOUBLE:
              dataString = evPatch::to_string(*(double*)matchDisplayData[currentDisplay]->displayData);

              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%s",
                matchDisplayData[currentDisplay]->Name,
                dataString.c_str()
              );
              break;

            case brainDataType::FUNC_INT:
              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%i",
                matchDisplayData[currentDisplay]->Name,
                (*matchDisplayData[currentDisplay]->funcInt)()
              );
              break;

            case brainDataType::FUNC_DOUBLE:
              dataString = evPatch::to_string((*matchDisplayData[currentDisplay]->funcDouble)());

              lv_label_set_text_fmt(
                matchDisplayTitle[currentDisplay],
                "%s%s",
                matchDisplayData[currentDisplay]->Name,
                dataString.c_str()
              );
              break;
          }
        //}
      }

      prevCompMode = compMode;
      
      this_thread::sleep_for(20);
    }

    return 0;
  }

  //extern lv_disp_t * lvglDisplay;

  void lvglUI::startUIThreads()
  {
    vex_lvgl_init();

    /* lv_color_t lvglDeepSkyBlue = lv_color_hex(ClrDeepSkyBlue.rgb());
    lv_color_t lvglDarkSlateBlue = lv_color_hex(ClrDarkSlateBlue.rgb());

    lv_theme_t * UITheme_LVGL = lv_theme_default_init(NULL, lvglDeepSkyBlue, lvglDarkSlateBlue, false, LV_FONT_DEFAULT);
    lv_disp_set_theme(NULL, UITheme_LVGL);
     */
    autoSelectorSetup();
    //matchUISetup();

    UIThread = new thread(UIThreadFunc);
  }
} // namespace evAPI