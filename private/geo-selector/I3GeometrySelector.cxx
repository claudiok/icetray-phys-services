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
#include "phys-services/geo-selector/I3GeometrySelector.h"
#include "phys-services/geo-selector/GeoSelUtils.h"

// other headers
//  global header for all the IceTray stuff
#include "icetray/I3TrayHeaders.h"
/* headers for the dataclasses stuff */
#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/OMKey.h"
#include <iostream>
#include <sstream>

I3_MODULE(I3GeometrySelector);

using namespace std;

I3GeometrySelector::I3GeometrySelector(const I3Context& ctx) : 
  I3Module(ctx),
  stringsToUse_("-19:80"),
  stringsToExclude_(""),
  stationsToUse_("1:80"),
  stationsToExclude_(""),
  newGeometryName_("NewGeometry")
{
    AddOutBox("OutBox");

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
    AddParameter("NewGeometryName", 
		 "Name of the geometry that's going into the frame", 
		 newGeometryName_);
}

I3GeometrySelector::~I3GeometrySelector() {
}

// transitions
void I3GeometrySelector::Configure() {
  GetParameter("StringsToUse",stringsToUse_);
  GetParameter("StringsToExclude",stringsToExclude_);
  GetParameter("StationsToUse",stationsToUse_);
  GetParameter("StationsToExclude",stationsToExclude_);
  GetParameter("NewGeometryName",newGeometryName_);

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
}

void I3GeometrySelector::Geometry(I3FramePtr frame) {

  log_debug("Entering Geometry method.");
  
  // Get the event information out of the Frame
  I3GeometryConstPtr geoPtr = frame->Get<I3GeometryConstPtr>();
  if(!geoPtr) log_fatal("Couldn't get geometry");

  log_trace("***before*** geoPtr->omgeo.size(): %zu",geoPtr->omgeo.size());

  I3GeometryPtr new_geo(new I3Geometry); //making a new geometry

  new_geo->startTime = geoPtr->startTime;
  new_geo->endTime = geoPtr->endTime;

  //erasing is too problematic
  I3OMGeoMap::const_iterator iter;
  for(iter = geoPtr->omgeo.begin();
      iter != geoPtr->omgeo.end(); ++iter){
    OMKey omkey = iter->first;
    if(geoPtr->omgeo.count(omkey)>1) log_error("***how the hell did that happen?***");
    if(geo_sel_utils::exists(omkey.GetString(),goodStrings_))
      new_geo->omgeo[omkey] = iter->second;
  }

  I3StationGeoMap::const_iterator siter;
  for(siter = geoPtr->stationgeo.begin();
      siter != geoPtr->stationgeo.end(); ++siter){
    int station = siter->first;
    if(geoPtr->stationgeo.count(station)>1) log_error("***how the hell did that happen?***");
    if(geo_sel_utils::exists(station,goodStrings_))
      new_geo->stationgeo[station] = siter->second;
  }

  log_trace("***after*** geoPtr->omgeo().size(): %zu",geoPtr->omgeo.size());
  log_trace("***after*** geoPtr->stationgeo.size(): %zu",geoPtr->stationgeo.size());

  frame->Put(newGeometryName_,new_geo);

  PushFrame(frame,"OutBox");  
}
