#include "../include/Button.h"

Button::Button(int ID, int * buttonDataLocation) {  // Creates a button and sets the ID and store location
  buttonID = ID;
  dataOuput = buttonDataLocation;
}

void Button::updateButtonID(int ID) {  // Changes the button ID
  buttonID = ID;
}

void Button::changeDataLocation(int * buttonDataLocation) {  // Changes the button's data output location
  dataOuput = buttonDataLocation;
}

void Button::setCallback(void (*callback)(int)) {  // Sets the callback function for the button
  buttonCallback = callback;
  hasCallback = true;
}

void Button::setButtonColor(color colorInput) {  // Sets the button color to a vex color object
  buttonColor = colorInput;
}

void Button::setButtonColor(int r, int g, int b) {  // Sets the button color to a RGB value
  buttonColor.rgb(r, g, b);
}

void Button::setBorderColor(color colorInput) {  // Sets the border color to vex color object
  buttonBorderColor = colorInput;
}

void Button::setBorderColor(int r, int g, int b) {  // Sets the border color to a RGB value
  buttonBorderColor.rgb(r, g, b);
}

void Button::setBorderThickness(int thickness) {  // Sets the thickness of the button border
  borderThickness = thickness;
}

void Button::setButtonIcon(bool * iconArray) { // Pass in the icon array
  buttonIcon = iconArray;
  hasIcon = true;
}

void Button::setButtonPosition(int x, int y) {  // Sets the position of the top left corner of the Button
  xPos = x;
  yPos = y;
}

void Button::setButtonSize(int widthIN, int hightIN) {  // Sets the size of the Button
  width = widthIN;
  hight = hightIN;
}

void Button::drawButton(bool border) {  // Draws the button with the option of adding the borderButton
  Brain.Screen.setPenColor(buttonBorderColor);  //draw the background color square
  if(border) {                                            // |
    Brain.Screen.setPenWidth(borderThickness);            // |
  } else {                                                // |
    Brain.Screen.setPenWidth(0);                          // |
  }                                                       // |
  Brain.Screen.setFillColor(buttonColor);                 // |
  Brain.Screen.drawRectangle(xPos, yPos, width, hight);   // \/

  if(hasIcon) {
    for(int yInc = 0; yInc < floor(hight / 2); yInc++) {
      for(int xInc = 0; xInc < floor(width / 2); xInc++) {
        if(buttonIcon[(yInc * 35) + xInc] == 1) {
          Brain.Screen.setPenColor(black);
        } else {
          Brain.Screen.setPenColor(buttonColor);
        }
        Brain.Screen.drawPixel(xPos + (xInc * 2), yPos + (yInc * 2));
        Brain.Screen.drawPixel((xPos + (xInc * 2)) + 1, yPos + (yInc * 2));
        Brain.Screen.drawPixel(xPos + (xInc * 2), (yPos + (yInc * 2)) + 1);
        Brain.Screen.drawPixel((xPos + (xInc * 2)) + 1, (yPos + (yInc * 2)) + 1);
      }
    }
  }
}

bool Button::pressed(int xPress, int yPress) {  // Call to tell the button the screen was pressed and tell it whereButton
  if(((xPress > xPos) && (xPress < xPos + width)) &&
     ((yPress > yPos) && (yPress < yPos + hight))) {
    
    *dataOuput = buttonID;

    if(hasCallback) {
      buttonCallback(buttonID);
    }

    return(1);
  } else {
    return(0);
  }
}
