/*
 * class: I3ParticleDataServiceFactory
 *
 * Version $Id: I3ParticleDataServiceFactory.cxx,v 1.2.2.2 2004/04/13 10:32:05 troy Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3ParticleDataServiceFactory.h"

ClassImp(I3ParticleDataServiceFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3ParticleDataService.h"

// Constructors

// FIXME: use std::string
I3ParticleDataServiceFactory::I3ParticleDataServiceFactory(const char* name)
  : I3ServiceFactory(name)
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
I3ParticleDataServiceFactory::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  I3ParticleDataService* pds = new I3ParticleDataService();
  return I3ServicesAccess<I3ParticleDataService>::Put(services,
						      pds,
						      GetServiceName().c_str());
}
