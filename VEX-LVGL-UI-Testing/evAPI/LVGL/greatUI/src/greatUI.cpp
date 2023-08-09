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

#define BUTTON_SIZE 70
#define STARTING_X_OFFSET 10
#define STARTING_Y_OFFSET 10
#define BUTTON_X_SPACING_DISTANCE 56
#define BUTTON_Y_SPACING_DISTANCE 25

namespace evAPI
{
  greatUI UI = greatUI();

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

  const void *buttonIcon[MAX_BUTTON_COUNT];
  lv_obj_t * buttonIconObject[MAX_BUTTON_COUNT];
  lv_color_t buttonIconColor[MAX_BUTTON_COUNT];
  lv_opa_t buttonIconIntense[MAX_BUTTON_COUNT];

  lv_obj_t * buttonInfoBox;
  timer buttonInfoBoxTime = timer();

  void closeInfoButtonBox()
  { lv_msgbox_close(buttonInfoBox); }

  static void autoButtonPressFunc(lv_event_t * event)
  {
    lv_event_code_t eventCode = lv_event_get_code(event);
    lv_obj_t * triggeredButton = lv_event_get_target(event);
    static lv_obj_t * prevTriggeredButton;
    static int prevTriggeredButtonID = -1;

    if(eventCode == LV_EVENT_CLICKED)
    {
      lv_obj_t * buttonIDLabel = lv_obj_get_child(triggeredButton, 0); //Get ID from button text.
      int buttonID = strtol(lv_label_get_text(buttonIDLabel), nullptr, 10);
      printf("ButtonID: %d\n", buttonID);

      UI.selectButton(buttonID, true);
      buttonInfoBoxTime.operator=(0);

      if(buttonID != prevTriggeredButtonID) //Prevent button from loosing selection border if it is repeatedly pressed.
      {
        lv_style_set_outline_opa(&buttonStyle[buttonID], 255);

        if(prevTriggeredButton != nullptr)
        { lv_style_set_outline_opa(&buttonStyle[prevTriggeredButtonID], 0); }
      }

      if(buttonList[buttonID]->descriptionLength > 0) //Print button info.
      {
        buttonInfoBox = lv_msgbox_create(NULL, buttonList[buttonID]->Title, buttonList[buttonID]->Description, NULL, false);
        lv_obj_center(buttonInfoBox);
        buttonInfoBoxTime.event(closeInfoButtonBox, UI.getDisplayTime());
      }

      prevTriggeredButtonID = buttonID;
      prevTriggeredButton = triggeredButton;
    }
  }

  int autoSelectorThread()
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
        selectorButtons[currentButton] = lv_btn_create(autoTabs[buttonTab]);
        lv_obj_set_width(selectorButtons[currentButton], BUTTON_SIZE);
        lv_obj_set_height(selectorButtons[currentButton], BUTTON_SIZE);

        lv_obj_set_x(selectorButtons[currentButton], ((BUTTON_SIZE + BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)));
        lv_obj_set_y(selectorButtons[currentButton], ((BUTTON_SIZE + BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)));
        
        selectorButtonID[currentButton] = lv_label_create(selectorButtons[currentButton]); //Create label to store ID.
        lv_label_set_text_fmt(selectorButtonID[currentButton], "%d", currentButton);
        lv_obj_add_flag(selectorButtonID[currentButton], LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_event_cb(selectorButtons[currentButton], autoButtonPressFunc, LV_EVENT_ALL, NULL);

        lv_color_t buttonColorLVGL = lv_color_hex(buttonList[currentButton]->buttonColor.rgb());

        lv_style_init(&buttonStyle[currentButton]);
        lv_style_set_bg_opa(&buttonStyle[currentButton], LV_OPA_100);
        lv_style_set_bg_color(&buttonStyle[currentButton], buttonColorLVGL);

        lv_obj_add_style(selectorButtons[currentButton], &buttonStyle[currentButton], LV_PART_MAIN);
        lv_style_set_outline_width(&buttonStyle[currentButton], 5);
        lv_style_set_outline_opa(&buttonStyle[currentButton], 0);

        #if REDEFINE_COLORS
          lv_style_set_outline_color(&buttonStyle[currentButton], lv_color_hex(ClrLightGrey.rgb()));
        #else
          lv_style_set_outline_color(&buttonStyle[currentButton], lv_color_hex(vexClrLightGrey.rgb()));
        #endif

        if(buttonList[currentButton]->titleLength > 0)
        {
          selectorButtonTitle[currentButton] = lv_label_create(selectorButtons[currentButton]); //Create label to store ID.
          lv_label_set_text_fmt(selectorButtonTitle[currentButton], "%s", buttonList[currentButton]->Title);
          lv_obj_add_flag(selectorButtons[currentButton], LV_OBJ_FLAG_OVERFLOW_VISIBLE);
          lv_obj_align_to(selectorButtonTitle[currentButton], selectorButtons[currentButton],  LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        }

        if(buttonIcon[currentButton] != nullptr)
        {
          printf("Setting Icon paramater\n");
          buttonIconObject[currentButton] = lv_img_create(selectorButtons[currentButton]);
          buttonIconColor[currentButton] = lv_color_make(0, 0, 0);
          buttonIconIntense[currentButton] = 255;

          this_thread::sleep_for(200);

          printf("Create Image\n");
          lv_img_set_src(buttonIconObject[currentButton], buttonIcon[currentButton]);
          this_thread::sleep_for(200);

          printf("Align to button\n");
          lv_obj_align_to(buttonIconObject[currentButton], selectorButtons[currentButton], LV_ALIGN_CENTER, 0, 0);
          this_thread::sleep_for(200);

          printf("Apply color parameters\n");
          lv_obj_set_style_img_recolor_opa(buttonIconObject[currentButton], buttonIconIntense[currentButton], 0);
          lv_obj_set_style_img_recolor(buttonIconObject[currentButton], buttonIconColor[currentButton], 0);
          this_thread::sleep_for(200);
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

    while(true)
    {

      this_thread::sleep_for(40);
    }


    return 0;
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
    brainThread = new thread(autoSelectorThread);
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

  bool greatUI::addIcon(int id, lv_img_dsc_t iconInput)
  {
    if(buttonList[id] == nullptr)
    { return true;}

    buttonIcon[id] = &iconInput;

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



  void greatUI::selectButton(int button, bool doNotShowSettings)
  {
    progMode = button;

    if(!doNotShowSettings)
    {

    }
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