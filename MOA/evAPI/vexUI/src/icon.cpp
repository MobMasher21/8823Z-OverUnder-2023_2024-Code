#include "..\include\icon.h"

namespace evAPI
{
  void icon::setIconArray(bool arrayInput[35][35]) {
    availableArray = 1;
    for(int i = 0; i < 35; i++) {
      for(int ii = 0; ii < 35; ii++) {
        iconArray[i][ii] = arrayInput[i][ii];
      }
    }
  }
  
  void icon::setButtonSize(int xPosIN, int yPosIN, int widthIN, int hightIN) {
    xPos = xPosIN;
    yPos = yPosIN;
    width = widthIN;
    hight = hightIN;
  }
  
  void icon::printIcon(color borderColor, int borderSize) {
    Brain.Screen.setPenColor(borderColor);  //draw the background color square
    Brain.Screen.setPenWidth(borderSize);                     // |
    Brain.Screen.setFillColor(backgroundColor);               // |
    Brain.Screen.drawRectangle(xPos, yPos, width, hight);     // \/
    if(availableArray != 0) {
      for(int yInc = 0; yInc < floor(hight / 2); yInc++) {
        for(int xInc = 0; xInc < floor(width / 2); xInc++) {
          if(iconArray[yInc][xInc] == 1) {
            Brain.Screen.setPenColor(black);
          } else {
            Brain.Screen.setPenColor(backgroundColor);
          }
          Brain.Screen.drawPixel(xPos + (xInc * 2), yPos + (yInc * 2));
          Brain.Screen.drawPixel((xPos + (xInc * 2)) + 1, yPos + (yInc * 2));
          Brain.Screen.drawPixel(xPos + (xInc * 2), (yPos + (yInc * 2)) + 1);
          Brain.Screen.drawPixel((xPos + (xInc * 2)) + 1, (yPos + (yInc * 2)) + 1);
        }
      }
    }
  
    Brain.Screen.setPenColor(borderColor);  //redraw the border of the icon
    Brain.Screen.setPenWidth(borderSize);                     // |
    Brain.Screen.setFillColor(transparent);                   // |      
    Brain.Screen.drawRectangle(xPos, yPos, width, hight);     // \/
  }
  
  void icon::setColor(int r, int g, int b) {
    backgroundColor.rgb(r, g, b);
  }
  
  void icon::setColor(color buttonColorInput) {
    backgroundColor = buttonColorInput;
  }
}