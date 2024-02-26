#ifndef AUTOSELECTOR_H_
#define AUTOSELECTOR_H_

#include "../../../Common/include/evAPIBasicConfig.h"
#include "../../../Common/include/evNamespace.h"
#include "../../../Common/include/colors.h"
#include "Button.h"
#include "pageArrowsIcons.h"
#include "iconArrays.h"
#include "AutoData.h"
#include <string>

#define MAX_BUTTON_COUNT 64

namespace evAPI {
  class AutoSelector {
    public:

      /**
       * @brief Creates an Auto Selector object.
      */
      AutoSelector();

      /**
       * @returns The ID of the selected button.
      */
      int getSelectedButton();

      /**
       * @returns A std::string containing the title of the selected button.
      */
      std::string getSelectedButtonTitle();

      /**
       * @brief Selects a button from it's ID.
       * @param button The ID of the button to select.
      */
      void setSelectedButton(int button);

      /**
       * @brief Selects a page from it's ID.
       * @param page The ID of the page to select.
      */
      void setSelectedPage(int page);
      
      /**
       * @brief Adds a button to the Auto Selector.
       * @param ID The ID of the new button.
       * @param r The amount of red in the button from 0-255.
       * @param g The amount of green in the button from 0-255.
       * @param b The amount of blue in the button from 0-255.
       * @returns The ID of the button if it was created. 0 if a button with that ID already exists.
      */
      int addButton(int ID, int r, int g, int b);

      /**
       * @brief Adds a button to the Auto Selector.
       * @param ID The ID of the new button.
       * @param buttonColor The base color of the button.
       * @returns The ID of the button if it was created. 0 if a button with that ID already exists.
      */
      int addButton(int ID, uint32_t buttonColor);

      /**
       * @brief Adds a button to the Auto Selector.
       * @param ID The ID of the new button.
       * @param buttonColor The base color of the button.
       * @returns The ID of the button if it was created. 0 if a button with that ID already exists.
      */
      int addButton(int ID, color buttonColor);
  
      /**
       * @brief Adds a function to run when a given button is pressed.
       * @param ID The ID of the target button.
       * @param callback The function to run. It must return void and have one int argument. The ID of the 
       *                 pressed button is passed into the function.
      */
      void setButtonFunction(int ID, void (*callback)(int));
  
      /**
       * @brief Changes the color of a button.
       * @param ID The ID of the target button.
       * @param r The amount of red in the button from 0-255.
       * @param g The amount of green in the button from 0-255.
       * @param b The amount of blue in the button from 0-255.
      */
      void setButtonColor(int ID, int r, int g, int b);

      /**
       * @brief Changes the color of a button.
       * @param ID The ID of the target button.
       * @param buttonColor The base color of the button.
      */
      void setButtonColor(int ID, color buttonColor);
  
      /**
       * @brief An object containing all the builtin icons.
      */
      defaultIconArrays icons;

      /**
       * @brief Sets the icon of a button.
       * @param ID The ID of the target button.
       * @param icon The icon. A 35x35 boolean array.
      */
      void setButtonIcon(int ID, const bool icon[35][35]);
  
      /**
       * @brief Sets the title of the button. It will appear when the button is pressed.
       * @param ID The ID of the target button.
       * @param title The title of the button. It can be up to 15 characters in length.
      */
      void setButtonTitle(int ID, const char title[MAX_TITLE_LENGTH]);

      /**
       * @brief Sets the description of a button. It will appear when the button is pressed.
       * @param ID The ID of the target button.
       * @param description The description of the button. It can be up to 188 characters in length.
      */
      void setButtonDescription(int ID, const char description[MAX_DESCRIPTION_LENGTH]);

      /**
       * @brief Sets how long the title and description will be displayed.
       * @param time The time in miliseconds.
      */
      void setDataDisplayTime(int time);

      /**
       * @brief Prints all the buttons to the screen
      */
      void printButtons();
  
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
      const color availablePage = color(150, 150, 150);  // Color of the page button if there is another page
      const color nonavailablePage = color(70, 70, 70);  // Color of the page button if there is not another page
      void printPageButtons();  // Prints the page turning buttons
  
      //===== Screen press and thread stuff =====

      /**
       * @brief Starts the main thread for the Auto Selector UI
      */
      void startThread();

      void pressed();  // Called when the screen is pressed
      
      /**
       * @brief Friend function that updates the screen when it is pressed.
       * @param thisContextRaw A pointer to a AutoSelector object.
      */
      friend void threadFunction(void *thisContextRaw);

      friend class vexUI; //Allow the vexUI class to access the startThread function

      thread * selectorThread;  // Looping thread for the selector to run
     
  };
}

#endif // AUTOSELECTOR_H_