/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Intake.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      July 22, 2023                                             */
/*    Description:  Header file for the intake class.                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"

namespace evAPI
{
  class intake
  {
    private:
      motor * intakeMotors[2];

      bool usingSecondMotor = false;
    public:
      intake();
      void intakeSetup(int32_t motorPort, bool reversed = false);
      void intakeSetup(int32_t motorPort, gearSetting gears, bool reversed = false);
      void intakeSetup(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed = false, bool secondMotorReversed = false);
      void intakeSetup(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed = false, bool secondMotorReversed = false);
      ~intake();

      /** 
       * @brief Sets the velocity of the intake based on the parameters set in the command.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
       */
      void setVelocity(double velocity, velocityUnits units);

      /** 
       * @brief Sets the velocity of the intake based on the parameters set in the command.
       * @param units The measurement unit for the velocity value.
       */
      void setVelocity(double velocity, percentUnits units);

      /** 
       * @brief Sets the stopping mode of the intake by passing a brake mode as a parameter.
       * @param mode The stopping mode can be set to coast, brake, or hold.  
       */
      void setStopping(brakeType mode);

      /** 
       * @brief Turns the intake on, and spins it in the specified direction.
       * @param dir The direction to spin the intake.
       */
      void  spin(directionType dir);

      /**
       * @brief Turns on the intake and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the intake. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void spin(directionType dir, double velocity, velocityUnits units);

      /**
       * @brief Turns on the intake and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the intake. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void spin(directionType dir, double velocity, percentUnits units);

      /**
       * @brief Turns on the intake and spins it in a specified direction and a specified voltage.
       * @param dir The direction to spin the intake. 
       * @param voltage Sets the amount of volts.
       * @param units The measurement unit for the voltage value. 
      */
      void spin(directionType dir, double voltage, voltageUnits units);

      /** 
       * @brief Stops the flywheel.
       */
      void stop();

      /** 
       * @brief Stops the motor using a specified brake mode.
       * @param mode The brake mode can be set to coast, brake, or hold. 
       */
      void stop(brakeType mode);

      /** 
       * @brief Sets the max torque of the intake.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, percentUnits units);

      /** 
       * @brief Sets the max torque of the intake.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, torqueUnits units);
      
      /** 
       * @brief Sets the max torque of the intake.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, currentUnits units);

      /** 
       * @brief Gets which direction the intake is spinning.
       * @return Returns the direction that the intake is spinning.
       */
      directionType direction();

      /** 
       * @brief Gets the current velocity of the intake.
       * @return Returns a double that represents the current velocity of the intake in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double velocity(velocityUnits units);
      
      /** 
       * @brief Gets the current velocity of the intake.
       * @return Returns a double that represents the current velocity of the intake in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double velocity(percentUnits units);

      /** 
       * @brief Gets the electrical current of the intake.
       * @return Returns a double that represents the electrical current of the intake in the units defined in the parameter.
       * @param units The measurement unit for the current.
       */
      double current(currentUnits units = currentUnits::amp);

      /** 
       * @brief Gets the electrical current of the intake in percentage of maximum.
       * @return Returns a double that represents the electrical current of the intake as percentage of max current.
       * @param units The measurement unit for the current.
       */
      double current(percentUnits units);

      /** 
       * @brief Gets the electrical voltage of the intake.
       * @return Returns a double that represents the electrical voltage of the intake in the units defined in the parameter.
       * @param units The measurement unit for the voltage.
       */
      double voltage(voltageUnits units = voltageUnits::volt);

      /** 
       * @brief Gets the power of the intake.
       * @return Returns a double that represents the power of the intake in the units defined in the parameter.
       * @param units The measurement unit for the power.
       */
      double power(powerUnits units = powerUnits::watt);

      /** 
       * @brief Gets the torque of the intake.
       * @return Returns a double that represents the torque of the intake in the units defined in the parameter.
       * @param units The measurement unit for the torque.
       */
      double torque(torqueUnits units = torqueUnits::Nm);

      /** 
       * @brief Gets the efficiency of the intake.
       * @return Returns the efficiency of the intake in the units defined in the parameter.
       * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
       */
      double efficiency(percentUnits units = percentUnits::pct);

      /** 
       * @brief Gets the temperature  of the intake.
       * @return Returns the temperature of the intake in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double temperature(percentUnits units = percentUnits::pct);
      
      /** 
       * @brief Gets the temperature  of the intake.
       * @return Returns the temperature of the intake in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double temperature(temperatureUnits units);
  };
  
} // namespace evAPI

#endif //INTAKE_H
