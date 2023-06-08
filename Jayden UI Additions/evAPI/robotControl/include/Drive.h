#ifndef __DRIVE_H__
#define __DRIVE_H__

#include "vex.h"
#include "../../odomSupport/include/odomMain.h"
#include "../../Common/include/evNamespace.h"
#include "../../Common/include/PID.h"

namespace evAPI
{
  #define MIN_DRIVE_SPEED 5
  #define MIN_TURN_SPEED 5
  class drive {
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
      double turnI = 0;
      double turnD = 0;

      PID drivePID = PID(0, driveP, driveI, driveD, 0);
      PID turnPID = PID(0, turnP, turnI, turnD, 0);
  
    public:
  
      /****** constructors ******/
      drive( void );    //empty constructor
      drive(gearSetting driveGear);    //sets gearbox for all motors
  
      /*********** setup ***********/
      /*----- debug -----*/
      void setDebugState(bool mode); //allows you to toggle debug mode
  
      /*----- Base Setup -----*/
      void geartrainSetup(float diameter, int gearIN, int gearOUT);  //used for setting up wheel size and gear ratio
      void setBaseType(driveBaseType type);

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
  
      /*----- Controller setup -----*/

      /**
       * @brief Configures how the controller joysticks will control the base.
       * @param type The type of base.
       * @param primaryStick Optional. Sets which joystick will be the primary one.
      */
      void setControlType(driveMode drivingMode, joystickType primaryStick = leftStick);

      void setDeadZoneRadius(uint8_t rad);

      /*----- PID setup -----*/

      /**
       * @brief Sets constant used for the driving PID Loop.
       * @param kp The KP factor.
      */
      void setDrivePID(double kp)
      { setDrivePID(kp, 0, 0); }

      /**
       * @brief Sets constants used for the driving PID Loop.
       * @param kp The KP factor.
       * @param kd The KD factor.
      */
      void setDrivePID(double kp, double kd)
      { setDrivePID(kp, 0, kd); }

      /**
       * @brief Sets constants used for the driving PID Loop.
       * @param kp The KP factor.
       * @param ki The KI factor.
       * @param kd The KD factor.
      */
      void setDrivePID(double kp, double ki, double kd);
      
      /**
       * @brief Sets constant used for the turning PID Loop.
       * @param kp The KP factor.
      */
      void setTurnPID(double kp)
      { setTurnPID(kp, 0, 0); }

      /**
       * @brief Sets constants used for the turning PID Loop.
       * @param kp The KP factor.
       * @param kd The KD factor.
      */
      void setTurnPID(double kp, double kd)
      { setTurnPID(kp, 0, kd); }

      /**
       * @brief Sets constants used for the turning PID Loop.
       * @param kp The KP factor.
       * @param ki The KI factor.
       * @param kd The KD factor.
      */
      void setTurnPID(double kp, double ki, double kd);

      /************ movement ************/
      /*----- manual movement -----*/
      void spinBase(int leftSpeed, int rightSpeed);  //spins both sides at speeds that are set in the function
      void stopRobot();  //stops robot with type coast
      void stopRobot(brakeType stoppingMode);  //stops robot with given type

      /**
       * @brief Controls the base motors based on the inputs from the controller and what drive mode is selected.
      */
      void controllerDrive();
  
      /************ Odometry Movement ************/
  
      /**
       * @brief Turns the robot to the corresponding angle.
       * @param angle The angle to turn to.
      */
      void turnToAngle(double angle)
      { turnToAngle(angle, turnSpeed); }
  
      /**
       * @brief Turns the robot to the corresponding angle.
       * @param angle The angle to turn to.
       * @param speed The maximum speed the robot should turn at.
      */
      void turnToAngle(double angle, int speed);
  
      /**
       * @brief Turns the robot to face a point.
       * @param point The point the robot should turn to to face.
      */
      void turnToPoint(int point)
      { turnToPoint(point, turnSpeed, 0); }
  
      /**
       * @brief Turns the robot to face a point.
       * @param point The point the robot should turn to to face.
       * @param speed The maximum speed the robot should turn at.
      */
      void turnToPoint(int point, int speed)
      { turnToPoint(point, speed, 0); }
      
      /**
       * @brief Turns the robot to face a point.
       * @param point The point the robot should turn to to face.
       * @param speed The maximum speed the robot should turn at.
       * @param maxTime The maximum amount of time the turn can take before the robot aborts the turn.
      */
      void turnToPoint(int point, int speed, int maxTime);
  
      /**
       * @brief Turns the robot to face a point.
       * @param x The X-Position of the point the robot should turn to to face.
       * @param y The Y-Position of the point the robot should turn to to face.
       * @param speed The maximum speed the robot should turn at.
      */
      void turnToPoint(double x, double y, int speed);
  
      /**
       * @brief Drives to the point.
       * @param point point to drive to.
      */
      void driveToPoint(int point)
      { driveToPoint(point, driveSpeed, turnSpeed, 0); }
  
      /**
       * @brief Drives to the point.
       * @param point point to drive to.
       * @param drivingSpeed The maximum speed the robot will drive at.
      */
      void driveToPoint(int point, int drivingSpeed)
      { driveToPoint(point, drivingSpeed, turnSpeed, 0); }
  
      /**
       * @brief Drives to the point.
       * @param point point to drive to.
       * @param turningSpeed The maximum speed the robot will turn at.
      */
      void driveToPoint(int point, uint turningSpeed)
      { driveToPoint(point, driveSpeed, turningSpeed, 0); }
  
      /**
       * @brief Drives to the point.
       * @param point point to drive to.
       * @param drivingSpeed The maximum speed the robot will drive at.
       * @param turningSpeed The maximum speed the robot will turn at.
      */
      void driveToPoint(int point, int drivingSpeed, int turningSpeed)
      { driveToPoint(point, drivingSpeed, turningSpeed, 0); }
  
      /**
       * @brief Drives to the point.
       * @param point point to drive to.
       * @param drivingSpeed The maximum speed the robot will drive at.
       * @param turningSpeed The maximum speed the robot will turn at.
       * @param maxTime The maximum amount of time the turn can take before the robot aborts the movement.
      */
      void driveToPoint(int point, int drivingSpeed, int turningSpeed, int maxTime);
  
      /**
       * @brief Drives the robot to a specified X and Y position at a specified speed. 
       * Turns the robot to an angle if hasAngle is set
       * @param x The X-Position to drive to.
       * @param y The Y-Position to drive to.
       * @param drivingSpeed The speed the robot drives forward with. Optional.
       * @param angle The angle the robot will turn to after it reaches its destination
       * @param turningSpeed The speed the robot turns with. Optional.
      */
      void driveToPlace(double x, double y, int drivingSpeed, double angle,
        int turningSpeed, bool hasAngle, int locationType);
  
      /**
       * @brief Drives the robot to a specified X and Y position at a specified speed. 
       * Turns the robot to an angle if hasAngle is set
       * @param x The X-Position to drive to.
       * @param y The Y-Position to drive to.
      */
      void driveToPlace(double x, double y)
      { driveToPlace(x, y, driveSpeed, 0, turnSpeed, false, odomPoint::endPoint); }
  
      /**
       * @brief Drives along a line and stops at te final point.
       * @param positionValues An array that contains all the position values for the robot to drive along.
      */
      void driveAlongLine(double positionValues[2][MAX_LINE_POINTS+3]);
  
      /*----- automatic -----*/
      void setDriveSpeed(int speed);  //sets the drive speed for when one is not entered
      void setTurnSpeed(int speed);  //sets the drive speed for when one is not entered
      void driveForward(double distance, int speed);  //enter a distance and speed to go forward
      void driveForward(double distance);  //enter a distance to go forward
      void driveBackward(double distance, int speed);  //enter a distance and speed to go backward
      void driveBackward(double distance);  //enter a distance to go backward
      void turnToHeading(int angle, int speed);  //enter an angle and speed to turn
      void turnToHeading(int angle);  //enter an angle to turn
  
      turnType findDir(int startingAngle, int endingAngle);  //finds the direction that is faster

    private:
      /************ motors ************/
      /*----- left motors -----*/
      void spinLeftMotors(int speed);  //spins all motors on the left side
      void stopLeftMotors(brakeType type);  //stop all motors on the left side
      motor * leftMotors[4];
  
      /*----- right motors -----*/
      void spinRightMotors(int speed);  //spins all motors on the right side
      void stopRightMotors(brakeType type);  //stop all motors on the right side
      motor * rightMotors[4];
  
      /****** motor and wheel settings ******/
      bool isDebugMode = false;  //is debug mode on
      int baseMotorCount;
      gearSetting currentGear;
      float wheelSize;  //stores the diameter of wheel
      float gearInput;  //stores the input value of the gear ratio
      float gearOutput;  //stores the output value of the gear ratio
      float degsPerInch;  //store the calculated degrees per inch.

      int baseType;
      int driverMode;
      int primaryControllerStick;

      double generalHandicap;
      double turnHandicap;

      uint8_t deadZoneRad = 0;
  
      /****** formulas ******/
      int turnError(turnType direction, int startAngle, int endAngle);
  };

  extern drive Drivetrain;
}

#endif // __DRIVE_H__