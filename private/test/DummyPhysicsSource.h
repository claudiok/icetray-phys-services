#ifndef SIMPLEPHYSICSSOURCE_H
#define SIMPLEPHYSICSSOURCE_H

#include "phys-source/I3PhysicsSource.h"
#include "phys-source/I3DummyGeoFactory.h"
#include "phys-source/I3DummyCalibFactory.h"
#include "phys-source/I3DummyEventFactory.h"

class DummyPhysicsSource : public I3PhysicsSource
{
  I3DummyEventFactory eventFactory_;
  I3DummyGeoFactory geoFactory_;
  I3DummyCalibFactory calibFactory_;
 public:
  DummyPhysicsSource(I3Context& context) : I3PhysicsSource(context)
    {
    }

  I3EventFactory& GetEventFactory()
    {
      return eventFactory_;
    }

  I3GeometryFactory& GetGeometryFactory()
    {
      return geoFactory_;
    }

  I3CalibrationFactory& GetCalibrationFactory()
    {
      return calibFactory_;
    }
};

#endif
