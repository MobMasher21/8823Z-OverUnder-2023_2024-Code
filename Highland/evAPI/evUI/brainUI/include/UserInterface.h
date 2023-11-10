#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "vex.h"
#include "../include/button.h"
#include "../include/iconArrays.h"
#include "../evAPI/Common/include/colors.h"
#include "../evAPI/Common/include/constantObjects.h"
#include "../../controllerUI/include/controllerUI.hpp"

#define maxButtonCount 64  //Setup for the max amount of buttons used
#define MAX_BRAIN_GRAPH_COUNT 32 
#define MAX_BRAIN_NAME_LENGTH 22
#define MAX_CONTROLLER_GRAPH_COUNT 6
#define MAX_CONTROLLER_NAME_LENGTH 20

namespace evAPI
{
  class goodUI {

    private:
      //!General Private
      bool debugMode = false;
      thread *brainThread;
      thread *controllerThread;

      enum dataType
      {
        NO_DATA = 0,
        INT = 1,
        FLOAT = 2,
        DOUBLE = 3,
        TEXT = 4
      };

      //!Auto Select UI Private
      int buttonCount;
      button * buttonList[maxButtonCount];
      button * pageBack;
      button * pageForward;
      void (*printPointer)(void);
      int activeAutoPage;
      int progMode = 0;
      int * buttonMode = &progMode;
      int pageTurnIndex;
      int * pageTurnButton = &pageTurnIndex;
      int blankPage;
      int * blankPagePointer = &blankPage;
      bool prePress;
      void addButton(void (*callback)(int));
      void pressed();
      void displayButtonName();

      int displayTime = 1500;

      //!Match UI Private

      int activeMatchPage = 0;

      bool createdField = false;
      turnType feildSide;

      struct tile
      {
        color tileColor = fieldGrey;
        int tileColorInt = -1;
        int xCord;
        int yCord;
      } fieldTiles[36];
      
      int brainOutCount = 0;

      struct brainReadOut
      {
        dataType graphDataType;
        char Name[MAX_CONTROLLER_NAME_LENGTH];
        uint nameLength = 0;
        int *intData;
        float *floatData;
        double *doubleData;
        color graphColor = blue;
      } brainObjects[MAX_BRAIN_GRAPH_COUNT];

      color defaultReadoutColor = blue;
  
    public:
      //!General

      /**
       * @brief Sets if debugging is enabled.
       * @param mode A boolean controlling debug mode.
      */
      void setDebugMode(bool mode);

      /**
       * @brief Starts the UI thread handling screen updates and touch detection.
      */
      void startUIThreads();

      /**
       * @brief Sets the display function to be called when any button is pressed.
      */
      void setDisplayFunc(void (*callback)(void));

      void printButtons(); //!Reserved for thread. DO NOT USE!
      void pressCheck(); //!Reserved for thread. DO NOT USE!
      void renderRobotPosition(); //!Reserved for thread. DO NOT USE!
      void printArrowButtons(); //!Reserved for thread. DO NOT USE!

      //!Auto Select UI
      goodUI();
      int addButton(int r, int g, int b);
      int addButton(int r, int g, int b, void (*callback)(int));
      int addButton(int r, int g, int b, bool iconInput[35][35]);
      int addButton(int r, int g, int b, void (*callback)(int), bool iconInput[35][35]);
      int addButton(color buttonColor);
      int addButton(color buttonColor, void (*callback)(int));
      int addButton(color buttonColor, bool iconInput[35][35]);
      int addButton(color buttonColor, void (*callback)(int), bool iconInput[35][35]);
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH]);
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], void (*callback)(int));
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], bool iconInput[35][35]);
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], void (*callback)(int), bool iconInput[35][35]);
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH]);
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], void (*callback)(int));
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], bool iconInput[35][35]);
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], void (*callback)(int), bool iconInput[35][35]);
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH]);
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int));
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], bool iconInput[35][35]);
      int addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int), bool iconInput[35][35]);
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH]);
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int));
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], bool iconInput[35][35]);
      int addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int), bool iconInput[35][35]);

      int addBlank();
      void changeButtonColor(int button, int r, int g, int b);
      int getButtonCount();
      int getProgNumber();

      /**
       * @brief Changes the selected button.
       * @param button The button that will be selected.
       * @param doNotShowSettings Optional. Allows the user to change the program showing the name on the screen.
      */
      void selectButton(int button, bool doNotShowSettings = false);

      /**
       * @brief Sets the time the text will be displayed on the Brain.
       * @param time The time in ms.
      */
      void setDisplayTime(int time);

      /**
       * @brief A structure containing all of the arrays for the icons.
      */
      iconArrays Icons;
      
      //!Match UI

      /**
       * @brief Draws the match UI to the screen.
      */
      void drawBrainGraphData();

      //Field Setup

      /**
       * @brief Creates the field display. NOTE: USING THIS WILL REMOVE 4 SLOTS FOR GRAPHS ON THE
       *  BRAIN SCREEN.
       * @param side Which side of the brain's screen the field will be displayed on.
      */
      void createFieldDisplay(turnType side);

      /**
       * @param Sets a tile's color on the field display.
       * @param tileID The numerical ID of the tile. Ranges from 0-35, with 0 being the top left,
       * and 35 being the bottom right. The value goes up by one for each tile to he right.
       * @param tileColor The color the tile will be set too.
      */
      void setTileColor(uint8_t tileID, color tileColor);

      /**
       * @param Sets a tile's color on the field display.
       * @param tileID The numerical ID of the tile. Ranges from 0-35, with 0 being the top left,
       * and 35 being the bottom right. The value goes up by one for each tile to he right.
       * @param tileColor The color the tile will be set too.
      */
      void setTileColor(uint8_t tileID, int tileColor);

      //!Read Out Setup

      bool createBlankBrainReadOut();

      /**
       * @brief Sets the default color of the readouts on the Brain during the match.
       * @param Color The color of the readouts.
      */
      void setDefaultReadOutColor(color Color);

      /**
       * @brief Creates text to display on the Brain.
       * @param name An array of characters containing the name of the data.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH]);

      /**
       * @brief Creates text to display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param Color Optional. The color of the data displayed.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], color Color);

      /**
       * @brief Creates a new variable display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], int &data);

      /**
       * @brief Creates a new variable display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
       * @param Color Optional. The color of the data displayed.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], int &data, color Color);

      /**
       * @brief Creates a new variable display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], float &data);

      /**
       * @brief Creates a new variable display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
       * @param Color Optional. The color of the data displayed.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], float &data, color Color);

      /**
       * @brief Creates a new variable display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], double &data);

      /**
       * @brief Creates a new variable display on the Brain.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
       * @param Color Optional. The color of the data displayed.
      */
      bool createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], double &data, color Color);

      //!Controller UI

      /**
       * @brief UI for the primary controller.
      */
      controllerUI primaryControllerUI = controllerUI(&primaryController.Screen);

      /**
       * @brief UI for the secondary controller.
      */
      controllerUI secondaryControllerUI = controllerUI(&secondaryController.Screen);
  };

  extern goodUI UI;
}

#endif // __USERINTERFACE_H__