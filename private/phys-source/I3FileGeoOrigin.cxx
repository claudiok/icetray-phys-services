#include "phys-source/I3FileGeoOrigin.h"
#include "dataclasses/I3OMGeoAMANDA.h"
#include "dataclasses/I3OMGeoIceCube.h"
#include "icetray/I3TrayHeaders.h"

void I3FileGeoOrigin::Fatal(const string& message)
{
  log_fatal(message.c_str());
  throw I3TrayException();
}

Time I3FileGeoOrigin::NextGeometryTime()
{
  return nextTime_;
}

GeometryPair I3FileGeoOrigin::GetGeometry(Time time)
{
  GeometryPair p;
  p.geometry = I3GeometryPtr(new I3Geometry());
  p.header = I3GeometryHeaderPtr(new I3GeometryHeader());
  FillGeometryFromFile(*p.geometry,*p.header);
  nextTime_ = INFINITY;
  return p;
}

void I3FileGeoOrigin::FillGeometryFromFile(I3Geometry& Geometry, 
						 I3GeometryHeader& GeometryHeader){
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
  
  while(AmaGeoInFile>>string_F>>tube_F>>x_F>>y_F>>z_F>>orientation_F)
    {    
      I3OMGeoAMANDAPtr amanda = I3OMGeoAMANDAPtr(new I3OMGeoAMANDA());
      Geometry.GetInIceGeometry()[OMKey(string_F,tube_F)] = amanda;
      
      amanda->SetPos(x_F * I3Units::m,
		     y_F * I3Units::m,
		     z_F * I3Units::m);
      if (orientation_F == -1) amanda->SetOrientation(I3OMGeo::Down);
      else if (orientation_F == 1) amanda->SetOrientation(I3OMGeo::Up);
      amanda->SetArea(0.0284 * I3Units::m2);
      amanda->SetRelativeQE(1.0);
    }
  
  while(I3GeoInFile>>string_F>>tube_F>>x_F>>y_F>>z_F>>orientation_F)
    {
      I3OMGeoIceCubePtr icecube = I3OMGeoIceCubePtr(new I3OMGeoIceCube());
      Geometry.GetInIceGeometry()[OMKey(string_F,tube_F)] = icecube;
      
      icecube->SetPos(x_F * I3Units::m,
		      y_F * I3Units::m,
		      z_F * I3Units::m);
      icecube->SetOrientation(I3OMGeo::Down); 
      icecube->SetArea(0.0444 * I3Units::m2);
      icecube->SetRelativeQE(1.0);
    }
  
  AmaGeoInFile.close();
  I3GeoInFile.close();
  
  //Integrate into DB Access part too?
  log_warn("I3Db::FillFileGeometry: ATTENTION: No date set in header or date set to 0.")
    GeometryHeader.SetJulianDay(0);
  GeometryHeader.SetSec(0);
  GeometryHeader.SetNanoSec(0);  
  GeometryHeader.SetArrayName("FullIceCube+Amanda");
}

