#ifndef I3DUMMYDETECTORSTATUSORIGIN_H
#define I3DUMMYDETECTORSTATUSORIGIN_H

#include "phys-source/I3DetectorStatusOrigin.h"
#include <cmath>
/**
 * @brief A simple implemetation of the I3DetectorStatusOrigin which serves
 * up one (empty) geometry
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3DummyDetectorStatusOrigin : public I3DetectorStatusOrigin
{
 public:
  DetectorStatusPair GetDetectorStatus(I3Time time);
};
 
typedef PtrPolicy<I3DummyDetectorStatusOrigin>::ThePolicy 
I3DummyDetectorStatusOriginPtr;

#endif
