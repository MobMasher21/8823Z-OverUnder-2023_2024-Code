/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       evAPISettings.h                                           */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Settings for the evAPI.                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//!Colors
/**
 * This enables the redefining if the colors in "v5_color.h" so they use the vex color class.
 * Set this to zero to disable the redefining.
 * If disabled, the color objects will have their name changed to have "vex" at the start.
 * Example: vexClrAliceBlue
*/
#define REDEFINE_COLORS 1

/**
 * This enables use of LVGL color objects with with evColor class.
 * 0 - Force disable use of LVGL color with evColor
 * 1 - Default. Enable LVGL color use if "lvgl.h" is present.
 * 2 - Force enabling of LVGL color usage.
*/
#define ENABLE_LVGL_COLOR 1

//!UI
/**
 * This controls what UI system evAPI will use. They are mostly compatable with each other, aside from icons.
 * 0: This is the default option. evAPI will check if LVGL is present and use it if possible.
 * 1: This forces evAPI to use the standard UI. A warning will appear if it can't use it.
 * 2: This forces evAPI to use the LVGL UI. A warning will appear if it can't use it.
*/
#define FORCE_UI_VERSION 0

//*General UI
#define SELECTOR_TAB_COUNT 5
#define SELECTOR_TAB_NAME_LENGTH 5

//*Auto Selector UI
#define MAX_AUTO_BUTTON_COUNT (SELECTOR_TAB_COUNT * 8)

#define MAX_AUTO_TITLE_LENGTH 10
#define MAX_AUTO_DESCRIPTION_LENGTH 200

#define AUTO_BUTTON_SIZE 70
#define AUTO_BUTTON_X_OFFSET 0
#define AUTO_BUTTON_Y_OFFSET -7
#define AUTO_BUTTON_X_SPACING_DISTANCE 56
#define AUTO_BUTTON_Y_SPACING_DISTANCE 30

//*Match UI
#define MAX_MATCH_DATA_COUNT (SELECTOR_TAB_COUNT * 8)
#define MAX_MATCH_DATA_NAME_LENGTH 15

#define MATCH_BUTTON_X_SIZE 210
#define MATCH_BUTTON_Y_SIZE 35
#define MATCH_BUTTON_X_OFFSET 0
#define MATCH_BUTTON_Y_OFFSET -7
#define MATCH_BUTTON_X_SPACING_DISTANCE 26
#define MATCH_BUTTON_Y_SPACING_DISTANCE 12

//*Controller UI
#define MAX_CONTROLLER_DATA_COUNT 6
#define MAX_CONTROLLER_NAME_LENGTH 20