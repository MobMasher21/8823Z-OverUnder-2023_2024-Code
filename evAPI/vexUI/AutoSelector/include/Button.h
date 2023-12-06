#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../../Common/include/evAPIBasicConfig.h"
#include "../../../Common/include/evNamespace.h"

class Button {
  public:
    Button(int ID, int * buttonDataLocation);  // Creates a button and sets the ID and store location

    void updateButtonID(int ID);  // Changes the button ID
    void changeDataLocation(int * buttonDataLocation);  // Changes the button's data output location
    void setCallback(void (*callback)(int));  // Sets the callback function for the button

    void setButtonColor(color colorInput);  // Sets the button color to a vex color object
    void setButtonColor(int r, int g, int b);  // Sets the button color to a RGB value
    void setBorderColor(color colorInput);  // Sets the border color to vex color object
    void setBorderColor(int r, int g, int b);  // Sets the border color to a RGB value
    void setBorderThickness(int thickness);  // Sets the thickness of the button border

    void setButtonIcon(bool * iconArray);  // Pass in the icon array

    void setButtonPosition(int x, int y);  // Sets the position of the top left corner of the button
    void setButtonSize(int widthIN, int hightIN);  // Sets the size of the button

    void drawButton(bool border);  // Draws the button with the option of adding the border
    bool pressed(int xPress, int yPress);  // Call to tell the button the screen was pressed and tell it where

  private:
    int buttonID;  // The number that will be passed to the data output when the button is pressed
    int * dataOuput;  // A pointer to the variable that the button will set with its ID when it is pressed
    void (*buttonCallback)(int);  // *Optional* The function that will be called when the button is pressed, passes the button ID
    bool hasCallback = false;  // If the button has a callback
    bool * buttonIcon;  // *Optional* The array that is used to draw a monochrome 35x35 image on the button
    bool hasIcon = false;  // If the button has an icon
    int xPos;  // X position of the top left corner
    int yPos;  // Y position of the top left corner
    int width;  // Width of the button
    int hight;  // Hight of the button
    color buttonColor;  // Color of the button
    color buttonBorderColor = white;  // Color of the button border Default: white
    int borderThickness;  // Thickness of the button border
};

#endif // BUTTON_H_