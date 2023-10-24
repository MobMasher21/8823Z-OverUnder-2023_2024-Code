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

#define BLUE_SCORING_AUTO 0
#define BLUE_LOADING_AUTO 4
#define RED_SCORING_AUTO 3
#define RED_LOADING_AUTO 7
#define SKILLS_AUTO_BASIC 8

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

LV_IMG_DECLARE(Exclamation_Points)

void testCallback(u_int id)
{
  printf("Button %i was pressed.\n\n", id);
}

uint batteryCapacity = Brain.Battery.capacity();
double batteryTemperature = Brain.Battery.temperature(celsius);
double batteryCurrent = Brain.Battery.current();
double batteryVoltage = Brain.Battery.voltage();

double testFunc()
{
  static double var = 0;

  if(var > 100)
  { var = 0; }

  else
  { var += 0.357; }

  return var;
}

int main() {
  //Auto Page
  UI.autoSelector.addAutoTab("Auto");
  UI.autoSelector.addButton(BLUE_SCORING_AUTO, blue);
  UI.autoSelector.addTitle(BLUE_SCORING_AUTO, "Scoring");
  UI.autoSelector.addDescription(BLUE_SCORING_AUTO, "Auto for a blue alliance robot on the scoring side.");
  UI.autoSelector.addIcon(BLUE_SCORING_AUTO, iconType::Left_Arrow);
  UI.autoSelector.changeIconColor(BLUE_SCORING_AUTO, black);
  UI.autoSelector.addCallbackFunc(BLUE_SCORING_AUTO, testCallback);

  UI.autoSelector.addButton(BLUE_LOADING_AUTO, blue);
  UI.autoSelector.addTitle(BLUE_LOADING_AUTO, "Load");
  UI.autoSelector.addDescription(BLUE_LOADING_AUTO, "Auto for a blue alliance robot on the match loading side.");
  UI.autoSelector.addIcon(BLUE_LOADING_AUTO, iconType::Right_Arrow);
  UI.autoSelector.changeIconColor(BLUE_LOADING_AUTO, black);

  UI.autoSelector.addButton(RED_SCORING_AUTO, red);
  UI.autoSelector.addTitle(RED_SCORING_AUTO, "Scoring");
  UI.autoSelector.addDescription(RED_SCORING_AUTO, "Auto for a red alliance robot on the scoring side.");
  UI.autoSelector.addIcon(RED_SCORING_AUTO, iconType::Left_Arrow);
  UI.autoSelector.changeIconColor(RED_SCORING_AUTO, black);

  UI.autoSelector.addButton(RED_LOADING_AUTO, red);
  UI.autoSelector.addTitle(RED_LOADING_AUTO, "Load");
  UI.autoSelector.addDescription(RED_LOADING_AUTO, "Auto for a red alliance robot on the match loading side.");
  UI.autoSelector.addIcon(RED_LOADING_AUTO, iconType::Right_Arrow);
  UI.autoSelector.changeIconColor(RED_LOADING_AUTO, black);
    
  //Skills Page
  UI.autoSelector.addAutoTab("Skills");
  UI.autoSelector.addButton(SKILLS_AUTO_BASIC, 0xff, 0x10, 0xa0);
  UI.autoSelector.addTitle(SKILLS_AUTO_BASIC, "Skills 1");
  UI.autoSelector.addDescription(SKILLS_AUTO_BASIC, "Skills auto that just shoots match loads into the field.");
  UI.autoSelector.addIcon(SKILLS_AUTO_BASIC, iconType::Skills_Icon);
  UI.autoSelector.changeIconColor(SKILLS_AUTO_BASIC, black);

  //Other Page
  UI.autoSelector.addAutoTab("Other");
  UI.autoSelector.addButton(16, noAlliance);
  UI.autoSelector.addTitle(16, "Built In");
  UI.autoSelector.addCallbackFunc(16, testCallback);
  UI.autoSelector.addIcon(16, iconType::Exclamation_Points);

  UI.autoSelector.addButton(20, noAlliance);
  UI.autoSelector.addTitle(20, "Dance");
  UI.autoSelector.addCallbackFunc(20, testCallback);
  UI.autoSelector.addIcon(20, &Exclamation_Points);
  UI.autoSelector.changeIconColor(20, black);

  //UI.autoSelector.setDisplayTime(1500);

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

  //UI.startUI();
  //UI.autoSelector.selectButton(BLUE_LOADING_AUTO, true);

  //UI.setManualControl(false);

  /* startLVGL();

  const char * codeData = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

  lv_color_hsv_t hsvColor;
  hsvColor.h = 121;
  hsvColor.s = 76;
  hsvColor.v = 34;

  evColor qrCodeColor = hsvColor;
  evColor defaultBackgroundColor = vexDisplayBackgroundDark;

  lv_obj_t * qrCode = lv_qrcode_create(lv_scr_act(), 150, qrCodeColor, defaultBackgroundColor);
  lv_qrcode_update(qrCode, codeData, strlen(codeData));

  lv_obj_center(qrCode);

  evColorData qrCodeColorInfoRGB = qrCodeColor.rgbData();
  evColorData qrCodeColorInfoHSV = qrCodeColor.hsvData();

  printf("QR Code Color Red: %d\n", qrCodeColorInfoRGB.red);
  printf("QR Code Color Green: %d\n", qrCodeColorInfoRGB.green);
  printf("QR Code Color Blue: %d\n", qrCodeColorInfoRGB.blue);
  printf("\n");
  printf("QR Code Color Hue: %d\n", qrCodeColorInfoHSV.hue);
  printf("QR Code Color Saturation: %d\n", qrCodeColorInfoHSV.saturation);
  printf("QR Code Color Value: %d\n", qrCodeColorInfoHSV.value);
  printf("\n"); */

  //wait(20, msec);
  //timer toggleTimer;
  //UI.setUIMode(UIStates::Match_UI);

  while(1)
  {
    batteryCapacity = Brain.Battery.capacity();
    batteryTemperature = Brain.Battery.temperature(celsius);
    batteryCurrent = Brain.Battery.current();
    batteryVoltage = Brain.Battery.voltage();

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