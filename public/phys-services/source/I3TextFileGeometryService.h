/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3TextFileGeometryService.h 15038 2006-01-30 22:47:23Z pretz $
 *
 * @file I3TextFileGeometryService.h
 * @version $Revision:$
 * @date $Date: 2006-01-30 17:47:23 -0500 (Mon, 30 Jan 2006) $
 * @author pretz
 */

#ifndef I3TEXTFILEGEOMETRYSOURCE_H
#define I3TEXTFILEGEOMETRYSOURCE_H

#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <interfaces/I3GeometryService.h>


/**
 * @brief A I3GeometryOrigin which reads the geometry from two files,
 * one for icecube and one for inice
 */
class I3TextFileGeometryService : public I3GeometryService
{
  std::string fAmaGeoInputFile;
  std::string fI3GeoInputFile;
 public:
  I3TextFileGeometryService(const std::string& amafile,const std::string& icefile) :
    fAmaGeoInputFile(amafile),
    fI3GeoInputFile(icefile) 
    {}
  virtual ~I3TextFileGeometryService(){}

  I3GeometryConstPtr GetGeometry(I3Time time);
 private:
  void Fatal(const std::string& message);

  void FillGeometryFromFile(I3Geometry& geo);
};

typedef boost::shared_ptr<I3TextFileGeometryService> I3TextFileGeometryServicePtr;

#endif
