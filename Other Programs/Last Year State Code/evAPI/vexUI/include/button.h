#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "vex.h"
#include "..\..\vexUI\include\icon.h"

namespace evAPI
{
  class button {
    public:
      button(int ID, int * buttonDataLocation);
      button(int ID, int * buttonDataLocation, void (*callback)(int));
      void setIconArray(bool arrayInput[35][35]);
      void drawButton();
      void drawButton(color borderColor);
      void drawButton(color borderColor, int borderSize);
      void setColor(int r, int g, int b);
      void setColor(color buttonColor);
      void setDims(int x, int y, int w, int h);
      bool pressed(int xPress, int yPress);
  
    private:
      int buttonID;
      int * IDStore;
      void (*buttonCallback)(int);
      icon buttonIcon;
      int xPos;
      int yPos;
      int width;
      int hight;
      color buttonColor;
  };
}

#endif // __BUTTON_H__