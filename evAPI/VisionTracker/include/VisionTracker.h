#ifndef _VISION_TRACKER_
#define _VISION_TRACKER_

#include "../../../evAPI/Common/include/evAPIBasicConfig.h"
#include "../../../evAPI/Common/include/evNamespace.h"

#define AVERAGE_COUNT 100

using namespace evAPI;

class VisionTracker {
  public:
    /****** setup code ******/
    /**
     * @brief Sets up the pointer for the sensor and the color the object will track
     * 
     * @param vision* The pointer to a vex vision sensor object that will be used to track
     * @param visoin::signature* The pointer to the vex signature object of the color it will track
    */
    VisionTracker(vision * sensorAddress, vision::signature * signatureAddress);
    
    /**
     * @brief Used to set if the LED on the sensor will indicate the state of the tracking
     * 
     * @param state Is the LED being used
     * @return bool Will bounce back the state passed in
     */
    bool tglLEDIndicator(bool state);  //allows you to control if the LED on the sensor is used to indicate the object
    
    /**
     * @brief Used to set if the object will be printed on the screen
     * 
     * @param state Is the object being printed on the screen
     * @return bool Will bounce back the state passed in 
     */
    bool tglScreenIndicator(bool state);  //allows you to control if the brain screen is used to indicate the object
    
    /**
     * @brief Used to set if object data will be printed in the terminal
     * 
     * @param state Is data being printed in the terminal
     * @return bool Will bounce back the state passed in 
     */
    bool tglDebugMode(bool state);  //allows you to control if data is printed to the terminal
    
    /**
     * @brief Sets how many pixels off center the object can be to be considered locked on
     * 
     * @param range The amout of pixles to the left or right the object can be
     * @return int Will bounce back the range inputed
     */
    int setLockRange(int range);  //set how far the object can be form the center to be considered "Locked on"


    /****** monocular distance setup code ******/
    /**
     * used to calculate single eye distance using downward exponential curve
     * desmos calculator link https://www.desmos.com/calculator/vflase42t0
     * format y=a^(-(x+b))+c
     *
     * @brief Sets up a, b, and c values for distance curve y=a^(-(x+b))+c
     * 
     * @param a A value in function
     * @param b B value in function
     * @param c C value in function
     */
    void setupDistanceMath(double a, double b, double c);  //set up a, b, and c values
    
    /**
     * @brief 
     * 
     * @param state Toggle if monocular distace is being calculated
     * @return bool Will bounce back the state passed in
     */
    bool tglDistanceCalculation(bool state);  //allow you to turn on and off distance calculations
    
    /**
     * @brief Returns the average distance of object over the count time
     * 
     * @return double The estimated distance to the object
     */
    double returnAverageDistance();  //returns the average distance of object over the count time
    
    /**
     * @brief Turns off distace estimation and averages the object width for use in calibrating distace
     * 
     */
    void enableCalibration();  //turns off distance estimation and averages object width instead

    /****** functional code ******/

    /**
     * @brief Takes snapshot and does all math and calculations
     * 
     */
    void trackObject();  //takes snapshot and sets object variables

    /**
     * @brief Return the object count
     * 
     * @return int How many objects are on the screen
     */
    int getObjectCount();

    /**
     * @brief Return the object width
     * 
     * @return int The amout of pixels wide the object is
     */
    int getObjectXDim();

    /**
     * @brief Return the object height
     * 
     * @return int The amount of pixels tall the object is
     */
    int getObjectYDim();

    /**
     * @brief Return the object x position
     * 
     * @return int The position of the center of the object in pixels
     */
    int getObjectXPos();

    /**
     * @brief Returns the object y position
     * 
     * @return int The position of the center of the object in pixels
     */
    int getObjectYPos();

    /**
     * @brief Returns if the object is in the center range of the sensor
     * 
     * @return true The object is in the center
     * @return false The object is not in the center
     */
    bool getLockedState();

    /**
     * @brief Returns the off direction
     * 
     * @return leftAndRight LEFT the object is to the left of the sensor
     * @return leftAndRight RIGHT the object is to the right of the sensor
     */
    leftAndRight getOffDirection();

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
    bool calibrationMode;

    /****** object data ******/
    int objectCount;
    int objectXDim;
    int objectYDim;
    int objectXPos;
    int objectYPos;

    bool isLocked;
    leftAndRight directionOff;

};

#endif //_VISION_TRACKER_