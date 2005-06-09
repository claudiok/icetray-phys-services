/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3FileGeoOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3FILEGEOORIGIN_H
#define I3FILEGEOORIGIN_H

#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3GeometryHeader.h"
#include "phys-source/I3GeometrySource.h"
#include "dataclasses/I3Time.h"

using namespace std;

/**
 * @brief A class which reads the geometry from two files,
 * one for icecube and one for inice
 */
class I3FileGeoOrigin 
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
 private:
  void Fatal(const string& message);

  void FillGeometryFromFile(I3Geometry& geo, I3GeometryHeader& header);
};

typedef boost::shared_ptr<I3FileGeoOrigin> I3FileGeoOriginPtr;

#endif
