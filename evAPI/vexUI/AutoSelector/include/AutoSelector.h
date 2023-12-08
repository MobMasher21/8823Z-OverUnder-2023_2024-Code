#ifndef AUTOSELECTOR_H_
#define AUTOSELECTOR_H_

#include "../../../Common/include/evAPIBasicConfig.h"
#include "../../../Common/include/evNamespace.h"
#include "../../../Common/include/colors.h"
#include "Button.h"
#include "pageArrowsIcons.h"
#include "iconArrays.h"
#include "AutoData.h"

#define MAX_BUTTON_COUNT 64

namespace evAPI {
  class AutoSelector {
    public:
      AutoSelector();  // Constructor to set up page turning buttons
      int getSelectedButton();  // Returns the selectedButton
      void setSelectedButton(int button);  // Sets the currently selected button
      void setSelectedPage(int page);  // Sets the currently selected page
      
      int addButton(int ID, int r, int g, int b);  // Adds a button with the set ID and RGB color
      int addButton(int ID, color buttonColor);  // Adds a button with the set ID and vex color object
  
      void setButtonFunction(int ID, void (*callback)(int));  // Sets a function the button will run when pressed
  
      void setButtonColor(int ID, int r, int g, int b);  // Changes the color of a button
      void setButtonColor(int ID, color buttonColor);  // Changes the color of a button
  
      defaultIconArrays icons;  // An instance of the default icons
      void setButtonIcon(int ID, const bool icon[35][35]);  // Changes the icon array of the button
  
      void printButtons();  // Prints all the buttons to the screen
  
      void setButtonTitle(int ID, char title[MAX_TITLE_LENGTH]);  // Sets a button's title
      void setButtonDescription(int ID, char description[MAX_DESCRIPTION_LENGTH]);  // Sets a button's description
      void setDataDisplayTime(int time);  // Sets the time the data will be displayed in milliseconds
  
      //===== Screen press and thread stuff =====
      void pressed();  // Called when the screen is pressed
      void startThread();  // Starts the main loop thread for the auto selector
  
    private:
      //===== Button data =====
      Button * buttonList[MAX_BUTTON_COUNT];  // List of all button objects in selector
      AutoData * dataList[MAX_BUTTON_COUNT];  // List of all the data objects for the buttons;
      int buttonIDList[MAX_BUTTON_COUNT];  // List of all button IDs in selector
      int buttonCount;  // How many buttons there are
      int highestID;  // What is the highest used ID
      int selectedButton = 0;  // The button that is currently selected
      bool doesButtonExist(int ID);  // Returns true if the button exists in the list
      int dataDisplayTime = 3000;  // How long the button data will be on the screen;
  
      //===== Page turning button stuff =====
      arrowIcons arrows;  // Structure with the arrow icons in it
      Button * pageBack;  // Button to move to next page
      Button * pageForward;  // Button to move to previous page
      int pageTurner;  // Used by page turn buttons to tell selector to go forward or back
      int selectedPage = 0;  // The page that is being shown
      int highestUsedPage;  // The biggest page number that has buttons on it
      color availablePage = color(150, 150, 150);  // Color of the page button if there is another page
      color nonavailablePage = color(70, 70, 70);  // Color of the page button if there is not another page
      void printPageButtons();  // Prints the page turning buttons
  
      //===== Thread items =====
      thread * selectorThread;  // Looping thread for the selector to run
     
  };
}

#endif // AUTOSELECTOR_H_