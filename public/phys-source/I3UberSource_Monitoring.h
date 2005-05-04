/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3UberSource_Monitoring.h 7067 2005-04-28 15:04:38Z pretz $
 *
 * @file I3UberSource_Monitoring.h
 * @version $Revision:$
 * @date $Date: 2005-04-28 11:04:38 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#ifndef I3UBERSOURCE_MONITORING_H
#define I3UBERSOURCE_MONITORING_H

#include "I3MonitoringOrigin.h"
#include "I3CalibrationOrigin.h"
#include "I3GeometryOrigin.h"
#include "I3DetectorStatusOrigin.h"

#include "icetray/I3Source.h"

#include "dataclasses/I3Time.h"
#include "I3TimeRange.h"

/**
 * @brief An I3Source which uses abstract interfaces
 * interfaces to get events, calibration and geometries.
 * from.
 *
 * Uses the I3GeometryOrigin, the I3DetectorStatusOrigin, the
 * I3MonitoringOrigin, and the I3CalibrationOrigin interfaces
 *
 * If you don't like the idea of this being one module, you can
 * use the four modules I3PhysicsSource, I3GeometrySource, 
 * I3CalibrationSource, and I3DetectorStatusSource together instead.
 */
class I3UberSource_Monitoring : public I3Source
{
 public:
  I3UberSource_Monitoring(I3Context& ctx);

  void Process();

 private:

  enum Stream {NONE,EVENT,GEOMETRY,CALIBRATION,DETECTORSTATUS};

  I3MonitoringOrigin& GetMonitoringOrigin();

  I3GeometryOrigin& GetGeometryOrigin();

  I3CalibrationOrigin& GetCalibrationOrigin();
  
  I3DetectorStatusOrigin& GetDetectorStatusOrigin();

  Stream NextStream();

  void SendMonitoring();
  
  void SendGeometry();

  void SendCalibration();

  void SendDetectorStatus();

  void SendAll(I3Frame& frame);

  bool IsGeometryCurrent(I3Time time);
  
  bool IsCalibrationCurrent(I3Time time);

  bool IsDetectorStatusCurrent(I3Time time);

  void QueueUpMonitoring();
  
  I3Time NextMonitoringTime();
 private:
  MonitoringPair currentMonitoring_;
  GeometryPair currentGeometry_;
  I3TimeRange currentGeometryRange_;
  CalibrationPair currentCalibration_;
  I3TimeRange currentCalibrationRange_;
  DetectorStatusPair currentDetectorStatus_;
  I3TimeRange currentDetectorStatusRange_;
};


#endif
