/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       preautoButton.hpp                                         */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Aug 6, 2023                                               */
/*    Description:  Button structure used for storing the preauto buttons.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "vex.h"
#include "lvgl.h"
#include "../evAPI/Common/include/evNamespace.h"
#include "../evAPI/Common/include/colors.h"
#include "../evAPI/Common/include/evColor.h"
#include "../evAPI/Common/include/evErrorTypes.hpp"

namespace evAPI
{
  enum class iconType
  {
    No_Icon = 0,

    //Builtin Icons
    Skills_Icon = 1,
    Left_Arrow = 2,
    Right_Arrow = 3,
    Exclamation_Points = 4,

    Custom_Icon
  };

  class preautoButton
  {
    private:
      //The ID of the button
      uint buttonID;

      /**
       * @brief An optional callback that runs whenever the button is pressed.
      */
      void (*buttonCallback)(uint) = nullptr;

      /**
       * @brief A function that runs whenever the button is pressed. It controls button selection, highlighting,
       * the button info display, and running the optional button callback.
      */
      void (*pressedCallback)(lv_event_t *event);

      //Title for the button info box
      std::string Title = "NULL";

      //Description for the button info box
      std::string Description = "NULL";

      //Alliance associated with the button
      allianceType buttonAlliance = noChange;

      //*LVGL Objects
      //The core button object in LVGL
      lv_obj_t *LVGLButton;

      //ID of the Icon
      lv_obj_t *LVGLButtonID;

      //A label that sores the title of the button
      lv_obj_t *LVGLButtonTitle;

      //The icon of the button
      lv_obj_t *LVGLButtonIcon = nullptr;

      /* //Image of a custom icon
      lv_img_dsc_t LVGLCustomIcon; */

    public:
      /**
       * @brief A constructor for the preautoButton object.
       * @param id The ID of the button.
       * @param x The x-position of the button.
       * @param y The y-position of the button.
       * @param tab The address of the tab the button is attached to.
       * @param callback A function to run when the button is pressed.
      */
      preautoButton(uint id, int x, int y, lv_obj_t *tab, void (*callback)(lv_event_t *event));
      
      /**
       * @brief A destructor for the button.
      */
      ~preautoButton();

      /**
       * @brief Sets the color of the button.
       * @param color The color of the button.
      */
      void setButtonColor(evColor color);

      /**
       * @brief Sets the color of the button depending on the alliance input.
       * @param alliance The alliance of the robot.
      */
      void setButtonColor(allianceType alliance);

      /**
       * @brief Sets the title of the button.
       * @param title A character array containing the title.
      */
      void setTitle(const char *title);

      /**
       * @brief Sets the description of the button.
       * @param title A character array containing the description.
      */
      void setDescription(const char *description);

      /**
       * @brief Sets the alliance of the button. Will not change its color.
       * @param alliance The alliance of the robot.
      */
      void setAlliance(allianceType alliance);

      /**
       * @brief Sets the icon of the button to one of the builtin icons.
       * @param icon A builtin icon to use for the button.
       * @param iconColor The color the icon will be.
       * @returns An evError.
       *          Invalid_Argument_Data: If the icon type if Custom_Icon.
       *          No_Error: If the icon was added successful.
      */
      evError setIcon(iconType icon, evColor iconColor);

      /**
       * @brief Sets the icon of the button to a user defined icon.
       * @param icon An icon to display on the button.
       * @param iconColor The color the icon will be.
       * @returns An evError.
       *          No_Error: If the icon was added successful.
      */
      void setIcon(const lv_img_dsc_t &icon, evColor iconColor);

      /**
       * @brief Sets the color of the icon.
       * @param iconColor The color of the icon.
       * @returns An evError.
       *          Object_Property_Not_Specified: If the icon wasn't created.
       *          No_Error: If the icon color was changed successful.
      */
      evError changeIconColor(evColor iconColor);

      /**
       * @brief Sets the optional callback for the button to run when it is pressed.
       * @param callback A function with an int argument. The ID will be passed into the function.
       * @returns An evError.
       *          Invalid_Argument_Data: If the callback function was invalid.
       *          No_Error: If the callback was added successfully.
      */
      evError setCallbackFunction(void (*callback)(uint));

      /**
       * @brief Selects the button. It will also set the alliance of the robot to match that of
       *        the button.
      */
      void selectButton();

      /**
       * @brief Deselects the button.
      */
      void deselectButton();

      /**
       * @returns The title as an evErrorData structure with the std::string type.
       *          Object_Property_Not_Specified: If the title wasn't specified.
       *          No_Error: If the title was returned successfully + The title.
      */
      evErrorString &getTitle();

      /**
       * @returns The description as an evErrorData structure with the std::string type.
       *          Object_Property_Not_Specified: If the description wasn't specified.
       *          No_Error: If the description was returned successfully + The description.
      */
      evErrorString &getDescription();
  };
} //evAPI

#endif // BUTTON_H
