/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       button.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Button structure used for storing info about buttons      */
/*                  until they are created in LVGL.                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef BUTTON_H
#define BUTTON_H

#include "vex.h"
#include "v5lvgl.h"
#include "..\..\..\Common\include\evNamespace.h"
#include "..\..\..\Common\include\colors.h"


#define MAX_TITLE_LENGTH 16
#define MAX_DESCRIPTION_LENGTH 240

namespace evAPI
{
  struct button
  {
    int buttonID;
    int xPos;
    int yPos;
    int width;
    int hight;
    
    void (*buttonCallback)(int);

    color buttonColor;

    allianceType buttonAlliance = noAlliance;

    char Title[MAX_TITLE_LENGTH];
    char Description[MAX_DESCRIPTION_LENGTH];
    int titleLength = 0;
    int descriptionLength = 0;
  };
} //evAPI

#endif // BUTTON_H
