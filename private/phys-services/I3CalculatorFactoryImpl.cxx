/**
 * class: I3CalculatorFactoryImpl
 *
 * Version $Id: I3CalculatorFactoryImpl.cxx,v 1.7 2005/04/04 18:40:39 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3CalculatorFactoryImpl.h"

ClassImp(I3CalculatorFactoryImpl);

// Other header files

#include "icetray/I3ServicesAccess.h"
#include "phys-services/I3CalculatorImpl.h"

// Constructors

I3CalculatorFactoryImpl::I3CalculatorFactoryImpl(const I3Context& context)
  : I3ServiceFactory(context)
{
}

// Destructors

I3CalculatorFactoryImpl::~I3CalculatorFactoryImpl()
{
}

// Member functions

/**
 * @todo implement a fatal call if the tables don't load
 */
bool
I3CalculatorFactoryImpl::InstallService(I3Services& services)
{
  if(!fCalculator)
    {
      fCalculator = I3CalculatorPtr(new I3CalculatorImpl());
    }
  return I3ServicesAccess<I3Calculator>::Put(services,
					    fCalculator,
					    "Calculator");
}
