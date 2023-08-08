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
  UI.addButton(SKILLS_AUTO_BASIC, blue);
  UI.addTitle(SKILLS_AUTO_BASIC, "Skills 1");
  UI.addDescription(SKILLS_AUTO_BASIC, "Skills auto that just shoots match loads into the field.");

  //Other Page
  UI.setTitleName(2, "Other");
  UI.addButton(20, blue);
  UI.addTitle(20, "Testing");

  UI.setDisplayTime(1500);
  UI.startUIThreads();

  while(1) {
      // Allow other tasks to run
      this_thread::sleep_for(10);
  }
}