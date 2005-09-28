/*
 * class: I3SPRNGRandomServiceFactory
 *
 * Version $Id$
 *
 * Date: 2 Apr 2005
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3SPRNGRandomServiceFactory.h"


#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3SPRNGRandomService.h"

// Constructors

I3SPRNGRandomServiceFactory::I3SPRNGRandomServiceFactory(I3Context& context)
  : I3ServiceFactory(context)
{
  random_ = NULL;
  AddParameter("Seed","Seed for random number generator",seed_);
  AddParameter("NStreams","Number of streams used in cluster",nstreams_);
  AddParameter("StreamNum","Thread number for this generator",streamnum_);
}

// Destructors

I3SPRNGRandomServiceFactory::~I3SPRNGRandomServiceFactory()
{
}

// Member functions

bool
I3SPRNGRandomServiceFactory::InstallService(I3Services& services)
{
  if (!random_)  {
     if(!nstreams_) {
		random_ = I3RandomServicePtr(new I3SPRNGRandomService());
	} else
		random_ = I3RandomServicePtr(
				new I3SPRNGRandomService(seed_,nstreams_,streamnum_));
  }

  return I3ServicesAccess<I3RandomService>::Put(services,
						random_,
						I3RandomService::DefaultName());
}

void I3SPRNGRandomServiceFactory::Configure()
{
  GetParameter("Seed",seed_);
  GetParameter("NStreams",nstreams_);
  GetParameter("StreamNum",streamnum_);
}
/* eof */
