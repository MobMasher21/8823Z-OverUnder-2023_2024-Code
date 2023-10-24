/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       preautoButton.cpp                                         */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Oct 14, 2023                                              */
/*    Description:  Class for the button object used in the preauto UI.       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/preautoButton.hpp"
#include "../evAPI/Common/include/constantObjects.h"
#include "../evAPI/LVGL/lvglUI/Assets/include/UIImages.h"

namespace evAPI
{
  preautoButton::preautoButton(uint id, int x, int y, lv_obj_t *tab, void (*callback)(lv_event_t *event))
  {
    //Store the ID of the button
    buttonID = id;

    //Create the button
    LVGLButton = lv_btn_create(tab);

    //Set the size of the button
    lv_obj_set_width(LVGLButton, AUTO_BUTTON_SIZE);
    lv_obj_set_height(LVGLButton, AUTO_BUTTON_SIZE);

    //Set the position of the button
    lv_obj_set_x(LVGLButton, x);
    lv_obj_set_y(LVGLButton, y);

    //Set the style of the button
    lv_obj_set_style_bg_opa(LVGLButton, LV_OPA_100, LV_PART_MAIN);
    lv_obj_set_style_outline_width(LVGLButton, 2, LV_PART_MAIN);
    lv_obj_set_style_outline_opa(LVGLButton, 0, LV_PART_MAIN);

    //Set the outline color of the button
    #if REDEFINE_COLORS
      lv_obj_set_style_outline_color(LVGLButton, lv_color_hex(ClrLightGrey.rgb()), LV_PART_MAIN);
    #else
      lv_obj_set_style_outline_color(LVGLButton, lv_color_hex(vexClrLightGrey.rgb()), LV_PART_MAIN));
    #endif

    //Store the function to run when the button is pressed.
    pressedCallback = callback;

    //Add an event to run the button pressing code when the button is touched
    lv_obj_add_event_cb(LVGLButton, pressedCallback, LV_EVENT_ALL, NULL);

    //Create a label object on the button to store the ID of the button
    LVGLButtonID = lv_label_create(LVGLButton);
    lv_label_set_text_fmt(LVGLButtonID, "%d", id);
    lv_obj_add_flag(LVGLButtonID, LV_OBJ_FLAG_HIDDEN);

    //Create title object
    LVGLButtonTitle = lv_label_create(LVGLButton);

    //Allow the title to show up outside the button
    lv_obj_add_flag(LVGLButton, LV_OBJ_FLAG_OVERFLOW_VISIBLE);

    //Align the title to be just under the button
    lv_obj_align_to(LVGLButtonTitle, LVGLButton, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);

    //Hide the title
    lv_obj_add_flag(LVGLButtonTitle, LV_OBJ_FLAG_HIDDEN);
  }

  preautoButton::~preautoButton()
  {
    //Delete the button and all objects associated with it
    lv_obj_del(LVGLButton);
  }

  void preautoButton::setButtonColor(evColor color)
  {
    lv_obj_set_style_bg_color(LVGLButton, color, LV_PART_MAIN);
  }

  void preautoButton::setButtonColor(allianceType alliance)
  {
    //The color the button will be
    evColor buttonColor;

    //Selects the color of the button
    switch(alliance)
    {
      case allianceType::redAlliance:
        buttonColor = vex::red;
        break;

      case allianceType::blueAlliance:
        buttonColor = blue;
        break;

      case allianceType::noChange:
        buttonColor = ClrGray;
        break;

      default: //noAlliance
        buttonColor = ClrGray;
        break;
    }

    //Set the color of the button
    lv_obj_set_style_bg_color(LVGLButton, buttonColor, LV_PART_MAIN);

    //Store the alliance type of the button
    buttonAlliance = alliance;
  }

  void preautoButton::setTitle(const char *title)
  {
    //Set the label text and show the title
    lv_label_set_text_fmt(LVGLButtonTitle, "%s", title);
    lv_obj_clear_flag(LVGLButtonTitle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align_to(LVGLButtonTitle, LVGLButton, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);

    //Store the title
    Title = title;
  }

  void preautoButton::setDescription(const char *description)
  {
    Description = description;
  }

  void preautoButton::setAlliance(allianceType alliance)
  {
    buttonAlliance = alliance;
  }

  evError preautoButton::setIcon(iconType icon, evColor iconColor)
  {
    switch(icon)
    {
      case iconType::Skills_Icon:
        LVGLButtonIcon = lv_img_create(LVGLButton);
        lv_img_set_src(LVGLButtonIcon, &Skills_Icon);
        break;

      case iconType::Left_Arrow:
        LVGLButtonIcon = lv_img_create(LVGLButton);
        lv_img_set_src(LVGLButtonIcon, &Left_Arrow);
        break;

      case iconType::Right_Arrow:
        LVGLButtonIcon = lv_img_create(LVGLButton);
        lv_img_set_src(LVGLButtonIcon, &Right_Arrow);
        break;

      case iconType::Exclamation_Points:
        LVGLButtonIcon = lv_img_create(LVGLButton);
        lv_img_set_src(LVGLButtonIcon, &Exclamation_Points);
        break;

      case iconType::Custom_Icon:
        //Custom icons need an LVGL image object.
        return evError::Invalid_Argument_Data;
        break;

      default: //No_Icon
        return evError::No_Error;
        break;
    }

    //Align the icon with the button
    lv_obj_align_to(LVGLButtonIcon, LVGLButton, LV_ALIGN_CENTER, 0, 0);

    //Set color parameters for the icon
    lv_obj_set_style_img_recolor_opa(LVGLButtonIcon, LV_OPA_100, 0);
    lv_obj_set_style_img_recolor(LVGLButtonIcon, iconColor, 0);

    return evError::No_Error;
  }

  evError preautoButton::setIcon(const lv_img_dsc_t *icon, evColor iconColor)
  {
    //Make sure the icon exists
    if(icon == nullptr)
    {
      return evError::Object_Property_Not_Specified;
    }

    //Create the icon
    LVGLButtonIcon = lv_img_create(LVGLButton);

    //Set the image of the icon
    lv_img_set_src(LVGLButtonIcon, icon);

    //Align the icon with the button
    lv_obj_align_to(LVGLButtonIcon, LVGLButton, LV_ALIGN_CENTER, 0, 0);

    //Set color parameters for the icon
    lv_obj_set_style_img_recolor_opa(LVGLButtonIcon, LV_OPA_100, 0);
    lv_obj_set_style_img_recolor(LVGLButtonIcon, iconColor, 0);

    return evError::No_Error;
  }

  evError preautoButton::changeIconColor(evColor iconColor)
  {
    //If the icon wasn't created
    if(LVGLButtonIcon == nullptr)
    {
      return evError::Object_Property_Not_Specified;
    }

    //Set the color of the icon
    lv_obj_set_style_img_recolor(LVGLButtonIcon, iconColor, 0);

    return evError::No_Error;
  }

  evError preautoButton::setCallbackFunction(void (*callback)(uint))
  {
    //Return an error if the callback function is null
    if(callback == nullptr)
    {
      return evError::Invalid_Argument_Data;
    }

    //Set the callback function
    buttonCallback = callback;

    return evError::No_Error;
  }

  void preautoButton::selectButton()
  {
    //Show the outline of the button
    lv_obj_set_style_outline_opa(LVGLButton, LV_OPA_100, 0);

    //Set the alliance of the robot
    if(buttonAlliance != allianceType::noChange)
    {
      robotAlliance = buttonAlliance;
    }

    //Run the callback
    if(buttonCallback != nullptr)
    {
      buttonCallback(buttonID);
    }
  }

  void preautoButton::deselectButton()
  {
    lv_obj_set_style_outline_opa(LVGLButton, LV_OPA_0, 0);
  }

  evErrorData<std::string *> &preautoButton::getTitle()
  {
    //Data to return
    static evErrorData<std::string *> returnData;

    //Get the data to return
    if(Title == "NULL")
    {
      returnData.errorData = evError::Object_Property_Not_Specified;
    }

    else
    {
      returnData.errorData = evError::No_Error;
      returnData.data = &Title;
    }

    return returnData;
  }

  evErrorData<std::string *> &preautoButton::getDescription()
  {
    //Data to return
    static evErrorData<std::string *> returnData;

    //Get the data to return
    if(Description == "NULL")
    {
      returnData.errorData = evError::Object_Property_Not_Specified;
    }

    else
    {
      returnData.errorData = evError::No_Error;
      returnData.data = &Description;
    }

    return returnData;
  }

} // namespace evAPI