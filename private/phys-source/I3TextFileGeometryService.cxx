#include "phys-services/source/I3TextFileGeometryService.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/geometry/I3OMGeo.h"
#include "icetray/I3TrayHeaders.h"

void I3TextFileGeometryService::Fatal(const string& message)
{
  log_fatal(message.c_str());
}

I3GeometryConstPtr I3TextFileGeometryService::GetGeometry(I3Time time)
{
  I3GeometryPtr geometry = I3GeometryPtr(new I3Geometry());
  FillGeometryFromFile(*geometry);
  I3Time start;
  start.SetDaqTime(0,0);
  I3Time end;
  end.SetDaqTime(3000,0);
  geometry->startTime = start;
  geometry->endTime = end;
  return geometry;
}

void I3TextFileGeometryService::FillGeometryFromFile(I3Geometry& Geometry)
{
  //
  // NB: This code was cut and pasted with minor tweaks from the I3Db code.
  // The author is Georges Kohnen
  //
  // Any bugs are probably my fault, and any praises should
  // probably go to him. -JPretz
  //
  
  //Create GeoInFile
  ifstream AmaGeoInFile;	
  ifstream I3GeoInFile;		
  log_warn("I3Db: Reading IceCube Geometry from file");
  
  //Open the files ama.geo and icecube.geo
  AmaGeoInFile.open(fAmaGeoInputFile.c_str(), ifstream::in); 	
  I3GeoInFile.open(fI3GeoInputFile.c_str(), ifstream::in); 
  
  //Did the files open correctly?
  if (AmaGeoInFile.fail())
    Fatal("I3Db: The specified AMANDA geometry file does not exist "
	  "or did not want to be opened!");
  if (I3GeoInFile.fail())
    Fatal("I3Db: The specified IceCube geometry file does not exist "
	  "or did not want to be opened!");	
  
  log_info("I3Db: FILES opened successfully. Getting the geometry "
	   "and filling it into the frame");
  log_info("Coordinates of OM's in meters \n\n");
  
  //The variables declared hereafter are followed by "_F" to denote 
  //that they serve the
  //"Fill Geometry From File" method and not the DB Access method...
  
  int string_F;
  int tube_F;
  int orientation_F;		
  double x_F, y_F, z_F;

  // Changed all objects that were I3InIceGeometry (the vars amanda and icecube)  to the I3Geometry's omgeo map.
  
  while(AmaGeoInFile>>string_F>>tube_F>>x_F>>y_F>>z_F>>orientation_F)
    {    
      I3OMGeoPtr amanda = I3OMGeoPtr(new I3OMGeo());
      Geometry.omgeo[OMKey(string_F, tube_F)] = *amanda;
      
      amanda->position.SetPosition(x_F * I3Units::m,
		     y_F * I3Units::m,
		     z_F * I3Units::m);
      if (orientation_F == -1) amanda->orientation = (I3OMGeo::Down);
      else if (orientation_F == 1) amanda->orientation = (I3OMGeo::Up);
      amanda->area = (0.0284 * I3Units::m2);
      amanda->omtype = I3OMGeo::AMANDA;
      //amanda->relativeQE = 1.0;
    }
  
  while(I3GeoInFile>>string_F>>tube_F>>x_F>>y_F>>z_F>>orientation_F)
    {
      if(tube_F<61)
      {
        I3OMGeoPtr icecube = I3OMGeoPtr(new I3OMGeo());
	Geometry.omgeo[OMKey(string_F, tube_F)] = *icecube;

        icecube->position.SetPosition(x_F * I3Units::m,
                        y_F * I3Units::m,
		        z_F * I3Units::m);
        icecube->orientation = (I3OMGeo::Down); 
        icecube->area = (0.0444 * I3Units::m2);
	icecube->omtype = I3OMGeo::IceCube;
        //icecube->relativeQE = 1.0;
      }
      else
      {
	I3StationGeoMap &station_geo = Geometry.stationgeo;
	//Initializes a new I3StationGeo Object if it does not already exist.
	//Condensed initialization into one step (originally created new vector
	//and added pushed two new TankGeo objects into it.
        if(station_geo.find(string_F)==station_geo.end()) 
        {
          station_geo[string_F] = I3StationGeo(2);
        }

        I3OMGeoPtr icecube = I3OMGeoPtr(new I3OMGeo());
	Geometry.omgeo[OMKey(string_F, tube_F)] = *icecube;
#warning Not sure this is needed with updated Geometry (TankGeo has no OMGeoPtr info
#if 0
        switch(tube_F)
        {
          case 61:
          case 62: (*(*station_map[string_F])[0])[OMKey(string_F, tube_F)] = icecube; break;
          case 63:
          case 64: (*(*station_map[string_F])[1])[OMKey(string_F, tube_F)] = icecube; break;
          default: Fatal("Got a wrong tube number.");
        }
#endif
        icecube->position.SetPosition(x_F * I3Units::m,
                        y_F * I3Units::m,
		        z_F * I3Units::m);
        icecube->orientation = (I3OMGeo::Down); 
        icecube->area = (0.0444 * I3Units::m2);
	icecube->omtype = I3OMGeo::IceTop;
        //icecube->relativeQE = 1.0;
      }
    }
  
  AmaGeoInFile.close();
  I3GeoInFile.close();
  
  //Integrate into DB Access part too?
  log_warn("I3Db::FillFileGeometry: ATTENTION: No date set in header or date set to 0.");
  
  I3Time time;
  time.SetModJulianTime(0,0,0.0);
  Geometry.startTime = time;
}

