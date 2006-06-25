/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3GeometrySelector.cxx 2598 2005-02-04 17:18:56Z olivas $
 *
 * @file I3GeometrySelector.cxx
 * @version $Revision: 1.8 $
 * @date $Date: 2005-02-04 18:18:56 +0100 (Fri, 04 Feb 2005) $
 * @author olivas
 *
 * This class shows how to add a Selection to the event.
*/

// headers for this selection
#include <I3Test.h>
#include "phys-services/geo-selector/I3GeoSelTestModule.h"
#include "phys-services/geo-selector/GeoSelUtils.h"

// other headers
//  global header for all the IceTray stuff
#include "icetray/I3TrayHeaders.h"
/* headers for the dataclasses stuff */
#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/OMKey.h"
#include <iostream>
#include <sstream>

using namespace std;

I3_MODULE(I3GeoSelTestModule);

I3GeoSelTestModule::I3GeoSelTestModule(const I3Context& ctx) : 
  I3Module(ctx),
  stringsToUse_("-19:80"),
  stringsToExclude_(""),
  stationsToUse_("1:80"),
  stationsToExclude_("")
{
    AddOutBox("OutBox");

    AddParameter("StringsToUse", 
		 "The strings that should be included", 
		 stringsToUse_);
    AddParameter("StringsToExclude", 
		 "The strings that should be excluded", 
		 stringsToExclude_);
    AddParameter("StationsToUse", 
		 "The stations that should be included", 
		 stationsToUse_);
    AddParameter("StationsToExclude", 
		 "The stations that should be excluded", 
		 stationsToExclude_);

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

I3GeoSelTestModule::~I3GeoSelTestModule() {
}

// transitions
void I3GeoSelTestModule::Configure() {
  GetParameter("StringsToUse",stringsToUse_);
  GetParameter("StringsToExclude",stringsToExclude_);
  GetParameter("StationsToUse",stationsToUse_);
  GetParameter("StationsToExclude",stationsToExclude_);
  GetParameter("ShiftX",shiftX_);
  GetParameter("ShiftY",shiftY_);
  GetParameter("ShiftZ",shiftZ_);

  if(!geo_sel_utils::good_input(stringsToUse_)) 
    log_fatal("couldn't parse %s",stringsToUse_.c_str());
  if(!geo_sel_utils::good_input(stringsToExclude_)) 
    log_fatal("couldn't parse %s",stringsToExclude_.c_str());
  if(!geo_sel_utils::good_input(stationsToUse_)) 
    log_fatal("couldn't parse %s",stationsToUse_.c_str());
  if(!geo_sel_utils::good_input(stationsToExclude_)) 
    log_fatal("couldn't parse %s",stationsToExclude_.c_str());

  log_trace("stringsToUse_ %s",stringsToUse_.c_str());
  log_trace("stringsToExclude %s",stringsToUse_.c_str());
  log_trace("stationsToUse_ %s",stationsToUse_.c_str());
  log_trace("stationsToExclude_ %s",stationsToUse_.c_str());

  goodStrings_ = geo_sel_utils::make_good_strings(stringsToUse_, stringsToExclude_);
  goodStations_ = geo_sel_utils::make_good_strings(stationsToUse_, stationsToExclude_);}

void I3GeoSelTestModule::Geometry(I3FramePtr frame) {

  log_debug("Entering Geometry method.");
  
  // Get the event information out of the Frame
  I3GeometryConstPtr geoPtr = frame->Get<I3GeometryConstPtr>();
  ENSURE(geoPtr,"Couldn't get geometry");

  //loop through the in ice geometry and make sure that
  //1) All the DOMs that exist in the geometry are in goodStrings_
  //2) None of the DOMs correspond to string in stringsToExclude_

  log_trace("***before*** geoPtr->omgeo.size(): %zu",geoPtr->omgeo.size());

  log_trace("goodStrings_.size(): %zu",goodStrings_.size());
  for(vector<int>::iterator iter = goodStrings_.begin(); iter != goodStrings_.end(); ++iter)
    log_trace("%d ",*iter);

  log_trace("goodStations_.size(): %zu",goodStations_.size());
  for(vector<int>::iterator iter = goodStations_.begin(); iter != goodStations_.end(); ++iter)
    log_trace("%d ",*iter);

  std::vector<int> strings_exclude_list = geo_sel_utils::parse_string_list(stringsToExclude_);
  std::vector<int> stations_exclude_list = geo_sel_utils::parse_string_list(stationsToExclude_);

  I3OMGeoMap::const_iterator iter;
  for(iter = geoPtr->omgeo.begin();
      iter != geoPtr->omgeo.end(); ++iter){
    OMKey omkey = iter->first;
    log_trace("OM: %s",omkey.str().c_str());    
    cout<<"OM: "<<omkey.str().c_str()<<endl;
    ENSURE(geo_sel_utils::exists(omkey.GetString(),goodStrings_));
    ENSURE(!geo_sel_utils::exists(omkey.GetString(),strings_exclude_list));
  }

  I3StationGeoMap::const_iterator siter;
  for(siter = geoPtr->stationgeo.begin();
      siter != geoPtr->stationgeo.end(); ++siter){
    int station = siter->first;
    log_trace("Station: %d",station);    
    ENSURE(geo_sel_utils::exists(station,goodStrings_));
    ENSURE(!geo_sel_utils::exists(station,stations_exclude_list));
  }
  
  PushFrame(frame,"OutBox");
  
  log_debug("Added selection.");
}


