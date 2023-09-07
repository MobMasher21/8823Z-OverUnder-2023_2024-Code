#ifndef _VISION_TRACKER_
#define _VISION_TRACKER_

#include "vex.h"

#define AVERAGE_COUNT 100

class VisionTracker
{
  public:
    /****** setup code ******/
    VisionTracker(vision * sensorAddress, vision::signature * signatureAddress);  //constructor to pass in sensor and tracking signature
    bool tglLEDIndicator(bool state);  //allows you to control if the LED on the sensor is used to indicate the object
    bool tglScreenIndicator(bool state);  //allows you to control if the brain screen is used to indicate the object
    bool tglDebugMode(bool state);  //allows you to control if data is printed to the terminal
    int setLockRange(int range);  //set how far the object can be form the center to be considered "Locked on"

    /****** monocular distance setup code ******/
    //used to calculate single eye distance using downward exponential curve
    //desmos calculator link https://www.desmos.com/calculator/y1xjjfv2ld
    //format y=a^(-(x+b))+c
    void setupDistanceMath(double a, double b, double c);  //set up a, b, and c values
    bool tglDistanceCalculation(bool state);  //allow you to turn on and off distance calculations
    double returnAverageDistance();  //returns the average distance of ball over the count time

    /****** constants ******/
    enum {
      LEFT,
      RIGHT
    };

    /****** functional code ******/
    void trackObject();  //takes snapshot and sets object variables
    
    int objectCount;  //number of object that are detected
    int objectXDim;  //number of pixels wide the object is
    int objectYDim;  //number of pixels tall the object is
    int objectXPos;  //x position of the center of the object
    int objectYPos;  //y position of the center of the object

    bool isLocked;  //is the object in the center of the view
    bool directionOff;  //is it off the the left or right

  private:
    vision * sensorPointer;
    vision::signature * trackingSignature;
    bool LEDMode;
    bool screenMode;
    bool debugMode;
    int lockRange;
    int lockTop;
    int lockBottom;

    /****** monocular distance ******/
    bool distanceMode;
    double aValue;
    double bValue;
    double cValue;
    double findDistance(int xDimIn) { return(pow(aValue, -(xDimIn + bValue)) + cValue); }
    double averageNumbers[AVERAGE_COUNT];
    double averageSum = 0;
    int headPosition = AVERAGE_COUNT - 1;
    int tailPosition = 0;

};

#endif //_VISION_TRACKER_