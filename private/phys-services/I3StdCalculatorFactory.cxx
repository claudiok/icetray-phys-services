/**
 * class: I3StdCalculatorFactory
 *
 * Version $Id: I3StdCalculatorFactory.cxx,v 1.1 2004/06/24 14:27:55 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3StdCalculatorFactory.h"

ClassImp(I3StdCalculatorFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3StdCalculator.h"

// Constructors

I3StdCalculatorFactory::I3StdCalculatorFactory(const char* name)
  : I3ServiceFactory(name),
    fCalculator(0)
{
  if ("" == GetServiceName()) {
    SetServiceName("Calculator");
  }
}

// Destructors

I3StdCalculatorFactory::~I3StdCalculatorFactory()
{
}

// Member functions

/**
 * @todo implement a fatal call if the tables don't load
 */
Bool_t
I3StdCalculatorFactory::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  if(!fCalculator)
    {
      fCalculator = new I3StdCalculator();
    }
  return I3ServicesAccess<I3Calculator>::Put(services,
					    fCalculator,
					    GetServiceName());
}
