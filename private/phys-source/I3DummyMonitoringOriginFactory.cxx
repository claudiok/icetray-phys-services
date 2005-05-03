/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3DummyMonitoringOriginFactory.cxx 7067 2005-04-28 15:04:38Z pretz $
 *
 * @file I3DummyMonitoringOriginFactory.cxx
 * @version $Revision:$
 * @date $Date: 2005-04-28 11:04:38 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */


#include "phys-source/I3DummyMonitoringOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3DummyMonitoringOriginFactory::I3DummyMonitoringOriginFactory(const I3Context& context)
  : I3ServiceFactory(context),
    maxMonitorings_(10)
{
  AddParameter("MonitoringsToReturn",
	       "The maximum number of events to return",
	       maxMonitorings_);
}

I3DummyMonitoringOriginFactory::~I3DummyMonitoringOriginFactory()
{
}

void I3DummyMonitoringOriginFactory::Configure()
{
  GetParameter("MonitoringsToReturn",maxMonitorings_);
}

bool
I3DummyMonitoringOriginFactory::InstallService(I3Services& services)
{
  if(!eventOrigin_)
    eventOrigin_ = I3DummyMonitoringOriginPtr(new I3DummyMonitoringOrigin(maxMonitorings_));
  return I3ServicesAccess<I3MonitoringOrigin>::Put(services,
						eventOrigin_,
						I3MonitoringOrigin::DefaultName());
}
