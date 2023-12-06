#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI
{
  //======================================== public =============================================
  /****** constructors ******/
  Drive::Drive( void ) {
  
  }
  
  Drive::Drive(gearSetting driveGear) {
    currentGear = driveGear;
  }

  /****** debug ******/
  void Drive::setDebugState(bool mode) { //allows you to toggle debug mode
    isDebugMode = mode;
  }
  
  void Drive::printAllEncoderData() {  //prints all 3 encoder values to the terminal
    printf("%f, ", getLeftPosition(degrees));
    printf("%f, ", getRightPosition(degrees));
    printf("%f\n", getBackPosition(degrees));
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

  /*----- automatic -----*/
    void Drive::setDriveSpeed(int speed) {  //sets the drive speed for when one is not entered
      driveSpeed = speed;
    }

    void Drive::setTurnSpeed(int speed) {  //sets the drive speed for when one is not entered
      turnSpeed = speed;
    }

    void Drive::driveForward(double distance, int speed) {  //enter a distance and speed to go forward
      //*setup of all variables*
      double leftPosition;  //angle of left encoder
      double rightPosition;  //angle of right encoder
      double averagePosition;  //average position of both encoders
      int error;  // desired value - sensor value
      int desiredValue;  // angle of rotation sensor that we want
      bool isPIDRunning = true;  // is true as the PID is running
      int moveSpeed;  // the speed the motors are set to every cycle
      drivePID.setTotalError(0);

      //*checks to see if you have encoders and then sets the desired angle of the pid*
      if(leftEncoder) {
        desiredValue = distance * leftEncoderDegsPerInch;
      } else {
        desiredValue = distance * degsPerInch;
      }

      //*resets encoders*
      resetLeftPosition();
      resetRightPosition();

      //*print debug header*
      if(isDebugMode) printf("error, moveSpeed");

      //*main PID loop*
      while(isPIDRunning) {
        //*get encoder positions*
        leftPosition = getLeftPosition(degrees);
        rightPosition = getRightPosition(degrees);
        averagePosition = (leftPosition + rightPosition) / 2; 

        //*calculate error for this cycle*
        error =  desiredValue - averagePosition;

        //*adding all tunning values*
        moveSpeed = drivePID.compute(error);

        //*speed cap
        if(moveSpeed > speed) moveSpeed = speed;
        if(moveSpeed < -speed) moveSpeed = -speed;

        //*setting motor speeds*
        spinBase(moveSpeed, moveSpeed);

        //*stopping code*
        if(drivePID.isSettled()) {isPIDRunning = false;}

        //*print debug data*
        if(isDebugMode) {
          printf("%i, ", error);
          printf("%i\n", moveSpeed);
        }

        //*wait to avoid overloading*
        vex::task::sleep(20);
      }
      stopRobot(brake);

    }

    void Drive::driveForward(double distance) {  //enter a distance to go forward
      driveForward(distance, driveSpeed);
    }

    void Drive::driveBackward(double distance, int speed) {  //enter a distance and speed to go backward
      driveForward(-distance, speed);
    }

    void Drive::driveBackward(double distance) {  //enter a distance to go backward
      driveForward(-distance, driveSpeed);
    }

    void Drive::turnToHeading(int angle, int speed) {  //enter an angle and speed to turn
      //*setup of all variables*
      leftAndRight turnDirection;
      int currentHeading;
      int error;  // desired value - sensor value
      int desiredValue;  // angle of rotation sensor that we want
      bool isPIDRunning = true;  // is true as the PID is running
      int moveSpeed;  // the speed the motors are set to every cycle
      turnPID.setTotalError(0);

      //*checks to see if you have an inertial and then sets the desired angle of the pid*
      if(turnSensor) {
        desiredValue = angle;
        turnDirection = findDir(turnSensor->heading(deg), desiredValue);
      } else {
        return;
      }

      //*print debug header*
      if(isDebugMode) printf("error, moveSpeed");

      //*main PID loop*
      while(isPIDRunning) {
        //*get heading*
        currentHeading = turnSensor->heading(deg);

        //*calculate error for this cycle*
        error =  turnError(turnDirection, currentHeading, desiredValue);

        //*adding all tunning values*
        moveSpeed = turnPID.compute(error);

        //*speed cap
        if(moveSpeed > speed) moveSpeed = speed;
        if(moveSpeed < -speed) moveSpeed = -speed;

        //*setting motor speeds*
        if(turnDirection == LEFT) {
          spinBase(-moveSpeed, moveSpeed);
        } else if(turnDirection == RIGHT) {
          spinBase(moveSpeed, -moveSpeed);
        }

        //*stopping code*
        if(turnPID.isSettled()) {isPIDRunning = false;}

        //*print debug data*
        if(isDebugMode) {
          printf("%i, ", error);
          printf("%i\n", moveSpeed);
        }

        //*wait to avoid overloading*
        vex::task::sleep(20);
      }

      stopRobot(brake);
    }

    void Drive::turnToHeading(int angle) {  //enter an angle to turn
      turnToHeading(angle, turnSpeed);
    }

  
  //======================================== private =============================================
  /****** formulas ******/
  leftAndRight Drive::findDir(int startingAngle, int endingAngle) {
    leftAndRight output;
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
  
  int Drive::turnError(leftAndRight direction, int startAngle, int endAngle) {
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