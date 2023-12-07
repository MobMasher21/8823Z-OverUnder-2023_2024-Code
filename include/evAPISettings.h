/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       evAPISettings.h                                           */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sun Aug 6, 2023                                           */
/*    Description:  Settings for the evAPI.                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef EVAPISETTINGS_H
#define EVAPISETTINGS_H

//!Colors
/**
 * This enables the redefining if the colors in "v5_color.h" so they use the vex color class.
 * Set this to zero to disable the redefining.
 * If disabled, the color objects will have their name changed to have "vex" at the start.
 * Example: vexClrAliceBlue
*/
#define REDEFINE_COLORS 1

#endif // EVAPISETTINGS_H