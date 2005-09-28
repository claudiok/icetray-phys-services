#ifndef I3DUMMYDETECTORSTATUSSOURCE_H
#define I3DUMMYDETECTORSTATUSSOURCE_H

#include "I3DetectorStatusSource.h"

class I3DummyDetectorStatusSource : public I3DetectorStatusSource
{
 public:
  I3DummyDetectorStatusSource(const I3Context& context);

  DetectorStatusPair GetDetectorStatus(I3Time eventTime);


};


#endif
