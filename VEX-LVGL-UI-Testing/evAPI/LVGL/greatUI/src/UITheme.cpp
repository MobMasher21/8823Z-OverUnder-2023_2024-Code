/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UITheme.cpp                                               */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Sep 2 2023                                            */
/*    Description:  Data for LVGL UI Themes                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <algorithm>
#include "../include/UITheme.h"
#include "../../../Common/include/colors.h"

namespace evAPI
{

  UITheme::UITheme(evColor backgroundColor, evColor textColor)
  {
    _backgroundColor = backgroundColor;
    _textColor = textColor;
    _tabTextColor = textColor;

    if(backgroundColor.getColorBrightness() < 20)
    { _tabBackgroundColor = lv_color_lighten(backgroundColor, 10); }

    else
    { _tabBackgroundColor = lv_color_darken(backgroundColor, 10); }
  }

  UITheme::UITheme(int backgroundColor, int textColor)
  {
    _backgroundColor = evColor(backgroundColor);
    _textColor = evColor(textColor);
    _tabTextColor = evColor(textColor);

    if(_backgroundColor.getColorBrightness() < 20)
    { _tabBackgroundColor = lv_color_lighten(_backgroundColor, 10); }

    else
    { _tabBackgroundColor = lv_color_darken(_backgroundColor, 10); }
  }

  UITheme::UITheme(evColor backgroundColor, evColor textColor, evColor tabBackgroundColor, evColor tabTextColor)
  {
    _backgroundColor = backgroundColor;
    _textColor = textColor;
    _tabBackgroundColor = tabBackgroundColor;
    _tabTextColor = tabTextColor;
  }

  UITheme::UITheme(int backgroundColor, int textColor, int tabBackgroundColor, int tabTextColor)
  {
    _backgroundColor = evColor(backgroundColor);
    _textColor = evColor(textColor);
    _tabBackgroundColor = evColor(tabBackgroundColor);
    _tabTextColor = evColor(tabTextColor);
  }
  
  UITheme::~UITheme()
  {}

  lv_style_t UITheme::getThemeData(themeData data)
  {
    if(data == themeData::BackgroundTheme)
    {
      //Create style now to prevent memory errors due to LVGL not being initalized.
      if(!backgroundStyleInit)
      {
        lv_style_init(&backgroundStyle);
        backgroundStyleInit = true;
      }

      lv_style_set_bg_color(&backgroundStyle, _backgroundColor);
      lv_style_set_text_color(&backgroundStyle, _textColor);
      //printf("Background Hex Color: %x\n", _backgroundColor);
      return backgroundStyle;
    }

    else
    {
      //Create style now to prevent memory errors due to LVGL not being initalized.
      if(!tabStyleInit)
      {
        lv_style_init(&tabStyle);
        tabStyleInit = true;
      }

      lv_style_set_bg_color(&tabStyle, _backgroundColor);
      lv_style_set_text_color(&tabStyle, _textColor);
      //printf("Background Hex Color: %x\n", _backgroundColor);
      return tabStyle;
    }
  }

  UITheme darkModeStyle(0x15171a, 0xFFFFFF);
  UITheme lightModeStyle(0xFFFFFF, 0x15171a);
} // namespace evAPI