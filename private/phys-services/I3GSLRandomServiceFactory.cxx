/*
 * class: I3GSLRandomServiceFactory
 *
 * Version $Id: I3GSLRandomServiceFactory.cxx,v 1.3 2005/03/09 19:12:24 pretz Exp $
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

I3GSLRandomServiceFactory::I3GSLRandomServiceFactory(I3Context& context)
  : I3ServiceFactory(context),
    random(0)
{
}

// Destructors

I3GSLRandomServiceFactory::~I3GSLRandomServiceFactory()
{
}

// Member functions

Bool_t
I3GSLRandomServiceFactory::InstallService(I3Services& services)
{
  if(!random)
    random = I3RandomServicePtr(new I3GSLRandomService());
  return I3ServicesAccess<I3RandomService>::Put(services,
						random,
						I3RandomService::DefaultName());
}
