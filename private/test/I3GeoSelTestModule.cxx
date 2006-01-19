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
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3InIceGeometry.h"
#include "dataclasses/OMKey.h"
#include <iostream>
#include <sstream>

I3_MODULE(I3GeoSelTestModule);

using namespace std;

I3GeoSelTestModule::I3GeoSelTestModule(const I3Context& ctx) : 
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

I3GeoSelTestModule::~I3GeoSelTestModule() {
}

// transitions
void I3GeoSelTestModule::Configure() {
  GetParameter("StringsToUse",stringsToUse_);
  GetParameter("StringsToExclude",stringsToExclude_);

  if(!geo_sel_utils::good_input(stringsToUse_)) 
    log_fatal("couldn't parse %s",stringsToUse_.c_str());
  if(!geo_sel_utils::good_input(stringsToExclude_)) 
    log_fatal("couldn't parse %s",stringsToExclude_.c_str());

  cout<<"stringsToUse_"<<stringsToUse_<<endl;

  goodStrings_ = geo_sel_utils::make_good_strings(stringsToUse_, stringsToExclude_);
}

void I3GeoSelTestModule::Geometry(I3Frame& frame) {

  log_debug("Entering Geometry method.");
  
  // Get the event information out of the Frame
  I3GeometryPtr geoPtr = frame.Get<I3GeometryPtr>("Geometry");
  if(!geoPtr) log_fatal("Couldn't get geometry");
  I3InIceGeometry& inicegeo = geoPtr->GetInIceGeometry();

  //loop through the in ice geometry and make sure that
  //1) All the DOMs that exist in the geometry are in goodStrings_
  //2) None of the DOMs correspond to string in stringsToExclude_

  log_error("inicegeo.count(): %zu",inicegeo.size());

  cout<<"goodStrings_.size(): "<<goodStrings_.size()<<endl;
  for(vector<int>::iterator iter = goodStrings_.begin(); iter != goodStrings_.end(); ++iter)
    cout<<*iter<<" ";
  cout<<endl;

  cout<<endl;
  std::vector<int> exclude_list = geo_sel_utils::parse_string_list(stringsToExclude_);
  for(I3InIceGeometry::iterator iter = inicegeo.begin();
      iter != inicegeo.end(); ++iter){
    OMKey omkey = iter->first;
    cout<<omkey<<" ";
    ENSURE(geo_sel_utils::exists(omkey.GetString(),goodStrings_));
    ENSURE(!geo_sel_utils::exists(omkey.GetString(),exclude_list));
  }
  
  PushFrame(frame,"OutBox");
  
  log_debug("Added selection.");
}


