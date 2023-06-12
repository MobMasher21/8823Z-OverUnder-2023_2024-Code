#include "..\..\vexUI\include\UserInterface.h"
#include "..\..\vexUI\include\pageArrowsIcons.h"

namespace evAPI
{
  arrowIcons Arrows;

  goodUI::goodUI() {
    fflush(stdout);
    activePage = 0;
    pageBack = new button(-1, pageTurnButton);
    pageForward = new button(1, pageTurnButton);
    pageBack->setDims(165, 200, 60, 30);
    pageForward->setDims(255, 200, 60, 30);
    pageBack->setIconArray(Arrows.previousPageArrow);
    pageForward->setIconArray(Arrows.nextPageArrow);
  }

  goodUI::goodUI(void (*callback)(void)) {
    printPointer = callback;
    fflush(stdout);
    activePage = 0;
    pageBack = new button(-1, pageTurnButton);
    pageForward = new button(1, pageTurnButton);
    pageBack->setDims(165, 200, 60, 30);
    pageForward->setDims(255, 200, 60, 30);
    pageBack->setIconArray(Arrows.previousPageArrow);
    pageForward->setIconArray(Arrows.nextPageArrow);
    printPointer();
  }

  void goodUI::addButton(void (*callback)(int)) {
    int pgIndex;
    int xIndex;
    int newButton = buttonCount;
    buttonCount ++;
    buttonList[newButton] = new button(newButton, buttonMode, callback);
    pgIndex = newButton % 8;
    xIndex = pgIndex % 4;
    if(pgIndex >= 0 && pgIndex <= 3) {
      buttonList[newButton]->setDims(((40 * (xIndex + 1)) + xIndex * 70), 20, 70, 70);
    } else if(pgIndex >= 4 && pgIndex <= 7) {
      buttonList[newButton]->setDims(((40 * (xIndex + 1)) + xIndex * 70), 115, 70, 70);
    }
  }

  int goodUI::addButton(int r, int g, int b) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, void (*callback)(int)) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, bool iconInput[35][35]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, void (*callback)(int), bool iconInput[35][35]) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, void (*callback)(int)) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, bool iconInput[35][35]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, void (*callback)(int), bool iconInput[35][35]) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    return(buttonCount);
  }

  int goodUI::addBlank() {
    buttonList[buttonCount] = new button(0, blankPagePointer);
    buttonCount ++;
    return(buttonCount);
  }

  void goodUI::changeButtonColor(int button, int r, int g, int b) {
    buttonList[button]->setColor(r, g, b);
  }

  int goodUI::getButtonCount() {
    return(buttonCount);
  }

  int goodUI::getProgNumber() {
    return(progMode);
  }

  void goodUI::pressCheck() {
    if(Brain.Screen.pressing() && !prePress) {
      pressed();
    }
    prePress = Brain.Screen.pressing();
    vex::task::sleep(20);
  }

  void goodUI::pressed() {
    int preButton = progMode;
    int pressPointX = Brain.Screen.xPosition();
    int pressPointY = Brain.Screen.yPosition();
    for(int i = activePage * 8; i <= (activePage + 1) * 8 - 1; i++) {
      if(i < buttonCount) {
        buttonList[i]->pressed(pressPointX, pressPointY);
      }
    }
    pageBack->pressed(pressPointX, pressPointY);
    pageForward->pressed(pressPointX, pressPointY);
    if(pageTurnIndex == -1) {
      activePage = activePage - 1;
    }
    if(pageTurnIndex == 1) {
      activePage = activePage + 1;
    }
    if(activePage < 0) {
      activePage = 0;
    }
    if(activePage > (buttonCount - 1) / 8) {
      activePage = (buttonCount - 1) / 8;
    }
    Brain.Screen.clearScreen();
    printButtons();
    printf("xPos = %i, yPos = %i, button = %i\n", pressPointX, pressPointY, progMode);
    if(preButton != progMode && printPointer) {
      Brain.Screen.setFont(monoXXL);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setFillColor(transparent);
      Brain.Screen.setPenColor(white);
      printPointer();
      vex::task::sleep(3000);
      Brain.Screen.clearScreen();
      goodUI::printButtons();
    }
  }

  void goodUI::printButtons() {
    for(int i = activePage * 8; i <= (activePage + 1) * 8 - 1; i++) {
      if(i < buttonCount) {
        if(i == progMode) {
          buttonList[i]->drawButton(white);
        } else {
          buttonList[i]->drawButton();
        }
      }
    }
    if(activePage - 1 < 0) {
      pageBack->setColor(50, 50, 50);
    } else {
      pageBack->setColor(150, 150, 150);
    }
    if(activePage >= (buttonCount - 1) / 8) {
      pageForward->setColor(50, 50, 50);
    } else {
      pageForward->setColor(150, 150, 150);
    }
    pageBack->drawButton(white, 2);
    pageForward->drawButton(white, 2);
  }

  void goodUI::selectButton(int button, bool doNotShowSettings)
  {
    progMode = button;

    if(!doNotShowSettings)
    { 
      Brain.Screen.setFont(monoXXL);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setFillColor(transparent);
      Brain.Screen.setPenColor(white);
      printPointer();
      vex::task::sleep(3000);
      Brain.Screen.clearScreen();
      goodUI::printButtons();
    }

    printButtons();
  }
}