#ifndef __DRIVE_H__
#define __DRIVE_H__

#include "vex.h"

namespace evAPI
{
  class Drive {
    private:
  
    /****** drive variables ******/
      int driveSpeed = 80;
      int turnSpeed = 40;

      int minTurnSpeed = 2;
      
      double driveP = 0.2;
      double driveI = 0;
      double driveD = 0;
      double driveStop = 5;

      double turnP = 0.35;
  
    public:
  
      /****** constructors ******/
      Drive( void );    //empty constructor
      Drive(gearSetting driveGear);    //sets gearbox for all motors
  
      /*********** setup ***********/
      /*----- debug -----*/
      void setDebugState(bool mode); //allows you to toggle debug mode
  
      /*----- Base Setup -----*/
      void geartrainSetup(float diameter, int gearIN, int gearOUT);  //used for setting up wheel size and gear ratio

      /*----- Limit setup -----*/
      void setGeneralHandicap(double cap);
      void setTurningHandicap(double cap);
  
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
      void leftReverseSetup(int reverse1);    //left motor reverse setup for 2 motor drive
      void leftReverseSetup(int reverse1, int reverse2);    //left motor reverse setup for 4 motor drive
      void leftReverseSetup(int reverse1, int reverse2, int reverse3);    //left motor reverse setup for 6 motor drive
      void leftReverseSetup(int reverse1, int reverse2, int reverse3, int reverse4);    //left motor reverse setup for 8 motor drive
      void rightReverseSetup(int reverse1);    //right motor reverse setup for 2 motor drive
      void rightReverseSetup(int reverse1, int reverse2);    //right motor reverse setup for 4 motor drive
      void rightReverseSetup(int reverse1, int reverse2, int reverse3);    //right motor reverse setup for 6 motor drive
      void rightReverseSetup(int reverse1, int reverse2, int reverse3, int reverse4);    //right motor reverse setup for 8 motor drive

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
  
      bool findDir(int startingAngle, int endingAngle);  //finds the direction that is faster
  
    private:
      /************ motors ************/
      /*----- left motors -----*/
      void spinLeftMotors(int speed);  //spins all motors on the left side
      void stopLeftMotors(brakeType type);  //stop all motors on the left side
      motor * leftMotor1;  //used in 2, 4 (front), 6 (front), 8 (front) motor drive
      motor * leftMotor2;  //used in 4 (back), 6 (middle), 8 (front middle) motor drive
      motor * leftMotor3;  //used in 6 (back), 8 (back middle) motor drive
      motor * leftMotor4;  //used in 8 (back) motor drive
  
      /*----- right motors -----*/
      void spinRightMotors(int speed);  //spins all motors on the right side
      void stopRightMotors(brakeType type);  //stop all motors on the right side
      motor * rightMotor1;  //used in 2, 4 (front), 6 (front), 8 (front) motor drive
      motor * rightMotor2;  //used in 4 (back), 6 (middle), 8 (front middle) motor drive
      motor * rightMotor3;  //used in 6 (back), 8 (back middle) motor drive
      motor * rightMotor4;  //used in 8 (back) motor drive
  
      /****** motor and wheel settings ******/
      bool isDebugMode = false;  //is debug mode on
      int baseMotorCount;
      gearSetting currentGear;
      float wheelSize;  //stores the diameter of wheel
      float gearInput;  //stores the input value of the gear ratio
      float gearOutput;  //stores the output value of the gear ratio
      float degsPerInch;  //store the calculated degrees per inch.
  
      /****** drive variables ******/
      enum constDirection {
        LEFT,
        RIGHT
      };

      /****** formulas ******/
      int turnError(bool direction, int startAngle, int endAngle);
  };
}

#endif // __DRIVE_H__