/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DummyDetectoryStatusOriginFactory.cxx
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#include "phys-source/I3DummyDetectorStatusOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3DummyDetectorStatusOriginFactory::
I3DummyDetectorStatusOriginFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
}

I3DummyDetectorStatusOriginFactory::~I3DummyDetectorStatusOriginFactory()
{
}

bool
I3DummyDetectorStatusOriginFactory::InstallService(I3Services& services)
{
  if(!eventOrigin_)
    eventOrigin_ = 
      I3DummyDetectorStatusOriginPtr(new I3DummyDetectorStatusOrigin());
  return I3ServicesAccess<I3DetectorStatusOrigin>::
    Put(services,
	eventOrigin_,
	I3DetectorStatusOrigin::DefaultName());
}
