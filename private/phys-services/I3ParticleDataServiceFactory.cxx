/*
 * class: I3ParticleDataServiceFactory
 *
 * Version $Id$
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3ParticleDataServiceFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3ParticleDataService.h"

// Constructors

// FIXME: use std::string
I3ParticleDataServiceFactory::I3ParticleDataServiceFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
}

// Destructors

I3ParticleDataServiceFactory::~I3ParticleDataServiceFactory()
{
}

// Member functions

bool
I3ParticleDataServiceFactory::InstallService(I3Services& services)
{
  I3ParticleDataServicePtr pds(new I3ParticleDataService());
  return I3ServicesAccess<I3ParticleDataService>::Put(services,
						      pds,
						      I3ParticleDataService::DefaultName());
}
