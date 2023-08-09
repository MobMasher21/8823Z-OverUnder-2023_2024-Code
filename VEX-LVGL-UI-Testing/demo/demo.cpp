/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       james                                                     */
/*    Created:      Sun Sep 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "v5lvgl.h"
#include "evAPI.h"

using namespace evAPI;

#define BLUE_SCORING_AUTO 0
#define BLUE_LOADING_AUTO 3
#define SKILLS_AUTO_BASIC 8

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

/* static void buttonPress(lv_event_t * event)
{
  lv_event_code_t eventCode = lv_event_get_code(event);

  if(eventCode == LV_EVENT_CLICKED)
  {
    printf("Pressed\n");
  }

} */

LV_IMG_DECLARE(Skills_Icon);

int main() {
  //! COLORS CURRENTLY DO NOT WORK!\

  //Auto Page
  UI.setTitleName(0, "Auto");
  UI.addButton(BLUE_SCORING_AUTO, blue);
  UI.addTitle(BLUE_SCORING_AUTO, "Scoring");
  UI.addDescription(BLUE_SCORING_AUTO, "Auto for a blue alliance robot on the scoring side.");

  UI.addButton(BLUE_LOADING_AUTO, blue);
  UI.addTitle(BLUE_LOADING_AUTO, "Load");
  UI.addDescription(BLUE_LOADING_AUTO, "Auto for a blue alliance robot on the match loading side.");
    
  //Skills Page
  UI.setTitleName(1, "Skills");
  UI.addButton(SKILLS_AUTO_BASIC, 0xff, 0x10, 0xa0);
  UI.addTitle(SKILLS_AUTO_BASIC, "Skills 1");
  UI.addDescription(SKILLS_AUTO_BASIC, "Skills auto that just shoots match loads into the field.");
  //UI.addIcon(SKILLS_AUTO_BASIC, Skills_Icon);

  //Other Page
  UI.setTitleName(2, "Other");
  UI.addButton(20, noAlliance);
  UI.addTitle(20, "Testing");

  UI.setDisplayTime(1500);
  UI.startUIThreads();

  /* v5_lv_init();

  lv_obj_t * testButton = lv_btn_create(lv_scr_act());
  lv_obj_t * testButtonLabel = lv_label_create(testButton);
  lv_obj_t * buttonImage = lv_img_create(testButton);
  lv_color_t buttonColor = lv_color_make(0, 0, 0);
  lv_opa_t intense = 255;

  lv_img_set_src(buttonImage, &Skills_Icon);

  lv_obj_add_event_cb(testButton, buttonPress, LV_EVENT_ALL, NULL);

  lv_obj_set_height(testButton, 70);
  lv_obj_set_width(testButton, 70);

  lv_obj_align_to(buttonImage, testButton, LV_ALIGN_CENTER, 0, 0);
  lv_obj_center(testButton);

  lv_obj_set_style_img_recolor_opa(buttonImage, intense, 0);
  lv_obj_set_style_img_recolor(buttonImage, buttonColor, 0);

  lv_obj_clear_flag(testButtonLabel, LV_LABEL_LONG_CLIP);
  lv_label_set_text(testButtonLabel, "Test Button");
  lv_obj_align_to(testButtonLabel, testButton, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); */

  while(1) {
      // Allow other tasks to run
      this_thread::sleep_for(10);
  }
}