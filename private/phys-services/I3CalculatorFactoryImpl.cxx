/**
 * class: I3CalculatorFactoryImpl
 *
 * Version $Id: I3CalculatorFactoryImpl.cxx,v 1.2.2.1 2004/09/17 20:55:53 pretz Exp $
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

I3CalculatorFactoryImpl::I3CalculatorFactoryImpl(const char* name)
  : I3ServiceFactory(name)
{
  if ("" == GetServiceName()) {
    SetServiceName("Calculator");
  }
}

// Destructors

I3CalculatorFactoryImpl::~I3CalculatorFactoryImpl()
{
}

// Member functions

/**
 * @todo implement a fatal call if the tables don't load
 */
Bool_t
I3CalculatorFactoryImpl::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  if(!fCalculator)
    {
      fCalculator = I3CalculatorPtr(new I3CalculatorImpl());
    }
  return I3ServicesAccess<I3Calculator>::Put(services,
					    fCalculator,
					    GetServiceName());
}
