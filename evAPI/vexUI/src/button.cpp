#include "../include/button.h"

namespace evAPI
{
  button::button(int ID, int * buttonDataLocation) {
    buttonID = ID;
    IDStore = buttonDataLocation;
  }
  
  button::button(int ID, int * buttonDataLocation, void (*callback)(int)) {
    buttonID = ID;
    IDStore = buttonDataLocation;
    buttonCallback = callback;
  }
  
  void button::setIconArray(bool arrayInput[35][35]) {
    buttonIcon.setIconArray(arrayInput);
  }
  
  void button::drawButton() {
    buttonIcon.printIcon(white, 0);
  }
  
  void button::drawButton(color borderColor) {
    buttonIcon.printIcon(borderColor, 7);
  }
  
  void button::drawButton(color borderColor, int borderSize){
    buttonIcon.printIcon(borderColor, borderSize);
  }
  
  void button::setColor(int r, int g, int b) {
    buttonColor.rgb(r, g, b);
    buttonIcon.setColor(buttonColor);
  }
  
  void button::setColor(color buttonColorInput) {
    buttonColor = buttonColorInput;
    buttonIcon.setColor(buttonColor);
  }
  
  void button::setDims(int x, int y, int w, int h) {
    buttonIcon.setButtonSize(x, y, w, h);
    xPos = x;
    yPos = y;
    width = w;
    hight = h;
  }
  
  bool button::pressed(int xPress, int yPress) {
    if(xPress >= xPos && xPress <= (xPos + width)) {
      if(yPress >= yPos && yPress <= (yPos + hight)) {
        *IDStore = buttonID;
        if(buttonCallback) {
          buttonCallback(buttonID);
        }
        return(1);
      } else {
        return(0);
      }
    } else {
      return(0);
    }
  }

  void button::setTitle(const char newTitle[MAX_TITLE_LENGTH])
  {
    for (int i = 0; i < MAX_TITLE_LENGTH; i++)
    { Title[i] = newTitle[i]; }

    titleLength = strlen(Title);
  }

  void button::setDescription(const char newDescription[MAX_DESCRIPTION_LENGTH])
  {
    for (int i = 0; i < MAX_DESCRIPTION_LENGTH; i++)
    { Description[i] = newDescription[i]; }

    descriptionLength = strlen(Description);
  }

  char button::getTitle(int index)
  { return Title[index]; }

  char button::getDescription(int index)
  { return Description[index]; }

  int button::getTitleLength()
  { return titleLength; }

  int button::getDescriptionLength()
  { return descriptionLength; }
}