#include "../include/AutoSelector.h"

namespace evAPI {
  // This is the work around for the vex thread call not taking class members
  void threadFunction( void );  // Function that is run in the thread
  AutoSelector * thisContext;

  AutoSelector::AutoSelector() {  // Constructor to set up page turning buttons
    pageBack = new Button(-1, &pageTurner);
    pageForward = new Button(1, &pageTurner);
    pageBack->setButtonPosition(165, 200);
    pageBack->setButtonSize(60, 30);
    pageForward->setButtonPosition(255, 200);
    pageForward->setButtonSize(60, 30);
    pageBack->setButtonIcon((bool*)arrows.previousPageArrow);
    pageForward->setButtonIcon((bool*)arrows.nextPageArrow);

    thisContext = this;
  }

  int AutoSelector::getSelectedButton() {  // Returns the selectedButton
    return(selectedButton);
  }

  void AutoSelector::setSelectedButton(int button) {  // Sets the currently selected button
    selectedButton = button;
  }

  void AutoSelector::setSelectedPage(int page) {  // Sets the currently selected page
    selectedPage = page;
  }

  int AutoSelector::addButton(int ID, int r, int g, int b) {  // Adds a button with the set ID and RGB color. Returns button count
      bool buttonExits = doesButtonExist(ID);

    if(!buttonExits) {
      int pgIndex = ID % 8;  // Position of the button on the screen
      int xIndex = pgIndex % 4;  // How many places from the left the button is
      buttonIDList[buttonCount] = ID;  // Adds the ID to the list of used IDs
      buttonList[ID] = new Button(ID, &selectedButton);  // Adds the button to the list of button objects
      dataList[ID] = new AutoData;  // Creates a blank data object and adds it to the list

      if(pgIndex >= 0 && pgIndex <= 3) {  // Sets up the position and size of the new button. Hard coded for 2 rows 4 columns
        buttonList[ID]->setButtonPosition(((40 * (xIndex + 1)) + xIndex * 70), 20);
        buttonList[ID]->setButtonSize(70, 70);
      } else if(pgIndex >= 4 && pgIndex <= 7) {
        buttonList[ID]->setButtonPosition(((40 * (xIndex + 1)) + xIndex * 70), 115);
        buttonList[ID]->setButtonSize(70, 70);
      }
  
      buttonList[ID]->setBorderColor(white);
      buttonList[ID]->setBorderThickness(7);
      buttonList[ID]->setButtonColor(r, g, b);

      // Checks if the added button is on a new page
      if(ID / 8 > highestUsedPage) {
        highestUsedPage = ID / 8;
      }
      if(ID > highestID) {
        highestID = ID;
      }

      buttonCount++;
      return(buttonCount);
    } else {
      return(0);
    }
  }

  int AutoSelector::addButton(int ID, color buttonColor) {  // Adds a button with the set ID and vex color object. Returns button count
    bool buttonExits = doesButtonExist(ID);

    if(!buttonExits) {
      int pgIndex = ID % 8;  // Position of the button on the screen
      int xIndex = pgIndex % 4;  // How many places from the left the button is
      buttonIDList[buttonCount] = ID;  // Adds the ID to the list of used IDs
      buttonList[ID] = new Button(ID, &selectedButton);  // Adds the button to the list of button objects
      dataList[ID] = new AutoData;  // Creates a blank data object and adds it to the list

      if(pgIndex >= 0 && pgIndex <= 3) {  // Sets up the position and size of the new button. Hard coded for 2 rows 4 columns
        buttonList[ID]->setButtonPosition(((40 * (xIndex + 1)) + xIndex * 70), 20);
        buttonList[ID]->setButtonSize(70, 70);
      } else if(pgIndex >= 4 && pgIndex <= 7) {
        buttonList[ID]->setButtonPosition(((40 * (xIndex + 1)) + xIndex * 70), 115);
        buttonList[ID]->setButtonSize(70, 70);
      }

      buttonList[ID]->setBorderColor(white);
      buttonList[ID]->setBorderThickness(7);
      buttonList[ID]->setButtonColor(buttonColor);

      // Checks if the added button is on a new page
      if(ID / 8 > highestUsedPage) {
        highestUsedPage = ID / 8;
      }
      if(ID > highestID) {
        highestID = ID;
      }

      buttonCount++;
      return(buttonCount);
    } else {
      return(0);
    }
  }

  void AutoSelector::setButtonFunction(int ID, void (*callback)(int)) {  // Sets a function the button will run when pressed
    if(doesButtonExist(ID)) {
      buttonList[ID]->setCallback(callback);
    }
  }

  void AutoSelector::setButtonColor(int ID, int r, int g, int b) {  // Changes the color of a button
    if(doesButtonExist(ID)) {
      buttonList[ID]->setButtonColor(r, g, b);
    }
  }

  void AutoSelector::setButtonColor(int ID, color buttonColor) {  // Changes the color of a button
    if(doesButtonExist(ID)) {
      buttonList[ID]->setButtonColor(buttonColor);
    }
  }

  void AutoSelector::setButtonIcon(int ID, const bool icon[35][35]) {  // Changes the icon array of the button
    if(doesButtonExist(ID)) {
      buttonList[ID]->setButtonIcon((bool*)icon);
    }
  }

  void AutoSelector::printButtons() {  // Prints all the buttons to the screen
    printPageButtons();
    // Records the ID of all the buttons on the screen
    int buttonsOnPage[] = {-1, -1, -1, -1, -1, -1, -1, -1};  // List will be filled with all the ID of the buttons being used
    int headPos = 0;
    for(int i = selectedPage * 8; i <= (selectedPage * 8) + 7; i++) {
      if(doesButtonExist(i)) {
        buttonsOnPage[headPos] = i;
        headPos++;
      }
    }

    // Draws all the buttons
    for(int i = 0; i < 8; i++) {
      if(buttonsOnPage[i] != -1) {
        if(selectedButton == buttonsOnPage[i]) {
          buttonList[buttonsOnPage[i]]->drawButton(true);
        } else {
          buttonList[buttonsOnPage[i]]->drawButton(false);
        }
      }
    }

  }

  void AutoSelector::setButtonTitle(int ID, const char title[MAX_TITLE_LENGTH]) {  // Sets a button's title
    if(doesButtonExist(ID)) {
      dataList[ID]->setTitle((char *)title);
    }
  }

  void AutoSelector::setButtonDescription(int ID, const char description[MAX_DESCRIPTION_LENGTH]) {  // Sets a button's description
    if(doesButtonExist(ID)) {
      dataList[ID]->setDescription((char *)description);
    }
  }

  void AutoSelector::setDataDisplayTime(int time) {  // Sets the time the data will be displayed in milliseconds
    dataDisplayTime = time;
  }

  void AutoSelector::startThread() {  // Starts the main loop thread for the auto selector
    selectorThread = new thread(threadFunction);
  }

  // ------------------ PRIVATE ---------------------------
  bool AutoSelector::doesButtonExist(int ID) {  // Returns true if the button exists in the list
    bool buttonExits = false;
    for(int i = 0; i < buttonCount; i++) {  // Run through all existing button IDs to see if the passed in ID is being used
      if(buttonIDList[i] == ID) buttonExits = true;
    }
    return(buttonExits);
  }

  void AutoSelector::printPageButtons() {  // Prints the page turning buttons
    if(selectedPage == 0) {
      pageBack->setButtonColor(nonavailablePage);
    } else {
      pageBack->setButtonColor(availablePage);
    }

    if(selectedPage >= highestUsedPage) {
      pageForward->setButtonColor(nonavailablePage);
    } else {
      pageForward->setButtonColor(availablePage);
    }
    pageBack->setBorderColor(white);
    pageForward->setBorderColor(white);
    pageBack->setBorderThickness(1);
    pageForward->setBorderThickness(1);

    pageBack->drawButton(true);
    pageForward->drawButton(true);
  }

  void AutoSelector::pressed() {  // Called when the screen is pressed
    int xPos = Brain.Screen.xPosition();  // X position of where the button was pressed
    int yPos = Brain.Screen.yPosition();  // Y position of where the button was pressed

    // Records the ID of all the buttons on the screen
    int buttonsOnPage[8] = {-1, -1, -1, -1, -1, -1, -1, -1};  // List will be filled with all the ID of the buttons being used
    int headPos = 0;
    for(int i = selectedPage * 8; i <= (selectedPage * 8) + 7; i++) {
      if(doesButtonExist(i)) {
        buttonsOnPage[headPos] = i;
        headPos++;
      }
    }

    int prePressButton = selectedButton;

    // Passes pressed location to all buttons
    for(int i = 0; i < 8; i++) {
      if(buttonsOnPage[i] != -1) {
        buttonList[buttonsOnPage[i]]->pressed(xPos, yPos);
      }
    }

    Brain.Screen.clearScreen();
    if(prePressButton != selectedButton) {
      if(dataList[selectedButton]->printButtonData()) {
        vex::task::sleep(dataDisplayTime);
      }
    }

    if(selectedPage != 0) {
      pageBack->pressed(xPos, yPos);
    }
    if(selectedPage < highestUsedPage) {
      pageForward->pressed(xPos, yPos);
    }
    selectedPage += pageTurner;
    pageTurner = 0;

    Brain.Screen.clearScreen();
    printButtons();

  }

  void threadFunction( void ) {  // Function that is run in the thread
    static bool prePressState;
    while(1) {
      if(Brain.Screen.pressing() && !prePressState) {
        thisContext->pressed();
      }
      prePressState = Brain.Screen.pressing();
      vex::this_thread::sleep_for(50);
    }
  }
} // namespace evAPI