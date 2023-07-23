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
  class Flywheel
  {
    private:
      motor * flywheelMotors[8];

      bool usingSecondMotor = false;

    public:
      Flywheel(int32_t motorPort, bool reversed = false);
      Flywheel(int32_t motorPort, gearSetting gears, bool reversed = false);
      Flywheel(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed = false, bool secondMotorReversed = false);
      Flywheel(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed = false, bool secondMotorReversed = false);
      ~Flywheel();

      /** 
       * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
       */
      void setVelocity(double velocity, velocityUnits units);

      /** 
       * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value.
       */
      void setVelocity(double velocity, percentUnits units);

      /** 
       * @brief Turns the motor on, and spins it in the specified direction.
       * @param dir The direction to spin the motor.
       */
      void  spin(directionType dir);

      /**
       * @brief Turns on the motor and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the motor. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void spin(directionType dir, double velocity, velocityUnits units);

      /**
       * @brief Turns on the motor and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the motor. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void spin(directionType dir, double velocity, percentUnits units);

      /**
       * @brief Turns on the motor and spins it in a specified direction and a specified voltage.
       * @param dir The direction to spin the motor. 
       * @param voltage Sets the amount of volts.
       * @param units The measurement unit for the voltage value. 
      */
      void spin(directionType dir, double voltage, voltageUnits units);

      /** 
       * @brief Stops the flywheel.
       */
      void stop();

      /** 
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, percentUnits units);

      /** 
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, torqueUnits units);
      
      /** 
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void setMaxTorque(double value, currentUnits units);

      /** 
       * @brief Gets which direction the motor is spinning.
       * @return Returns the direction that the motor is spinning.
       */
      directionType direction();

      /** 
       * @brief Gets the current velocity of the motor.
       * @return Returns a double that represents the current velocity of the motor in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double velocity(velocityUnits units);
      
      /** 
       * @brief Gets the current velocity of the motor.
       * @return Returns a double that represents the current velocity of the motor in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double velocity(percentUnits units);

      /** 
       * @brief Gets the electrical current of the motor.
       * @return Returns a double that represents the electrical current of the motor in the units defined in the parameter.
       * @param units The measurement unit for the current.
       */
      double current(currentUnits units = currentUnits::amp);

      /** 
       * @brief Gets the electrical current of the motor in percentage of maximum.
       * @return Returns a double that represents the electrical current of the motor as percentage of max current.
       * @param units The measurement unit for the current.
       */
      double current(percentUnits units);

      /** 
       * @brief Gets the electrical voltage of the motor.
       * @return Returns a double that represents the electrical voltage of the motor in the units defined in the parameter.
       * @param units The measurement unit for the voltage.
       */
      double voltage(voltageUnits units = voltageUnits::volt);

      /** 
       * @brief Gets the power of the motor.
       * @return Returns a double that represents the power of the motor in the units defined in the parameter.
       * @param units The measurement unit for the power.
       */
      double power(powerUnits units = powerUnits::watt);

      /** 
       * @brief Gets the torque of the motor.
       * @return Returns a double that represents the torque of the motor in the units defined in the parameter.
       * @param units The measurement unit for the torque.
       */
      double torque(torqueUnits units = torqueUnits::Nm);

      /** 
       * @brief Gets the efficiency of the motor.
       * @return Returns the efficiency of the motor in the units defined in the parameter.
       * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
       */
      double efficiency(percentUnits units = percentUnits::pct);

      /** 
       * @brief Gets the temperature  of the motor.
       * @return Returns the temperature of the motor in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double temperature(percentUnits units = percentUnits::pct);
      
      /** 
       * @brief Gets the temperature  of the motor.
       * @return Returns the temperature of the motor in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double temperature(temperatureUnits units);

  };
  
} // namespace evAPI

#endif // FLYWHEEL_H