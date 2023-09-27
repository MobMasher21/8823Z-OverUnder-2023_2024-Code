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

LV_IMG_DECLARE(Exclamation_Points)

void testCallback(int id)
{
  printf("Button %d was pressed.\n\n", id);
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
  UI.setAutoTabName(0, "Auto");
  UI.addButton(BLUE_SCORING_AUTO, blue);
  UI.addTitle(BLUE_SCORING_AUTO, "Scoring");
  UI.addDescription(BLUE_SCORING_AUTO, "Auto for a blue alliance robot on the scoring side.");
  UI.addIcon(BLUE_SCORING_AUTO, LEFT_ARROW);
  UI.changeIconColor(BLUE_SCORING_AUTO, black);

  UI.addButton(BLUE_LOADING_AUTO, blue);
  UI.addTitle(BLUE_LOADING_AUTO, "Load");
  UI.addDescription(BLUE_LOADING_AUTO, "Auto for a blue alliance robot on the match loading side.");
  UI.addIcon(BLUE_LOADING_AUTO, RIGHT_ARROW);
  UI.changeIconColor(BLUE_LOADING_AUTO, black);

  UI.addButton(RED_SCORING_AUTO, red);
  UI.addTitle(RED_SCORING_AUTO, "Scoring");
  UI.addDescription(RED_SCORING_AUTO, "Auto for a red alliance robot on the scoring side.");
  UI.addIcon(RED_SCORING_AUTO, LEFT_ARROW);
  UI.changeIconColor(RED_SCORING_AUTO, black);

  UI.addButton(RED_LOADING_AUTO, red);
  UI.addTitle(RED_LOADING_AUTO, "Load");
  UI.addDescription(RED_LOADING_AUTO, "Auto for a red alliance robot on the match loading side.");
  UI.addIcon(RED_LOADING_AUTO, RIGHT_ARROW);
  UI.changeIconColor(RED_LOADING_AUTO, black);
    
  //Skills Page
  UI.setAutoTabName(1, "Skills");
  UI.addButton(SKILLS_AUTO_BASIC, 0xff, 0x10, 0xa0);
  UI.addTitle(SKILLS_AUTO_BASIC, "Skills 1");
  UI.addDescription(SKILLS_AUTO_BASIC, "Skills auto that just shoots match loads into the field.");
  UI.addIcon(SKILLS_AUTO_BASIC, SKILLS_ICON);
  UI.changeIconColor(SKILLS_AUTO_BASIC, black);

  //Other Page
  UI.setAutoTabName(2, "Other");
  UI.addButton(16, noAlliance);
  UI.addTitle(16, "Built In");
  UI.addCallbackFunc(16, testCallback);
  UI.addIcon(16, EXCLAMATION_POINTS);

  UI.addButton(20, noAlliance);
  UI.addTitle(20, "Custom");
  UI.addCallbackFunc(20, testCallback);
  UI.addIcon(20, Exclamation_Points);

  UI.setDisplayTime(1500);

  UI.setMatchTabName(0, "Brain");

  UI.createBrainDisplay(0, "Capacity: ");
  UI.setBrainDisplayColor(0, ClrSteelBlue);
  UI.setBrainDisplayData(0, &batteryCapacity, brainDataType::UINT);

  UI.createBrainDisplay(2, "Current: ");
  UI.setBrainDisplayColor(2, ClrSteelBlue);
  UI.setBrainDisplayData(2, &batteryCurrent, brainDataType::DOUBLE);

  UI.createBrainDisplay(4, "Voltage: ");
  UI.setBrainDisplayColor(4, ClrSteelBlue);
  UI.setBrainDisplayData(4, &batteryVoltage, brainDataType::DOUBLE);

  UI.createBrainDisplay(6, "Temp: ");
  UI.setBrainDisplayColor(6, red);
  UI.setBrainDisplayData(6, &batteryTemperature, brainDataType::DOUBLE);

  UI.createBrainDisplay(1, "Func: ");
  UI.setBrainDisplayColor(1, ClrForestGreen);
  UI.setBrainDisplayData(1, testFunc);

  UI.setMatchTabName(1, "Other");
  UI.createBrainDisplay(8, "Test 1:");

  UI.startUIThreads();
  UI.selectButton(BLUE_LOADING_AUTO, true);

  /* vex_lvgl_init();

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

  while(1)
  {
    batteryCapacity = Brain.Battery.capacity();
    batteryTemperature = Brain.Battery.temperature(celsius);
    batteryCurrent = Brain.Battery.current();
    batteryVoltage = Brain.Battery.voltage();

    // Allow other tasks to run
    this_thread::sleep_for(40);
  }
}