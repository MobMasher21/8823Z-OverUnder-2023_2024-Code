/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UITheme.h                                                 */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Sep 2 2023                                            */
/*    Description:  Data for LVGL UI Themes                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef UITHEME_H
#define UITHEME_H

#include "lvgl.h"
#include "vex.h"
#include "../../../Common/include/evColor.h"


namespace evAPI
{
  enum class themeData
  {
    BackgroundTheme = 0,
    TabTheme,
  };
  
  class UITheme
  {
    private:
      lv_style_t backgroundStyle;
      lv_style_t tabStyle;
      bool backgroundStyleInit = false;
      bool tabStyleInit = false;

      evColor _backgroundColor;
      evColor _textColor;
      evColor _tabBackgroundColor;
      evColor _tabTextColor;

    public:
      UITheme(evColor backgroundColor, evColor textColor);
      UITheme(int backgroundColor, int textColor);
      UITheme(evColor backgroundColor, evColor textColor, evColor tabColor, evColor tabTextColor);
      UITheme(int backgroundColor, int textColor, int tabColor, int tabTextColor);
      ~UITheme();

      lv_style_t getThemeData(themeData data);
  };
  
  extern UITheme darkModeStyle;
  extern UITheme lightModeStyle;
} // namespace evAPI


#endif // UITHEME_H
