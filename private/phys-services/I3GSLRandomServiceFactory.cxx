/*
 * class: I3GSLRandomServiceFactory
 *
 * Version $Id: I3GSLRandomServiceFactory.cxx,v 1.1 2004/10/18 14:21:42 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3GSLRandomServiceFactory.h"

ClassImp(I3GSLRandomServiceFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3GSLRandomService.h"

// Constructors

I3GSLRandomServiceFactory::I3GSLRandomServiceFactory(const char* name)
  : I3ServiceFactory(name),
    random(0)
{
  if (!IsNameSet()) {
    SetServiceName(I3GSLRandomService::DefaultName());
  }
}

// Destructors

I3GSLRandomServiceFactory::~I3GSLRandomServiceFactory()
{
}

// Member functions

Bool_t
I3GSLRandomServiceFactory::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  if(!random)
    random = new I3GSLRandomService();
  return I3ServicesAccess<I3RandomService>::Lend(services,
						random,
						GetServiceName().c_str());
}
