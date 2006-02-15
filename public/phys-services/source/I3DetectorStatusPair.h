#ifndef I3DETECTORSTATUSPAIR_H
#define I3DETECTORSTATUSPAIR_H

#include "dataclasses/status/I3DetectorStatus.h"

/**
 * @brief Dumb struct for holding an I3DetectorStatus and its 
 * I3DetectorStatusHeader
 */
struct DetectorStatusPair
{
  I3DetectorStatusPtr status;

  operator bool()
  {
    if(status)
      return true;
    return false;
  }
};


#endif
