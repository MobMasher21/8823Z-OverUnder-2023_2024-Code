#include "../../robotControl/include/Drive.h"
#include "../../Common/include/arduinoDef.h"
#include "../../Common/include/robotStatus.h"
#include "../../Common/include/evNamespace.h"
#include "../../robotControl/include/Controllers.h"

namespace evAPI
{
  #define MIN_DRIVE_SPEED 5
  #define MIN_TURN_SPEED 5
  
  //======================================== public =============================================
  /****** constructors ******/
  Drive::Drive( void ) {
  
  }
  
  Drive::Drive(gearSetting driveGear) {
    currentGear = driveGear;
  }
  
  /*********** setup ***********/
  /*----- debug -----*/
  void Drive::setDebugState(bool mode) { //allows you to toggle debug mode
    isDebugMode = mode;
  }
  
  /*----- Base Setup -----*/
  void Drive::geartrainSetup(float diameter, int gearIN, int gearOUT) { //used for setting up the wheel size and gear
    wheelSize = diameter;                                           //ratios for using auto commands
    gearInput = gearIN;
    gearOutput = gearOUT;
    degsPerInch = ((360 / (wheelSize * M_PI)) * (gearOutput / gearInput));   
    // ^^ finds the amount of encoder degrees in one inch of movement
  }

  void Drive::setBaseType(driveBaseType type)
  { baseType = type; }
  
  /*----- motor ports and reverses -----*/
  void Drive::setGearbox(gearSetting driveGear) {    //sets gearbox for all motors
    currentGear = driveGear;
  }
  
  void Drive::leftPortSetup(int port1) {    //left motor port setup for 2 motor drive
    leftMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    baseMotorCount = 2;
  }
  
  void Drive::leftPortSetup(int port1, int port2) {    //left motor port setup for 4 motor drive
    leftMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    leftMotor2 = new motor(smartPortLookupTable[port2], currentGear);
    baseMotorCount = 4;
  }
  
  void Drive::leftPortSetup(int port1, int port2, int port3) {    //left motor port setup for 6 motor drive
    leftMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    leftMotor2 = new motor(smartPortLookupTable[port2], currentGear);
    leftMotor3 = new motor(smartPortLookupTable[port3], currentGear);
    baseMotorCount = 6;
  }
  
  void Drive::leftPortSetup(int port1, int port2, int port3, int port4) {    //left motor port setup for 8 motor drive
    leftMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    leftMotor2 = new motor(smartPortLookupTable[port2], currentGear);
    leftMotor3 = new motor(smartPortLookupTable[port3], currentGear);
    leftMotor4 = new motor(smartPortLookupTable[port4], currentGear);
    baseMotorCount = 8;
  }
  
  void Drive::rightPortSetup(int port1) {    //right motor port setup for 2 motor drive
    rightMotor1 = new motor(smartPortLookupTable[port1], currentGear);
  }
  
  void Drive::rightPortSetup(int port1, int port2) {    //right motor port setup for 4 motor drive
    rightMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    rightMotor2 = new motor(smartPortLookupTable[port2], currentGear);
  }
  
  void Drive::rightPortSetup(int port1, int port2, int port3) {    //right motor port setup for 6 motor drive
    rightMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    rightMotor2 = new motor(smartPortLookupTable[port2], currentGear);
    rightMotor3 = new motor(smartPortLookupTable[port3], currentGear);
  }
  
  void Drive::rightPortSetup(int port1, int port2, int port3, int port4) {    //right motor port setup for 8 motor drive
    rightMotor1 = new motor(smartPortLookupTable[port1], currentGear);
    rightMotor2 = new motor(smartPortLookupTable[port2], currentGear);
    rightMotor3 = new motor(smartPortLookupTable[port3], currentGear);
    rightMotor4 = new motor(smartPortLookupTable[port4], currentGear);
  }
  
  void Drive::leftReverseSetup(int reverse1) {    //left motor reverse setup for 2 motor drive
    leftMotor1->setReversed(reverse1);
  }
  
  void Drive::leftReverseSetup(int reverse1, int reverse2) {    //left motor reverse setup for 4 motor drive
    leftMotor1->setReversed(reverse1);
    leftMotor2->setReversed(reverse2);
  }
  
  void Drive::leftReverseSetup(int reverse1, int reverse2, int reverse3) {    //left motor reverse setup for 6 motor drive
    leftMotor1->setReversed(reverse1);
    leftMotor2->setReversed(reverse2);
    leftMotor3->setReversed(reverse3);
  }
  
  void Drive::leftReverseSetup(int reverse1, int reverse2, int reverse3, int reverse4) {    //left motor reverse setup for 8 motor drive
    leftMotor1->setReversed(reverse1);
    leftMotor2->setReversed(reverse2);
    leftMotor3->setReversed(reverse3);
    leftMotor4->setReversed(reverse4);
  }
  
  void Drive::rightReverseSetup(int reverse1) {    //right motor reverse setup for 2 motor drive
    rightMotor1->setReversed(reverse1);
  }
  
  void Drive::rightReverseSetup(int reverse1, int reverse2) {    //right motor reverse setup for 4 motor drive
    rightMotor1->setReversed(reverse1);
    rightMotor2->setReversed(reverse2);
  }
  
  void Drive::rightReverseSetup(int reverse1, int reverse2, int reverse3) {    //right motor reverse setup for 6 motor drive
    rightMotor1->setReversed(reverse1);
    rightMotor2->setReversed(reverse2);
    rightMotor3->setReversed(reverse3);
  }
  
  void Drive::rightReverseSetup(int reverse1, int reverse2, int reverse3, int reverse4) {    //right motor reverse setup for 8 motor drive
    rightMotor1->setReversed(reverse1);
    rightMotor2->setReversed(reverse2);
    rightMotor3->setReversed(reverse3);
    rightMotor4->setReversed(reverse4);
  }

  /*----- Controller setup -----*/

  void Drive::setControlType(driveMode drivingMode, joystickType primaryStick)
  {
    driverMode = drivingMode;
    primaryControllerStick = primaryStick;
  }
  
  /************ movement ************/  
  /*----- manual movement -----*/
  void Drive::spinBase(int leftSpeed, int rightSpeed) {
    spinLeftMotors(leftSpeed);
    spinRightMotors(rightSpeed); 
  }
  
  void Drive::stopRobot() {  //stops robot with type coast
    stopLeftMotors(coast);
    stopRightMotors(coast);
  }
  
  void Drive::stopRobot(brakeType stoppingMode) {  //stops robot with given type
    stopLeftMotors(stoppingMode);
    stopRightMotors(stoppingMode);
  }

  void Drive::controllerDrive()
  {
    switch(driverMode)
    {
      case Custom:
        break;

      case Arcade:
        switch(baseType)
        {
          case HDriveStandard:

            double leftSpeed;
            double rightSpeed;

            switch(primaryControllerStick)
            {
              case leftStick:
                leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;
                break;

              case rightStick:
                leftSpeed = (primaryController.Axis2.position(pct) + primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis2.position(pct) - primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;

                break;

            }
            spinBase(leftSpeed, rightSpeed);
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }

        break;

      case Tank:
        switch(baseType)
        {
          case HDriveStandard:
            switch(primaryControllerStick)
            {
              case leftStick:

                break;

              case rightStick:

                break;
            }
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }
        break;

      case ServoSteering:
        switch(baseType)
        {
          case HDriveStandard:
            switch(primaryControllerStick)
            {
              case leftStick:

                break;

              case rightStick:

                break;
            }
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }

        break;

      case RCControl:

        switch(baseType)
        {
          case HDriveStandard:
            double leftSpeed;
            double rightSpeed;

            switch(primaryControllerStick)
            {
              case leftStick:
                leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;
                break;

              case rightStick:
                leftSpeed = (primaryController.Axis2.position(pct) + primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis2.position(pct) - primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;

                break;

            }
            spinBase(leftSpeed, rightSpeed);
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:

                break;

              case rightStick:

                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }
        break;
    }
  }

  /*----- Limit setup -----*/

  void Drive::setGeneralHandicap(double cap)
  { generalHandicap = cap; }

  void Drive::setTurningHandicap(double cap)
  { turnHandicap = cap; }
  
  /*----- automatic -----*/
  void Drive::setDriveSpeed(int speed) {  //sets the drive speed for when one is not entered
    driveSpeed = speed;
  }
  
  void Drive::setTurnSpeed(int speed) {  //sets the drive speed for when one is not entered
    turnSpeed = speed;
  }
  
  void Drive::driveForward(double distance, int speed) {  //enter a distance and speed to go forward
    if(isDebugMode) {
      printf("error, ");
      printf("error dif, ");
      printf("total error, ");
      printf("speed Controller, ");
      printf("leftPOS, ");
      printf("rightPOS\n");
    }
  
    //setup vars =====================================================
    int difference;
    int wantedAngle = distance * degsPerInch;
  
    leftMotor1->resetRotation();
    rightMotor1->resetRotation();
  
    double kP = driveP;
    double kI = driveI;
    double kD = driveD;
    double error;
    double preError;
    long totalError = 0;
    double speedControl;
    double realSpeed = speed;
    uint8_t zeroCount = 0;
  
    error = wantedAngle - ((leftMotor1->rotation(degrees) + rightMotor1->rotation(degrees)) / 2);
    spinLeftMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
    spinRightMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
  
    //print start command in terminal ================================
    if(isDebugMode) {
      printf("wantedAngle = %i\n", wantedAngle);
    }
  
    //main loop ======================================================
    while(1) {
      //pid ==========================================================
      preError = error;
      error = wantedAngle - ((leftMotor1->rotation(degrees) + rightMotor1->rotation(degrees)) / 2);
      totalError = totalError + error;
  
      speedControl = (error * kP) + ((error - preError) * kD) + (totalError * kI);
      if(speedControl > 100) {
        speedControl = 100;
      }
  
      //drift control ===============================================
      realSpeed = speed * (speedControl / 100);
      difference = leftMotor1->rotation(degrees) - rightMotor1->rotation(degrees);
      if(difference > 0) {
        spinLeftMotors(constrain((realSpeed /* - .5 * (difference * 0.50) */), MIN_DRIVE_SPEED, 100));
        spinRightMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
      }
      if(difference < 0) {
        spinLeftMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
        spinRightMotors(constrain((realSpeed /* - .5 * -(difference * 0.50) */), MIN_DRIVE_SPEED, 100));
      }
  
      //stop code ====================================================
      if((error) <= driveStop) {
        zeroCount ++;
      }
      if(zeroCount > 5) {
        break;
      }
  
      //debug print ==================================================
      if(isDebugMode) {
        printf("%f, ", error);
        printf("%f, ", error - preError);
        printf("%li, ", totalError);
        printf("%f, ", speedControl);
        printf("%d, ", zeroCount);
        printf("%f, ", leftMotor1->rotation(degrees));
        printf("%f\n", rightMotor1->rotation(degrees));
      }
  
      //wait =========================================================
      vex::task::sleep(15);
    }
  
    if(isDebugMode)
    { printf("Stopped Drive forward\n"); }
  
    stopLeftMotors(brake);
    stopRightMotors(brake);
  }
  
  void Drive::driveForward(double distance) {
    driveForward(distance, driveSpeed);
  }
  
  void Drive::driveBackward(double distance, int speed) {  //enter a distance and speed to go backward
    if(isDebugMode) {
      //printf("");
      printf("error, ");
      printf("error dif, ");
      printf("total error, ");
      printf("speed Controller, ");
      printf("leftPOS, ");
      printf("rightPOS\n");
    }
  
    //setup vars =====================================================
    int difference;
    int wantedAngle = -distance * degsPerInch;
  
    leftMotor1->resetRotation();
    rightMotor1->resetRotation();
  
    double kP = driveP;
    double kI = driveI;
    double kD = driveD;
    double error;
    double preError;
    long totalError = 0;
    double speedControl;
    double realSpeed = speed;
    uint8_t zeroCount = 0;
  
    error = wantedAngle - ((leftMotor1->rotation(degrees) + rightMotor1->rotation(degrees)) / 2);
    spinLeftMotors(-realSpeed);
    spinRightMotors(-realSpeed);
  
    //print start command in terminal ================================
    if(isDebugMode) {
      printf("wantedAngle = %i\n", wantedAngle);
    }
  
    //main loop ======================================================
    while(1) {
      //pid ==========================================================
      totalError = totalError + error;
      preError = error;
      error = wantedAngle - ((leftMotor1->rotation(degrees) + rightMotor1->rotation(degrees)) / 2);
  
      speedControl = (error * kP) + ((error - preError) * kD) + (totalError * kI);
      if(speedControl > 100) {
        speedControl = 100;
      }
  
      //drift control ===============================================
      realSpeed = speed * (speedControl / 100);
      if(realSpeed >= 0) realSpeed = constrain(realSpeed, MIN_DRIVE_SPEED, 100);
      else realSpeed = -constrain(absf(realSpeed), MIN_DRIVE_SPEED, 100);
  
      difference = leftMotor1->rotation(degrees) - rightMotor1->rotation(degrees);
      if(difference > 0) {
        spinLeftMotors(realSpeed - .5 * difference);
        spinRightMotors(realSpeed);
      }
      if(difference < 0) {
        spinLeftMotors(realSpeed);
        spinRightMotors(realSpeed - .5 * -difference);
      }
  
      //stop code ====================================================
      if(absf(error) <= 20) { //TODO: COME UP WITH A BETTER FIX!
        zeroCount ++;
        break;
      }
      if(zeroCount > 5) {
        break;
      }
  
      //debug print ==================================================
      if(isDebugMode) {
        printf("%f, ", error);
        printf("%f, ", error - preError);
        printf("%li, ", totalError);
        printf("%f, ", speedControl);
        printf("%d, ", zeroCount);
        printf("%f, ", leftMotor1->rotation(degrees));
        printf("%f\n", rightMotor1->rotation(degrees));
      }
  
      //wait =========================================================
      vex::task::sleep(15);
    }
  
    stopLeftMotors(brake);
    stopRightMotors(brake);
  }
  
  void Drive::driveBackward(double distance) {
    driveBackward(distance, driveSpeed);
  }
  
  void Drive::turnToHeading(int angle, int speed) {  //enter an angle and speed to turn
    bool direction = findDir(Odometry.Inertial.heading(), angle);
    double error;
    double turningSpeed;

    if(direction == LEFT) {
      spinLeftMotors(-speed);
      spinRightMotors(speed);
      while(1) {
        error = turnError(direction, Odometry.Inertial.heading(), angle) * turnP;

        turningSpeed = error;

        if(absf(turningSpeed) > speed)
        { 
          if(turningSpeed > 0)
          {
            turningSpeed = speed;
          } else {
            turningSpeed = -speed;
          }
        }

        else if(turningSpeed < minTurnSpeed)
        { turningSpeed = minTurnSpeed; }

        spinLeftMotors(-turningSpeed);
        spinRightMotors(turningSpeed);
  
        if(isDebugMode) 
        {
          printf("Heading: %f\n", Odometry.Inertial.heading());
          printf("error: %f\n", error);
          printf("tuningSpeed: %f\n", turningSpeed);
          printf("\n");
        }
  
        if(error <= 0) {
          break;
        }
      }
    } else if(direction == RIGHT) {
      spinLeftMotors(speed);
      spinRightMotors(-speed);
      while(1) {
        error = turnError(direction, Odometry.Inertial.heading(), angle) * turnP;

        turningSpeed = error;

        if(absf(turningSpeed) > speed)
        { 
          if(turningSpeed > 0)
          {
            turningSpeed = speed;
          } else {
            turningSpeed = -speed;
          }
        }

        else if(turningSpeed < minTurnSpeed)
        { turningSpeed = minTurnSpeed; }

        spinLeftMotors(turningSpeed);
        spinRightMotors(-turningSpeed);
  
        if(isDebugMode) 
        {
          printf("Heading: %f\n", Odometry.Inertial.heading());
          printf("error: %f\n", error);
          printf("tuningSpeed: %f\n", turningSpeed);
          printf("\n");
        }
  
        if(error <= 0) {
          break;
        }
      }
    }
    stopRobot();
  }
  
  void Drive::turnToHeading(int angle) {  //enter an angle to turn
    turnToHeading(angle, turnSpeed);
  }
  
  void Drive::turnToAngle(double angle, int speed)
  {
    double error;
    #define kP 0.8
  
    while(1)
    {
      error = Odometry.Points.angleToTargetAngle(angle);
  
      if(isDebugMode) 
      {
        printf("Angle: %f, ", angle);
        printf("error: %f, ", error);
        printf("Robot Angle: %f\n", Odometry.Core.angle());
      }
  
      if(Odometry.Points.angleToTargetAngle(angle) >= 0) //Needs to turn right
      {
        spinLeftMotors(constrain((error * kP), MIN_TURN_SPEED, speed));
        spinRightMotors(-constrain((error * kP), MIN_TURN_SPEED, speed));
      }
  
      else //Needs to turn left
      {
        spinLeftMotors(-constrain((error * kP), MIN_TURN_SPEED, speed));
        spinRightMotors(constrain((error * kP), MIN_TURN_SPEED, speed));
      }
  
  
      if(absf(error) <= 0.5) 
      { break; }
  
      vex::task::sleep(10);
    }
  
    stopRobot(brake);
  }
  #undef kP
  
  void Drive::turnToPoint(int point, int speed, int maxTime)
  {
    double error;
    bool hasTime = false;
    #define kP 0.8
  
    if(maxTime != 0)
    {
      Odometry.Timer.resetTimer();
      hasTime = true;
    }
  
    while(1)
    {
      error = Odometry.Points.angleToPoint(point);
  
      if(Odometry.Points.angleToPoint(point) >= 0) //Needs to turn right
      {
        spinLeftMotors(constrain((error * kP), MIN_TURN_SPEED, speed));
        spinRightMotors(-constrain((error * kP), MIN_TURN_SPEED, speed));
      }
  
      else //Needs to turn left
      {
        spinLeftMotors(-constrain((error * kP), MIN_TURN_SPEED, speed));
        spinRightMotors(constrain((error * kP), MIN_TURN_SPEED, speed));
      }
  
      if(isDebugMode) printf("error: %f\n", error);
        
      if(absf(error) <= 0.5)  
      { break; }
  
      if(hasTime && Odometry.Timer.getCurrentTime())
      { break; }
  
      vex::task::sleep(10);
    }
  
    stopRobot(brake);
  }
  #undef kP
  
  void Drive::turnToPoint(double x, double y, int speed)
  {
    double error;
    #define kP 0.8
  
    error = Odometry.Points.angleToPoint(x, y);
  
    if(isDebugMode) printf("Starting Error: %f\n", error);
  
    while(1)
    {
      error = Odometry.Points.angleToPoint(x, y);
  
      if(Odometry.Points.angleToPoint(x, y) > 0) //Needs to turn right
      {
        spinLeftMotors(constrain((error * kP), MIN_TURN_SPEED, speed));
        spinRightMotors(-constrain((error * kP), MIN_TURN_SPEED, speed));
      }
  
      else //Needs to turn left
      {
        spinLeftMotors(-constrain((error * kP), MIN_TURN_SPEED, speed));
        spinRightMotors(constrain((error * kP), MIN_TURN_SPEED, speed));
      }
  
      if(isDebugMode) printf("error: %f\n", error);
        
      if(absf(error) <= 0.2)
      { break; }
  
      vex::task::sleep(10);
    }
  
    stopRobot(brake);
  }
  #undef kP
  
  void Drive::driveToPoint(int point, int drivingSpeed, int turningSpeed, int maxTime)
  {
    turnToPoint(point, turningSpeed);
    bool hasTime = false;
  
    if(maxTime != 0)
    {
      Odometry.Timer.resetTimer();
      hasTime = true;
    }
  
    if(isDebugMode) {
      printf("error, ");
      printf("error dif, ");
      printf("total error, ");
      printf("speed Controller, ");
      printf("leftPOS, ");
      printf("rightPOS\n");
    }
  
    //setup vars =====================================================
    double difference;
    //int wantedDistance = Odometry.distanceToPoint(point);
  
    double error;
    double preError;
    long totalError = 0;
    double speedControl;
    int realSpeed = drivingSpeed;
    int zeroCount = 0;
  
    //double leftWheelStart = Odometry.encoderAngle(odometry::leftEncoder);
    //double rightWheelStart = Odometry.encoderAngle(odometry::rightEncoder);
  
    #define kP 2
    #define kI .00003
    #define kD .1
  
    error = Odometry.Points.distanceToPoint(point);
    spinLeftMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
    spinRightMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
  
    //print start command in terminal ================================
    if(isDebugMode) {
      printf("error = %f\n", error);
    }
  
    //main loop ======================================================
    while(1) {
      //pid ==========================================================
      preError = error;
      //wantedDistance = Odometry.distanceToPoint(point);
      error = Odometry.Points.distanceToPoint(point);
      totalError = totalError + error;
  
      //Controls how the robot will drive based on the point type.
      if(Odometry.Points.returnPointType(point) == odomPoint::guidePoint) //Guide point.
      { realSpeed = drivingSpeed; }
  
      else //Other types of points.
      {
        speedControl = (error * kP)/*  + ((error - preError) * kD) + (totalError * kI )*/;
        if(speedControl > 100) {
          speedControl = 100;
        }
  
        realSpeed = drivingSpeed * (speedControl / 100); //drivingSpeed was driveSpeed
      }
  
      //drift control ===============================================
      /* difference = (Odometry.encoderAngle(odometry::leftEncoder) - leftWheelStart)
        - (Odometry.encoderAngle(odometry::rightEncoder) - rightWheelStart); */
  
      difference = Odometry.Points.angleToPoint(point);
  
      if(isDebugMode) printf("Difference: %f\n", difference);
  
      if(difference < 0) {
        spinLeftMotors(constrain((realSpeed), MIN_DRIVE_SPEED, 100) - (difference * 0.5));
        spinRightMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
      }
      if(difference < 0) {
        spinLeftMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
        spinRightMotors(constrain((realSpeed), MIN_DRIVE_SPEED, 100) - (difference * 0.5));
      }
  
      //stop code ====================================================
      if((error) <= 5) {
        zeroCount ++;
      }
      if(zeroCount > 5) {
        break;
      }
  
      if(hasTime && Odometry.Timer.getCurrentTime() > maxTime)
      { break; }
  
      //debug print ==================================================
      if(isDebugMode) {
        printf("%f, ", error);
        printf("%f, ", error - preError);
        printf("%li, ", totalError);
        printf("%f, ", speedControl);
        printf("%d, ", zeroCount);
        printf("%f, ", leftMotor1->rotation(degrees));
        printf("%f\n", rightMotor1->rotation(degrees));
      }
  
      //wait =========================================================
      vex::task::sleep(15);
    }
  
    if(isDebugMode)
    { printf("Stopped Odom Drive forward\n"); }
  
    stopRobot(brake);
  
    if(Odometry.Points.pointHasAngle(point)) //Turns to the angle of the point if one is present
    { turnToAngle(Odometry.Points.returnPointAngle(point)); }
  }
  #undef kP
  #undef kI
  #undef kD
  
  void Drive::driveToPlace(double x, double y, int drivingSpeed, double angle, int turningSpeed, 
    bool hasAngle, int locationType)
  {
    turnToPoint(x, y, turningSpeed);
    //bool hasTime = false;
  
    //setup vars =====================================================
    double difference = 0;
    //double startDistance = Odometry.distanceToPoint(x, y);
    //double startingAngle = Odometry.angleToPoint(x, y);
  
    double error;
    double preError;
    long totalError = 0;
    double speedControl;
    int realSpeed = drivingSpeed;
    //int zeroCount = 0;
  
    //double leftWheelStart = Odometry.encoderAngle(odometry::leftEncoder);
    //double rightWheelStart = Odometry.encoderAngle(odometry::rightEncoder);
  
    #define kP 6
    #define kI .00003
    #define kD .1
  
    error = Odometry.Points.distanceToPoint(x, y);
    spinLeftMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
    spinRightMotors(constrain(realSpeed, MIN_DRIVE_SPEED, 100));
  
    //print start command in terminal ================================
    if(isDebugMode) {
      printf("error = %f\n", error);
    }
  
    //main loop ======================================================
    while(1) {
      //pid ==========================================================
      preError = error;
      error = Odometry.Points.distanceToPoint(x, y);
      totalError = totalError + error;
  
      //Controls how the robot will drive based on the point type.
      if(locationType == odomPoint::guidePoint) //Guide point.
      { realSpeed = drivingSpeed; }
  
      else //Other types of points.
      {
        speedControl = (error * kP)/*  + ((error - preError) * kD) + (totalError * kI) */;
        if(speedControl > 100) {
          speedControl = 100;
        }
  
        realSpeed = drivingSpeed * (speedControl / 100); //? DrivingSpeed was driveSpeed
      }
  
      //drift control ===============================================
      /* difference = (Odometry.encoderAngle(odometry::leftEncoder) - leftWheelStart)
        - (Odometry.encoderAngle(odometry::rightEncoder) - rightWheelStart); */
  
      difference = Odometry.Points.angleToPoint(x, y) * (error * 0.1); //TODO: FIX DRIFT CONTROL
  
      if((difference <= 2) || (error <= 5)) difference = 0;
  
      if(isDebugMode)
      {
        printf("Difference: %f\n", difference);
  
        if(Odometry.Points.angleToTargetAngle(Odometry.Points.angleToPoint(x, y)) < 0)
        { printf("Direction To turn: LEFT: %f\n", Odometry.Points.angleToPoint(x, y)); }
  
        else
        { printf("Direction To turn: RIGHT: %f\n", Odometry.Points.angleToPoint(x, y)); }
      }
  
      if(Odometry.Points.angleToTargetAngle(Odometry.Points.angleToPoint(x, y)) < 0) {
        spinLeftMotors(constrain((realSpeed), MIN_DRIVE_SPEED, drivingSpeed) - (difference * 0.5));
        spinRightMotors(constrain(realSpeed, MIN_DRIVE_SPEED, drivingSpeed));
      }
      else {
        spinLeftMotors(constrain(realSpeed, MIN_DRIVE_SPEED, drivingSpeed));
        spinRightMotors(constrain((realSpeed), MIN_DRIVE_SPEED, drivingSpeed) - (difference * 0.5));
      }
  
      //stop code ====================================================
      if((error) <= 2.8) {
        break;
        //zeroCount ++;
      }
      /* if(zeroCount > 5) {
        break;
      } */
  
      //debug print ==================================================
      if(isDebugMode) {
        printf("%f, ", error);
        printf("%f, ", error - preError);
        printf("%li, ", totalError);
        printf("%f, ", speedControl);
        //printf("%d, ", zeroCount);
        printf("%f, ", leftMotor1->rotation(degrees));
        printf("%f\n", rightMotor1->rotation(degrees));
      }
  
      //wait =========================================================
      vex::task::sleep(15);
    }
  
    if(isDebugMode)
    { printf("Stopped Odom Drive To Point\n"); }
  
    stopRobot(brake);
  
    if(hasAngle) //Turns to the angle of the point if one is present
    { turnToAngle(angle); }
  }
  #undef kP
  #undef kI
  #undef kD
  
  /*
    Array Format:
  
    double arrayNameHere[2][lengthOfArray] = {
      {Number of points, Turning Angle, Turn when Complete, Point X Values...}
      {Driving Speed,    Turning Speed, Unused,             Point Y Values...}
    };
  */
  
  void Drive::driveAlongLine(double positionValues[2][MAX_LINE_POINTS+3])
  {
    int currentPoint = 3;
    
    int pathLength = positionValues[0][0]; //Store path metadata values
    int drivingSpeed = positionValues[1][0];
    int turningSpeed = positionValues[1][1];
    double finalTurningAngle = positionValues[0][1];
    bool hasFinalTurningAngle = positionValues[0][2];
    //double pointDiameter = positionValues[1][2];
  
    for (int i = 0; i < pathLength-1; i++)
    {
      driveToPlace(positionValues[0][currentPoint], positionValues[1][currentPoint], drivingSpeed, 0, 
        turningSpeed, false, odomPoint::guidePoint);
      currentPoint++;
    }
  
    driveToPlace(positionValues[0][currentPoint], positionValues[1][currentPoint], drivingSpeed,
        finalTurningAngle, turningSpeed, hasFinalTurningAngle, odomPoint::endPoint);
    
  }
  
  
  //======================================== private =============================================
  /************ motors ************/
  /*----- left motors -----*/
  void Drive::spinLeftMotors(int speed) {  //spins all motors on the left side
    switch(baseMotorCount){
      case 2:
        leftMotor1->spin(fwd, speed, percent);
        break;
      case 4:
        leftMotor1->spin(fwd, speed, percent);
        leftMotor2->spin(fwd, speed, percent);
        break;
      case 6:
        leftMotor1->spin(fwd, speed, percent);
        leftMotor2->spin(fwd, speed, percent);
        leftMotor3->spin(fwd, speed, percent);
        break;
      case 8:
        leftMotor1->spin(fwd, speed, percent);
        leftMotor2->spin(fwd, speed, percent);
        leftMotor3->spin(fwd, speed, percent);
        leftMotor4->spin(fwd, speed, percent);
        break;
    }
  }
  
  void Drive::stopLeftMotors(brakeType type) {  //stop all motors on the left side
    switch(baseMotorCount){
      case 2:
        leftMotor1->stop(type);
        break;
      case 4:
        leftMotor1->stop(type);
        leftMotor2->stop(type);
        break;
      case 6:
        leftMotor1->stop(type);
        leftMotor2->stop(type);
        leftMotor3->stop(type);
        break;
      case 8:
        leftMotor1->stop(type);
        leftMotor2->stop(type);
        leftMotor3->stop(type);
        leftMotor4->stop(type);
        break;
    }
  }
  
  /*----- right motors -----*/
  void Drive::spinRightMotors(int speed) {  //spins all motors on the right side
    switch(baseMotorCount){
      case 2:
        rightMotor1->spin(fwd, speed, percent);
        break;
      case 4:
        rightMotor1->spin(fwd, speed, percent);
        rightMotor2->spin(fwd, speed, percent);
        break;
      case 6:
        rightMotor1->spin(fwd, speed, percent);
        rightMotor2->spin(fwd, speed, percent);
        rightMotor3->spin(fwd, speed, percent);
        break;
      case 8:
        rightMotor1->spin(fwd, speed, percent);
        rightMotor2->spin(fwd, speed, percent);
        rightMotor3->spin(fwd, speed, percent);
        rightMotor4->spin(fwd, speed, percent);
        break;
    }
  }
  
  void Drive::stopRightMotors(brakeType type) {  //stop all motors on the right side
    switch(baseMotorCount){
      case 2:
        rightMotor1->stop(type);
        break;
      case 4:
        rightMotor1->stop(type);
        rightMotor2->stop(type);
        break;
      case 6:
        rightMotor1->stop(type);
        rightMotor2->stop(type);
        rightMotor3->stop(type);
        break;
      case 8:
        rightMotor1->stop(type);
        rightMotor2->stop(type);
        rightMotor3->stop(type);
        rightMotor4->stop(type);
        break;
    }
  }
  
  /****** formulas ******/
  bool Drive::findDir(int startingAngle, int endingAngle) {
    bool output;
    int leftDegs;
    int rightDegs;
    int x;  //starting angle + 360
    //left turn
    x = startingAngle + 360;
    if(x - endingAngle > 360) {
      x = startingAngle;
    }
    leftDegs = x - endingAngle;
    //right turn
    x = endingAngle + 360;
    if(x - startingAngle > 360) {
      x = endingAngle;
    }
    rightDegs = x - startingAngle;
    //return lines
    if(leftDegs > rightDegs) {
      output = RIGHT;
    } else {
      output = LEFT;
    }
    return(output);
  }
  
  int Drive::turnError(bool direction, int startAngle, int endAngle) {
    int turnError = 0;
    if(direction == LEFT) {
    
      //===============================LEFT
      if(((startAngle + 360) - endAngle) > 180) {
        if(startAngle - endAngle < 180) {
          turnError = startAngle - endAngle;
        } else if(startAngle - endAngle > 180) {
          turnError = (startAngle - endAngle) - 360;
        }
      } else if(((startAngle + 360) - endAngle) < 180) {
        turnError = (startAngle + 360) - endAngle;
      }  
    } else if(direction == RIGHT) {
    
      //===============================RIGHT
      if(((endAngle + 360) - startAngle) > 180) {
        if(endAngle - startAngle < 180) {
          turnError = endAngle - startAngle;
        } else if(endAngle - startAngle > 180) {
          turnError = (endAngle - startAngle) - 360;
        }
      } else if(((endAngle + 360) - startAngle) < 180) {
        turnError = (endAngle + 360) - startAngle;
      }
      //===============================
    }
  
    return(turnError);
  }
}