/*
 * class: I3TRandomServiceFactory
 *
 * Version $Id: I3TRandomServiceFactory.cxx,v 1.6 2004/09/17 21:12:02 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3TRandomServiceFactory.h"

ClassImp(I3TRandomServiceFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

// Constructors

I3TRandomServiceFactory::I3TRandomServiceFactory(const char* name)
  : I3ServiceFactory(name)
{
  if (!IsNameSet()) {
    SetServiceName(I3TRandomService::DefaultName());
  }
}

// Destructors

I3TRandomServiceFactory::~I3TRandomServiceFactory()
{
}

// Member functions

Bool_t
I3TRandomServiceFactory::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  I3TRandomService* pds = new I3TRandomService();
  return I3ServicesAccess<I3RandomService>::Put(services,
						pds,
						GetServiceName().c_str());
}
