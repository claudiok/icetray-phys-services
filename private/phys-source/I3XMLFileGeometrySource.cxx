#include "phys-source/I3XMLFileGeometrySource.h"

#include "dataclasses/I3OMGeoAMANDA.h"
#include "dataclasses/I3OMGeoIceCube.h"
#include "dataclasses/I3StationMap.h"
#include "dataclasses/I3SurfModuleGeo.h"
#include "icetray/I3TrayHeaders.h"

I3XMLFileGeometrySource::I3XMLFileGeometrySource(I3Context& context) :
  I3GeometrySource(context)
{
    AddParameter("ICGeometryFile",
		 "Geometry file for the IceCube detector",
		 ICGeometryFile_);
}

void I3XMLFileGeometrySource::Configure()
{
    GetParameter("IceCubeGeometryFile", ICGeometryFile_);
}

void I3XMLFileGeometrySource::FillGeometry(I3Geometry& Geometry, 
					   I3GeometryHeader& GeometryHeader)
{}

GeometryPair I3XMLFileGeometrySource::GetGeometry(I3Time eventTime)
{
    GeometryPair p;
    p.geometry = I3GeometryPtr(new I3Geometry());
    p.header = I3GeometryHeaderPtr(new I3GeometryHeader());
    FillGeometry(*p.geometry,*p.header);
    I3Time start;
    start.SetDaqTime(0,0);
    I3Time end;
    end.SetDaqTime(3000,0);
    p.header->SetStartTime(start);
    p.header->SetEndTime(end);
    return p;
}
