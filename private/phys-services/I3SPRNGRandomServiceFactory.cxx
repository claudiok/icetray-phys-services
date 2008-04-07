/*
 * class: I3SPRNGRandomServiceFactory
 *
 * Version $Id: I3SPRNGRandomServiceFactory.cxx 43645 2008-03-25 18:12:38Z tschmidt $
 *
 * Date: 2 Apr 2005
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3SPRNGRandomServiceFactory.h"
I3_SERVICE_FACTORY(I3SPRNGRandomServiceFactory);

// Other header files

#include "phys-services/I3SPRNGRandomService.h"

// Constructors

I3SPRNGRandomServiceFactory::I3SPRNGRandomServiceFactory(const I3Context& context)
  : I3ServiceFactory(context),
  seed_(0),
  nstreams_(1),
  streamnum_(0),
  instatefile_(),
  outstatefile_()
{
  AddParameter("Seed","Seed for random number generator",seed_);

  AddParameter("NStreams","Number of streams used in cluster",nstreams_);

  AddParameter("StreamNum","Thread number for this generator",streamnum_);

  AddParameter("inStateFile","If set, load saved state from file",instatefile_);

  AddParameter("outStateFile","If set, save state to file",outstatefile_);

  installServiceAs_ = I3DefaultName<I3RandomService>::value();
  AddParameter("InstallServiceAs",
               "Install the random service at the following location",
               installServiceAs_);
}

// Destructors

I3SPRNGRandomServiceFactory::~I3SPRNGRandomServiceFactory()
{
}

// Member functions

bool
I3SPRNGRandomServiceFactory::InstallService(I3Context& services)
{
  if (!random_)  {
	random_ = I3RandomServicePtr(
				new I3SPRNGRandomService(seed_, nstreams_,
						streamnum_, instatefile_, outstatefile_));
  }

  return services.Put<I3RandomService>(installServiceAs_, random_);
}

void I3SPRNGRandomServiceFactory::Configure()
{
  GetParameter("Seed",seed_);
  GetParameter("NStreams",nstreams_);
  GetParameter("StreamNum",streamnum_);
  GetParameter("inStateFile",instatefile_);
  GetParameter("outStateFile",outstatefile_);
  GetParameter("InstallServiceAs",installServiceAs_);
}
/* eof */
