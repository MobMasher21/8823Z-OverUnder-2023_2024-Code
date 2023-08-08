/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     vexPrivateRebuild.h (Rebuilt)                               */
/*    Author:     Jayden Liffick                                              */
/*    Created:    6 Aug 2023                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef VEXPRIVATEREBUILD_H
#define VEXPRIVATEREBUILD_H

#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

void vexTaskSleep(uint32_t time);
int vexDisplayThemeIdGet();

#ifdef __cplusplus
}
#endif

#endif // VEXPRIVATEREBUILD_H
