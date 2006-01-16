#ifndef I3DETECTORSTATUSPAIR_H
#define I3DETECTORSTATUSPAIR_H

#include "dataclasses/status/I3DetectorStatus.h"
#include "dataclasses/status/I3DetectorStatusHeader.h"

/**
 * @brief Dumb struct for holding an I3DetectorStatus and its 
 * I3DetectorStatusHeader
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


#endif
