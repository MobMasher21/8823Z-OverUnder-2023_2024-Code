#include "../include/vex.h"
#include "VisionConfig.h"

class VisionTracker
{
  public:
    /****** setup code ******/
    VisionTracker(vision * sensorAddress, vision::signature * signatureAddress);  //constructor to pass in sensor and tracking signature
    bool tglLEDIndicator(bool state);  //allows you to control if the LED on the sensor is used to indicate the object
    bool tglScreenIndicator(bool state);  //allows you to control if the brain screen is used to indicate the object
    bool tglDebugMode(bool state);  //allows you to control if data is printed to the terminal
    int setLockRange(int range);  //set how far the object can be form the center to be considered "Locked on"

    /****** constants ******/
    enum {
      LEFT,
      RIGHT
    };

    /****** functional code ******/
    void trackObject();  //takes snapshot and sets object variables
    int objectXDim;  //number of pixels wide the object is
    int objectYDim;  //number of pixels tall the object is
    int objectXPos;  //x position of the center of the object
    int objectYPos;  //y position of the center of the object

  private:
    vision * sensorPointer;
    vision::signature * trackingSignature;
    bool LEDMode;
    bool screenMode;
    bool debugMode;
    int lockRange;
    int lockTop;
    int lockBottom;

    bool isLocked;
    bool directionOff;

};
