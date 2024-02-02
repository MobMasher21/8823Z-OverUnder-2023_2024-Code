#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI {
  Drive* threadReference;

  //======================================== public =============================================
  /****** constructors ******/
  Drive::Drive( void ) {
    threadReference = this;
  }
  
  Drive::Drive(gearSetting driveGear) {
    currentGear = driveGear;
    threadReference = this;
  }

  /****** debug ******/
  void Drive::setDebugState(bool mode) { //allows you to toggle debug mode
    isDebugMode = mode;
  }
  
  void Drive::printAllEncoderData() {  //prints all 3 encoder values to the terminal
    printf("drive action (l, r): %f, %f\n", leftTracker->readTrackerPosition(leftDriveTracker), rightTracker->readTrackerPosition(rightDriveTracker));
    printf("odo action (l, r): %f, %f\n", leftTracker->readTrackerPosition(leftOdoTracker), rightTracker->readTrackerPosition(rightOdoTracker));
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

    void Drive::setDriveBaseWidth(int width) {  //sets the distance between the two wheels for arc turns
      driveBaseWidth = width;
    }

    void Drive::driveForward(double distance, int speed) {  //enter a distance and speed to go forward
      //*setup of all variables*
      double leftPosition;  //angle of left encoder
      double rightPosition;  //angle of right encoder
      int averagePosition;  //average position of both encoders
      int error;  // desired value - sensor value
      int driftError;  // difference between left - right
      int desiredValue;  // angle of rotation sensor that we want
      bool isPIDRunning = true;  // is true as the PID is running
      int moveSpeed;  // the speed the motors are set to every cycle
      int driftPower;  // output of the drift PID
      drivePID.setTotalError(0);
      driftPID.setTotalError(0);
      drivePID.resetTimeout();

      //*checks to see if you have encoders and then sets the desired angle of the pid*
      if(leftEncoder) {
        desiredValue = distance * leftEncoderDegsPerInch;
      } else {
        desiredValue = distance * degsPerInch;
      }
      if(isDebugMode) printf("desiredValue: %i\n", desiredValue);

      //*resets encoders*
      leftTracker->resetTrackerPosition(leftDriveTracker);
      rightTracker->resetTrackerPosition(rightDriveTracker);
      if(isDebugMode) printf("rightAngle: %f\n", leftTracker->readTrackerPosition(leftDriveTracker));
      if(isDebugMode) printf("leftAngle: %f\n", rightTracker->readTrackerPosition(rightDriveTracker));

      //*print debug header*
      if(isDebugMode) printf("position, error, moveSpeed\n");

      //*main PID loop*
      while(isPIDRunning) {
        //*get encoder positions*
        leftPosition = leftTracker->readTrackerPosition(leftDriveTracker);
        rightPosition = rightTracker->readTrackerPosition(rightDriveTracker);
        averagePosition = (leftPosition + rightPosition) / 2; 
        driftError = leftPosition - rightPosition;

        //*calculate error for this cycle*
        error =  desiredValue - averagePosition;

        //*adding all tunning values*
        moveSpeed = drivePID.compute(error);
        driftPower = driftPID.compute(driftError);

        //*speed cap
        if(moveSpeed > speed) moveSpeed = speed;
        if(moveSpeed < -speed) moveSpeed = -speed;

        //*setting motor speeds*
        spinBase(moveSpeed - driftPower, moveSpeed + driftPower);

        //*stopping code*
        if(drivePID.isSettled()) {isPIDRunning = false;}

        //*print debug data*
        if(isDebugMode) {
          printf("%i, ", averagePosition);
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
      turnPID.resetTimeout();

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

    void Drive::arcTurn(double radius, leftAndRight direction, int angle, int speed) {  // turns in an arc
      //*setup of all variables*
      double leftPosition;  //angle of left encoder
      double rightPosition;  //angle of right encoder
      int error;  // desired value - sensor value
      int driftError;  // difference between left - right
      int desiredValue;  // angle of rotation sensor that we want
      int outerDistance;  // length of the outer arc of the turn
      int innerDistance;  // length of the inner arc of the turn
      double wheelPowerRatio;  // ratio of length between outer and inner wheel
      bool isPIDRunning = true;  // is true as the PID is running
      int moveSpeed;  // the speed the motors are set to every cycle
      int driftPower;  // output of the drift PID
      arcPID.setTotalError(0);
      arcDriftPID.setTotalError(0);
      arcPID.resetTimeout();

      outerDistance = ((radius + (driveBaseWidth / 2)) * 2) * M_PI;
      innerDistance = ((radius - (driveBaseWidth / 2)) * 2) * M_PI;
      wheelPowerRatio = innerDistance / outerDistance;
      
      if(direction == LEFT) {
        
      } else if(direction == RIGHT) {

      }

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
        } else {
          turnError = 180;
        }
      } else if(((startAngle + 360) - endAngle) < 180) {
        turnError = (startAngle + 360) - endAngle;
      } else {
        turnError = 180;
      }
      
    } else if(direction == RIGHT) {
    
      //===============================RIGHT
      if(((endAngle + 360) - startAngle) > 180) {
        if(endAngle - startAngle < 180) {
          turnError = endAngle - startAngle;
        } else if(endAngle - startAngle > 180) {
          turnError = (endAngle - startAngle) - 360;
        } else {
          turnError = 180;
        }
      } else if(((endAngle + 360) - startAngle) < 180) {
        turnError = (endAngle + 360) - startAngle;
      } else {
        turnError = 180;
      }
      //===============================
    }
  
    return(turnError);
  }
}