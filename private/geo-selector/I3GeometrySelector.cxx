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
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3InIceGeometry.h"
#include "dataclasses/OMKey.h"
#include <iostream>
#include <sstream>

I3_MODULE(I3GeometrySelector);

using namespace std;

I3GeometrySelector::I3GeometrySelector(const I3Context& ctx) : 
  I3PhysicsModule(ctx),
  stringsToUse_("-19:80"),
  stringsToExclude_("")

{
    AddOutBox("OutBox");

    AddParameter("StringsToUse", 
		 "The strings that should be included", 
		 stringsToUse_);
    AddParameter("StringsToExclude", 
		 "The strings that should be excluded", 
		 stringsToExclude_);
}

I3GeometrySelector::~I3GeometrySelector() {
}

// transitions
void I3GeometrySelector::Configure() {
  GetParameter("StringsToUse",stringsToUse_);
  GetParameter("StringsToExclude",stringsToExclude_);

  if(!geo_sel_utils::good_input(stringsToUse_)) 
    log_fatal("couldn't parse %s",stringsToUse_.c_str());
  if(!geo_sel_utils::good_input(stringsToExclude_)) 
    log_fatal("couldn't parse %s",stringsToExclude_.c_str());

  goodStrings_ = geo_sel_utils::make_good_strings(stringsToUse_, stringsToExclude_);
}

void I3GeometrySelector::Geometry(I3Frame& frame) {

  log_debug("Entering Geometry method.");
  
  // Get the event information out of the Frame
  I3GeometryPtr geoPtr = frame.Get<I3GeometryPtr>("Geometry");
  if(!geoPtr) log_fatal("Couldn't get geometry");
  I3InIceGeometry& inicegeo = geoPtr->GetInIceGeometry();

  log_trace("***before*** inicegeo.count(): %zu",inicegeo.size());

  I3InIceGeometry new_geo; //making a new geometry
  //erasing is too problematic
  for(I3InIceGeometry::iterator iter = inicegeo.begin();
      iter != inicegeo.end(); ++iter){
    OMKey omkey = iter->first;
    if(inicegeo.count(omkey)>1) log_error("***how the hell did that happen?***");
    if(geo_sel_utils::exists(omkey.GetString(),goodStrings_))
      new_geo[omkey] = iter->second;
  }
  //swap 'em
  geoPtr->GetInIceGeometry() = new_geo;

  log_trace("***after*** inicegeo.count(): %zu",geoPtr->GetInIceGeometry().size());

  PushFrame(frame,"OutBox");  
}
