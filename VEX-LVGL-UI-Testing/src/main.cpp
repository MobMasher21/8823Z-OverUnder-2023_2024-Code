/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       james                                                     */
/*    Created:      Sun Sep 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "lvgl.h"
#include "evAPI.h"

using namespace evAPI;

//IDs of buttons in the preauto UI
#define BLUE_SCORING_AUTO 0
#define BLUE_LOADING_AUTO 4
#define RED_SCORING_AUTO 3
#define RED_LOADING_AUTO 7
#define SKILLS_AUTO_BASIC 8

//A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;

LV_IMG_DECLARE(Exclamation_Points)

void testCallback(uint id)
{
  printf("Button %i was pressed.\n\n", id);
}

uint batteryCapacity = Brain.Battery.capacity();
double batteryTemperature = Brain.Battery.temperature(fahrenheit);
double batteryCurrent = Brain.Battery.current();
double batteryVoltage = Brain.Battery.voltage();

uint selectedProgramID = UI.autoSelector.getProgNumber();
uint preautoUIButtons = UI.autoSelector.getButtonCount();

double testFunc()
{
  static double var = 0;

  if(var > 100)
  { var = 0; }

  else
  { var += 0.357; }

  return var;
}

void scrollUp()
{
  UI.primaryControllerUI.scrollUp();
}

void scrollDown()
{
  UI.primaryControllerUI.scrollDown();
}

int main() {

  //*Auto Selector / Preauto UI
  //Auto Page
  UI.autoSelector.addAutoTab("Auto");
  UI.autoSelector.addButton(BLUE_SCORING_AUTO, blue);
  UI.autoSelector.addTitle(BLUE_SCORING_AUTO, "Scoring");
  UI.autoSelector.addDescription(BLUE_SCORING_AUTO, "Auto for a blue alliance robot on the scoring side.");
  UI.autoSelector.addIcon(BLUE_SCORING_AUTO, LEFT_ARROW);
  UI.autoSelector.changeIconColor(BLUE_SCORING_AUTO, black);
  UI.autoSelector.addCallbackFunc(BLUE_SCORING_AUTO, testCallback);

  UI.autoSelector.addButton(BLUE_LOADING_AUTO, blue);
  UI.autoSelector.addTitle(BLUE_LOADING_AUTO, "Load");
  UI.autoSelector.addDescription(BLUE_LOADING_AUTO, "Auto for a blue alliance robot on the match loading side.");
  UI.autoSelector.addIcon(BLUE_LOADING_AUTO, RIGHT_ARROW);
  UI.autoSelector.changeIconColor(BLUE_LOADING_AUTO, black);

  UI.autoSelector.addButton(RED_SCORING_AUTO, red);
  UI.autoSelector.addTitle(RED_SCORING_AUTO, "Scoring");
  UI.autoSelector.addDescription(RED_SCORING_AUTO, "Auto for a red alliance robot on the scoring side.");
  UI.autoSelector.addIcon(RED_SCORING_AUTO, LEFT_ARROW);
  UI.autoSelector.changeIconColor(RED_SCORING_AUTO, black);

  UI.autoSelector.addButton(RED_LOADING_AUTO, red);
  UI.autoSelector.addTitle(RED_LOADING_AUTO, "Load");
  UI.autoSelector.addDescription(RED_LOADING_AUTO, "Auto for a red alliance robot on the match loading side.");
  UI.autoSelector.addIcon(RED_LOADING_AUTO, RIGHT_ARROW);
  UI.autoSelector.changeIconColor(RED_LOADING_AUTO, black);
    
  //Skills Page
  UI.autoSelector.addAutoTab("Skills");
  UI.autoSelector.addButton(SKILLS_AUTO_BASIC, 0xff10a0);
  UI.autoSelector.addTitle(SKILLS_AUTO_BASIC, "Skills 1");
  UI.autoSelector.addDescription(SKILLS_AUTO_BASIC, "Skills auto that just shoots match loads into the field.");
  UI.autoSelector.addIcon(SKILLS_AUTO_BASIC, SKILLS_ICON);
  UI.autoSelector.changeIconColor(SKILLS_AUTO_BASIC, black);

  //Other Page
  UI.autoSelector.addAutoTab("Other");
  UI.autoSelector.addButton(16, noAlliance);
  UI.autoSelector.addTitle(16, "Built In");
  UI.autoSelector.addCallbackFunc(16, testCallback);
  UI.autoSelector.addIcon(16, EXCLAMATION_POINTS);

  UI.autoSelector.addButton(20, noAlliance);
  UI.autoSelector.addTitle(20, "Test");
  UI.autoSelector.addCallbackFunc(20, testCallback);
  UI.autoSelector.addIcon(20, Exclamation_Points);
  UI.autoSelector.changeIconColor(20, black);

  //Preauto UI Parameters
  UI.autoSelector.setDisplayTime(1500);
  UI.autoSelector.selectButton(BLUE_LOADING_AUTO, true);
  UI.setManualControl(true);
  UI.setUIMode(UIStates::Preauto_UI);

  /* UI.addMatchTab("Brain");
  UI.createBrainDisplay(0, "Capacity: ");
  UI.setBrainDisplayColor(0, ClrSteelBlue);
  UI.setBrainDisplayData(0, &batteryCapacity, matchDisplayDataType::UINT);

  UI.createBrainDisplay(2, "Current: ");
  UI.setBrainDisplayColor(2, ClrSteelBlue);
  UI.setBrainDisplayData(2, &batteryCurrent, matchDisplayDataType::DOUBLE);

  UI.createBrainDisplay(4, "Voltage: ");
  UI.setBrainDisplayColor(4, ClrSteelBlue);
  UI.setBrainDisplayData(4, &batteryVoltage, matchDisplayDataType::DOUBLE);

  UI.createBrainDisplay(6, "Temp: ");
  UI.setBrainDisplayColor(6, red);
  UI.setBrainDisplayData(6, &batteryTemperature, matchDisplayDataType::DOUBLE);

  UI.createBrainDisplay(1, "Func: ");
  UI.setBrainDisplayColor(1, ClrForestGreen);
  UI.setBrainDisplayData(1, testFunc);

  UI.addMatchTab("Other");
  UI.createBrainDisplay(8, "Test 1:"); */

  //*Primary Controller UI
  //Battery info
  UI.primaryControllerUI.addData(0, "Battery:");
  UI.primaryControllerUI.addData(1, "  Capacity: ", batteryCapacity);
  UI.primaryControllerUI.addData(2, "  Voltage: ", batteryVoltage);
  UI.primaryControllerUI.addData(3, "  Current: ", batteryCurrent);
  UI.primaryControllerUI.addData(4, "  Temperature: ", batteryTemperature);

  UI.primaryControllerUI.addData(6, "UI:");
  UI.primaryControllerUI.addData(7, "  Preauto ID: ", selectedProgramID);
  UI.primaryControllerUI.addData(8, "  Button Count: ", preautoUIButtons);

  //Have buttons scroll the screen up and down
  primaryController.ButtonDown.pressed(scrollDown);
  primaryController.ButtonUp.pressed(scrollUp);

  //Start UI Thread
  UI.startUI();

  //timer toggleTimer;

  while(1)
  {
    //Update stored variables
    batteryCapacity = Brain.Battery.capacity();
    batteryTemperature = Brain.Battery.temperature(fahrenheit);
    batteryCurrent = Brain.Battery.current();
    batteryVoltage = Brain.Battery.voltage();
    selectedProgramID = UI.autoSelector.getProgNumber();
    preautoUIButtons = UI.autoSelector.getButtonCount();

    /* if(toggleTimer.time() >= 1000)
    {
      toggleTimer = 0;

      if(UI.getUIMode() == UIStates::Match_UI)
      {
        UI.setUIMode(UIStates::Preauto_UI);
      }

      else
      {
        UI.setUIMode(UIStates::Match_UI);
      }
    } */

    // Allow other tasks to run
    this_thread::sleep_for(40);
  }
}