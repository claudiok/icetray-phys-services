#ifndef I3PHYSICSSOURCE_H
#define I3PHYSICSSOURCE_H

#include "dataclasses/I3Event.h"
#include "dataclasses/I3EventHeader.h"

#include "icetray/I3Source.h"

#include "phys-source/I3EventOrigin.h"

class I3PhysicsSource : public I3Source
{
 public:
  I3PhysicsSource(I3Context& context);

  void SendEvent();

  void Process();

  I3EventOrigin& GetEventFactory();

 private:
  EventPair currentEvent_;
  

};

#endif
