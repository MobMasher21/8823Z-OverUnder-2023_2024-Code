/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomCore.cpp                                              */
/*    Authors:      Jayden Liffick / Colton Ring                              */
/*    Created:      26 Dec 2022                                               */
/*    Description:  Code for using odometry tracking with a robot.            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "../../odomSupport/include/odomMain.h"
#include "../../Common/include/generalFunctions.h"
#include "../../Common/include/robotStatus.h"
#include "../../Common/include/evNamespace.h"

namespace evAPI
{
  thread * odomThread;

  double globalX = 0; //X coordinate
  double globalY = 0; //Y coordinate
  double absAngle = 0;

  double distL = 1.5; //Distance from left sensor to center of robot
  double distR = 1.5; //Distance from right sensor to center of robot
  double distB = 2; //Distance from back wheel to center of robot
  double startingAngle = 0; //Starting Angle
  double wheelDiameter = 2.25; //Wheel Diameter

  int8_t encoderCount = 0; //Number of encoders on the robot

  bool useInertialSensor = false;

  bool posTrackingEnabled = false;

  /**
  * @brief An array containing all the encoder objects. One is the left encoder, two is the right encoder,
  *  and three is the back encoder.
  */
  rotation * baseEncoders[3];

  /** 
  * @brief Thread used for tracking the position of the robot for the odometry code.
  */
  int positionTracking()
  {
    posTrackingEnabled = true;

    double prevLEncoder = 0;
    double LEncoder = 0;
    double prevREncoder = 0;
    double REncoder = 0;
    double prevBEncoder = 0;
    double BEncoder = 0;
    double prevAngle = 0;
    double deltaL = 0;
    double deltaR = 0;
    double deltaB = 0;
    double deltaAngle = 0;
    double totalDeltaL;
    double totalDeltaR;
    double totalDeltaB;
    double avgAngle;
    double localX;
    double localY;
    double radius;
    double polarAngle;
    double deltaGlobalX = 0;
    double deltaGlobalY = 0;
    double unModAbsAngle = startingAngle;
    double angleModifier;

    double DeltaL = 0,
    DeltaR = 0,
    PreviousL = 0,
    PreviousR = 0,
    DeltaTheta = 0,
    Theta = startingAngle;

    if(Odometry.Inertial.wasCreated())
    { Odometry.Inertial.setRotation(startingAngle, degrees); }

    baseEncoders[odomCore::leftEncoder]->resetPosition(); //Left
    baseEncoders[odomCore::backEncoder]->resetPosition(); //Back

    if(encoderCount >= 3) //Right
    { baseEncoders[odomCore::rightEncoder]->resetPosition(); }

    while(1)
    {
      LEncoder = baseEncoders[odomCore::leftEncoder]->position(rev);
      BEncoder = baseEncoders[odomCore::backEncoder]->position(rev);

      if(encoderCount >= 3)
      { REncoder = baseEncoders[odomCore::rightEncoder]->position(rev); }

      if(encoderCount >= 3 && !useInertialSensor)
      {
        //Creates variables for change in each side info in inches.
        DeltaL = ((LEncoder - PreviousL) * (M_PI * wheelDiameter));
        DeltaR = ((REncoder - PreviousR) * (M_PI * wheelDiameter));

        //Determines the change in angle of the robot using the rotational change in each side
        DeltaTheta = (DeltaR - DeltaL) / (distL + distR);

        if(DeltaTheta != 0) 
        { Theta += DeltaTheta; }

        //Odom heading is converting the radian value of Theta into degrees
        unModAbsAngle = -degrees(Theta);

        if(unModAbsAngle == -0) 
        { unModAbsAngle = 0; }

        angleModifier = unModAbsAngle;

        while(angleModifier >= 360) //Converts absAngle to a value between -360 and 360.
        { angleModifier -= 360; } 

        while(angleModifier <= -360)
        { angleModifier += 360; }

        absAngle = (angleModifier);

        //Converts values into newer values to allow for code to effectively work in next cycle
        PreviousL = LEncoder;
        PreviousR = REncoder;
        DeltaTheta = 0;
      }

      else
      { 
        if(Odometry.Inertial.wasCreated()) //! Nested to prevent memory errors if not configured.
        {
          if(Odometry.Inertial.installed())
          { absAngle = Odometry.Inertial.rotation(degrees); }

          else
          {
            Brain.Screen.clearScreen();
            Brain.Screen.print("CAN'T DETECT ANGLE!");

            printf("\n\nNOT ABLE TO DETECT ANGLE!\n\n");
            posTrackingEnabled = false;
            this_thread::yield();
          }
        }

        else
        {
          Brain.Screen.clearScreen();
          Brain.Screen.print("CAN'T DETECT ANGLE!");

          printf("\n\nNOT ABLE TO DETECT ANGLE!\n\n");
          posTrackingEnabled = false;
          this_thread::yield();
        }
      }

      //Reduce number of variables after it works
      //Step 1: Grab the current encoder values

      //Step 2: Calculate inches traveled since previous iteration of the loop (circumference * rev) for both
      //sides.
      deltaL = (LEncoder-prevLEncoder)*wheelDiameter*M_PI;
      deltaB = (BEncoder-prevBEncoder)*wheelDiameter*M_PI;

      //Step 2.5: Update previous encoder values
      prevLEncoder = LEncoder;
      prevBEncoder = BEncoder;

      //Step 3: Calculate the absolute change in the encoder value since the last full reset of the robot. 
      //Convert to inches.
      //These are only ever used to calculate the angle so if the inertial sensor works this step can
      //be eliminated
      totalDeltaL = LEncoder*wheelDiameter*M_PI;
      totalDeltaB = BEncoder*wheelDiameter*M_PI;

      //Do the same stuff for the right encoder if it is defined
      if(encoderCount >= 3) 
      {
        deltaR = (REncoder-prevREncoder)*wheelDiameter*M_PI;          //Step 2
        prevREncoder = REncoder;                                      //Step 2.5
        totalDeltaR = REncoder*wheelDiameter*M_PI;                    //Step 3
        //printf("REcoder %f\n", baseEncoders[1]->position(degrees));
      }

      //Step 4: Calculate the absolute angle using
      //deltaTheta = startingTheta + (deltaL - deltaR)/(wheelDistanceL + wheelDistanceR)
      //absAngle = Inertial.rotation(degrees)*M_PI/180;
      /* if(encoderCount == 3) //Use Inertial
      { absAngle = (startingAngle + (deltaL - deltaR) / (distL + distR)); }

      else //Use Wheels //TODO: FIX AND TEST
      { absAngle = Odometry.Inertial.rotation(degrees)*M_PI/180; } */

      //Steps 3 and 4 can probably be replaced by the inertia sensor as it is more accurate and easier to use
      //Need to convert degrees to radians because all the other equations use radians. rad = degrees * M_PI/180

      //Step 5: Calculate the change in angle using deltaTheta = currentTheta - prevTheta
      deltaAngle = (radians(absAngle)) - prevAngle;

      //Step 6: If deltaTheta is EXACTLY 0, the local offset is <deltaBack, deltaRight or
      //deltaLeft (they are equal)
      if(deltaAngle == 0)
      {
        localX = deltaB;
        localY = deltaL;
      }

      //Step 7: If deltaTheta is NOT 0, calculate the local coordinates of
      // 2sin(deltaTheta/2) * <(deltaS/deltaTheta) + distanceS, (deltaR/deltaTheta) + distanceR>
      else
      {
        localX = 2*sin(deltaAngle/2)*((deltaB/deltaAngle) + distB);
        localY = 2*sin(deltaAngle/2)*((deltaR/deltaAngle) + distR);
      }

      //Convert to global
      avgAngle = prevAngle + deltaAngle/2;
      radius = sqrt((localX*localX)+(localY*localY));

      if(localX != 0)
      { polarAngle = atan2(localY, localX); }

      else
      {
        if(localY > 0)
        { polarAngle = M_PI /2; }

        else
        { polarAngle = (-M_PI) /2; }
      }

      deltaGlobalX = radius*sin(polarAngle-avgAngle);
      deltaGlobalY = radius*cos(polarAngle-avgAngle);

      //Step 10: FINALLY update the global coordinates <xglobal, yglobal> = <xprev, yprev> 
      //+ <xrotated, yrotated>

      globalX += deltaGlobalX;
      globalY += deltaGlobalY;

      //Step 11: Update prevTheta
      prevAngle = radians(absAngle);

      // printf("globalX: %f, ", globalX);
      // printf("globalY: %f, ", globalY);
      // printf("absAngle: %f\n", absAngle); 

      this_thread::sleep_for(10);
    }

    return 0;
  }

  void odomCore::createEncoders(int leftEncoderPort, bool leftEncoderReversed, int rightEncoderPort,
    bool rightEncoderReversed, int backEncoderPort, bool backEncoderReversed)
  {
    baseEncoders[odomCore::leftEncoder] = new rotation(smartPortLookupTable[leftEncoderPort], 
      leftEncoderReversed);
    baseEncoders[odomCore::backEncoder] = new rotation(smartPortLookupTable[backEncoderPort], 
      backEncoderReversed);

    encoderCount = 2;

    if(rightEncoderPort != -1)
    {
      baseEncoders[odomCore::rightEncoder] = new rotation(smartPortLookupTable[rightEncoderPort],
        rightEncoderReversed);
      encoderCount++;
    }
  }

  void odomCore::configureEncoderWheels(double leftDistance, double rightDistance, double backDistance,
    double WheelDiameter)
  {
    distL = leftDistance; //Distance from left sensor to center of robot
    distR = rightDistance; //Distance from right sensor to center of robot
    distB = backDistance; //Distance from back wheel to center of robot
    wheelDiameter = WheelDiameter; //Wheel Diameter
  }

  void odomCore::startingParameters(double xPos, double yPos, double angle)
  {
    bool wasEnabled = false;

    if(posTrackingEnabled)
    {
      delete odomThread;
      this_thread::sleep_for(10);
      posTrackingEnabled = false;
      wasEnabled = true;
    }

    globalX = xPos; //X coordinate
    globalY = yPos; //Y coordinate
    startingAngle = angle; //Starting Angle
    absAngle = angle;

    if(wasEnabled)
    {
      startOdometry();
      this_thread::sleep_for(10);
    }
  }

  void odomCore::startOdometry()
  {
    odomThread = new thread(positionTracking);
    this_thread::sleep_for(15);
  }

  double odomCore::xPosition()
  { return globalX; }

  double odomCore::yPosition()
  { return globalY; }

  double odomCore::angle()
  { return absAngle; }

  double odomCore::encoderAngle(encoderNames encoder)
  { return baseEncoders[encoder]->angle(degrees); }

  void odomCore::useInertial(bool stat)
  { useInertialSensor = stat; }

  bool odomCore::usingInertial()
  { return useInertialSensor; }
}