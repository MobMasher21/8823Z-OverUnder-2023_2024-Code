/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       dualPneumatics.cpp                                        */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      31 Aug 2023                                               */
/*    Description:  Class for using duel action pneumatics.                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/dualPneumatics.h"

namespace evAPI
{
  dualPneumatics::dualPneumatics(triport::port &port)
  {
    pneumaticPrimary = new digital_out(port);
  }

  dualPneumatics::dualPneumatics(triport::port &port1, triport::port &port2)
  {
    pneumaticPrimary = new digital_out(port1);
    pneumaticSecondary = new digital_out(port2);
  }
  
  dualPneumatics::~dualPneumatics()
  {}

  void dualPneumatics::setSecondaryPneumatic(bool value)
  {
    if(pneumaticSecondary != nullptr)
    { pneumaticSecondary->set(value); }
  }

  void dualPneumatics::open()
  {
    pneumaticPrimary->set(true);
    setSecondaryPneumatic(false);
  }

  void dualPneumatics::close()
  {
    pneumaticPrimary->set(false);
    setSecondaryPneumatic(true);
  }

  void dualPneumatics::set(bool value)
  {
    pneumaticPrimary->set(value);
    setSecondaryPneumatic(!value);
  }

  int32_t dualPneumatics::value()
  { return pneumaticPrimary->value(); }

  void dualPneumatics::operator=(bool value)
  {
    pneumaticPrimary->set(value);
    setSecondaryPneumatic(!value);
  }

} // namespace evAPI
