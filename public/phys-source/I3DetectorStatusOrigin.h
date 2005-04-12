#ifndef I3DETECTORSTATUSORIGIN_H
#define I3DETECTORSTATUSORIGIN_H

#include "I3TimeRange.h"
#include "dataclasses/I3DetectorStatus.h"
#include "dataclasses/I3DetectorStatusHeader.h"
#include "dataclasses/StoragePolicy.h"

/**
 * @brief Dumb struct for holding an I3DetectorStatus and its 
 * I3DetectorStatusHeader
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
struct DetectorStatusPair
{
  I3DetectorStatusPtr status;
  I3DetectorStatusHeaderPtr header;

  operator bool()
  {
    if(status && header)
      return true;
    return false;
  }
};

/**
 * @brief Produces I3DetectorStatus objects given a time.
 * 
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3DetectorStatusOrigin
{
 public:
  static const char* DefaultName() { return "DetectorStatusOrigin";}
  virtual DetectorStatusPair GetDetectorStatus(I3Time time) = 0;
};

typedef shared_ptr<I3DetectorStatusOrigin> I3DetectorStatusOriginPtr;

#endif
