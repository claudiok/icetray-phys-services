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
    if(geo_sel_utils::exists(omkey.GetString(),goodStrings_)){
      I3OMGeo om = iter->second;
      om.position.SetX(iter->second.position.GetX() + shiftX_);
      om.position.SetY(iter->second.position.GetY() + shiftY_);
      om.position.SetZ(iter->second.position.GetZ() + shiftZ_);
      log_trace("OLD POSITION:(%.2f,%.2f,%.2f)",
		iter->second.position.GetX(),
		iter->second.position.GetY(),
		iter->second.position.GetZ());
      log_trace("NEW POSITION:(%.2f,%.2f,%.2f)",
		om.position.GetX(),
		om.position.GetY(),
		om.position.GetZ());
      new_geo->omgeo[omkey] = om;
    }
  }

  I3StationGeoMap::const_iterator siter;
  for(siter = old_geo->stationgeo.begin();
      siter != old_geo->stationgeo.end(); ++siter){
    int station = siter->first;
    if(geo_sel_utils::exists(station,goodStations_)){
      I3StationGeo s = siter->second;
      vector<I3TankGeo>::iterator i = s.begin();
      for(; i != s.end(); i++){
	i->position.SetX(iter->second.position.GetX() + shiftX_);
	i->position.SetY(iter->second.position.GetY() + shiftY_);
	i->position.SetZ(iter->second.position.GetZ() + shiftZ_);
      }
      new_geo->stationgeo[station] = s;
    }
  }

  log_trace("***before*** old_geo->omgeo().size(): %zu",old_geo->omgeo.size());
  log_trace("***before*** old_geo->stationgeo.size(): %zu",old_geo->stationgeo.size());

  log_trace("***after*** new_geo->omgeo().size(): %zu",new_geo->omgeo.size());
  log_trace("***after*** new_geo->stationgeo.size(): %zu",new_geo->stationgeo.size());

  return new_geo;
}

