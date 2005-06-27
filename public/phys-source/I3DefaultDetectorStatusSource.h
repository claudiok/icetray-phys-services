#ifndef I3DEFAULTDETECTORSTATUSSOURCE_H
#define I3DEFAULTDETECTORSTATUSSOURCE_H

#include "I3DetectorStatusSource.h"

class I3DefaultDetectorStatusSource : public I3DetectorStatusSource
{
 public:
  I3DefaultDetectorStatusSource(I3Context& context);

  DetectorStatusPair GetDetectorStatus(I3Time eventTime);


};


#endif
