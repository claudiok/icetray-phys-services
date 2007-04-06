/// This file contains tools for manipulating Geometries, to take out various
/// bad/good/desired/notdesired OM's.

// Available functions:
//---------------------------------------
// GeoFromPulseSeries:   Include OM's only from a PulseSeries
// GeoFromPulseSeriesWithNeighbors:   Inlucde OM's only from a PulseSeries,
//      plus their local-coincidence neighbors (whether hit or not hit)
// GeoWithoutBadOMs:     Exclude a list of bad OM's
// GeoWithoutIceTop:     Exclude all IceTop OM's
// GeoIceTopOnly:        Exclude all InIce OM's
//---------------------------------------

#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/I3Vector.h"
#include "dataclasses/OMKey.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3DOMLaunch.h"
#include "dataclasses/physics/I3Waveform.h"
#include "dataclasses/physics/I3AMANDAAnalogReadout.h"

// this #define helps to decide in flat-ntuple (and other user code) whether
// the geotrimmers can only be used for recopulses or just for practically all
// domdata-types.
#define NEW_GEOTRIMMERS 1

namespace I3GeoTrimmers
{

  /// Utility function 
  void AddMeToTheMap(OMKey mykey, I3OMGeo me, I3OMGeoMapPtr themap) {
    // is it already in the map?
    if (themap->find(mykey)!=themap->end()) log_debug("It's already in there.");
    else 
      (*themap)[mykey]=me;
  }


/// Create a reduced geometry containing only the hit OMs.
/// Currently use OMs which appear as keys in pulseseries_; maybe it should
/// be made possible to use DOMLaunchSeries or AMANDAAnalogReadout
/// maps instead...

template <class omdatamap>
I3OMGeoMapPtr GeoFromEventData(const I3OMGeoMap &input_geo,
                               const omdatamap &datamap ){
  // The output
  I3OMGeoMapPtr output_geoptr=I3OMGeoMapPtr(new I3OMGeoMap);

  // The loop
  typename omdatamap::const_iterator ipulse;
  for (ipulse=datamap.begin(); ipulse!=datamap.end(); ipulse++) {
    I3OMGeoMap::const_iterator i_omgeo=input_geo.find(ipulse->first);
    if (i_omgeo==input_geo.end())
      log_warn("OM %d/%d found in pulse series, but not in geometry!",
		ipulse->first.GetString(), ipulse->first.GetOM());
    else 
      //(*output_geoptr)[ipulse->first]=i_omgeo->second;
      AddMeToTheMap(ipulse->first,i_omgeo->second,output_geoptr);
  }
  return output_geoptr;
}

I3OMGeoMapPtr GeoFromPulseSeries(const I3OMGeoMap &input_geo,
                                 const I3RecoPulseSeriesMap &psm) {
    return GeoFromEventData(input_geo,psm);
}
I3OMGeoMapPtr GeoFromDOMLaunchSeries(const I3OMGeoMap &input_geo,
                                     const I3DOMLaunchSeriesMap &dlsm) {
    return GeoFromEventData(input_geo,dlsm);
}
I3OMGeoMapPtr GeoFromWFSeries(const I3OMGeoMap &input_geo,
                              const I3WaveformSeriesMap &wfsm) {
    return GeoFromEventData(input_geo,wfsm);
}
I3OMGeoMapPtr GeoFromAMANDAAnalogReadout(const I3OMGeoMap &input_geo,
                              const I3AMANDAAnalogReadoutMap &aarm) {
    return GeoFromEventData(input_geo,aarm);
}

/// Create a reduced geometry containing only the hit OMs.
/// Currently use OMs which appear as keys in pulseseries_; maybe it should
/// be made possible to use DOMLaunchSeries or AMANDAAnalogReadout
/// maps instead...
I3OMGeoMapPtr GeoFromPulseSeriesWithNeighbors(I3OMGeoMap input_geo, I3RecoPulseSeriesMap psm) {

  // The output
  I3OMGeoMapPtr output_geoptr=I3OMGeoMapPtr(new I3OMGeoMap);

  // The loop
  I3RecoPulseSeriesMap::const_iterator ipulse;
  for (ipulse=psm.begin(); ipulse!=psm.end(); ipulse++) {
    I3OMGeoMap::const_iterator i_omgeo=input_geo.find(ipulse->first);
    if (i_omgeo==input_geo.end())
      log_warn("OM %d/%d found in pulse series, but not in geometry!",
		ipulse->first.GetString(), ipulse->first.GetOM());
    else {
      AddMeToTheMap(ipulse->first,i_omgeo->second,output_geoptr);

      // Find its neighbors...
      int istring = i_omgeo->first.GetString();
      int iom = i_omgeo->first.GetOM();
      // Neighbor up:
      I3OMGeoMap::const_iterator found_up=input_geo.find(OMKey(istring,iom-1));
      if ((found_up!=input_geo.end()) &&
	  (found_up->second.omtype == i_omgeo->second.omtype))
	AddMeToTheMap(found_up->first,found_up->second,output_geoptr);
      // Neighbor down:
      I3OMGeoMap::const_iterator found_down=input_geo.find(OMKey(istring,iom+1));
      if ((found_down!=input_geo.end()) &&
	  (found_down->second.omtype == i_omgeo->second.omtype))
	AddMeToTheMap(found_down->first,found_down->second,output_geoptr);
    }
  }
  return output_geoptr;
  }

/// Create a reduced geometry in which Bad OM's have been removed.
I3OMGeoMapPtr GeoWithoutBadOMs(I3OMGeoMap input_geo, I3VectorOMKey badomlist) {

  // The output
  I3OMGeoMapPtr output_geoptr=I3OMGeoMapPtr(new I3OMGeoMap(input_geo));

  // Remove Bad OM's from the duplicate geometry which will be used.
  I3VectorOMKey::iterator ib;
  for(ib = badomlist.begin(); ib != badomlist.end(); ib++) {
    if (output_geoptr->find(*ib) != output_geoptr->end())
      output_geoptr->erase(*ib);
    else 
      log_warn("Your bad OM %d %d is not in the geometry", 
	       ib->GetString(), ib->GetOM());
  }
  return output_geoptr;
}


/// Create a reduced geometry in which all IceTop DOM's have been removed.
I3OMGeoMapPtr GeoWithoutIceTop(I3OMGeoMap input_geo) {

  I3VectorOMKey badicetop;  
  for (int istr=1; istr<=80; istr++)
    for (int iom=61; iom<=64; iom++)
      if (input_geo.find(OMKey(istr,iom)) != input_geo.end())
	badicetop.push_back(OMKey(istr,iom));
  

  return GeoWithoutBadOMs(input_geo, badicetop);
}

/// Create a reduced geometry in which only IceTop DOM's are included.
I3OMGeoMapPtr GeoIceTopOnly(I3OMGeoMap input_geo) {

  I3RecoPulseSeriesMap goodicetop;
  I3RecoPulse junkpulse;
  for (int istr=1; istr<=80; istr++)
    for (int iom=61; iom<=64; iom++)
      if (input_geo.find(OMKey(istr,iom)) != input_geo.end())
	goodicetop[OMKey(istr,iom)].push_back(junkpulse);

  return GeoFromPulseSeries(input_geo, goodicetop);
}


/////////////////// DUPLICATE VERSIONS which are for I3Geometry
/////////////////// rather than I3OMGeoMap
I3GeometryPtr GeoFromPulseSeries(I3Geometry input_geo, I3RecoPulseSeriesMap psm) {
  I3GeometryPtr output_geoptr=I3GeometryPtr(new I3Geometry(input_geo));
  output_geoptr->omgeo = *(GeoFromPulseSeries(input_geo.omgeo, psm));
  return output_geoptr;
}
I3GeometryPtr GeoFromPulseSeriesWithNeighbors(I3Geometry input_geo, I3RecoPulseSeriesMap psm) {
  I3GeometryPtr output_geoptr=I3GeometryPtr(new I3Geometry(input_geo));
  output_geoptr->omgeo = *(GeoFromPulseSeriesWithNeighbors(input_geo.omgeo, psm));
  return output_geoptr;
}
I3GeometryPtr GeoWithoutBadOMs(I3Geometry input_geo, I3VectorOMKey badomlist) {
  I3GeometryPtr output_geoptr=I3GeometryPtr(new I3Geometry(input_geo));
  output_geoptr->omgeo = *(GeoWithoutBadOMs(input_geo.omgeo, badomlist));
  return output_geoptr;
}
I3GeometryPtr GeoWithoutIceTop(I3Geometry input_geo) {
  I3GeometryPtr output_geoptr=I3GeometryPtr(new I3Geometry(input_geo));
  output_geoptr->omgeo = *(GeoWithoutIceTop(input_geo.omgeo));
  return output_geoptr;
}
I3GeometryPtr GeoIceTopOnly(I3Geometry input_geo) {
  I3GeometryPtr output_geoptr=I3GeometryPtr(new I3Geometry(input_geo));
  output_geoptr->omgeo = *(GeoIceTopOnly(input_geo.omgeo));
  return output_geoptr;
}





} //end of namespace
