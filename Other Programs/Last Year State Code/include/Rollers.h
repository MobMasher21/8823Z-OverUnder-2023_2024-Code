#ifndef __ROLLERS_H__
#define __ROLLERS_H__

#include "vex.h"
#include "MotorC.h"

#define FIRST_ROLLER_SPEED 100
#define SECOND_ROLLER_SPEED 100

#define ROLLER_ROLLER_SPEED 40

#define ROLLER_AUTO_SPEED 35

#define BRIGHTNESS_THRESHOLD 70
#define DISTANCE_THRESHOLD 50

#define DISK_SENSING_LIMIT 5

#define RED_HUE_MIN 10
#define RED_HUE_MAX 20

#define BLUE_HUE_MIN 225
#define BLUE_HUE_MAX 245

class Rollers {
  public:
    /****** setup ******/
    void setDebugState(bool mode); //allows you to toggle debug mode
    void setupIntakeMotor(int port, bool reversed, gearSetting gear);  //sets up port settings for lower roller
    void setupRollerMotor(int port, bool reversed, gearSetting gear);  //sets up port settings for upper roller
    void setupOutputSensor(int port);  //sets up output distance sensor
    void setupInputSensor(int port);  //sets up input optical sensor
    void setFirstStageStopping(brakeType type);  //sets the brake type of first stage motor
    void setRollerStopping(brakeType type);  //sets the brake type of the second stage motor

    void setupRollerSensors(int topPort, int bottomPort);

    /****** direct movement contorl ******/
    void spinIntake(int speed);  //spins first stage motor at set speed
    void spinIntake(int voltage, voltageUnits units); //spins first stage motor at set voltage
    void stopIntake();  //stops first stage motor with preset mode
    void stopIntake(brakeType type);  //stops first stage motor with entered mode

    /****** automatic functions ******/
    int setDiskCount(int input);  //manually sets the disk count
    int getDiskCount();  //returns the current disk count
    bool getDrain();  //sees if the rollers are set to drain the disks
    bool toggleAutomatic();  //toggles weather or not the rollers are running in automatic mode
    bool getAutomatic();  //returns if automatic mode is on
    void automaticLoop();  //command that needs to be ran in a loop to keep automatic rollers running
    void diskCheckLoop();  //call this command in a loop to keep the disk checker going
    void diskFire();  //shoots a disk
    bool toggleDrain();  //reverses rollers to drain the disks
    void spinRoller(int speed);  //spins second stage motor at set speed
    void stopRoller();  //stops second stage motor with preset mode
    void stopRoller(brakeType type);  //stops second stage motor with entered mode

    /**
     * @brief A function that automaticaly cycles the roller to match the current alliance of the robot.
     * Put this function in its own thread with a delay and while loop.
    */
    void rollerCheckLoop();

    /**
     * @returns True if the roller-roller is near a roller.
    */
    bool isNearRoller();

    /**
     * @returns True if the roller-roller is rolling a roller. 
     * False if the roller-roller is not rolling a roller.
    */
    bool isChangingRoller();

    /**
     * @brief Enables or disables the roller assist.
    */
    void rollerAssistStatus(bool enabled);

  private:
    /****** motor pointers ******/
    MotorC * intakeMotor;
    MotorC * rollerMotor;
    distance * outputSensor;
    optical * inputSensor;
    optical * topRollerSensor;
    optical * bottomRollerSensor;

    /****** variables ******/
    bool isDebugMode = false;  //is debug mode on
    bool isAutomatic;
    bool drainDisks;
    int diskCount = 0;
    bool inputBounce;
    bool outputBounce; 
    bool rollingRoller;
    bool rollerAssistEnabled = true;
    bool finishedRolling = true;

};

#endif // __ROLLERS_H__