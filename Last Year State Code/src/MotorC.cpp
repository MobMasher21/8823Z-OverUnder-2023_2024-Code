#include "vex.h"
#include "MotorC.h"
#include "evAPI.h"

using namespace evAPI;

/****** constructors ******/
MotorC::MotorC(int port, gearSetting gear) {
  setPort = port;
  setGear = gear;
  vexMotor = new motor(smartPortLookupTable[port], gear);
}

MotorC::MotorC(int port, gearSetting gear, bool reversed) {
  setPort = port;
  setGear = gear;
  vexMotor = new motor(smartPortLookupTable[port], gear, reversed);
}


/************ motor commands ************/
/*----- motor settings commands -----*/
void MotorC::setReversed(bool reverse) {    //can be used to chang the reversed status of the motor
  reversed = reverse;
  vexMotor->setReversed(reverse);
}

void MotorC::setVelocity(int speed) {    //sets the velocity of the motor that will be used when not stated
  vexMotor->setVelocity(speed, pct);
}

void MotorC::setVelocity(int speed, percentUnits units)
{ vexMotor->setVelocity(speed, units); }

void MotorC::setVelocity(int speed, velocityUnits units)
{ vexMotor->setVelocity(speed, units); }

/*----- stopping -----*/
void MotorC::stop() {    //stops motor with preset stopping
  vexMotor->stop(stoppingType);
}

void MotorC::stop(brakeType type) {    //stops motor with argument stopping type
  vexMotor->stop(stoppingType);
}

void MotorC::setStopping(brakeType type) {    //sets stopping type of motor
  vexMotor->setStopping(type);
  stoppingType = type;
}


/*----- movement -----*/
void MotorC::spin(directionType direction) {    //spins motor with pre-set speed in argument direction
  vexMotor->spin(direction, currentSpeed, pct);
}

void MotorC::spin(directionType direction, int speed) {    //spins motor with argument speed and direction
  vexMotor->spin(direction, speed, pct);
}

void MotorC::spin(directionType direction, int voltage, voltageUnits unit) {    //allows you to spin the flywheel with volts
  vexMotor->spin(direction, voltage, unit);
}


/*----- sensing -----*/
void MotorC::resetRotation( void ) {    //sets the encoder angle to 0
  vexMotor->resetRotation();
}

void MotorC::setRotation(double value) {    //set the encoder to the angle in the argument
  vexMotor->setRotation(value, degrees);
}

double MotorC::rotation( void ) {    //gets the current rotation of motor encoder
  double r = vexMotor->rotation(degrees);
  return(r);
}

double MotorC::velocity( void ) {    //gets the current rotation speed of the motor
  double r = vexMotor->velocity(pct);
  return(r);
}

double MotorC::current( void ) {    //gets the current current being drawn by the motor
  double r = vexMotor->current();
  return(r);
}

double MotorC::voltage( void ) {    //gets the current voltage being drawn by the motor
  double r = vexMotor->voltage();
  return(r);
}

double MotorC::torque( void ) {    //gets the current torque of the motor
  double r = vexMotor->torque();
  return(r);
}

double MotorC::temperature(temperatureUnits units) {    //get the temperature of the motor in C or F
  double r = vexMotor->temperature(units);
  return(r);
}