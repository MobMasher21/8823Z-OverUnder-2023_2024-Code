#include "VisionTracker.h"

VisionTracker::VisionTracker(vision * sensorAddress, vision::signature * signatureAddress) {
  fflush(stdout);
	sensorPointer = sensorAddress;
	trackingSignature = signatureAddress;
}

bool VisionTracker::tglLEDIndicator(bool state) {
  LEDMode = state;
  return LEDMode;
}

bool VisionTracker::tglScreenIndicator(bool state) {
  screenMode = state;
  return screenMode;
}

bool VisionTracker::tglDebugMode(bool state) {
  debugMode = state;
  return debugMode;
}

int VisionTracker::setLockRange(int range) {
  lockRange = range;
  lockTop = 157 + range; //157 is half of the total vision sensor range
  lockBottom = 157 - range;
  return lockRange;
}

void VisionTracker::trackObject() {
  sensorPointer->takeSnapshot(*trackingSignature);
  if(sensorPointer->objectCount > 0) {
    //sets variables to biggest object values
    objectXDim = sensorPointer->objects[0].width;
    objectYDim = sensorPointer->objects[0].height;
    objectXPos = sensorPointer->objects[0].centerX;
    objectYPos = sensorPointer->objects[0].centerY;

    //calculates if it is locked and which direction off it is
    if(objectXPos <= lockBottom && objectXPos >= lockTop) {
      isLocked = true;
    } else {
      isLocked = false;
      if(objectXPos > lockTop) {
        directionOff = LEFT;
      } else if(objectXPos < lockBottom) {
        directionOff = RIGHT;
      }
    }
  }

  //prints object to screen
  if(screenMode) {
    Brain.Screen.clearScreen();
    if(sensorPointer->objectCount > 0) {
      //draw border
      Brain.Screen.setFillColor(black);
      Brain.Screen.setPenColor(white);
      Brain.Screen.setPenWidth(5);
      Brain.Screen.drawRectangle(10, 10, 316, 212);

      //set draw object
      Brain.Screen.setPenWidth(1);
      if(isLocked) {
        Brain.Screen.setFillColor(blue);
      } else {
        if(directionOff == LEFT) {
          Brain.Screen.setFillColor(green);
        } else if(directionOff == RIGHT) {
          Brain.Screen.setFillColor(red);
        }
      }
      Brain.Screen.drawRectangle(sensorPointer->objects[0].originX + 10, sensorPointer->objects[0].originY + 10, objectXDim, objectYDim);
    }
  }

  //set sensor LED color
  if(LEDMode) {
    if(sensorPointer->objectCount > 0) {
      if(isLocked) {
        sensorPointer->setLedColor(0, 0, 255);
      } else {
        if(directionOff == LEFT) {
          sensorPointer->setLedColor(0, 255, 0);
        } else if(directionOff == RIGHT) {
          sensorPointer->setLedColor(255, 0, 0);
        }
      }
    } else {
      sensorPointer->getLedColor(0, 0, 0);
    }
  }

  //print data to terminal
  if(debugMode) {
    printf("xPos = %i, ", objectXPos);
    printf("yPos = %i, ", objectYPos);
    printf("xDim = %i, ", objectXDim);
    printf("yDim = %i\n", objectYDim);
  }
}