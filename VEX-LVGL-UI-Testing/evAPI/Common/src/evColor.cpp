/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       evColor.cpp                                               */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      05 Sep 2023                                               */
/*    Description:  Color class with more color formats/                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <algorithm>
#include "../include/evColor.h"

namespace evAPI
{
  //!Constructors
  evColor::evColor()
  {}

  evColor::evColor(uint8_t red, uint8_t green, uint8_t blue)
  { _rgb = red * 0x10000 + green * 0x100  + blue; }

  evColor::evColor(uint32_t color)
  { _rgb = color; }

  evColor::evColor(color Color)
  {
    _rgb = Color.rgb();
    _transparent = Color.isTransparent();
  }

  evColor::evColor(uint16_t hue, uint8_t saturation, uint8_t value)
  {
    double hueProcessed;
    double chroma;
    double m;
    double X;
    double redProcessed;
    double greenProcessed;
    double blueProcessed;
    uint8_t redOut;
    uint8_t greenOut;
    uint8_t blueOut;

    hueProcessed = hue / 60.0;
    chroma = value * saturation;
    X = chroma * (1 - fabs(fmod(hueProcessed, 2) - 1));
    m = value - chroma;

    if(hueProcessed <= 1)
    {
      redProcessed   = chroma + m;
      greenProcessed = X + m;
      blueProcessed  = 0 + m;
    }

    else if(hueProcessed <= 2)
    {
      redProcessed = X + m;
      greenProcessed = chroma + m;
      blueProcessed = 0 + m;
    }

    else if(hueProcessed <= 3)
    {
      redProcessed   = 0 + m;
      greenProcessed = chroma + m;
      blueProcessed  = X + m;
    }

    else if(hueProcessed <= 4)
    {
      redProcessed   = 0 + m;
      greenProcessed = X + m;
      blueProcessed  = chroma + m;
    }

    else if(hueProcessed <= 5)
    {
      redProcessed   = X + m;
      greenProcessed = 0 + m;
      blueProcessed  = chroma + m;
    }
    
    else
    {
      redProcessed   = chroma + m;
      greenProcessed = 0 + m;
      blueProcessed  = X + m;
    }

    redOut   = round(redProcessed * 255);
    greenOut = round(greenProcessed * 255);
    blueOut  = round(blueProcessed * 255);

    _rgb = redOut * 0x10000 + greenOut * 0x100  + blueOut;
  }

  evColor::evColor(evColorData Color)
  {
    if(Color.isRGB) //RGB
    { evColor(Color.red, Color.green, Color.blue); }

    else //HSV
    { evColor(Color.hue, Color.saturation, Color.value); }
  }

  evColor::evColor(uint32_t color, bool isTransparent)
  {
    _rgb = color;
    _transparent = isTransparent;
  }

  #if USE_LVGL_COLOR == 1
    evColor::evColor(lv_color_t color)
    {
      auto red   = color.ch.red;
      auto green = color.ch.green;
      auto blue  = color.ch.blue;

      _rgb = red * 0x10000 + green * 0x100  + blue;
    }

    evColor::evColor(lv_color_hsv_t color)
    {
      lv_color_t tempColor = lv_color_hsv_to_rgb(color.h, color.s, color.v);
      
      auto red   = tempColor.ch.red;
      auto green = tempColor.ch.green;
      auto blue  = tempColor.ch.blue;

      _rgb = red * 0x10000 + green * 0x100  + blue;
    }
  #endif
  
  evColor::~evColor()
  {}

  //!Assignment
  uint32_t evColor::rgb(uint32_t color)
  {
    _rgb = color;
    return _rgb;
  }

  uint32_t evColor::rgb(uint8_t red, uint8_t green, uint8_t blue)
  {
    _rgb = red * 0x10000 + green * 0x100  + blue;
    return _rgb;
  }

  evColor& evColor::hsv(uint16_t hue, uint8_t saturation, uint8_t value, bool setCurrentColor)
  {
    double hueProcessed;
    double chroma;
    double m;
    double X;
    double redProcessed;
    double greenProcessed;
    double blueProcessed;
    uint8_t redOut;
    uint8_t greenOut;
    uint8_t blueOut;
    static evColor colorOut;

    hueProcessed = hue / 60.0;
    chroma = value * saturation;
    X = chroma * (1 - fabs(fmod(hueProcessed, 2) - 1));
    m = value - chroma;

    if(hueProcessed <= 1)
    {
      redProcessed   = chroma + m;
      greenProcessed = X + m;
      blueProcessed  = 0 + m;
    }

    else if(hueProcessed <= 2)
    {
      redProcessed   = X + m;
      greenProcessed = chroma + m;
      blueProcessed  = 0 + m;
    }

    else if(hueProcessed <= 3)
    {
      redProcessed   = 0 + m;
      greenProcessed = chroma + m;
      blueProcessed  = X + m;
    }

    else if(hueProcessed <= 4)
    {
      redProcessed   = 0 + m;
      greenProcessed = X + m;
      blueProcessed  = chroma + m;
    }

    else if(hueProcessed <= 5)
    {
      redProcessed   = X + m;
      greenProcessed = 0 + m;
      blueProcessed  = chroma + m;
    }
    
    else
    {
      redProcessed   = chroma + m;
      greenProcessed = 0 + m;
      blueProcessed  = X + m;
    }

    redOut   = round(redProcessed   * 255);
    greenOut = round(greenProcessed * 255);
    blueOut  = round(blueProcessed  * 255);

    colorOut.rgb(redOut * 0x10000 + greenOut * 0x100  + blueOut);

    if(setCurrentColor)
    { _rgb = colorOut.rgb(); }
    
    return colorOut;
  }

  /* uint _hexDigit(char character)
  {
    int characterInt;
    uint valueOut;

    characterInt = (int)character;
    valueOut = characterInt - 0x30U & 0xff;

    if (valueOut < 10)
    { return valueOut; }

    if (characterInt - 0x41U < 6)
    { valueOut = characterInt - 0x37; }

    else
    {
      if (5 < characterInt - 0x61U)
      { return 0; }

      valueOut = characterInt - 0x57;
    }

    return valueOut & 0xff;
  } */

  /* void evColor::web(const char * color)
  {
    size_t colorLength;
    uint32_t finalColor;
    int redColor;
    int greenColor;
    int blueColor;

    if ((*color == '#') && (colorLength = strlen(color), colorLength == 7)) {
      finalColor = strtol(color + 1,(char **)0x0,0x10);
    }
    else {
      finalColor = 0;
    }
    if ((*color == '#') && (colorLength = strlen(color), colorLength == 4)) {
      redColor = _hexDigit(color[1]);
      greenColor = _hexDigit(color[2]);
      blueColor = _hexDigit(color[3]);
      finalColor = redColor * 0x110000 + greenColor * 0x1100 + blueColor * 0x11;
    }
    
    _rgb = finalColor;
  } */

  //TODO: ADD ACTUAL CODE AND NOT JUST A WRAPPER.
  evColor& evColor::web(const char * color, bool setCurrentColor)
  {
    vex::color tempColor;
    static evColor colorOut = tempColor.web(color);

    if(setCurrentColor)
    { _rgb = colorOut.rgb(); }
    
    return colorOut;
  }

  #if USE_LVGL_COLOR == 1
    evColor& evColor::lvglColor(lv_color_t color, bool setCurrentColor)
    {
      static evColor colorOut;

      auto red   = color.ch.red;
      auto green = color.ch.green;
      auto blue  = color.ch.blue;

      colorOut = red * 0x10000 + green * 0x100  + blue;
  
      if(setCurrentColor)
      { _rgb = colorOut.rgb(); }
       
      return colorOut;
    }

    evColor& evColor::lvglColorHsv(lv_color_hsv_t color, bool setCurrentColor)
    {
      static evColor colorOut;
      lv_color_t tempColor = lv_color_hsv_to_rgb(color.h, color.s, color.v);
      colorOut = lvglColor(tempColor, setCurrentColor);
      return colorOut;
    }
  #endif

  void evColor::operator=(uint32_t value)
  { _rgb = value; }

  void evColor::operator=(color value)
  { 
    _rgb = value.rgb();
    _transparent = value.isTransparent();
  }

  #if USE_LVGL_COLOR == 1
    void evColor::operator=(lv_color_t color)
    {
      auto red   = color.ch.red;
      auto green = color.ch.green;
      auto blue  = color.ch.blue;

      _rgb = red * 0x10000 + green * 0x100  + blue;
    }

    void evColor::operator=(lv_color_hsv_t color)
    {
      lv_color_t tempColor;
      tempColor = lv_color_hsv_to_rgb(color.h, color.s, color.v);
      
      auto red   = tempColor.ch.red;
      auto green = tempColor.ch.green;
      auto blue  = tempColor.ch.blue;

      _rgb = red * 0x10000 + green * 0x100  + blue;
    }
  #endif

  //!Get Value
  uint32_t evColor::rgb()
  { return _rgb; }

  evColor::operator uint32_t()
  { return _rgb; }

  evColor::operator color()
  {
    static vex::color returnColor;

    if(_transparent) //Enables transparency on the returned color if evColor is transparent.
    { returnColor = transparent; }

    else //Clears transparency if the evColor isn't transparent.
    { returnColor.rgb(0); }

    //The only method of setting a rgb value for vex::color without setting _transparent to false.
    returnColor = _rgb; 
    return returnColor;
  }

  #if USE_LVGL_COLOR == 1
    evColor::operator lv_color_t()
    {
      static lv_color_t returnColor;
      returnColor = lv_color_hex(_rgb);
      return returnColor;
    }

    evColor::operator lv_color_hsv_t()
    {
      static lv_color_hsv_t returnColor;
      
      uint8_t red   = (_rgb & 0xFF0000) >> 16;
      uint8_t green = (_rgb & 0x00FF00) >> 8;
      uint8_t blue  = (_rgb & 0x0000FF);

      returnColor = lv_color_rgb_to_hsv(red, green, blue);
      return returnColor;
    }
  #endif

  evColorData& evColor::rgbData()
  {
    static evColorData color;

    color.red   = (_rgb & 0xFF0000) >> 16;
    color.green = (_rgb & 0x00FF00) >> 8;
    color.blue  = (_rgb & 0x0000FF);
    color.isRGB = true;

    return color;
  }

  evColorData& evColor::hsvData() //https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
  {
    static evColorData colorOut;

    uint8_t redRaw   = (_rgb & 0xFF0000) >> 16;
    uint8_t greenRaw = (_rgb & 0x00FF00) >> 8;
    uint8_t blueRaw  = (_rgb & 0x0000FF);

    float red   = ((float)redRaw)   / 255;
    float green = ((float)greenRaw) / 255;
    float blue  = ((float)blueRaw)  / 255;

    float colorMax = std::max(red, std::max(green, blue));
    float colorMin = std::min(red, std::min(green, blue));
    float colorDifference = colorMax - colorMin;

    float hue;
    float saturation;
    float value;

    if(colorMax == colorMin)
    { hue = 0; }

    else if(colorMax == red)
    { hue = fmod((60 * ((green - blue) / colorDifference) + 360), 360); }

    else if(colorMax == green)
    { hue = fmod((60 * ((blue - red) / colorDifference) + 120), 360); }

    else //colorMax == blue
    { hue = fmod((60 * ((red - green) / colorDifference) + 240), 360); }

    if(colorMax == 0)
    { saturation = 0;}

    else
    { saturation = (colorDifference / colorMax) * 100; }

    value = colorMax * 100;

    colorOut.hue        = round(hue);
    colorOut.saturation = round(saturation);
    colorOut.value      = round(value);
    colorOut.isRGB      = false;

    return colorOut;
  }

  bool evColor::isTransparent()
  { return _transparent; }

  //!Other

  uint evColor::getColorBrightness(void)
  {
    float red   = ((_rgb & 0xFF0000) >> 16) / 255;
    float green = ((_rgb & 0x00FF00) >> 8) / 255;
    float blue  = ((_rgb & 0x0000FF) / 255);

    return std::max(red, std::max(green, blue)) * 100;
  }

  uint evColor::getColorBrightness(int color)
  {
    float red   = ((color & 0xFF0000) >> 16) / 255;
    float green = ((color & 0x00FF00) >> 8) / 255;
    float blue  = ((color & 0x0000FF) / 255);

    return std::round(std::max(red, std::max(green, blue)) * 100);
  }

  uint evColor::getColorBrightness(color color)
  {
    float red   = ((color.rgb() & 0xFF0000) >> 16) / 255;
    float green = ((color.rgb() & 0x00FF00) >> 8) / 255;
    float blue  = ((color.rgb() & 0x0000FF) / 255);

    return std::round(std::max(red, std::max(green, blue)) * 100);
  }

  uint evColor::getColorBrightness(evColor color)
  {
    float red   = ((color.rgb() & 0xFF0000) >> 16) / 255;
    float green = ((color.rgb() & 0x00FF00) >> 8) / 255;
    float blue  = ((color.rgb() & 0x0000FF) / 255);

    return std::round(std::max(red, std::max(green, blue)) * 100);
  }

} // namespace evAPI