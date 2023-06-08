#ifndef __ICON_H__
#define __ICON_H__

#include "vex.h"

namespace evAPI
{
  class icon {
    public:
      void setIconArray(bool arrayInput[35][35]);  //sets a bool icon patter array
      void setButtonSize(int xPosIN, int yPosIN, int widthIN, int hightIN);  //sets the size of the button
      void printIcon(color borderColor, int borderSize);  //prints the full icon on the screens
      void setColor(int r, int g, int b);  //sets color using RGB
      void setColor(color buttonColor);  //sets color using vex presets
  
    private:
      bool availableArray;
      bool iconArray[35][35];
      int xPos;  //top left position of the button
      int yPos;  //top left position of the button
      int width;  //with of the button
      int hight;  //hight of the button
      color backgroundColor;
  
  };
}

#endif // __ICON_H__