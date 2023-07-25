#include <ctype.h>
#include "..\include\UserInterface.h"
#include "..\include\pageArrowsIcons.h"
#include "../../Common/include/evNamespace.h"
#include "../../Common/include/Controllers.h"

#define TILE_SIDE_LENGTH 30
#define TILE_BORDER_DISTANCE 10
#define TILE_VERTICAL_OFFSET 10
#define TILE_LEFT_HORIZONTAL_OFFSET (TILE_BORDER_DISTANCE - 3)
#define TILE_RIGHT_HORIZONTAL_OFFSET ((480 - (TILE_SIDE_LENGTH * 6)) - 3 - TILE_BORDER_DISTANCE)
#define GRAPH_RIGHT_HORIZONTAL_OFFSET 100

#define GRAPH_TOP_VERTICAL_OFFSET 10
#define GRAPH_LEFT_HORINZONTAL_OFFSET 10
#define GRAPH_RIGHT_HORINZONTAL_OFFSET 255
#define GRAPH_STANDARD_HEIGHT 30
#define GRAPH_STANDARD_LENGTH 215
#define GRAPH_BETWEEN_SPACING 20
#define BRAIN_CHARACTER_WIDTH 10

#define BRAIN_DISPLAY_TRIGGER 1 //How often the Brain display graphs get updated
#define CONTROLLER_DISPLAY_TRIGGER 2 //How often the Brain display graphs get updated
namespace evAPI
{
  goodUI UI = goodUI();

  uint8_t currentMatchState = disabled; //0 = Disabled; 1 = Auto; 2 = Driver
  uint8_t preMatchState = 0;

  int UIControllerFunc()
  {
    uint8_t controllerUpdateCounter = 0;

    while(true)
    {
      if(controllerUpdateCounter >= CONTROLLER_DISPLAY_TRIGGER) //Update Controller
      {
        UI.drawControllerGraphData();
        controllerUpdateCounter = 0;
      }
      
      else
      { controllerUpdateCounter++; }

      this_thread::sleep_for(25);
    }
    return 0;
  }


  int UIBrainFunc()
  {
    uint8_t brainUpdateCounter = 0;
    
    while(true)
    {
      if(!competition().isEnabled()) //Stores the current match state
      { currentMatchState = disabled; }

      else if(competition().isAutonomous())
      { currentMatchState = autonomousControl; }

      else
      { currentMatchState = driverControl; }

      UI.pressCheck(); //Checks the screen for presses

      //Draws match info to the screen
      if(currentMatchState != disabled)
      {
        UI.renderRobotPosition();

        if(brainUpdateCounter >= BRAIN_DISPLAY_TRIGGER) //Updates Graphs
        {
          UI.drawBrainGraphData();
          brainUpdateCounter = 0;
        }

        else
        { brainUpdateCounter++; }
      }
      
      if(preMatchState != currentMatchState) //Redraws screen to reflect match state
      {
        if(currentMatchState != disabled)
        {
          Brain.Screen.clearScreen();
          UI.printArrowButtons();
          UI.drawBrainGraphData();
          brainUpdateCounter = 0; //Resets display timer
        }

        else
        {
          Brain.Screen.clearScreen();
          UI.printButtons();
        }
      }

      preMatchState = currentMatchState;

      this_thread::sleep_for(50);
    }

    return 0;
  }

  //!General
  void goodUI::setDebugMode(bool mode)
  { debugMode = mode; }

  void goodUI::startUIThreads()
  {
    brainThread = new thread(UIBrainFunc);
    controllerThread = new thread(UIControllerFunc);
  }

  void goodUI::setDisplayFunc(void (*callback)(void))
  { printPointer = callback; }

  //!Auto Select UI
  arrowIcons Arrows;

  goodUI::goodUI() {
    fflush(stdout);
    activeAutoPage = 0;
    pageBack = new button(-1, pageTurnButton);
    pageForward = new button(1, pageTurnButton);
    pageBack->setDims(165, 200, 60, 30);
    pageForward->setDims(255, 200, 60, 30);
    pageBack->setIconArray(Arrows.previousPageArrow);
    pageForward->setIconArray(Arrows.nextPageArrow);
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

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH]) {
    goodUI::addButton(NULL);
    
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], void (*callback)(int)) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], bool iconInput[35][35]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], void (*callback)(int), bool iconInput[35][35]) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], void (*callback)(int)) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], bool iconInput[35][35]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], void (*callback)(int), bool iconInput[35][35]) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int)) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], bool iconInput[35][35]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(int r, int g, int b, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int), bool iconInput[35][35]) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(r, g, b);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int)) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], bool iconInput[35][35]) {
    goodUI::addButton(NULL);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
    return(buttonCount);
  }

  int goodUI::addButton(color buttonColor, const char Title[MAX_TITLE_LENGTH], const char Description[MAX_DESCRIPTION_LENGTH], void (*callback)(int), bool iconInput[35][35]) {
    goodUI::addButton(callback);
    buttonList[buttonCount - 1]->setColor(buttonColor);
    buttonList[buttonCount - 1]->setIconArray(iconInput);
    buttonList[buttonCount - 1]->setTitle(Title);
    buttonList[buttonCount - 1]->setDescription(Description);
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
    //int preButton = progMode; //Stores information
    int pressPointX = Brain.Screen.xPosition();
    int pressPointY = Brain.Screen.yPosition();

    if(debugMode)
    { printf("xPos = %i, yPos = %i, button = %i\n", pressPointX, pressPointY, progMode); }
    
    if(currentMatchState == disabled) //Auto UI Code
    {
      int prevProgMode = progMode;
      //Runs functions attached to buttons
      for(int i = activeAutoPage * 8; i <= (activeAutoPage + 1) * 8 - 1; i++) {
        if(i < buttonCount) {
          buttonList[i]->pressed(pressPointX, pressPointY);
        }
      }
    
      //Changes page
      pageBack->pressed(pressPointX, pressPointY);
      pageForward->pressed(pressPointX, pressPointY);
      if(pageTurnIndex == -1) { //Decrement page
        activeAutoPage = activeAutoPage - 1;
      }
      if(pageTurnIndex == 1) {  //Increment page
        activeAutoPage = activeAutoPage + 1;
      }
      if(activeAutoPage < 0) {  //Keep page value positive
        activeAutoPage = 0;
      }
      if(activeAutoPage > (buttonCount - 1) / 8) {  //Prevent from going into empty pages
        activeAutoPage = (buttonCount - 1) / 8;
      }
    
      if(prevProgMode != progMode) //Updates button info on screen
      { displayButtonName(); }

      Brain.Screen.clearScreen();
      goodUI::printButtons();
    }

    else //Match
    {
      //Changes page
      pageBack->pressed(pressPointX, pressPointY);
      pageForward->pressed(pressPointX, pressPointY);
      if(pageTurnIndex == -1) { //Decrement page
        activeMatchPage = activeMatchPage - 1;
      }
      if(pageTurnIndex == 1) {  //Increment page
        activeMatchPage = activeMatchPage + 1;
      }
      if(activeMatchPage < 0) {  //Keep page value positive
        activeMatchPage = 0;
      }

      if(createdField) //Prevent from going into empty pages
      {
        if(activeMatchPage > (brainOutCount - 1) / 4) {  
          activeMatchPage = (brainOutCount - 1) / 4;
        }
      }

      else
      {
        if(activeMatchPage > (brainOutCount - 1) / 8) {  
          activeMatchPage = (brainOutCount - 1) / 8;
        }
      }

      Brain.Screen.clearScreen();
      printArrowButtons();
      drawBrainGraphData();
    }
  }

  void goodUI::displayButtonName()
  {
    if(buttonList[progMode]->getTitleLength() == 0) //Don't display if there isn't a name.
    { return; }

    Brain.Screen.setFont(mono60); //Set up parameters for title.
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(transparent);
    Brain.Screen.setPenColor(white);

    for(uint8_t i = 0; i < buttonList[progMode]->getTitleLength(); i++) //Print title.
    { Brain.Screen.print("%c", buttonList[progMode]->getTitle(i)); }

    if(buttonList[progMode]->getDescriptionLength() != 0) //Checks if there is a description.
    {
      int descriptionLength = buttonList[progMode]->getDescriptionLength(); //Get description info.
      char Description[descriptionLength];
      int lastCharacterID = 0;
      char lastCharacter = '\0';

      for(int i = 0; i < descriptionLength; i++) //Copy the description to local for editing
      { Description[i] = buttonList[progMode]->getDescription(i); }

      Brain.Screen.newLine(); //Set up screen parameters.
      Brain.Screen.newLine();
      Brain.Screen.newLine();
      Brain.Screen.setFont(mono20);
            
      while(true)
      {
        int newLineCheckCount = 47; //Character IDs 0-47

        if(descriptionLength < 48) //Prevent newline code from looking into invalid areas.
        { newLineCheckCount = descriptionLength; }

        if(descriptionLength <= 48) //If it is less than 1 row, just print it all.
        {
          for(int i = 0; i < descriptionLength; i++)
          {
            if(Description[i] == '\n') //Check for new line
            { Brain.Screen.newLine(); }

            else
            { Brain.Screen.print("%c", Description[i]); }
          }

          vex::task::sleep(displayTime);
          Brain.Screen.clearScreen();
          goodUI::printButtons();
          return;
        }

        for(int i = 0; i < newLineCheckCount; i++) //Detect new line character
        {
          if(Description[i] == '\n') //Check for new line
          {
            if(lastCharacterID > 0) //Only print if there are characters to print
            {
              for(int ii = 0; ii < lastCharacterID; ii++) //Print characters until new line
              { Brain.Screen.print("%c", Description[ii]); } 
            }
            
            for(int i = lastCharacterID + 1; i < descriptionLength; i++) //Trim down description
            { Description[i - (lastCharacterID + 1)] = Description[i]; }

            descriptionLength -= (lastCharacterID + 1);
            lastCharacterID = 0;
            lastCharacter = '\0';
            Brain.Screen.newLine();
          }

          else
          { lastCharacterID++; }
        }
        
        if(lastCharacterID == 47) //Only check for line breaking if it needs to.
        {
          //Find character that is a space or punctuation.
          while (!(isspace(lastCharacter) || ispunct(lastCharacter)) && lastCharacterID != 0)
          {
            lastCharacterID--;
            lastCharacter = Description[lastCharacterID];
          }

          if(lastCharacterID == 0) //Cause the entire line to be printed if there isn't a place to break.
          { lastCharacterID = 47; }
              
          for(int i = 0; i <= lastCharacterID; i++) //Print until line break.
          { Brain.Screen.print("%c", Description[i]); }

          for(int i = lastCharacterID + 1; i <= descriptionLength; i++) //Trim down description
          { Description[i - (lastCharacterID + 1)] = Description[i]; }

          descriptionLength -= (lastCharacterID + 1); //Reset parameters and prep for next run.
          lastCharacterID = 0;
          lastCharacter = '\0';
          Brain.Screen.newLine();
        }
      }
    }

    vex::task::sleep(displayTime); //Wait before resetting screen.
    Brain.Screen.clearScreen();
    goodUI::printButtons();
  }

  void goodUI::printButtons() {
    //Print user buttons on screen, highlighting the selected one
    for(int i = activeAutoPage * 8; i <= (activeAutoPage + 1) * 8 - 1; i++) {
      if(i < buttonCount) {
        if(i == progMode) {
          buttonList[i]->drawButton(white);
        } else {
          buttonList[i]->drawButton();
        }
      }
    }

    printArrowButtons();
  }

  void goodUI::printArrowButtons() {
    //Draw arrow buttons, blanking them out if they would result in going to an invalid screen.

    if(currentMatchState != disabled) //Match
    {
      if(activeMatchPage - 1 < 0) {
        pageBack->setColor(50, 50, 50);
      } else {
        pageBack->setColor(150, 150, 150);
      }

      if(createdField)
      {
        if(activeMatchPage >= (brainOutCount - 1) / 4) {
          pageForward->setColor(50, 50, 50);
        } else {
          pageForward->setColor(150, 150, 150);
        }
      }

      else
      {
        if(activeMatchPage >= (brainOutCount - 1) / 8) {
          pageForward->setColor(50, 50, 50);
        } else {
          pageForward->setColor(150, 150, 150);
        }
      }
      
      pageBack->drawButton(white, 2);
      pageForward->drawButton(white, 2);
    }

    else //Preauto
    {
      if(activeAutoPage - 1 < 0) {
        pageBack->setColor(50, 50, 50);
      } else {
        pageBack->setColor(150, 150, 150);
      }
      if(activeAutoPage >= (buttonCount - 1) / 8) {
        pageForward->setColor(50, 50, 50);
      } else {
        pageForward->setColor(150, 150, 150);
      }
      pageBack->drawButton(white, 2);
      pageForward->drawButton(white, 2);
    }

    Brain.Screen.setFont(mono20); //Updates Match mode
    Brain.Screen.setCursor(12, 1);
    Brain.Screen.print("          ");
    Brain.Screen.setCursor(12, 1);
    this_thread::sleep_for(10);

    if(currentMatchState == disabled)
    { Brain.Screen.print("Disabled"); }

    else
    {
      if(currentMatchState == autonomousControl)
      { Brain.Screen.print("Autonomous"); }

      else
      { Brain.Screen.print("Driver"); }
    }
  }


  void goodUI::selectButton(int button, bool doNotShowSettings)
  {
    progMode = button;

    if(!doNotShowSettings)
    { displayButtonName(); }

    printButtons();
  }

  void goodUI::setDisplayTime(int time)
  { displayTime = time; }

  //!MATCH UI

  //Field Setup

  void goodUI::drawBrainGraphData()
  {
    if(brainOutCount != 0) //Draw graphs
    {
      int startingIndex = 0; //First graph ID to draw.
      int drawCount = 8; //Number of graphs to draw.
      int horizontalOffset = GRAPH_LEFT_HORINZONTAL_OFFSET;
      int verticalOffset = GRAPH_TOP_VERTICAL_OFFSET;
      int currentGraph = 0; //The graph currently being drawn out how many will be.

      if(createdField)
      {
        drawCount = 4;

        if(feildSide == left) //Change the offset to keep the graphs and field separate
        { horizontalOffset = GRAPH_RIGHT_HORINZONTAL_OFFSET; }
      }

      startingIndex = drawCount * activeMatchPage; //Select the first graph to draw

      for (int i = startingIndex; i < (drawCount + startingIndex); i++) //Draw graphs
      {
        if(currentGraph == 4) //Pushes the graphs to the right if all the ones on the lest are drawn
        {
          horizontalOffset = GRAPH_RIGHT_HORINZONTAL_OFFSET;
          verticalOffset = GRAPH_TOP_VERTICAL_OFFSET;
        }

        if(brainObjects[i].graphDataType != NO_DATA) //Only print on screen if there is data to print.
        {
          Brain.Screen.setFillColor(brainObjects[i].graphColor); //Set fill color for box

          Brain.Screen.drawRectangle(horizontalOffset, //Draw box
            verticalOffset, 
            GRAPH_STANDARD_LENGTH, 
            GRAPH_STANDARD_HEIGHT
          );

          Brain.Screen.printAt(horizontalOffset + 2, //Write text
            verticalOffset + (GRAPH_STANDARD_HEIGHT / 1.4), 
            brainObjects[i].Name
          );

          switch (brainObjects[i].graphDataType) //Print value
          {
            case INT:
              Brain.Screen.printAt(
                horizontalOffset + 2 + (brainObjects[i].nameLength * BRAIN_CHARACTER_WIDTH), 
                verticalOffset + (GRAPH_STANDARD_HEIGHT / 1.4), 
                "%d", *brainObjects[i].intData
              );

            break;

            case FLOAT:
              Brain.Screen.printAt(
                horizontalOffset + 2 + (brainObjects[i].nameLength * BRAIN_CHARACTER_WIDTH), 
                verticalOffset + (GRAPH_STANDARD_HEIGHT / 1.4), 
                "%.3f", *brainObjects[i].floatData
              );

            break;
              
            case DOUBLE:
              Brain.Screen.printAt(
                horizontalOffset + 2 + (brainObjects[i].nameLength * BRAIN_CHARACTER_WIDTH), 
                verticalOffset + (GRAPH_STANDARD_HEIGHT / 1.4), 
                "%.3f", *brainObjects[i].doubleData
              );

              break;

            default:
              break;
          }
        }

        //Lowers the vertical position for the next graph
        verticalOffset += (GRAPH_BETWEEN_SPACING + GRAPH_STANDARD_HEIGHT); 
        currentGraph++;
      }
      
    }

    printArrowButtons();
    if(createdField) //Field Tiles
    {
      for (uint8_t i = 0; i <= 35; i++)
      {
        if(fieldTiles[i].tileColorInt == -1) //Detects which color type to use
        {
          Brain.Screen.drawRectangle(fieldTiles[i].xCord + 1, //Color class; Plus 1 to account for border
            fieldTiles[i].yCord + 1,
            TILE_SIDE_LENGTH,
            TILE_SIDE_LENGTH,
            fieldTiles[i].tileColor
          );
        }

        else
        {
          Brain.Screen.drawRectangle(fieldTiles[i].xCord + 1, //Int type color
            fieldTiles[i].yCord + 1,
            TILE_SIDE_LENGTH,
            TILE_SIDE_LENGTH,
            fieldTiles[i].tileColorInt
          );
        }
      }
    }
  }

  void goodUI::renderRobotPosition()
  {

  }

  void goodUI::createFieldDisplay(turnType side)
  {
    feildSide = side; //Stores what side the field is on

    //Sets the correct horizontal offset depending on the side of the field
    int horizontalOffset = TILE_LEFT_HORIZONTAL_OFFSET; 

    if(side == right)
    { horizontalOffset = TILE_RIGHT_HORIZONTAL_OFFSET; }

    //Sets the coordinates of each tile on the brain.
    uint8_t Row = 0;
    uint8_t Colum = 0;

    for (int i = 0; i <= 35; i++)
    {
      if(Colum > 5)
      {
        Colum = 0;
        Row++;
      }

      fieldTiles[i].xCord = horizontalOffset + (TILE_SIDE_LENGTH * Colum);
      fieldTiles[i].yCord = TILE_VERTICAL_OFFSET + (TILE_SIDE_LENGTH * Row);

      Colum++;
    }

    createdField = true;
  }

  void goodUI::setTileColor(uint8_t tileID, color tileColor)
  {
    fieldTiles[tileID].tileColor = tileColor;
    fieldTiles[tileID].tileColorInt = -1;
  }

  void goodUI::setTileColor(uint8_t tileID, int tileColor)
  { fieldTiles[tileID].tileColorInt = tileColor; }

  //!Read Out Setup

  bool goodUI::createBlankBrainReadOut()
  {
    if(brainOutCount >= MAX_BRAIN_GRAPH_COUNT) //Stops if the maximum amount of data points has been reached.
    { return 1; }

    brainObjects[brainOutCount].graphDataType = NO_DATA;

    brainOutCount++;
    return 0;
  }

  void goodUI::setDefaultReadOutColor(color Color)
  { defaultReadoutColor = Color; }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH])
  { return createBrainReadOut(name, defaultReadoutColor); }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], color Color)
  {
    if(brainOutCount >= MAX_BRAIN_GRAPH_COUNT) //Stops if the maximum amount of data points has been reached.
    { return 1; }

    brainObjects[brainOutCount].graphDataType = TEXT;
    brainObjects[brainOutCount].graphColor = Color;
    brainObjects[brainOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { brainObjects[brainOutCount].Name[i] = name[i]; }

    brainOutCount++;
    return 0;
  }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], int &data)
  { return createBrainReadOut(name, data, defaultReadoutColor); }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], int &data, color Color)
  {
    if(brainOutCount >= MAX_BRAIN_GRAPH_COUNT) //Stops if the maximum amount of data points has been reached.
    { return 1; }

    brainObjects[brainOutCount].graphDataType = INT;
    brainObjects[brainOutCount].intData = &data;
    brainObjects[brainOutCount].graphColor = Color;
    brainObjects[brainOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { brainObjects[brainOutCount].Name[i] = name[i]; }

    brainOutCount++;
    return 0;
  }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], float &data)
  { return createBrainReadOut(name, data, defaultReadoutColor); }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], float &data, color Color)
  {
    if(brainOutCount >= MAX_BRAIN_GRAPH_COUNT) //Stops if the maximum amount of data points has been reached.
    { return 1; }

    brainObjects[brainOutCount].graphDataType = FLOAT;
    brainObjects[brainOutCount].floatData = &data;
    brainObjects[brainOutCount].graphColor = Color;
    brainObjects[brainOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { brainObjects[brainOutCount].Name[i] = name[i]; }

    brainOutCount++;
    return 0;
  }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], double &data)
  { return createBrainReadOut(name, data, defaultReadoutColor); }

  bool goodUI::createBrainReadOut(const char name[MAX_BRAIN_NAME_LENGTH], double &data, color Color)
  {
    if(brainOutCount >= MAX_BRAIN_GRAPH_COUNT) //Stops if the maximum amount of data points has been reached.
    { return 1; }

    brainObjects[brainOutCount].graphDataType = DOUBLE;
    brainObjects[brainOutCount].doubleData = &data;
    brainObjects[brainOutCount].graphColor = Color;
    brainObjects[brainOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { brainObjects[brainOutCount].Name[i] = name[i]; }

    brainOutCount++;
    return 0;
  }

  //!Controller UI
  
  void goodUI::drawControllerGraphData()
  {
    int currentLine = 0;
    int primaryDataCount = 0;
    int secondaryDataCount = 0;

    static bool clearedPrimaryScreen = 0;
    static bool clearedSecondaryScreen = 0;

    if(controllerOutCount <= 3) //How many objects need to be printed to the primary controller.
    { primaryDataCount = controllerOutCount; }

    else
    { primaryDataCount = 3; }

    if(controllerOutCount >= 4) //How many objects need to be printed to the secondary controller.
    { secondaryDataCount = (controllerOutCount - 3); }

    if(controllerOutCount > 0) //Draws UI on primary controller
    {
      if(!clearedPrimaryScreen) //Clear screen if it has not been.
      {
        primaryController.Screen.clearScreen();
        clearedPrimaryScreen = true;
      }

      for (int i = 0; i < primaryDataCount; i++)
      {
        switch (controllerObjects[i].graphDataType)
        {
          case TEXT:
            if(controllerObjects[i].prevRunIntData != 1) //Prevent the name from being printed multiple times
            {
              primaryController.Screen.setCursor(i + 1, 1);

              primaryController.Screen.print(controllerObjects[i].Name);

              controllerObjects[i].prevRunIntData = 1; //Make sure it only runs once.
            }
            break;

          case INT:
            if(controllerObjects[i].prevRunIntData != *controllerObjects[i].intData)
            {
              primaryController.Screen.setCursor(i + 1, 1); //Select and clear lines
              primaryController.Screen.clearLine(i + 1);

              this_thread::sleep_for(5);

              primaryController.Screen.print(controllerObjects[i].Name); //Print Name
              primaryController.Screen.print("%d", *controllerObjects[i].intData); //Print Data

              //Make sure it only runs when the value changes.
              controllerObjects[i].prevRunIntData = *controllerObjects[i].intData;
            }
            break;
          
          case FLOAT:
            if(controllerObjects[i].prevRunFloatData != *controllerObjects[i].floatData)
            {
              primaryController.Screen.setCursor(i + 1, 1); //Select and clear lines
              primaryController.Screen.clearLine(i + 1);

              this_thread::sleep_for(5);

              primaryController.Screen.print(controllerObjects[i].Name); //Print Name
              primaryController.Screen.print("%.2f", *controllerObjects[i].floatData); //Print Data

              //Make sure it only runs when the value changes.
              controllerObjects[i].prevRunFloatData = *controllerObjects[i].floatData;
            }
            break;
        
          case DOUBLE:
            if(controllerObjects[i].prevRunDoubleData != *controllerObjects[i].doubleData)
            {
              primaryController.Screen.setCursor(i + 1, 1); //Select and clear lines
              primaryController.Screen.clearLine(i + 1);

              this_thread::sleep_for(5);

              primaryController.Screen.print(controllerObjects[i].Name); //Print Name
              primaryController.Screen.print("%.2f", *controllerObjects[i].doubleData); //Print Data

              //Make sure it only runs when the value changes.
              controllerObjects[i].prevRunDoubleData = *controllerObjects[i].doubleData;
            }
            break;
          
          default:
            break;
        }
      }

      if(secondaryDataCount != 0) //Draws UI on secondary controller
      {
        currentLine = 1;

        if(!clearedSecondaryScreen) //Clear screen if it has not been.
        {
          secondaryController.Screen.clearScreen();
          clearedSecondaryScreen = true;
        }

        for (int i = 3; i < secondaryDataCount + 3; i++)
        {
          switch (controllerObjects[i].graphDataType)
          {
            case TEXT:
              if(controllerObjects[i].prevRunIntData != 1) //Prevent the name from being printed multiple times
              {
                secondaryController.Screen.setCursor(currentLine, 1);

                for (int ii = 0; ii < controllerObjects[ii].nameLength; ii++) //Print Name
                { secondaryController.Screen.print(controllerObjects[ii].Name); }

                controllerObjects[i].prevRunIntData = 1; //Make sure it only runs once.
                currentLine++;
              }
              break;
        
            case INT:
              if(controllerObjects[i].prevRunIntData != *controllerObjects[i].intData)
              {
                secondaryController.Screen.setCursor(currentLine, 1); //Select and clear lines
                secondaryController.Screen.clearLine();

                for (int ii = 0; ii < controllerObjects[ii].nameLength; ii++) //Print Name
                { secondaryController.Screen.print(controllerObjects[ii].Name); }

                secondaryController.Screen.print("%d", *controllerObjects[i].intData);

                //Make sure it only runs when the value changes.
                controllerObjects[i].prevRunIntData = *controllerObjects[i].intData;
                currentLine++;
              }
              break;
          
            case FLOAT:
              if(controllerObjects[i].prevRunFloatData != *controllerObjects[i].floatData)
              {
                secondaryController.Screen.setCursor(currentLine, 1); //Select and clear lines
                secondaryController.Screen.clearLine();

                for (int ii = 0; ii < controllerObjects[ii].nameLength; ii++) //Print Name
                { secondaryController.Screen.print(controllerObjects[ii].Name); }

                secondaryController.Screen.print("%.2f", *controllerObjects[i].floatData);

                //Make sure it only runs when the value changes.
                controllerObjects[i].prevRunFloatData = *controllerObjects[i].floatData;
                currentLine++;
              }
              break;
        
            case DOUBLE:
              if(controllerObjects[i].prevRunDoubleData != *controllerObjects[i].doubleData)
              {
                secondaryController.Screen.setCursor(currentLine, 1); //Select and clear lines
                secondaryController.Screen.clearLine();

                for (int ii = 0; ii < controllerObjects[ii].nameLength; ii++) //Print Name
                { secondaryController.Screen.print(controllerObjects[ii].Name); }

                secondaryController.Screen.print("%.2f", *controllerObjects[i].doubleData);

                //Make sure it only runs when the value changes.
                controllerObjects[i].prevRunDoubleData = *controllerObjects[i].doubleData;
                currentLine++;
              }
              break;

            default:
              break;
          }
        }
      }
    }
  }

  bool goodUI::createBlankControllerReadOut()
  {
    //Stops if the maximum amount of data points has been reached.
    if(controllerOutCount >= MAX_CONTROLLER_GRAPH_COUNT) 
    { return 1; }

    controllerObjects[controllerOutCount].graphDataType = NO_DATA;

    controllerOutCount++;
    return 0;
  }

  bool goodUI::createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH])
  {
    //Stops if the maximum amount of data points has been reached.
    if(controllerOutCount >= MAX_CONTROLLER_GRAPH_COUNT) 
    { return 1; }

    controllerObjects[controllerOutCount].graphDataType = TEXT;
    controllerObjects[controllerOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { controllerObjects[controllerOutCount].Name[i] = name[i]; }

    controllerOutCount++;
    return 0;
  }

  bool goodUI::createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH], int &data)
  {
    //Stops if the maximum amount of data points has been reached.
    if(controllerOutCount >= MAX_CONTROLLER_GRAPH_COUNT) 
    { return 1; }

    controllerObjects[controllerOutCount].graphDataType = INT;
    controllerObjects[controllerOutCount].intData = &data;
    controllerObjects[controllerOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { controllerObjects[controllerOutCount].Name[i] = name[i]; }

    controllerOutCount++;
    return 0;
  }

  bool goodUI::createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH], float &data)
  {
    //Stops if the maximum amount of data points has been reached.
    if(controllerOutCount >= MAX_CONTROLLER_GRAPH_COUNT) 
    { return 1; }

    controllerObjects[controllerOutCount].graphDataType = FLOAT;
    controllerObjects[controllerOutCount].floatData = &data;
    controllerObjects[controllerOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { controllerObjects[controllerOutCount].Name[i] = name[i]; }

    controllerOutCount++;
    return 0;
  }

  bool goodUI::createControllerReadOut(const char name[MAX_BRAIN_NAME_LENGTH], double &data)
  {
    //Stops if the maximum amount of data points has been reached.
    if(controllerOutCount >= MAX_CONTROLLER_GRAPH_COUNT) 
    { return 1; }

    controllerObjects[controllerOutCount].graphDataType = DOUBLE;
    controllerObjects[controllerOutCount].doubleData = &data;
    controllerObjects[controllerOutCount].nameLength = strlen(name);
    
    for (uint8_t i = 0; i < strlen(name); i++) //Stores the name.
    { controllerObjects[controllerOutCount].Name[i] = name[i]; }

    controllerOutCount++;
    return 0;
  }
}