#ifndef I3FILEGEOORIGIN_H
#define I3FILEGEOORIGIN_H

#include "phys-source/I3GeometryOrigin.h"
#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>

using namespace std;

/**
 * @brief A I3GeometryOrigin which reads the geometry from two files,
 * one for icecube and one for inice
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3FileGeoOrigin : public I3GeometryOrigin
{
  string fAmaGeoInputFile;
  string fI3GeoInputFile;
 public:
  I3FileGeoOrigin(const string& amafile,const string& icefile) :
    fAmaGeoInputFile(amafile),
    fI3GeoInputFile(icefile) 
    {}
  virtual ~I3FileGeoOrigin(){}

  GeometryPair GetGeometry(I3Time time);
  I3TimeRange GetGeometryValidityRange(I3Time time);
 private:
  void Fatal(const string& message);

  void FillGeometryFromFile(I3Geometry& geo, I3GeometryHeader& header);
};

typedef boost::shared_ptr<I3FileGeoOrigin> I3FileGeoOriginPtr;

#endif
