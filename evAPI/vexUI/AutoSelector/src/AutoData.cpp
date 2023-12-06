#include "../include/AutoData.h"

void AutoData::setTitle(char titleIN[MAX_TITLE_LENGTH]) {  // Set the auto title
  int i = 0;
  while(1) {
    title[i] = titleIN[i];
    i++;
    if(titleIN[i] == 0) {
      break;
    }
  }
  hasTitle = true;
}

void AutoData::setDescription(char descriptionIN[MAX_DESCRIPTION_LENGTH]) {  // Set the auto description
  int lineStartPos = 0;
  int lineEndPos = 0;
  int lineCharacterCount;
  bool tooLong = false;
  bool break1 = true;
  bool break2 = true;
  while(break1) {  // Breaks at end of input
    break2 = true;
    tooLong = false;
    lineCharacterCount = 1;
    while(break2) {  // Breaks at end of line
      if(descriptionIN[lineEndPos] == '\n') {  // Used to check if the user put in their own new line calls
        break2 = false;
      }

      if(lineCharacterCount > PER_LINE_MAX) {  // Checks to see if the current line would be too long
        tooLong = true;
      }

      if(tooLong && descriptionIN[lineEndPos] == ' ') {  // Roles back to find next space and makes that a new line-
        descriptionIN[lineEndPos] = '\n';
        break2 = false;
      }

      if(!tooLong) {
        lineEndPos++;
        lineCharacterCount++;
      } else if(tooLong) {
        lineEndPos--;
        lineCharacterCount--;
      }

      if(descriptionIN[lineEndPos] == '\0') {
        break1 = false;
      }
    }

    for(int i = lineStartPos; i <= lineEndPos; i++) {  // Saves the next line to the description
      description[i] = descriptionIN[i];
    }
    lineStartPos = lineEndPos + 1;
    lineEndPos++;


  }
  hasDescription = true;
}

bool AutoData::printButtonData() {  // Prints all the data to the screen
  bool printedStuff = false;
  int i = 0;
  if(hasTitle) {
    Brain.Screen.setFont(mono60); //Set up parameters for title.
    Brain.Screen.setFillColor(transparent);
    Brain.Screen.setPenColor(white);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(title);  // Print the title
    Brain.Screen.newLine();
    printedStuff = true;
    if(hasDescription) {
      Brain.Screen.setFont(mono20);  //Set up description parameters.
      Brain.Screen.setCursor(4, 1);
      //Brain.Screen.print(description);
      while(1) {
        Brain.Screen.print("%c", description[i]);
        if(description[i] == '\n') {
          Brain.Screen.newLine();
        }
        if(description[i] == '\0') {
          break;
        }
        i++;
      }
    }
  }
  return(printedStuff);
}