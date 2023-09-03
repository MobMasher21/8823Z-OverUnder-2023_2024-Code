/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UITheme.cpp                                               */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Sep 2 2023                                            */
/*    Description:  Data for LVGL UI Themes                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/UITheme.h"
#include "../../../Common/include/colors.h"

namespace evAPI
{
  UITheme::UITheme(color backgroundColor, color textColor)
  {
    lv_style_init(&backgroundStyle);
    lv_style_set_bg_color(&backgroundStyle, lv_color_hex(backgroundColor.rgb()));

    lv_style_init(&textStyle);
    lv_style_set_bg_color(&textStyle, lv_color_hex(textColor.rgb()));
  }
  
  UITheme::~UITheme()
  {
  }

  lv_style_t *UITheme::getBackgroundData()
  { return &backgroundStyle; }

  lv_style_t UITheme::getTextData()
  { return textStyle; }

  const UITheme darkModeStyle(darkBackgroundColor, white);
  const UITheme lightModeStyle(white, darkBackgroundColor);
} // namespace evAPI
