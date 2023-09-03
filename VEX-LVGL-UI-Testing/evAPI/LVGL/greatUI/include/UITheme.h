/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UITheme.h                                                 */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Sep 2 2023                                            */
/*    Description:  Data for LVGL UI Themes                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __UI_THEME_H__
#define __UI_THEME_H__

#include "v5lvgl.h"
#include "vex.h"

namespace evAPI
{
  class UITheme
  {
    private:
      lv_style_t backgroundStyle;
      lv_style_t textStyle;

    public:
      UITheme(color backgroundColor, color textColor);
      ~UITheme();

      lv_style_t getBackgroundData();
      lv_style_t getTextData();
  };
  
  extern const UITheme darkModeStyle;
  extern const UITheme lightModeStyle;
} // namespace evAPI

#endif