/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       evColor.h                                                 */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      05 Sep 2023                                               */
/*    Description:  Color class with more color formats/                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef EVCOLOR_H
#define EVCOLOR_H

#include "vex.h"
#include "evAPISettings.h"

#if ENABLE_LVGL_COLOR == 0
  #define USE_LVGL_COLOR 0
#elif ENABLE_LVGL_COLOR == 1
  #ifdef __has_include
    #if __has_include("lvgl.h")
      #define USE_LVGL_COLOR 1
    #else
      #define USE_LVGL_COLOR 0
    #endif
  #elif
    #define USE_LVGL_COLOR 1
  #endif
#elif ENABLE_LVGL_COLOR >= 2
  #define USE_LVGL_COLOR 1
#endif

#if USE_LVGL_COLOR == 1
  #include "../../../lvgl/src/misc/lv_color.h"
#endif

namespace evAPI
{
  /**
   * @brief An object that can store data in either an RGB format or an HSV format, not both at the same time.
   * @param isRGB A bool that returns true if the data stored is in an RGB format.
   * @param red The amount of red in the color.
   * @param green The amount of red in the color.
   * @param blue The amount of red in the color.
   * @param hue The hue value of the color.
   * @param saturation The saturation value of the color.
   * @param value The brightness of the color.
  */
  struct evColorData
  {
    bool isRGB;

    union
    {
      uint8_t red;
      uint16_t hue;
    };
    
    union
    {
      uint8_t green;
      uint8_t saturation;
    };
    
    union
    {
      uint8_t blue;
      uint8_t value;
    };
  };

  /**
   * @brief A color class that is able to be used with the standard vex color objects, RGB colors, HSV colors,
   * and LVGL colors.
  */
  class evColor
  {
    private:
      uint32_t _rgb = 0x000000;
      bool _transparent = false;

      /**
       * @brief Creates an evColor object with 3 separate hue, saturation, and brightness(value) values.
       * Private now due to having similar arguments to the RGB constructor.
       * @param hue The hue of the color.
       * @param saturation The saturation of the color.
       * @param value The brightness of the color.
      */
      evColor(uint16_t hue, uint8_t saturation, uint8_t value);
    public:
      //!Constructors

      /**
       * @brief Empty constructor.
      */
      evColor();

      /**
       * @brief Creates an evColor object with 3 separate red, green, and blue values.
       * @param red The amount of red from 0-100.
       * @param green The amount of green from 0-100.
       * @param blue The amount of blue from 0-100.
      */
      evColor(uint8_t red, uint8_t green, uint8_t blue);

      /**
       * @brief Creates an evColor object with an RGB value stored in an int.
       * @param color An int containing the RGB color.
      */
      evColor(uint32_t color);

      /**
       * @brief Creates an evColor object with a vex color object.
       * @param color The vex color object.
      */
      evColor(color Color);

      /**
       * @brief Creates an evColor object with an evColorData object storing either RGB or HSV color data.
       * @param color The evColorData color object.
      */
      evColor(evColorData Color);

      /**
       * @brief Creates an evColor object with an RGB value stored in an int and a transparency flag.
       * Here to help with compatibility with vex color objects and functions with them as paramater.
       * @param color An int containing the RGB color.
       * @param isTransparent Controls if the color is transparent.
      */
      evColor(uint32_t color, bool isTransparent);

      #if USE_LVGL_COLOR == 1
        /**
         * @brief Creates an evColor object with an LVGL color object/
         * @param color The LVGL color object.
        */
        evColor(lv_color_t color);

        /**
         * @brief Creates an evColor object with an LVGL HSV object/
         * @param color The LVGL HSV object.
        */
        evColor(lv_color_hsv_t color);
      #endif

      ~evColor();

      //!Assignment
      /**
       * @brief Sets the color of the evColor to an RGB value stored as an int.
       * @param color An int containing the RGB color.
       * @returns The color the evColor was set to.
      */
      uint32_t rgb(uint32_t color);

      /**
       * @brief Sets the color of the evColor with 3 separate red, green, and blue values.
       * @param red The amount of red from 0-100.
       * @param green The amount of green from 0-100.
       * @param blue The amount of blue from 0-100.
       * @returns The color the evColor was set to as an int.
      */
      uint32_t rgb(uint8_t red, uint8_t green, uint8_t blue);

      /**
       * @brief Creates an evColor object with the color values from the HSV color put in.
       * @param hue The hue of the color.
       * @param saturation The saturation of the color.
       * @param value The brightness of the color.
       * @param setCurrentColor Optional. Sets the color of the object that ran the command if true.
       * @returns An evColor object containing the color data.
      */
      evColor& hsv(uint16_t hue, uint8_t saturation, uint8_t value, bool setCurrentColor = false);

      #if USE_LVGL_COLOR == 1
        /**
         * @brief Creates an evColor object with a LVGL color object.
         * @param color The LVGL color object.
         * @param setCurrentColor Optional. Sets the color of the object that ran the command if true.
         * @returns An evColor object containing the color data.
        */
        evColor& lvglColor(lv_color_t color, bool setCurrentColor = false);

        /**
         * @brief Creates an evColor object with a LVGL HSV object.
         * @param color The LVGL HSV object.
         * @param setCurrentColor Optional. Sets the color of the object that ran the command if true.
         * @returns An evColor object containing the color data.
        */
        evColor& lvglColorHsv(lv_color_hsv_t color, bool setCurrentColor = false);
      #endif

      //TODO: ADD ACTUAL CODE AND NOT JUST A WRAPPER.
      /**
       * @brief Creates an evColor object with a web color put in.
       * @param color A string containing the color data.
       * @param setCurrentColor Optional. Sets the color of the object that ran the command if true.
       * @returns An evColor object containing the color data.
      */
      evColor& web(const char * color, bool setCurrentColor = false); 

      void operator=(uint32_t value);
      void operator=(color value);

      #if USE_LVGL_COLOR == 1
        void operator=(lv_color_t color);
        void operator=(lv_color_hsv_t color);
      #endif

      //!Get Value
      /**
       * @returns The color the evColor was set to as an int.
      */
      uint32_t rgb();
      operator uint32_t();
      operator color();

      #if USE_LVGL_COLOR == 1
        operator lv_color_t();
        operator lv_color_hsv_t();
      #endif

      /**
       * @returns An evColorData object storing RGB data for the color.
      */
      evColorData& rgbData();

      /**
       * @returns An evColorData object storing HSV data for the color.
       * @link //https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
      */
      evColorData& hsvData();

      /**
       * @returns True if the color is transparent.
      */
      bool isTransparent();

      //!Other
      /**
       * @returns The brightness of the color between 0 - 100.
      */
      uint getColorBrightness(void);

      /**
       * @brief A function that takes in a color and returns the brightness in HSV format.
       * @param color An RGB color as an integer.
       * @returns A brightness value between 0 - 100.
      */
      uint getColorBrightness(int color);

      /**
       * @brief A function that takes in a color and returns the brightness in HSV format.
       * @param color A vex color object.
       * @returns A brightness value between 0 - 100.
      */
      uint getColorBrightness(color color);

      /**
       * @brief A function that takes in a color and returns the brightness in HSV format.
       * @param color An evAPI color object.
       * @returns A brightness value between 0 - 100.
      */
      uint getColorBrightness(evColor color);
  };
  
} // namespace evAPI

#endif // EVCOLOR_H