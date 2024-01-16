#include "../include/Drive.h"

namespace evAPI {
  //======================================== public =============================================
  /*********** setup ***********/
  /*----- Base Setup -----*/
  void Drive::geartrainSetup(float diameter, int gearIN, int gearOUT) { //used for setting up the wheel size and gear
    wheelSize = diameter;                                           //ratios for using auto commands
    gearInput = gearIN;
    gearOutput = gearOUT;
    degsPerInch = ((360 / (wheelSize * M_PI)) * (gearOutput / gearInput));   
    // ^^ finds the amount of encoder degrees in one inch of movement
    if(isDebugMode) printf("dpi: %f\n", degsPerInch);
  }

  void Drive::setStoppingMode(brakeType mode)
  {
    //Left motors
    if(leftMotor1 != nullptr)
    {
      leftMotor1->setStopping(mode);
    }

    if(leftMotor2 != nullptr)
    {
      leftMotor2->setStopping(mode);
    }

    if(leftMotor3 != nullptr)
    {
      leftMotor3->setStopping(mode);
    }

    if(leftMotor4 != nullptr)
    {
      leftMotor4->setStopping(mode);
    }

    //Right motors
    if(rightMotor1 != nullptr)
    {
      rightMotor1->setStopping(mode);
    }

    if(rightMotor2 != nullptr)
    {
      rightMotor2->setStopping(mode);
    }

    if(rightMotor3 != nullptr)
    {
      rightMotor3->setStopping(mode);
    }

    if(rightMotor4 != nullptr)
    {
      rightMotor4->setStopping(mode);
    }
  }
  
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
  
  void Drive::leftReverseSetup(bool reverse1) {    //left motor reverse setup for 2 motor drive
    leftMotor1->setReversed(reverse1);
  }
  
  void Drive::leftReverseSetup(bool reverse1, bool reverse2) {    //left motor reverse setup for 4 motor drive
    leftMotor1->setReversed(reverse1);
    leftMotor2->setReversed(reverse2);
  }
  
  void Drive::leftReverseSetup(bool reverse1, bool reverse2, bool reverse3) {    //left motor reverse setup for 6 motor drive
    leftMotor1->setReversed(reverse1);
    leftMotor2->setReversed(reverse2);
    leftMotor3->setReversed(reverse3);
  }
  
  void Drive::leftReverseSetup(bool reverse1, bool reverse2, bool reverse3, bool reverse4) {    //left motor reverse setup for 8 motor drive
    leftMotor1->setReversed(reverse1);
    leftMotor2->setReversed(reverse2);
    leftMotor3->setReversed(reverse3);
    leftMotor4->setReversed(reverse4);
  }
  
  void Drive::rightReverseSetup(bool reverse1) {    //right motor reverse setup for 2 motor drive
    rightMotor1->setReversed(reverse1);
  }
  
  void Drive::rightReverseSetup(bool reverse1, bool reverse2) {    //right motor reverse setup for 4 motor drive
    rightMotor1->setReversed(reverse1);
    rightMotor2->setReversed(reverse2);
  }
  
  void Drive::rightReverseSetup(bool reverse1, bool reverse2, bool reverse3) {    //right motor reverse setup for 6 motor drive
    rightMotor1->setReversed(reverse1);
    rightMotor2->setReversed(reverse2);
    rightMotor3->setReversed(reverse3);
  }
  
  void Drive::rightReverseSetup(bool reverse1, bool reverse2, bool reverse3, bool reverse4) {    //right motor reverse setup for 8 motor drive
    rightMotor1->setReversed(reverse1);
    rightMotor2->setReversed(reverse2);
    rightMotor3->setReversed(reverse3);
    rightMotor4->setReversed(reverse4);
  }

  /*----- encoder setup -----*/
  void Drive::leftEncoderSetup(int port, double wheelSize, bool reverse) {    //setup values for left encoder
    leftEncoder = new rotation(smartPortLookupTable[port], reverse);
    leftEncoderDegsPerInch = (360 / (wheelSize * M_PI));
  }

  void Drive::rightEncoderSetup(int port, double wheelSize, bool reverse) {    //setup values for right encoder
    rightEncoder = new rotation(smartPortLookupTable[port], reverse);
    rightEncoderDegsPerInch = (360 / (wheelSize * M_PI));
  }

  void Drive::backEncoderSetup(int port, double wheelSize, bool reverse) {    //setup values for back encoder
    backEncoder = new rotation(smartPortLookupTable[port], reverse);
    backEncoderDegsPerInch = (360 / (wheelSize * M_PI));
  }

  /*----- pid setup -----*/
  void Drive::setupDrivePID(double kp, double ki, double kd, int maxStopError, int timeToStop, int timeoutTime) {
    drivePID.setConstants(kp, ki, kd);
    drivePID.setStoppings(maxStopError, timeToStop, timeoutTime);
    driveP = kp;
    driveI = ki;
    driveD = kd;
    driveMaxStopError = maxStopError;
    driveTimeToStop = timeToStop;    
  }

  void Drive::setupTurnPID(double kp, double ki, double kd, int maxStopError, int timeToStop, int timeoutTime) {
    turnPID.setConstants(kp, ki, kd);
    turnPID.setStoppings(maxStopError, timeToStop, timeoutTime);
    turnP = kp;
    turnI = ki;
    turnD = kd;
    turnMaxStopError = maxStopError;
    turnTimeToStop = timeToStop;    
  }

  void Drive::setupDriftPID(double kp, double ki, double kd, int maxStopError, int timeToStop, int timeoutTime) {
    driftPID.setConstants(kp, ki, kd);
    driftPID.setStoppings(maxStopError, timeToStop, timeoutTime);
    driftP = kp;
    driftI = ki;
    driftD = kd;
    driftMaxStopError = maxStopError;
    driftTimeToStop = timeToStop;    
  }

  /*----- inertial setup -----*/
  void Drive::setupInertialSensor(int port) {  //sets the port of the inertial sensor
    turnSensor = new inertial(smartPortLookupTable[port]);
  }

  void Drive::calibrateInertial() {  //calibrate the inertial sensor
    turnSensor->calibrate();
  }

  bool Drive::isInertialCalibrating() {  //is the inertial sensor calibrating
    return(turnSensor->isCalibrating());
  }

  void Drive::setDriveHeading(int angle) {  //sets the current heading of the inertial sensor
    turnSensor->setHeading(angle, deg);
  }


}