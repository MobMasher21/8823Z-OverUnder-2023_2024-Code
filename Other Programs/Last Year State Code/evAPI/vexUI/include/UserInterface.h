#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "vex.h"
#include "..\..\vexUI\include\button.h"
#include "..\..\vexUI\include\iconArrays.h"

namespace evAPI
{
  #define maxButtonCount 64  //setup for the max amount of buttons used
  
  class goodUI {
  
    public:
      goodUI();
      goodUI(void (*callback)(void));
      int addButton(int r, int g, int b);
      int addButton(int r, int g, int b, void (*callback)(int));
      int addButton(int r, int g, int b, bool iconInput[35][35]);
      int addButton(int r, int g, int b, void (*callback)(int), bool iconInput[35][35]);
      int addButton(color buttonColor);
      int addButton(color buttonColor, void (*callback)(int));
      int addButton(color buttonColor, bool iconInput[35][35]);
      int addButton(color buttonColor, void (*callback)(int), bool iconInput[35][35]);
      int addBlank();
      void changeButtonColor(int button, int r, int g, int b);
      int getButtonCount();
      void pressCheck();
      int getProgNumber();
      void printButtons();

      /**
       * @brief Changes the selected button.
       * @param button The button that will be selected.
       * @param doNotShowSettings Optional. Allows the user to change the program showing the name on the screen.
      */
      void selectButton(int button, bool doNotShowSettings = false);
  
      /**
       * @brief A structure containing all of the arrays for the icons.
      */
      iconArrays Icons;

    private:
      int buttonCount;
      button * buttonList[maxButtonCount];
      button * pageBack;
      button * pageForward;
      void (*printPointer)(void);
      int activePage;
      int progMode = 0;     //Default Autonomous 15
      int * buttonMode = &progMode;
      int pageTurnIndex;
      int * pageTurnButton = &pageTurnIndex;
      int blankPage;
      int * blankPagePointer = &blankPage;
      bool prePress;
      void pressed();
      void addButton(void (*callback)(int));
  };
}

#endif // __USERINTERFACE_H__