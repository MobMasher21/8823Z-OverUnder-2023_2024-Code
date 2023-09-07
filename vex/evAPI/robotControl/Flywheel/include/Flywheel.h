/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Flywheel.h                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      July 22, 2023                                             */
/*    Description:  Header file for the flywheel class.                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "vex.h"

namespace evAPI
{
  class flywheel
  {
    private:
      motor * flywheelMotors[2];

      bool usingSecondMotor = false;

    public:
      flywheel();
      void flywheelSetup(int32_t motorPort, bool reversed = false);
      void flywheelSetup(int32_t motorPort, gearSetting gears, bool reversed = false);
      void flywheelSetup(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed = false, bool secondMotorReversed = false);
      void flywheelSetup(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed = false, bool secondMotorReversed = false);
      ~flywheel();

      /** 
       * @brief Sets the velocity of the flywheel based on the parameters set in the command.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
       */
      void setVelocity(double velocity, velocityUnits units);

      /** 
       * @brief Sets the velocity of the flywheel based on the parameters set in the command.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value.
       */
      void setVelocity(double velocity, percentUnits units);

      /** 
       * @brief Turns the flywheel on, and spins it in the specified direction.
       * @param dir The direction to spin the flywheel.
       */
      void  spin(directionType dir);

      /**
       * @brief Turns on the flywheel and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the flywheel. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void spin(directionType dir, double velocity, velocityUnits units);

      /**
       * @brief Turns on the flywheel and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the flywheel. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void spin(directionType dir, double velocity, percentUnits units);

      /**
       * @brief Turns on the flywheel and spins it in a specified direction and a specified voltage.
       * @param dir The direction to spin the flywheel. 
       * @param voltage Sets the amount of volts.
       * @param units The measurement unit for the voltage value. 
      */
      void spin(directionType dir, double voltage, voltageUnits units);

      /** 
       * @brief Stops the flywheel.
       */
      void stop();

      /** 
       * @brief Sets the max torque of the flywheel.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, percentUnits units);

      /** 
       * @brief Sets the max torque of the flywheel.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, torqueUnits units);
      
      /** 
       * @brief Sets the max torque of the flywheel.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, currentUnits units);

      /** 
       * @brief Gets which direction the flywheel is spinning.
       * @return Returns the direction that the flywheel is spinning.
       */
      directionType direction();

      /** 
       * @brief Gets the current velocity of the flywheel.
       * @return Returns a double that represents the current velocity of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double velocity(velocityUnits units);
      
      /** 
       * @brief Gets the current velocity of the flywheel.
       * @return Returns a double that represents the current velocity of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double velocity(percentUnits units);

      /** 
       * @brief Gets the electrical current of the flywheel.
       * @return Returns a double that represents the electrical current of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the current.
       */
      double current(currentUnits units = currentUnits::amp);

      /** 
       * @brief Gets the electrical current of the flywheel in percentage of maximum.
       * @return Returns a double that represents the electrical current of the flywheel as percentage of max current.
       * @param units The measurement unit for the current.
       */
      double current(percentUnits units);

      /** 
       * @brief Gets the electrical voltage of the flywheel.
       * @return Returns a double that represents the electrical voltage of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the voltage.
       */
      double voltage(voltageUnits units = voltageUnits::volt);

      /** 
       * @brief Gets the power of the flywheel.
       * @return Returns a double that represents the power of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the power.
       */
      double power(powerUnits units = powerUnits::watt);

      /** 
       * @brief Gets the torque of the flywheel.
       * @return Returns a double that represents the torque of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the torque.
       */
      double torque(torqueUnits units = torqueUnits::Nm);

      /** 
       * @brief Gets the efficiency of the flywheel.
       * @return Returns the efficiency of the flywheel in the units defined in the parameter.
       * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
       */
      double efficiency(percentUnits units = percentUnits::pct);

      /** 
       * @brief Gets the temperature  of the flywheel.
       * @return Returns the temperature of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double temperature(percentUnits units = percentUnits::pct);
      
      /** 
       * @brief Gets the temperature  of the flywheel.
       * @return Returns the temperature of the flywheel in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double temperature(temperatureUnits units);

  };
  
} // namespace evAPI

#endif // FLYWHEEL_H