/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3Muxer.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3MUXER_H
#define I3MUXER_H

#include "phys-services/I3EventService.h"
#include "phys-services/I3CalibrationService.h"
#include "phys-services/I3GeometryService.h"
#include "phys-services/I3DetectorStatusService.h"

#include "icetray/I3Frame.h"

#include "dataclasses/I3Time.h"
#include "phys-services/I3TimeRange.h"

/**
 * @brief An I3Module which uses abstract interfaces
 * interfaces to get events, calibration and geometries.
 * from.
 *
 * Uses the I3GeometryService, the I3DetectorStatusService, the
 * I3EventService, and the I3CalibrationService interfaces
 *
 * If you don't like the idea of this being one module, you can
 * use the four modules I3PhysicsSource, I3GeometrySource, 
 * I3CalibrationSource, and I3DetectorStatusSource together instead.
 */

class I3Muxer : public I3Module
{
 public:
  I3Muxer(const I3Context& ctx);

  void Process();

 private:

  enum Stream {NONE,EVENT,GEOMETRY,CALIBRATION,DETECTORSTATUS};

  Stream NextStream();

  void SendEvent();
  
  void SendGeometry();

  void SendCalibration();

  void SendDetectorStatus();

  bool IsGeometryCurrent(I3Time time);
  
  bool IsCalibrationCurrent(I3Time time);

  bool IsDetectorStatusCurrent(I3Time time);

  void QueueUpEvent();
  
  I3Time NextEventTime();

 private:

  I3Frame currentEvent_;
  bool currentEventQueued_;
  I3GeometryConstPtr currentGeometry_;
  I3TimeRange currentGeometryRange_;
  I3CalibrationConstPtr currentCalibration_;
  I3TimeRange currentCalibrationRange_;
  I3DetectorStatusConstPtr currentDetectorStatus_;
  I3TimeRange currentDetectorStatusRange_;
};


#endif
