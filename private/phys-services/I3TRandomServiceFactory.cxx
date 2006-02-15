/*
 * class: I3TRandomServiceFactory
 *
 * Version $Id$
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3TRandomServiceFactory.h"

#include "phys-services/I3TRandomService.h"

// Constructors

I3_SERVICE_FACTORY(I3TRandomServiceFactory);

I3TRandomServiceFactory::I3TRandomServiceFactory(const I3Context& context)
  : I3ServiceFactory(context),
  	seed_(-1), random_()
{
	// unfortunatelly we can not support a seed of unsigned int since
	// AddParameter only supports int
	AddParameter("Seed","Seed for random number generator", seed_);	
}

// Destructors

I3TRandomServiceFactory::~I3TRandomServiceFactory()
{
}

// Member functions

bool
I3TRandomServiceFactory::InstallService(I3Context& services)
{
	if(!random_){
		if(seed_ < 0) random_ = I3RandomServicePtr(new I3TRandomService());
		else random_ = I3RandomServicePtr(new I3TRandomService(seed_));
	}
	
	return services.Put(random_);
}

void I3TRandomServiceFactory::Configure()
{
  GetParameter("Seed", seed_);
}
