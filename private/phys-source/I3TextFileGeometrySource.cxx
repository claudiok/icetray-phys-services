#include "phys-services/source/I3TextFileGeometrySource.h"

#include "dataclasses/geometry/I3OMGeo.h"
#include "dataclasses/geometry/I3StationMap.h"
#include "dataclasses/geometry/I3SurfModuleGeo.h"
#include "icetray/I3TrayHeaders.h"

#include <fstream>

I3_MODULE(I3TextFileGeometrySource);

I3TextFileGeometrySource::I3TextFileGeometrySource(const I3Context& context) :
  I3GeometrySource(context)
{
    AddParameter("AmandaGeoFile",
		 "Geometry file for the AMANDA detector",
		 amaGeoFile_);
    AddParameter("IceCubeGeoFile",
		 "Geometry file for the IceCube detector",
		 icecubeGeoFile_);
}

void I3TextFileGeometrySource::Configure()
{
    GetParameter("AmandaGeoFile",amaGeoFile_);
    GetParameter("IceCubeGeoFile",icecubeGeoFile_);
}

void I3TextFileGeometrySource::FillGeometry(I3Geometry& Geometry, 
					   I3GeometryHeader& GeometryHeader)
{
  
    ifstream AmaGeoInFile;	
    ifstream I3GeoInFile;		
    log_warn("I3TextFileGeometrySource: Reading IceCube Geometry from file");
  
    AmaGeoInFile.open(amaGeoFile_.c_str(), ifstream::in); 	
    I3GeoInFile.open(icecubeGeoFile_.c_str(), ifstream::in); 
  
  //Did the files open correctly?
    if (AmaGeoInFile.fail())
	log_fatal("The specified AMANDA geometry file does not exist "
		  "or did not want to be opened!");
    if (I3GeoInFile.fail())
	log_fatal("The specified IceCube geometry file does not exist "
		  "or did not want to be opened!");	
  
    log_info("FILES opened successfully. Getting the geometry "
	     "and filling it into the frame");
   
    int string_F;
    int tube_F;
    int orientation_F;		
    double x_F, y_F, z_F;
  
    while(AmaGeoInFile>>string_F>>tube_F>>x_F>>y_F>>z_F>>orientation_F)
    {    
	I3OMGeoPtr amanda = I3OMGeoPtr(new I3OMGeo());
	Geometry.GetInIceGeometry()[OMKey(string_F,tube_F)] = amanda;
      
	amanda->SetPos(x_F * I3Units::m,
		       y_F * I3Units::m,
		       z_F * I3Units::m);

	if (orientation_F == -1) 
	    amanda->SetOrientation(I3OMGeo::Down);
	else if (orientation_F == 1) 
	    amanda->SetOrientation(I3OMGeo::Up);
      
	amanda->SetArea(0.0284 * I3Units::m2);
	amanda->SetRelativeQE(1.0);
    }
  
    while(I3GeoInFile>>string_F>>tube_F>>x_F>>y_F>>z_F>>orientation_F)
    {
	if(tube_F<61)
	{
	    I3OMGeoPtr icecube = I3OMGeoPtr(new I3OMGeo());
	    Geometry.GetInIceGeometry()[OMKey(string_F,tube_F)] = icecube;
      
	    icecube->SetPos(x_F * I3Units::m,
			    y_F * I3Units::m,
			    z_F * I3Units::m);
       
	    icecube->SetOrientation(I3OMGeo::Down); 
	    icecube->SetArea(0.0444 * I3Units::m2);
	    icecube->SetRelativeQE(1.0);
	}

	else
	{
	    I3StationMap &station_map = Geometry.GetIceTopGeometry().GetStationMap();
	    if(station_map.find(string_F)==station_map.end()) 
	    {
		station_map[string_F] = I3StationGeoPtr(new I3StationGeo);
		station_map[string_F]->push_back(I3SurfModuleGeoPtr(new I3SurfModuleGeo()));
		station_map[string_F]->push_back(I3SurfModuleGeoPtr(new I3SurfModuleGeo()));
	    }

	    I3OMGeoPtr icecube = I3OMGeoPtr(new I3OMGeo());
	    switch(tube_F)
	    {
	    case 61:
	    case 62: (*(*station_map[string_F])[0])[OMKey(string_F, tube_F)] = icecube; break;
	    case 63:
	    case 64: (*(*station_map[string_F])[1])[OMKey(string_F, tube_F)] = icecube; break;
	    default: log_fatal("Got a wrong tube number.");
	    }

	    icecube->SetPos(x_F * I3Units::m,
			    y_F * I3Units::m,
			    z_F * I3Units::m);
	    icecube->SetOrientation(I3OMGeo::Down); 
	    icecube->SetArea(0.0444 * I3Units::m2);
	    icecube->SetRelativeQE(1.0);
	}
    }
  
    AmaGeoInFile.close();
    I3GeoInFile.close();
  
    GeometryHeader.SetArrayName("FullIceCube+Amanda");
}

GeometryPair I3TextFileGeometrySource::GetGeometry(I3Time eventTime)
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
