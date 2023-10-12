/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vexLVGL.cpp                                               */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Tue Sep 5 2023                                            */
/*    Description:  LVGL setup used with the evAPI.                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "../include/vexLVGL.h"
#include "../../../Common/include/vexPrivateRebuild.h"

#define BRAIN_HORIZONTAL_RESOLUTION 480
#define BRAIN_VERTICAL_RESOLUTION 240

#define LVGL_RUN_RATE 4

using namespace vex;

lv_disp_draw_buf_t displayBuffer;
lv_color_t colorBuffer1[BRAIN_HORIZONTAL_RESOLUTION * BRAIN_VERTICAL_RESOLUTION];
lv_color_t colorBuffer2[BRAIN_HORIZONTAL_RESOLUTION * BRAIN_VERTICAL_RESOLUTION];

lv_indev_drv_t touchDriver;

lv_disp_drv_t lvglDisplayDriver;
lv_disp_t *lvglDisplay;

lv_obj_t *startingScreen;

thread *LVGLThread;

bool lvglStarted = false;

namespace evAPI
{
 static void flushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
  {
    vexDisplayCopyRect(area->x1, area->y1, area->x2, area->y2, (uint32_t*)color_p, area->x2 - area->x1 + 1);
    lv_disp_flush_ready(disp_drv);
  } 

  static void getTouchData(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
  {
    V5_TouchStatus touchState;
    vexTouchDataGet(&touchState);

    if(touchState.lastEvent == kTouchEventPress)
    { data->state = LV_INDEV_STATE_PR; }

    else if( touchState.lastEvent == kTouchEventRelease )
    { data->state = LV_INDEV_STATE_REL; }

    data->point.x = touchState.lastXpos;
    data->point.y = touchState.lastYpos;
  }

  int lvglThreadFunc()
  {
    while(true)
    {
      lv_tick_inc(LVGL_RUN_RATE);
      lv_task_handler();
      vexTaskSleep(LVGL_RUN_RATE);
    }

    return(0);
  }

  void startLVGL()
  {
    //Return if LVGL has already started
    if(!lvglStarted)
    {
      lvglStarted = true;
    }

    else
    {
      return;
    }

    lv_init();

    //Create display driver and set parameters
    lv_disp_draw_buf_init(&displayBuffer,
      colorBuffer1,
      colorBuffer2,
      (BRAIN_HORIZONTAL_RESOLUTION * BRAIN_VERTICAL_RESOLUTION)
    );

    lv_disp_drv_init(&lvglDisplayDriver);

    lvglDisplayDriver.hor_res = BRAIN_HORIZONTAL_RESOLUTION;
    lvglDisplayDriver.ver_res = BRAIN_VERTICAL_RESOLUTION;
    lvglDisplayDriver.flush_cb = flushDisplay;
    lvglDisplayDriver.draw_buf = &displayBuffer;

    //Setup display
    lvglDisplay = lv_disp_drv_register(&lvglDisplayDriver);

    //Setup touchscreen driver
    lv_indev_drv_init(&touchDriver);
    touchDriver.type = LV_INDEV_TYPE_POINTER;
    touchDriver.read_cb = getTouchData;
    lv_indev_drv_register(&touchDriver);

    //Setup first screen
    startingScreen = lv_obj_create(NULL);
    lv_scr_load(startingScreen);

    //Start thread for LVGL.
    LVGLThread = new thread(lvglThreadFunc);
  }
} // namespace evAPI