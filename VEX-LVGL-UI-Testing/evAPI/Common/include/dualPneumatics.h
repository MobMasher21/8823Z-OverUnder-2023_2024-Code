/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       dualPneumatics.h                                          */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      31 Aug 2023                                               */
/*    Description:  Class for using duel action pneumatics.                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef DUALPNEUMATICS_H
#define DUALPNEUMATICS_H

#include "vex.h"

namespace evAPI
{
  class dualPneumatics
  {
    private:
      digital_out *pneumaticPrimary;
      digital_out *pneumaticSecondary;

      void setSecondaryPneumatic(bool value);
    public:

      /**
       * @brief Creates a dualPneumatics object. Use this when you have one solenoid.
       * @param port The triport the solenoid is in.
      */
      dualPneumatics(triport::port &port);

      /**
       * @brief Creates a dualPneumatics object. Use this when you have two solenoids.
       * @param port1 The triport the primary solenoid is in. (Extends the pneumatic)
       * @param port2 The triport the secondary solenoid is in. (Retracts the pneumatic)
      */
      dualPneumatics(triport::port &port1, triport::port &port2); 
      ~dualPneumatics();

      /**
       * @brief Extends the pneumatic.
      */
      void open();

      /**
       * @brief Retracts the pneumatic.
      */
      void close();

      /**
       * @brief Extends or retracts the pneumatic.
       * @param value The value that controls the the pneumatic state. True extends it. False retracts it.
      */
      void set(bool value);

      /**
       * @returns True if the pneumatic is extended.
      */
      int32_t value();

      /**
       * @brief Extends or retracts the pneumatic.
       * @param value The value that controls the the pneumatic state. True extends it. False retracts it.
      */
      void operator=(bool value);
  };
} // namespace evAPI

#endif // DUALPNEUMATICS_H