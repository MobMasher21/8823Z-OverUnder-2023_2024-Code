/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     vexPrivateRebuild.h                                         */
/*    Author:     Jayden Liffick                                              */
/*    Created:    6 Aug 2023                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef VEXPRIVATEREBUILD_H
#define VEXPRIVATEREBUILD_H

#include "stdint.h"
#include "stdbool.h"
// #include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

//*Tasks functions
/**
 * @brief Pauses the task / thread it is run in for a specified amount of ms.
 * @param time The time to sleep in ms.
*/
void vexTaskSleep(uint32_t time);

void  vexTaskAdd(int (* callback)(void), int interval, char const *label);
void *vexTaskGetCallbackAndId(uint32_t index, int *callback_id);

//*Display functions
/**
 * @returns 1 if the display is set to light mode. 0 in dark mode.
*/
int vexDisplayThemeIdGet();

/**
 * @returns 1 if the display is inverted. 0 in normal mode.
*/
int vexDisplayRotateFlagGet();

void vexDisplayClipRegionSetWithIndex(int32_t index, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

//*Other
int32_t vexAdiAddrLedSet(uint32_t index, uint32_t port, uint32_t *pData, uint32_t nOffset, uint32_t nLength, uint32_t options);

#ifdef __cplusplus
}
#endif

#endif // VEXPRIVATEREBUILD_H