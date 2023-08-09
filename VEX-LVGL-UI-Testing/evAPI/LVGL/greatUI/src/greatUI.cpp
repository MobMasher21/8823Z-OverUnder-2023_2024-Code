/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       greatUI.cpp                                               */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Backend code for the UI.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/greatUI.h"
#include "../../../Common/include/evNamespace.h"
#include "../../../Common/include/Controllers.h"
#include "evAPISettings.h"

LV_IMG_DECLARE(Skills_Icon)
LV_IMG_DECLARE(Left_Arrow)
LV_IMG_DECLARE(Right_Arrow)

#define BUTTON_SIZE 70
#define BUTTON_X_OFFSET 0
#define BUTTON_Y_OFFSET -7
#define BUTTON_X_SPACING_DISTANCE 56
#define BUTTON_Y_SPACING_DISTANCE 30

namespace evAPI
{
  greatUI UI = greatUI();

  extern allianceType robotAlliance;

  button * buttonList[MAX_BUTTON_COUNT];

  int selectedButtonID = 0;

  lv_obj_t * pageTabs;
  lv_obj_t * autoTabs[MAX_TAB_COUNT];
  char autoTabNames[MAX_TAB_NAME_LENGTH][MAX_TAB_COUNT];
  uint autoTabNameLength[MAX_TAB_COUNT];

  lv_obj_t * selectorButtons[MAX_BUTTON_COUNT];
  lv_obj_t * selectorButtonID[MAX_BUTTON_COUNT];
  lv_obj_t * selectorButtonTitle[MAX_BUTTON_COUNT];
  lv_style_t buttonStyle[MAX_BUTTON_COUNT];

  lv_obj_t * buttonIconObject[MAX_BUTTON_COUNT];
  lv_color_t buttonIconColor[MAX_BUTTON_COUNT];
  //lv_opa_t buttonIconOpacity[MAX_BUTTON_COUNT];

  int prevTriggeredButtonID = -1;

  lv_obj_t * buttonInfoBox;
  timer buttonInfoBoxTime = timer();

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
      printf("ButtonID: %d\n", buttonID);

      UI.selectButton(buttonID, false);
    }
  }

  void autoSelectorSetup()
  {
    v5_lv_init();
    
    uint8_t tabCount = floor(UI.getFinalButtonID() / 8);

    printf("Final ID: %d\n", UI.getFinalButtonID());
    printf("Tab Count: %d\n\n", tabCount);

    this_thread::sleep_for(50);

    pageTabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 35);

    for (uint8_t i = 0; i < (tabCount + 1); i++)
    {
      if(autoTabNameLength[i] == 0) //If no name is set
      {
        char * name;
        asprintf(&name, "Tab %d", (i+1));
        autoTabs[i] = lv_tabview_add_tab(pageTabs, name);
        printf("No Name added\n\n");
      }

      else
      {
        char singleTabName[MAX_TAB_NAME_LENGTH];

        for (uint ii = 0; ii < autoTabNameLength[i]+1; ii++)
        { singleTabName[ii] = autoTabNames[ii][i]; }

        autoTabs[i] = lv_tabview_add_tab(pageTabs, singleTabName);
      }
    }
    
    int verticalOffsetMultiplier = 1;
    int horizontalOffsetMultiplier = 1;
    int buttonTab = 0;

    for (uint currentButton = 0; currentButton < (UI.getFinalButtonID() + 1); currentButton++)
    {
      printf("Check Button ID: %d\n", currentButton);
      if(buttonList[currentButton] != nullptr) //Create the button
      {
        printf("Printing Button ID: %d\n", currentButton);
        selectorButtons[currentButton] = lv_btn_create(autoTabs[buttonTab]);
        lv_obj_set_width(selectorButtons[currentButton], BUTTON_SIZE);
        lv_obj_set_height(selectorButtons[currentButton], BUTTON_SIZE);

        lv_obj_set_x(selectorButtons[currentButton], ((BUTTON_SIZE + BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)) + BUTTON_X_OFFSET);
        lv_obj_set_y(selectorButtons[currentButton], ((BUTTON_SIZE + BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)) + BUTTON_Y_OFFSET);
        
        selectorButtonID[currentButton] = lv_label_create(selectorButtons[currentButton]); //Create label to store ID.
        lv_label_set_text_fmt(selectorButtonID[currentButton], "%d", currentButton);
        lv_obj_add_flag(selectorButtonID[currentButton], LV_OBJ_FLAG_HIDDEN);

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

        if(buttonList[currentButton]->iconID != -1) //Add icon to button
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
          }

          lv_obj_align_to(buttonIconObject[currentButton], selectorButtons[currentButton], LV_ALIGN_CENTER, 0, 0);

          lv_obj_set_style_img_recolor_opa(buttonIconObject[currentButton], LV_OPA_100, 0);
          lv_obj_set_style_img_recolor(buttonIconObject[currentButton], buttonIconColor[currentButton], 0);
        }

        printf("\n");
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

    lv_obj_invalidate(pageTabs); //Force a redraw of the auto selection UI to make sure all assets show up.
    this_thread::sleep_for(50);
  }

  greatUI::greatUI()
  {
    for(uint i = 0; i < MAX_TAB_COUNT; i++)
    { autoTabNameLength[i] = 0; }
    
  }
  
  greatUI::~greatUI()
  {}

  void greatUI::setDebugMode(bool mode)
  { debugMode = mode; }

  void greatUI::startUIThreads()
  {
    autoSelectorSetup();
  }

  void greatUI::addButtonCore(int id)
  {
    if(buttonList[id] != nullptr)
    { return; }

    buttonList[id] = new button;
    buttonCount++;

    if(id > finalButtonID)
    { finalButtonID = id; }

    printf("Button Count: %d\n", buttonCount);
    printf("Final ID: %d\n\n", finalButtonID);
  }

  int greatUI::addButton(int id, int r, int g, int b)
  {
    addButtonCore(id);
    buttonList[id]->buttonColor.rgb(r, g, b);
    return buttonCount;
  }
  
  int greatUI::addButton(int id, color buttonColor)
  {
    addButtonCore(id);
    buttonList[id]->buttonColor = buttonColor;
    return buttonCount;
  }

  int greatUI::addButton(int id, allianceType alliance)
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

  bool greatUI::addIcon(int id, int iconID)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->iconID = iconID;

    return 0;
  }

  bool greatUI::setIconColor(int id, int r, int g, int b)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->iconColor.rgb(r, g, b);

    return 0;
  }

  bool greatUI::setIconColor(int id, color iconColor)
  {
    if(buttonList[id] == nullptr)
    { return true;}
    
    buttonList[id]->iconColor = iconColor;

    return 0;
  }



  bool greatUI::addTitle(int id, const char Title[MAX_TITLE_LENGTH])
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->titleLength = strlen(Title);

    for(uint i = 0; i < strlen(Title); i++)
    { buttonList[id]->Title[i] = Title[i]; }

    return false;
  }

  bool greatUI::addDescription(int id, const char Description[MAX_DESCRIPTION_LENGTH])
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonList[id]->descriptionLength = strlen(Description);

    for(uint i = 0; i < strlen(Description); i++)
    { buttonList[id]->Description[i] = Description[i]; }

    return false;
  }

  bool greatUI::setTitleName(int id, const char Name[MAX_TAB_NAME_LENGTH])
  {
    int nameLength = strlen(Name);

    autoTabNameLength[id] = nameLength;

    for(uint i = 0; i < nameLength; i++)
    { autoTabNames[i][id] = Name[i]; }
    
    return false;
  }



  void greatUI::selectButton(int id, bool doNotShowSettings)
  {
    if(pageTabs == nullptr)
    { return; }

    progMode = id;
    buttonInfoBoxTime.operator=(0);

      if(id != prevTriggeredButtonID) //Prevent button from loosing selection border if it is repeatedly pressed.
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

      if(buttonList[id]->buttonAlliance != noChange)
      { robotAlliance = buttonList[id]->buttonAlliance; }

      lv_obj_invalidate(pageTabs);

      prevTriggeredButtonID = id;
  }

  void greatUI::setDisplayTime(int time)
  { buttonInfoDisplayTime = time; }

  int greatUI::getDisplayTime()
  { return buttonInfoDisplayTime; }

  int greatUI::getProgNumber()
  { return selectedButtonID; }

  uint greatUI::getButtonCount()
  { return buttonCount; }

  uint greatUI::getFinalButtonID()
  { return finalButtonID; }
} // namespace evAPI