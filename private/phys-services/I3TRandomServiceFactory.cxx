/*
 * class: I3TRandomServiceFactory
 *
 * Version $Id: I3TRandomServiceFactory.cxx,v 1.9 2005/04/04 18:40:39 pretz Exp $
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

I3TRandomServiceFactory::I3TRandomServiceFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
}

// Destructors

I3TRandomServiceFactory::~I3TRandomServiceFactory()
{
}

// Member functions

bool
I3TRandomServiceFactory::InstallService(I3Services& services)
{
  I3RandomServicePtr random ( new I3TRandomService());
  return I3ServicesAccess<I3RandomService>::Put(services,
						random,
						I3RandomService::DefaultName());
}
