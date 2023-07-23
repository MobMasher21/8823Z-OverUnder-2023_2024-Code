#include "Rollers.h"
#include "evAPI.h"
#include "Robot.h"

using namespace evAPI;

void Rollers::setDebugState(bool mode) { //allows you to toggle debug mode
  isDebugMode = mode;
}

void Rollers::setupIntakeMotor(int port, bool reversed, gearSetting gear) {    //sets up port settings for lower roller
  intakeMotor = new MotorC(port, gear, reversed);
  if(isDebugMode) {
    printf("Intake Motor\n");
  }
}

void Rollers::setupRollerMotor(int port, bool reversed, gearSetting gear) {  //sets up port settings for upper roller
  rollerMotor = new MotorC(port, gear, reversed);
  if(isDebugMode) {
    printf("Roller Motor\n");
  }
}

void Rollers::setupOutputSensor(int port) {  //sets up output distance sensor
  outputSensor = new distance(smartPortLookupTable[port]);
  if(isDebugMode) {
    printf("output sensor\n");
  }
}

void Rollers::setupInputSensor(int port) {  //sets up input optical sensor
  inputSensor = new optical(smartPortLookupTable[port]);
  if(isDebugMode) {
    printf("input sensor\n");
  }
}

void Rollers::setFirstStageStopping(brakeType type) {  //sets the brake type of first stage motor
  intakeMotor->setStopping(type);
}

void Rollers::setRollerStopping(brakeType type) {  //sets the brake type of the second stage motor
  rollerMotor->setStopping(type);
}

void Rollers::spinIntake(int speed) {  //spins first stage motor at set speed
  intakeMotor->spin(fwd, speed);
}

void Rollers::spinIntake(int voltage, voltageUnits units) {  //spins first stage motor at set voltage
  intakeMotor->spin(fwd, voltage, units);
}

void Rollers::spinRoller(int speed) {  //spins second stage motor at set speed
  rollerMotor->spin(fwd, speed);
}

void Rollers::stopIntake() {  //stops first stage motor with preset mode
  intakeMotor->stop();
}

void Rollers::stopIntake(brakeType type) {  //stops first stage motor with entered mode
  intakeMotor->stop(type);
}

void Rollers::stopRoller() {  //stops second stage motor with preset mode
  rollerMotor->stop();
}

void Rollers::stopRoller(brakeType type) {  //stops second stage motor with entered mode
  rollerMotor->stop(type);
}

bool Rollers::toggleAutomatic() {  //toggles weather or not the rollers are running in automatic mode
  isAutomatic = !isAutomatic;
  return isAutomatic;
}

bool Rollers::getAutomatic() {  //returns if automatic mode is on
  return isAutomatic;
}

int Rollers::setDiskCount(int input) {  //manually sets the disk count
  diskCount = input;
  return diskCount;
}

int Rollers::getDiskCount() {  //returns the current disk count
  return diskCount;
}

bool Rollers::getDrain() {  //sees if the rollers are set to drain the disks
  return drainDisks;
}

void Rollers::automaticLoop() {
  if(isAutomatic) {  //if automatic mode is on
    if(drainDisks || trigger.value()) {
        //spinFirstStage(-FIRST_ROLLER_SPEED);
        spinIntake(12, voltageUnits::volt);
      
    } else {
      if(diskCount >= 3) {  //controls first stage motor
        stopIntake();

      } else if(diskCount < 3) {
          //spinFirstStage(FIRST_ROLLER_SPEED);
          spinIntake(-12, voltageUnits::volt);

      }
    }
  } else {  //if automatic mode is off

  }
}

void Rollers::diskCheckLoop() {  //call this command in a loop to keep the disk checker going
  if(absf(intakeMotor->velocity()) > 0) {  //toggle optical sensor LED
    inputSensor->setLightPower(100);
  } else {
    inputSensor->setLightPower(0);
  }

  if(inputSensor->brightness() > BRIGHTNESS_THRESHOLD) {  //check if there is a new disk in the system
    if(inputBounce == 0) {

      if(drainDisks)  //Increments or decrements the disk counter depending on the state of the intake
      { diskCount--; }

      else
      { diskCount++; }
     
      inputBounce = 1;
    }
  } else {
    inputBounce = 0;
  }

  if(outputSensor->objectDistance(mm) < DISTANCE_THRESHOLD) {  //check if a disk leaves the system
    if(outputBounce == 0) {
      outputBounce = 1;
    }
  } else {
    if(outputBounce == 1) {
      diskCount --;
    }
    outputBounce = 0;
  }

  if(diskCount < 0) {  //stops disk count from going negative
    diskCount = 0;
  }

  if(isDebugMode) {
    printf("dc = %i, ", diskCount);
    printf("od = %f, ", outputSensor->objectDistance(mm));
    printf("ib = %f, \n", inputSensor->brightness());
  }

}

void Rollers::diskFire()
{
  trigger.set(true);
  task::sleep(700);
  trigger.set(false);
  task::sleep(500);
}

bool Rollers::toggleDrain() {  //reverses rollers to drain the disks
  drainDisks = !drainDisks;
  return drainDisks;
}

void Rollers::setupRollerSensors(int topPort, int bottomPort)
{
  topRollerSensor = new optical(smartPortLookupTable[topPort]);
  topRollerSensor->setLightPower(100);

  bottomRollerSensor = new optical(smartPortLookupTable[bottomPort]);
  bottomRollerSensor->setLightPower(100);
}

void Rollers::rollerCheckLoop()
{
  //Checks if a roller is close and button x isn't pressed
  if(isNearRoller() && !primaryController.ButtonX.pressing() && robotInfo.Competition.isEnabled() 
    && rollerAssistEnabled) 
  {
    topRollerSensor->setLight(ledState::on);
    bottomRollerSensor->setLight(ledState::on);

    if(robotInfo.getAlliance() == redAlliance) //Checks the alliance of the robot
    {
      if((topRollerSensor->hue() > RED_HUE_MIN) && (topRollerSensor->hue() < RED_HUE_MAX) &&
        (bottomRollerSensor->hue() > BLUE_HUE_MIN) && (bottomRollerSensor->hue() < BLUE_HUE_MAX)) //Rolls roller
      {
        rollerMotor->stop();
        finishedRolling = true;

        if(isDebugMode)
        { printf("Finished Rolling\n"); }
      }

      else if(!finishedRolling) //Stops rolling roller
      { rollerMotor->spin(fwd, ROLLER_AUTO_SPEED); }
      
      printf("Red Alliance\n");
    }

    else if(robotInfo.getAlliance() == blueAlliance) //Checks the alliance of the robot
    {
      if((topRollerSensor->hue() > BLUE_HUE_MIN && topRollerSensor->hue() < BLUE_HUE_MAX) &&
        (bottomRollerSensor->hue() > RED_HUE_MIN && bottomRollerSensor->hue() < RED_HUE_MAX)) //Rolls roller
      {
        rollerMotor->stop();
        finishedRolling = true;

        if(isDebugMode)
        { printf("Finished Rolling\n"); }
      }

      else if(!finishedRolling)//Stops rolling roller
      { rollerMotor->spin(fwd, ROLLER_AUTO_SPEED); }

      printf("Blue Alliance\n");
    }

    if(isDebugMode)
    {
      printf("Top Sensor Hue: %f\n", topRollerSensor->hue());
      printf("Bottom Sensor Hue: %f\n", bottomRollerSensor->hue());
      printf("Rolling:%d\n\n", rollingRoller);
    }

    else {} //Do nothing if there isn't an alliance
  }

  else //No roller detected
  {
    topRollerSensor->setLight(ledState::off);
    bottomRollerSensor->setLight(ledState::off);
    finishedRolling = false;

    if(!primaryController.ButtonX.pressing() && rollerAssistEnabled)
    { rollerMotor->stop(); }
  }

  if(rollerMotor->velocity() >= 2)
  { rollingRoller = true; }

  else
  { rollingRoller = false; }
}

bool Rollers::isNearRoller()
{ return (topRollerSensor->isNearObject() || bottomRollerSensor->isNearObject()
   /* || rollerDistance.objectDistance(mm) <= 33 */);
}

bool Rollers::isChangingRoller()
{ return rollingRoller; }

void Rollers::rollerAssistStatus(bool enabled)
{ rollerAssistEnabled = enabled; }