#include "phys-services/source/I3MCRawDOMStatusService.h"
#include "dataclasses/status/I3DOMStatus.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/status/I3DetectorStatus.h"
#include "dataclasses/I3Units.h"
#include "icetray/I3TrayHeaders.h"
#include "phys-services/I3GeometryService.h"

I3DetectorStatusConstPtr
I3MCRawDOMStatusService::GetDetectorStatus(I3Time time)
{
  log_debug("GetDetectorStatus");

  I3GeometryConstPtr geo = geo_service_->GetGeometry(time);
  const I3OMGeoMap& om_geo = geo->omgeo;

  I3OMGeoMap::const_iterator iter;

  I3DetectorStatusPtr status = I3DetectorStatusPtr(new I3DetectorStatus);

  I3Time start(2000,0);
  I3Time end(3000,0);

  status->startTime = start;
  status->endTime = end;
  //changed all inice to om_geo
  for( iter  = om_geo.begin(); 
       iter != om_geo.end(); 
       iter++ )
    {
      OMKey thiskey = iter->first;

      I3DOMStatus raw;

      raw.trigMode = I3DOMStatus::SPE;
      raw.lcMode = I3DOMStatus::UpOrDown;
	
      raw.lcWindowPre = -800.0*I3Units::mV;
      raw.lcWindowPost = 800.0*I3Units::mV;

      raw.statusATWDa = I3DOMStatus::On;
      raw.statusATWDb = I3DOMStatus::On;
      raw.statusFADC = I3DOMStatus::On;
	
      raw.pmtHV = 1350*I3Units::volt;
      raw.speThreshold= 4.0*I3Units::mV;
      raw.fePedestal = 2.6*I3Units::volt;
    
      raw.nBinsATWD0 = 128;
      raw.nBinsATWD1 = 128;
      raw.nBinsATWD2  = 128;

      raw.nBinsFADC = 256;

      status->domStatus[thiskey] = raw;
    }
  return static_cast<I3DetectorStatusConstPtr>(status);
}


