/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       matchDisplay.h                                            */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Aug 23 2023                                           */
/*    Description:  Structure for storing data for the match UI.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef MATCHDISPLAY_H
#define MATCHDISPLAY_H

#include <string>
#include "vex.h"
#include "evAPISettings.h"
#include "lvgl.h"

namespace evAPI
{
  //All the types of data the brain displays can have
  enum class matchDisplayDataType
  {
    NULL_DATA = 0,
    INT,
    UINT,
    LONG,
    ULONG,
    FLOAT,
    DOUBLE,
    FUNC_INT,
    FUNC_DOUBLE
  };
  
  struct matchDisplay
  {
    //Name
    std::string Name;

    //Data to display
    union
    {
      //Pointer to an address of a variable
      void *displayData;

      //Function to run that returns an int
      int (*funcInt)();

      //Function to run that returns a double
      double (*funcDouble)();
    };

    //What type of data to display
    matchDisplayDataType dataType = matchDisplayDataType::NULL_DATA;

    //Match display color
    color graphColor = blue;

    //*LVGL Objects
    //The core match display object
    lv_obj_t *LVGLMatchDisplay;

    //A label that stores the ID of the match display
    lv_obj_t *LVGLMatchDisplayIDLabel;

    //A label that stores the title of the match display
    lv_obj_t *LVGLMatchDisplayTitle;

    //The style of the match display
    lv_style_t LVGLMatchDisplayStyle;
  };
};
#endif // MATCHDISPLAY_H