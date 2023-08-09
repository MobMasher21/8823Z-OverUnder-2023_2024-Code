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
#define BLUE_LOADING_AUTO 4
#define RED_SCORING_AUTO 3
#define RED_LOADING_AUTO 7
#define SKILLS_AUTO_BASIC 8

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

int main() {

  //Auto Page
  UI.setTitleName(0, "Auto");
  UI.addButton(BLUE_SCORING_AUTO, blue);
  UI.addTitle(BLUE_SCORING_AUTO, "Scoring");
  UI.addDescription(BLUE_SCORING_AUTO, "Auto for a blue alliance robot on the scoring side.");
  UI.addIcon(BLUE_SCORING_AUTO, LEFT_ARROW);
  UI.setIconColor(BLUE_SCORING_AUTO, black);

  UI.addButton(BLUE_LOADING_AUTO, blue);
  UI.addTitle(BLUE_LOADING_AUTO, "Load");
  UI.addDescription(BLUE_LOADING_AUTO, "Auto for a blue alliance robot on the match loading side.");
  UI.addIcon(BLUE_LOADING_AUTO, RIGHT_ARROW);
  UI.setIconColor(BLUE_LOADING_AUTO, black);

  UI.setTitleName(RED_SCORING_AUTO, "Auto");
  UI.addButton(RED_SCORING_AUTO, red);
  UI.addTitle(RED_SCORING_AUTO, "Scoring");
  UI.addDescription(RED_SCORING_AUTO, "Auto for a red alliance robot on the scoring side.");
  UI.addIcon(RED_SCORING_AUTO, LEFT_ARROW);
  UI.setIconColor(RED_SCORING_AUTO, black);

  UI.addButton(RED_LOADING_AUTO, red);
  UI.addTitle(RED_LOADING_AUTO, "Load");
  UI.addDescription(RED_LOADING_AUTO, "Auto for a red alliance robot on the match loading side.");
  UI.addIcon(RED_LOADING_AUTO, RIGHT_ARROW);
  UI.setIconColor(RED_LOADING_AUTO, black);
    
  //Skills Page
  UI.setTitleName(1, "Skills");
  UI.addButton(SKILLS_AUTO_BASIC, 0xff, 0x10, 0xa0);
  UI.addTitle(SKILLS_AUTO_BASIC, "Skills 1");
  UI.addDescription(SKILLS_AUTO_BASIC, "Skills auto that just shoots match loads into the field.");
  UI.addIcon(SKILLS_AUTO_BASIC, SKILLS_ICON);
  UI.setIconColor(SKILLS_AUTO_BASIC, black);

  //Other Page
  UI.setTitleName(2, "Other");
  UI.addButton(20, noAlliance);
  UI.addTitle(20, "Testing");

  UI.setDisplayTime(1500);

  UI.startUIThreads();
  UI.selectButton(BLUE_LOADING_AUTO, true);

  while(1) {
      // Allow other tasks to run
      this_thread::sleep_for(10);
  }
}