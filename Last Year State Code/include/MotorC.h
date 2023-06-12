#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "vex.h"

class MotorC {
  public:
    /****** constructors ******/
    MotorC(int port, gearSetting gear);    //sets up motor with set port and gearbox not being reversed
    MotorC(int port, gearSetting gear, bool reversed);    //sets up motor with set port, gearbox, and reversed
  
    /************ motor commands ************/
    /*----- motor settings commands -----*/
    void setReversed(bool reverse);    //can be used to chang the reversed status of the motor
    void setVelocity(int speed);    //sets the velocity of the motor that will be used when not stated
  
    void setVelocity(int speed, percentUnits units);
    void setVelocity(int speed, velocityUnits units);
  
    /*----- stopping -----*/
    void stop();    //stops motor with preset stopping
    void stop(brakeType type);    //stops motor with argument stopping type
    void setStopping(brakeType type);    //sets stopping type of motor
  
    /*----- movement -----*/
    void spin(directionType direction);    //spins motor with pre-set speed in argument direction
    void spin(directionType direction, int speed);    //spins motor with argument speed and direction
    void spin(directionType direction, int voltage, voltageUnits unit);    //allows you to spin the flywheel with volts
  
    /*----- sensing -----*/
    void resetRotation( void );    //sets the encoder angle to 0
    void setRotation(double value);    //set the encoder to the angle in the argument
    double rotation( void );    //gets the current rotation of motor encoder
    double velocity( void );    //gets the current rotation speed of the motor
    double current( void );    //gets the current current being drawn by the motor
    double voltage( void );    //gets the current voltage being drawn by the motor
    double torque( void );    //gets the current torque of the motor
    double temperature(temperatureUnits units);    //get the temperature of the motor in C or F
  
  private:
    motor * vexMotor;    //pointer to vex motor
    int setPort;    //the port that was set to the motor
    gearSetting setGear;    //the gearbox that was set to the motor
    int currentSpeed;    //the current speed the motor is set to spin
    bool reversed;    //if the motor is set in reversed mode
    brakeType stoppingType = coast;    //current break type; default coast
};

#endif  //_MOTOR_H_