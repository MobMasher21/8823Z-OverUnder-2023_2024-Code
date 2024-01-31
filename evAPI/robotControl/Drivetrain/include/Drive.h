#ifndef __DRIVE_H__
#define __DRIVE_H__

#include "../../../Common/include/generalFunctions.h"
#include "../../../Common/include/PID.h"
#include "../../OdoTracking/include/OdoMath.h"
#include "SmartEncoder.h"

/**
 * ! Remember to keep code well documented
 * * Item order is only and idea
 * * Some things can be done simultaneously
 * //TODO: write setup code for pid constants
 * //TODO: write pid for driving
 * //TODO: write pid for turning
 * //TODO: write setup code of inertial sensor
 * TODO: write drift contorl for driving
 * TODO: write automatic controller Configuration for driver control
 * TODO: write odometry position tracking
 * TODO: write drive to point for odometry
 * TODO: write path finding for odometry
 * TODO: integrate vision tracking
 * TODO: Add functions to get the current state of the drive base, like its velocity
 * 
*/

#define DRIVE_TRACKER 0
#define ODO_TRACKER 1

namespace evAPI {
  class Drive {
    public:
  
      /****** constructors ******/
      Drive( void );    //empty constructor
      Drive(gearSetting driveGear);    //sets gearbox for all motors
  
      /****** debug ******/
      void setDebugState(bool mode); //allows you to toggle debug mode
      void printAllEncoderData();  //prints all 3 encoder values to the terminal

      /*********** setup ***********/
      /*----- Base Setup -----*/
      void geartrainSetup(float diameter, int gearIN, int gearOUT);  //used for setting up wheel size and gear ratio
     
     /**
      * @brief Sets the stopping mode for the base.
      * @param mode The stopping mode.
     */
      void setStoppingMode(brakeType mode);

      /*----- motor ports and reverses -----*/
      void setGearbox(gearSetting driveGear);    //sets gearbox for all motors
      void leftPortSetup(int port1);    //left motor port setup for 2 motor drive
      void leftPortSetup(int port1, int port2);    //left motor port setup for 4 motor drive
      void leftPortSetup(int port1, int port2, int port3);    //left motor port setup for 6 motor drive
      void leftPortSetup(int port1, int port2, int port3, int port4);    //left motor port setup for 8 motor drive
      void rightPortSetup(int port1);    //right motor port setup for 2 motor drive
      void rightPortSetup(int port1, int port2);    //right motor port setup for 4 motor drive
      void rightPortSetup(int port1, int port2, int port3);    //right motor port setup for 6 motor drive
      void rightPortSetup(int port1, int port2, int port3, int port4);    //right motor port setup for 8 motor drive
      void leftReverseSetup(bool reverse1);    //left motor reverse setup for 2 motor drive
      void leftReverseSetup(bool reverse1, bool reverse2);    //left motor reverse setup for 4 motor drive
      void leftReverseSetup(bool reverse1, bool reverse2, bool reverse3);    //left motor reverse setup for 6 motor drive
      void leftReverseSetup(bool reverse1, bool reverse2, bool reverse3, bool reverse4);    //left motor reverse setup for 8 motor drive
      void rightReverseSetup(bool reverse1);    //right motor reverse setup for 2 motor drive
      void rightReverseSetup(bool reverse1, bool reverse2);    //right motor reverse setup for 4 motor drive
      void rightReverseSetup(bool reverse1, bool reverse2, bool reverse3);    //right motor reverse setup for 6 motor drive
      void rightReverseSetup(bool reverse1, bool reverse2, bool reverse3, bool reverse4);    //right motor reverse setup for 8 motor drive

      /*----- encoder setup -----*/
      void leftEncoderSetup(int port, double wheelSize, bool reverse);  //setup values for left encoder
      void rightEncoderSetup(int port, double wheelSize, bool reverse);  //setup values for right encoder
      void backEncoderSetup(int port, double wheelSize, bool reverse);  //setup values for back encoder
      void leftFullReset();  //resets all position data about left encoder
      void rightFullReset();  //resets all position data about right encoder

      /*----- pid setup -----*/
      void setupDrivePID(double kp, double ki, double kd, int maxStopError, int timeToStop, int timeoutTime);
      void setupTurnPID(double kp, double ki, double kd, int maxStopError, int timeToStop, int timeoutTime);
      void setupDriftPID(double kp, double ki, double kd, int maxStopError, int timeToStop, int timeoutTime);

      /*----- inertial setup -----*/
      void setupInertialSensor(int port);  //sets the port of the inertial sensor
      void calibrateInertial();  //calibrate the inertial sensor
      bool isInertialCalibrating();  //is the inertial sensor calibrating
      void setDriveHeading(int angle);  //sets the current heading of the inertial sensor
      
      /************ movement ************/
      /*----- manual movement -----*/
      void spinBase(int leftSpeed, int rightSpeed);  //spins both sides at speeds that are set in the function
      void stopRobot();  //stops robot with type coast
      void stopRobot(brakeType stoppingMode);  //stops robot with given type
  
      /*----- automatic -----*/
      void setDriveSpeed(int speed);  //sets the drive speed for when one is not entered
      void setTurnSpeed(int speed);  //sets the drive speed for when one is not entered
      void driveForward(double distance, int speed);  //enter a distance and speed to go forward
      void driveForward(double distance);  //enter a distance to go forward
      void driveBackward(double distance, int speed);  //enter a distance and speed to go backward
      void driveBackward(double distance);  //enter a distance to go backward
      void turnToHeading(int angle, int speed);  //enter an angle and speed to turn
      void turnToHeading(int angle);  //enter an angle to turn

      /*----- odo tracking -----*/
      void odoThreadCall();  // command only called by odo thread loop
      void startOdoThread();  // starts the odo thread
  
      /************ Sensors ************/
      /*----- movement -----*/
      /**
       * @returns True if the base motors are moving.
      */
      bool isMoving();

      /**
       * @brief Gets the wheel speed of teh specified side.
       * @param side The side to get the wheel speed from.
       * @returns The speed of the wheel.
       * @warning Doesn't fully function yet.
      */
      double getBaseSpeed(turnType side);
  
    private:
      /************ motors ************/
      /*----- left motors -----*/
      void spinLeftMotors(int speed);  //spins all motors on the left side
      void stopLeftMotors(brakeType type);  //stop all motors on the left side
      motor * leftMotor1 = nullptr;  //used in 2, 4 (front), 6 (front), 8 (front) motor drive
      motor * leftMotor2 = nullptr;  //used in 4 (back), 6 (middle), 8 (front middle) motor drive
      motor * leftMotor3 = nullptr;  //used in 6 (back), 8 (back middle) motor drive
      motor * leftMotor4 = nullptr;  //used in 8 (back) motor drive
  
      /*----- right motors -----*/
      void spinRightMotors(int speed);  //spins all motors on the right side
      void stopRightMotors(brakeType type);  //stop all motors on the right side
      motor * rightMotor1 = nullptr;  //used in 2, 4 (front), 6 (front), 8 (front) motor drive
      motor * rightMotor2 = nullptr;  //used in 4 (back), 6 (middle), 8 (front middle) motor drive
      motor * rightMotor3 = nullptr;  //used in 6 (back), 8 (back middle) motor drive
      motor * rightMotor4 = nullptr;  //used in 8 (back) motor drive

      /****** encoders ******/
      double getBackPosition(rotationUnits units);  //get the position of the back side on motor or rotation sensor
      void resetBackPosition();  //resets position of back encoder to 0

      rotation * leftEncoder;  //pointer to left encoder object
      rotation * rightEncoder;  //pointer to right encoder object
      rotation * backEncoder;  //pointer to back encoder object
      SmartEncoder * leftTracker;  //multi tracker for left side
      SmartEncoder * rightTracker;  //multi tracker for right Side
      
      int leftDriveTracker;  //ID for left drive tracker
      int leftOdoTracker;  //ID for left odo tracker
      int rightDriveTracker;  //ID for left drive tracker
      int rightOdoTracker;  //ID for left odo tracker

      double leftEncoderDegsPerInch;  //degrees per inch of wheel on left encoder
      double rightEncoderDegsPerInch;  //degrees per inch of wheel on right encoder
      double backEncoderDegsPerInch;  //degrees per inch of wheel on back encoder

      /****** inertial sensor ******/
      inertial * turnSensor;  //pointer to the inertial sensor 
  
      /****** motor and wheel settings ******/
      bool isDebugMode = false;  //is debug mode on
      int baseMotorCount;
      gearSetting currentGear;
      float wheelSize;  //stores the diameter of wheel
      float gearInput;  //stores the input value of the gear ratio
      float gearOutput;  //stores the output value of the gear ratio
      float degsPerInch;  //store the calculated degrees per inch.

      /****** odo stuff ******/
      thread * odoThread;  // thread used for odo tracking
      OdoMath odoTracker;  // object that runs odo math
  
      /****** drive variables ******/
      PID turnPID;
      PID drivePID;
      PID driftPID;
      int driveSpeed;
      int turnSpeed;

      double driveP;
      double driveI;
      double driveD;
      int driveMaxStopError;  //max amount of degrees to be considered "there"
      int driveTimeToStop;  //how many pid cycles of being "there" till it stops

      double turnP;
      double turnI;
      double turnD;
      int turnMaxStopError;  //max amount of degrees to be considered "there"
      int turnTimeToStop;  //how many pid cycles of being "there" till it stops

      double driftP;
      double driftI;
      double driftD;
      int driftMaxStopError;  //max amount of degrees to be considered "there"
      int driftTimeToStop;  //how many pid cycles of being "there" till it stops

      /****** formulas ******/
      leftAndRight findDir(int startingAngle, int endingAngle);  //finds the direction that is faster
      int turnError(leftAndRight direction, int startAngle, int endAngle);  //finds the error of a turn
  };
}

#endif // __DRIVE_H__