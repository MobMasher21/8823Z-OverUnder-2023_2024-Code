/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robotMonitoring.cpp                                       */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      21 Oct 2022                                               */
/*    Description:  Code for logging robot info to the controller screen      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Robot.h"
#include "robotMonitoring.h"
#include "evAPI.h"

int8_t preDiskCount = 10;
int8_t prevBatPercent = 0;
int8_t CompMode = 6;
int8_t prevCompMode = 5;
double prevCompTime = -5;

using namespace evAPI;

int robotMonitoring()
{
  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(1, 1);

  secondaryController.Screen.clearScreen();
  secondaryController.Screen.setCursor(1, 1);

  primaryController.Screen.print("Calibrating...");
  while(Odometry.Inertial.isCalibrating())
  { this_thread::sleep_for(10); }

  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(1, 1);
  this_thread::sleep_for(30); //! Don't remove this. It makes it work for some reason
  primaryController.Screen.print("Disks: %d", robot.rollers.getDiskCount());
  this_thread::sleep_for(100);

  while(true) {

    //! PRIMARY CONTROLLER

    if(preDiskCount != robot.rollers.getDiskCount())  //Prints disk count on screen
    {
      primaryController.Screen.setCursor(1, 1);
      primaryController.Screen.clearLine(1);
      primaryController.Screen.print("Disks: %d", robot.rollers.getDiskCount());
    }
  
    if(Brain.Battery.capacity(percent) != prevBatPercent) //Prints battery percentage to screen
    {
      primaryController.Screen.setCursor(2, 1);
      primaryController.Screen.clearLine(2);
      primaryController.Screen.print("Battery: %d   ", Brain.Battery.capacity(percent));
    }

    //Get the current state of the competition
    if (robotInfo.Competition.isDriverControl() && robotInfo.Competition.isEnabled()) 
    { CompMode = driverControl; }

    else if(robotInfo.Competition.isAutonomous() && robotInfo.Competition.isEnabled())
    { CompMode = autonomousControl; }

    else if(!robotInfo.Competition.isEnabled()) 
    { CompMode = disabled; }

    else
    { CompMode = -1; }

    if(CompMode != prevCompMode) //Prints competition mode to screen
    {
      primaryController.Screen.setCursor(3, 1);
      primaryController.Screen.clearLine(3);

      switch (CompMode)
      {
        case disabled:
          primaryController.Screen.print("Disabled");
          break;
        
        case autonomousControl:
          primaryController.Screen.print("Auton");
          break;

        case driverControl:
          primaryController.Screen.print("Driver");
          break;

        default:
          primaryController.Screen.print("Unknown");
          break;
      }
    }

    //! SECONDARY CONTROLLER

    if(robotInfo.getCompetitionTime() != prevCompTime) //Print the match time on the second controller
    {
      int Min = 0;
      int Sec = floor(robotInfo.getCompetitionTime());

      while(robotInfo.getCompetitionTime() >= 60)
      {
        Sec -= 60;
        Min++;
      }

      secondaryController.Screen.setCursor(1, 1);
      secondaryController.Screen.clearLine(1);

      if(Sec >= 10) //Makes sure the time shows us as M:SS (1:05), and not M:S (1:5)
      { secondaryController.Screen.print("Time: %d:%d", Min, Sec); }

      else
      { secondaryController.Screen.print("Time: %d:0%d", Min, Sec); }      
    }

    preDiskCount = robot.rollers.getDiskCount();
    prevBatPercent = Brain.Battery.capacity(percent);
    prevCompMode = CompMode;
    prevCompTime = robotInfo.getCompetitionTime();

    this_thread::sleep_for(50);
  }

  return 0;
}