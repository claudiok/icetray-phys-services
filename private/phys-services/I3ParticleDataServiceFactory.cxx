/*
 * class: I3ParticleDataServiceFactory
 *
 * Version $Id: I3ParticleDataServiceFactory.cxx,v 1.6.2.1 2005/02/05 01:45:15 troy Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3ParticleDataServiceFactory.h"

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3ParticleDataService.h"

// Constructors

// FIXME: use std::string
I3ParticleDataServiceFactory::I3ParticleDataServiceFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
  if (!IsNameSet()) {
  SetServiceName(I3ParticleDataService::DefaultName());
  }
}

// Destructors

I3ParticleDataServiceFactory::~I3ParticleDataServiceFactory()
{
}

// Member functions

Bool_t
I3ParticleDataServiceFactory::InstallService(I3Services& services)
{
  I3ParticleDataServicePtr pds(new I3ParticleDataService());
  return I3ServicesAccess<I3ParticleDataService>::Put(services,
						      pds,
						      GetServiceName().c_str());
}
