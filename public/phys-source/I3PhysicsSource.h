#ifndef I3PHYSICSSOURCE_H
#define I3PHYSICSSOURCE_H

#include "I3EventFactory.h"
#include "I3CalibrationFactory.h"
#include "I3GeometryFactory.h"

#include "icetray/I3Source.h"

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
 */
class I3PhysicsSource : public I3Source
{
 public:
  I3PhysicsSource(I3Context& ctx);

  enum Stream {NONE,EVENT,GEOMETRY,CALIBRATION};
  
  void Process();

  I3EventFactory& GetEventFactory();

  I3GeometryFactory& GetGeometryFactory();

  I3CalibrationFactory& GetCalibrationFactory();

 private:
  Stream NextStream();

  void SendEvent();
  
  void SendGeometry();

  void SendCalibration();

  void SendAll(I3Frame& frame);

 private:
  EventPair currentEvent_;
  GeometryPair currentGeometry_;
  CalibrationPair currentCalibration_;
};


#endif
