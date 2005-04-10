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
 * @brief An I3Source which uses abstract factory
 * interfaces to get events, calibration and geometries
 * from.
 * 
 * Since this class is abstract, one has to write a subclass
 * with the pure virtual methods overridden to get something that
 * works
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3UberSource : public I3Source
{
 public:
  I3UberSource(I3Context& ctx);

  enum Stream {NONE,EVENT,GEOMETRY,CALIBRATION,DETECTORSTATUS};
  
  void Process();

  I3EventOrigin& GetEventOrigin();

  I3GeometryOrigin& GetGeometryOrigin();

  I3CalibrationOrigin& GetCalibrationOrigin();
  
  I3DetectorStatusOrigin& GetDetectorStatusOrigin();

 private:
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
