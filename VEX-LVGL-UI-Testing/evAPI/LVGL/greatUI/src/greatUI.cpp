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

  static void autoButtonPressFunc(lv_event_t * event)
  {
    lv_event_code_t eventCode = lv_event_get_code(event);
    lv_obj_t * target = lv_event_get_target(event);

    if(eventCode == LV_EVENT_CLICKED) 
    {
      lv_obj_t * buttonIDLabel = lv_obj_get_child(target, 0); //Get ID from button text.
      char **justWork = nullptr;
      int buttonID = strtol(lv_label_get_text(buttonIDLabel), justWork, 10);
      printf("ButtonID: %d\n", buttonID);

      /* if(buttonList[buttonID].titleLength > 0)
      {
        lv_obj_add_flag(pageTabs, LV_OBJ_FLAG_HIDDEN);
        lv_obj_t * titleText = lv_label_create(lv_scr_act());
        lv_label_set_text(titleText, buttonList[buttonID].Title);
        lv_obj_align(titleText, LV_ALIGN_TOP_MID, 0, 0);

        
      } */
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

    for (uint i = 0; i < (UI.getFinalButtonID() + 1); i++)
    {
      printf("Check Button ID: %d\n", i);
      if(buttonList[i] != nullptr) //Create the button
      {
        printf("Printing Button ID: %d\n", i);
        selectorButtons[i] = lv_btn_create(autoTabs[buttonTab]);
        lv_obj_set_width(selectorButtons[i], BUTTON_SIZE);
        lv_obj_set_height(selectorButtons[i], BUTTON_SIZE);

        printf("Button X Offset: %d\n", horizontalOffsetMultiplier);
        printf("Button Y Offset: %d\n", verticalOffsetMultiplier);

        lv_obj_set_x(selectorButtons[i], ((BUTTON_SIZE + BUTTON_X_SPACING_DISTANCE) * (horizontalOffsetMultiplier - 1)));
        lv_obj_set_y(selectorButtons[i], ((BUTTON_SIZE + BUTTON_Y_SPACING_DISTANCE) * (verticalOffsetMultiplier - 1)));
        
        selectorButtonID[i] = lv_label_create(selectorButtons[i]); //Create label to store ID.
        lv_label_set_text_fmt(selectorButtonID[i], "%d", i);
        lv_obj_add_flag(selectorButtonID[i], LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_event_cb(selectorButtons[i], autoButtonPressFunc, LV_EVENT_ALL, NULL);

        if(buttonList[i]->titleLength > 0)
        {
          selectorButtonTitle[i] = lv_label_create(selectorButtons[i]); //Create label to store ID.
          lv_label_set_text_fmt(selectorButtonTitle[i], "%s", buttonList[i]->Title);
          lv_obj_add_flag(selectorButtonTitle[i], LV_OBJ_FLAG_OVERFLOW_VISIBLE);
          lv_obj_align_to(selectorButtonTitle[i], selectorButtons[i],  LV_ALIGN_CENTER, 0, 0);
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



  int greatUI::getProgNumber()
  { return selectedButtonID; }

  uint greatUI::getButtonCount()
  { return buttonCount; }

  uint greatUI::getFinalButtonID()
  { return finalButtonID; }
} // namespace evAPI