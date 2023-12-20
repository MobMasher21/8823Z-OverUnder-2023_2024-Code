#include "../include/Button.h"

namespace evAPI {
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

  void Button::setButtonIcon(bool *iconArray, int xOffset, int yOffset) { // Pass in the icon array
    buttonIcon = iconArray;
    xIconOffset = xOffset;
    yIconOffset = yOffset;
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
    //Draw the button with the appropriate color
    Brain.Screen.setPenColor(transparent); 
    Brain.Screen.setFillColor(buttonColor);
    Brain.Screen.drawRectangle(xPos, yPos, width, hight);

    //*Draw the icon if the button has one
    if(hasIcon)
    {
      //Loop over every single pixel in the image
      for(int yInc = 0; yInc < floor(hight / 2); yInc++)
      {
        for(int xInc = 0; xInc < floor(width / 2); xInc++)
        {
          //Set the tile color based on the boolean array
          if(buttonIcon[(yInc * 35) + xInc] == 1)
          {
            Brain.Screen.setPenColor(black);
          }

          else
          {
            Brain.Screen.setPenColor(buttonColor);
          }

          //Draw the pixels on the screen
          Brain.Screen.drawPixel(xPos + (xInc * 2), yPos + (yInc * 2));
          Brain.Screen.drawPixel((xPos + (xInc * 2)) + 1, yPos + (yInc * 2));
          Brain.Screen.drawPixel(xPos + (xInc * 2), (yPos + (yInc * 2)) + 1);
          Brain.Screen.drawPixel((xPos + (xInc * 2)) + 1, (yPos + (yInc * 2)) + 1);
        }
      }
    }

    //*Draw the boarder if the button is selected
    if(border)
    {
      //Setup pen parameters
      Brain.Screen.setFillColor(transparent);
      Brain.Screen.setPenColor(buttonBorderColor);
      Brain.Screen.setPenWidth(borderThickness);
      
      //Draw the boarder
      Brain.Screen.drawRectangle(xPos + xIconOffset, yPos + yIconOffset, width, hight);
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
} // namespace evAPI