/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3GCDFileGeometryService.h 15038 2006-01-30 22:47:23Z pretz $
 *
 * @file I3GCDFileGeometryService.h
 * @version $Revision:$
 * @date $Date: 2006-01-30 17:47:23 -0500 (Mon, 30 Jan 2006) $
 * @author pretz
 */

#ifndef I3GCDFILESOURCE_H
#define I3GCDFILESOURCE_H

#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <interfaces/I3GeometryService.h>
#include <interfaces/I3CalibrationService.h>
#include <interfaces/I3DetectorStatusService.h>

/**
 * @brief A I3GeometryOrigin which reads the geometry from a GCD File
 */
class I3GCDFileGeometryService : public I3GeometryService
{
 private:
  std::string filename_;
  I3GeometryConstPtr geo_;
 public:
  I3GCDFileGeometryService(const std::string& icefile) :
  filename_(icefile)     
    {}
  virtual ~I3GCDFileGeometryService(){}
  I3GeometryConstPtr GetGeometry(I3Time time);
};

/**
 * @brief A I3CalibrationOrigin which reads the geometry from a GCD File
 */
class I3GCDFileCalibrationService : public I3CalibrationService
{
 private:
  std::string filename_;
  I3CalibrationConstPtr cal_;
 public:
 I3GCDFileCalibrationService(const std::string& icefile) :
  filename_(icefile) 
  {}
  virtual ~I3GCDFileCalibrationService(){}
  I3CalibrationConstPtr GetCalibration(I3Time time);
};

/**
 * @brief A I3DetectorStatusOrigin which reads the geometry from a GCD File
 */
class I3GCDFileDetectorStatusService : public I3DetectorStatusService
{
 private:
  std::string filename_;
  I3DetectorStatusConstPtr stat_;
 public:
  I3GCDFileDetectorStatusService(const std::string& icefile) :
    filename_(icefile) 
    {}
  virtual ~I3GCDFileDetectorStatusService(){}
  I3DetectorStatusConstPtr GetDetectorStatus(I3Time time);
};

#endif
