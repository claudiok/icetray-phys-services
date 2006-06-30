#include "phys-services/geo-selector/I3GeometrySelectorServiceFactory.h"
#include "phys-services/geo-selector/I3GeometrySelectorService.h"
#include "phys-services/geo-selector/GeoSelUtils.h"

I3_SERVICE_FACTORY(I3GeometrySelectorServiceFactory);

/**
 * Minimum distance you can shift the detector
 */
const double MIN_SHIFT = 1.;

I3GeometrySelectorServiceFactory::
I3GeometrySelectorServiceFactory(const I3Context& context) : 
  I3ServiceFactory(context),
  stringsToUse_("-19:80"),
  stringsToExclude_(""),
  stationsToUse_("-19:80"),
  stationsToExclude_(""),
  shiftX_(0.),
  shiftY_(0.),
  shiftZ_(0.)
{
    AddParameter("StringsToUse", 
		 "The strings that should be included", 
		 stringsToUse_);
    AddParameter("StringsToExclude", 
		 "The strings that should be excluded", 
		 stringsToExclude_);
    AddParameter("StationsToUse", 
		 "The strings that should be included", 
		 stationsToUse_);
    AddParameter("StationsToExclude", 
		 "The strings that should be excluded", 
		 stationsToExclude_);
    AddParameter("GeoSelectorName",
		 "Name of the new geometry service. The muxer needs this name.",
		 geoSelectorName_);
    AddParameter("ShiftX",
		 "Distance to shift the entire detector",
		 shiftX_);
    AddParameter("ShiftY",
		 "Distance to shift the entire detector",
		 shiftY_);
    AddParameter("ShiftZ",
		 "Distance to shift the entire detector",
		 shiftZ_);
}

I3GeometrySelectorServiceFactory::
~I3GeometrySelectorServiceFactory()
{

}

void I3GeometrySelectorServiceFactory::Configure()
{
  GetParameter("StringsToUse",stringsToUse_);
  GetParameter("StringsToExclude",stringsToExclude_);
  GetParameter("StationsToUse",stationsToUse_);
  GetParameter("StationsToExclude",stationsToExclude_);
  GetParameter("GeoSelectorName",geoSelectorName_);
  GetParameter("ShiftX",shiftX_);
  GetParameter("ShiftY",shiftY_);
  GetParameter("ShiftZ",shiftZ_);
}

bool I3GeometrySelectorServiceFactory::InstallService(I3Context& services)
{
  if(!geometry_)
    geometry_ = 
      shared_ptr<I3GeometrySelectorService>
      (new I3GeometrySelectorService(context_.Get<I3GeometryServicePtr>(),
       shiftX_, shiftY_, shiftZ_));

  if(!geo_sel_utils::good_input(stringsToUse_)) 
    log_fatal("couldn't parse %s",stringsToUse_.c_str());
  if(!geo_sel_utils::good_input(stringsToExclude_)) 
    log_fatal("couldn't parse %s",stringsToExclude_.c_str());
  if(!geo_sel_utils::good_input(stationsToUse_)) 
    log_fatal("couldn't parse %s",stationsToUse_.c_str());
  if(!geo_sel_utils::good_input(stationsToExclude_)) 
    log_fatal("couldn't parse %s",stationsToExclude_.c_str());

  goodStrings_ = geo_sel_utils::make_good_strings(stringsToUse_, stringsToExclude_);
  goodStations_ = geo_sel_utils::make_good_strings(stationsToUse_, stationsToExclude_);

  dynamic_pointer_cast<I3GeometrySelectorService>(geometry_)->SetGoodStrings(goodStrings_);
  dynamic_pointer_cast<I3GeometrySelectorService>(geometry_)->SetGoodStations(goodStations_);

  return services.Put<I3GeometryService>(geoSelectorName_,geometry_);
}

