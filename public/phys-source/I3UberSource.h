/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3UberSource.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3UBERSOURCE_H
#define I3UBERSOURCE_H

#include "I3EventOrigin.h"
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
 * I3EventOrigin, and the I3CalibrationOrigin interfaces
 *
 * If you don't like the idea of this being one module, you can
 * use the four modules I3PhysicsSource, I3GeometrySource, 
 * I3CalibrationSource, and I3DetectorStatusSource together instead.
 */
class I3UberSource : public I3Source
{
 public:
  I3UberSource(I3Context& ctx);

  void Process();

 private:

  enum Stream {NONE,EVENT,GEOMETRY,CALIBRATION,DETECTORSTATUS};

  I3EventOrigin& GetEventOrigin();

  I3GeometryOrigin& GetGeometryOrigin();

  I3CalibrationOrigin& GetCalibrationOrigin();
  
  I3DetectorStatusOrigin& GetDetectorStatusOrigin();

  Stream NextStream();

  void SendEvent();
  
  void SendGeometry();

  void SendCalibration();

  void SendDetectorStatus();

  void SendAll(I3Frame& frame);

  bool IsGeometryCurrent(I3Time time);
  
  bool IsCalibrationCurrent(I3Time time);

  bool IsDetectorStatusCurrent(I3Time time);

  void QueueUpEvent();
  
  I3Time NextEventTime();
 private:
  EventPair currentEvent_;
  GeometryPair currentGeometry_;
  I3TimeRange currentGeometryRange_;
  CalibrationPair currentCalibration_;
  I3TimeRange currentCalibrationRange_;
  DetectorStatusPair currentDetectorStatus_;
  I3TimeRange currentDetectorStatusRange_;
};


#endif
