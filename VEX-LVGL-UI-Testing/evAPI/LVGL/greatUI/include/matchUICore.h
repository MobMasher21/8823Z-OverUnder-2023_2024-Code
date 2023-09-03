/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       matchUICore.h                                             */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Sat Aug 23 2023                                           */
/*    Description:  Structure for storing data for the match UI.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef MATCHUICORE_H
#define MATCHUICORE_H

#include "vex.h"
#include "evAPISettings.h"

namespace evAPI
{
  enum class brainDataType
  {
    NULL_DATA = 0,
    INT,
    UINT,
    LONG,
    ULONG,
    FLOAT,
    DOUBLE,
    FUNC_INT,
    FUNC_DOUBLE
  };

  struct brainReadOut
  {
    char Name[MAX_MATCH_DATA_NAME_LENGTH];
    uint nameLength = 0;

    void *displayData;
    int (*funcInt)();
    double (*funcDouble)();

    brainDataType dataType = brainDataType::NULL_DATA;
    color graphColor = blue;
  };
};
#endif // MATCHUICORE_H