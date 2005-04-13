/*
 * class: I3SPRNGRandomServiceFactory
 *
 * Version $Id: I3SPRNGRandomServiceFactory.cxx,v 1.1 2005/04/13 16:29:34 juancarlos Exp $
 *
 * Date: 2 Apr 2005
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3SPRNGRandomServiceFactory.h"

ClassImp(I3SPRNGRandomServiceFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3SPRNGRandomService.h"

// Constructors

I3SPRNGRandomServiceFactory::I3SPRNGRandomServiceFactory(I3Context& context)
  : I3ServiceFactory(context)
{
  random = NULL;
  AddParameter("Seed","Seed for random number generator",seed);
  AddParameter("NStreams","Number of streams used in cluster",nstreams);
  AddParameter("StreamNum","Thread number for this generator",streamnum);
}

// Destructors

I3SPRNGRandomServiceFactory::~I3SPRNGRandomServiceFactory()
{
}

// Member functions

Bool_t
I3SPRNGRandomServiceFactory::InstallService(I3Services& services)
{
  if (!random)  {
     if(!nstreams) {
		random = I3RandomServicePtr(new I3SPRNGRandomService());
	} else
		random = I3RandomServicePtr(
				new I3SPRNGRandomService(seed,nstreams,streamnum));
  }

  return I3ServicesAccess<I3RandomService>::Put(services,
						random,
						I3RandomService::DefaultName());
}

void I3SPRNGRandomServiceFactory::Configure()
{
  GetParameter("Seed",seed);
  GetParameter("NStreams",nstreams);
  GetParameter("StreamNum",streamnum);
}
/* eof */
