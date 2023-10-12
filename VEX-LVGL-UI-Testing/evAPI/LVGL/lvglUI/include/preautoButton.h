/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       preautoButton.h                                           */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Button structure used for storing the preauto buttons.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "vex.h"
#include "lvgl.h"
#include "evAPISettings.h"
#include "../../../Common/include/evNamespace.h"
#include "../../../Common/include/colors.h"

namespace evAPI
{
  struct preautoButton
  {
    //ID of the button
    int buttonID;

    //Location of the button
    int xPos;
    int yPos;

    //Size of the button
    int width;
    int hight;
    
    //Function the button can run when pressed
    void (*buttonCallback)(int);

    //Color of the button
    color buttonColor;

    //Icon parameters
    int iconID = -1;
    lv_img_dsc_t buttonIconCustom;
    color iconColor = black;

    //Alliance associated with the button
    allianceType buttonAlliance = noChange;

    //Title
    std::string Title;

    //Description
    std::string Description;

    //*LVGL Object parameters
    //The core button object in LVGL
    lv_obj_t *LVGLButton;

    //A label that stores the ID of the button
    lv_obj_t *LVGLButtonID;

    //A label that sores the title of the button
    lv_obj_t *LVGLButtonTitle;

    //The style of the button
    lv_style_t LVGLButtonStyle;

    //The icon of the button
    lv_obj_t *LVGLButtonIcon;

    //The color of the button icon
    lv_color_t LVGLButtonIconColor;
  };
} //evAPI

#endif // BUTTON_H
