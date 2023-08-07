#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "vex.h"
#include "..\include\button.h"
#include "..\include\iconArrays.h"
#include "..\..\Common\include\colors.h"
#include "..\..\Common\include\evNamespace.h"

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
      thread * brainThread;
      thread * controllerThread;

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

      //!Controller UI Private

      struct controllerReadOut
      {
        dataType graphDataType;
        char Name[MAX_BRAIN_NAME_LENGTH];
        uint nameLength = 0;
        int *intData;
        float *floatData;
        double *doubleData;
        int prevRunIntData;
        float prevRunFloatData;
        double prevRunDoubleData;
      } controllerObjects[MAX_CONTROLLER_GRAPH_COUNT];

      int controllerOutCount = 0; //Number of displayed outputs on controllers.
  
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

      //!New code

      void addButtonCore(int id); //!Make private upon completion of refactor

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param r The red value for the color of the button.
       * @param g The green value for the color of the button.
       * @param b The blue value for the color of the button.
       * 
      */
      int addButton(int id, int r, int g, int b);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param buttonColor A color object that contains the color of the button.
       * 
      */
      int addButton(int id, color buttonColor);

      /**
       * @brief Creates a new button with an ID and a color.
       * @param id The ID of the new button.
       * @param alliance The alliance the robot will be part of when this button is selected.
       * It's color will match that of the alliance, with no alliance producing a grey button.
      */
      int addButton(int id, allianceType alliance);
      
      /**
       * @brief Adds an icon to the button.
       * @param id The ID of the button.
       * @param iconInput A 35 by 35 array, with each value being treated as the value of a pixel.
      */
      bool addIcon(int id, bool iconInput[35][35]);
      bool addIcon(int id, color iconInput[35][35]);

      /**
       * @brief Adds a function to be called when the button is pressed.
       * @param id The ID of the button.
       * @param callback The function to be run.
      */
      bool addCallbackFunc(int id, void (*callback)(int));

      /**
       * @brief Adds a title to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Title An array of characters that contains the title.
      */
      bool addTitle(int id, const char Title[MAX_TITLE_LENGTH]);

      /**
       * @brief Adds a description to be displayed when the button is pressed.
       * The length it is displayed for is controlled by setDisplayTime.
       * @param id The ID of the button.
       * @param Title An array of characters that contains the description.
       * @returns False if it successfully adds the data.
      */
      bool addDescription(int id, const char Description[MAX_DESCRIPTION_LENGTH]);

      /**
       * @brief Maps a button to a specific alliance. This will not change the color of the button.
       * @param id The ID of the button.
       * @param alliance The alliance the robot will be part of when this button is selected.
      */
      bool addAlliance(int id, allianceType alliance);


      uint largestID = 0;


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
       * @brief Draws the match UI to the screen.
      */
      void drawControllerGraphData();

      bool createBlankControllerReadOut();

      /**
       * @brief Creates text to display on the Controllers.
       * @param name An array of characters containing the name of the data.
      */
      bool createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH]);

      /**
       * @brief Creates a new variable display on the Controllers.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
      */
      bool createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH], int &data);

      /**
       * @brief Creates a new variable display on the Controllers.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
      */
      bool createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH], float &data);

      /**
       * @brief Creates a new variable display on the Controllers.
       * @param name An array of characters containing the name of the data.
       * @param &data A variable to display.
      */
      bool createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH], double &data);
  };

  extern goodUI UI;
}

#endif // __USERINTERFACE_H__