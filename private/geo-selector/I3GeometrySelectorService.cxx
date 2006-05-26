#include "phys-services/geo-selector/I3GeometrySelectorService.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/geometry/I3OMGeo.h"
#include "icetray/I3TrayHeaders.h"
#include "phys-services/geo-selector/GeoSelUtils.h"

I3GeometryConstPtr I3GeometrySelectorService::GetGeometry(I3Time time)
{
  //Get the default geometry from wherever
  I3GeometryConstPtr old_geo = geo_service_->GetGeometry(time);

  //This will be the new geometry
  I3GeometryPtr new_geo = I3GeometryPtr(new I3Geometry());

  new_geo->startTime = old_geo->startTime;
  new_geo->endTime = old_geo->endTime;

  //erasing is too problematic
  I3OMGeoMap::const_iterator iter;
  for(iter = old_geo->omgeo.begin();
      iter != old_geo->omgeo.end(); ++iter){
    OMKey omkey = iter->first;
    if(geo_sel_utils::exists(omkey.GetString(),goodStrings_))
      new_geo->omgeo[omkey] = iter->second;
  }

  I3StationGeoMap::const_iterator siter;
  for(siter = old_geo->stationgeo.begin();
      siter != old_geo->stationgeo.end(); ++siter){
    int station = siter->first;
    if(geo_sel_utils::exists(station,goodStrings_))
      new_geo->stationgeo[station] = siter->second;
  }

  log_trace("***before*** old_geo->omgeo().size(): %zu",old_geo->omgeo.size());
  log_trace("***before*** old_geo->stationgeo.size(): %zu",old_geo->stationgeo.size());

  log_trace("***after*** new_geo->omgeo().size(): %zu",new_geo->omgeo.size());
  log_trace("***after*** new_geo->stationgeo.size(): %zu",new_geo->stationgeo.size());

  return new_geo;
}

