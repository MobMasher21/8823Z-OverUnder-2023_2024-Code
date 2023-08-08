#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "vex.h"
#include "..\include\icon.h"
#include "..\..\Common\include\evNamespace.h"

#define MAX_TITLE_LENGTH 16
#define MAX_DESCRIPTION_LENGTH 240

namespace evAPI
{
  class button {
    public:
      button(int ID, int * buttonDataLocation);
      button(int ID, int * buttonDataLocation, void (*callback)(int));
      void setIconArray(bool arrayInput[35][35]);
      void drawButton();
      void drawButton(color borderColor);
      void drawButton(color borderColor, int borderSize);
      void setColor(int r, int g, int b);
      void setColor(color buttonColor);
      void setDims(int x, int y, int w, int h);
      bool pressed(int xPress, int yPress);

      void setTitle(const char newTitle[MAX_TITLE_LENGTH]);
      void setDescription(const char newDescription[MAX_DESCRIPTION_LENGTH]);

      char getTitle(int index);
      char getDescription(int index);
      int getTitleLength();
      int getDescriptionLength();

      void setCallback(void (*callback)(int));

      void setButtonAlliance(allianceType alliance);
      allianceType getButtonAlliance();
  
    private:
      int buttonID;
      int * IDStore;
      void (*buttonCallback)(int);
      icon buttonIcon;
      int xPos;
      int yPos;
      int width;
      int hight;
      color buttonColor;
      char Title[MAX_TITLE_LENGTH];
      char Description[MAX_DESCRIPTION_LENGTH];
      int titleLength = 0;
      int descriptionLength = 0;
      allianceType buttonAlliance = noAlliance;
  };
}

#endif // __BUTTON_H__