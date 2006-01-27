/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DetectorStatusOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3DETECTORSTATUSORIGIN_H
#define I3DETECTORSTATUSORIGIN_H

#include "I3TimeRange.h"
#include "dataclasses/status/I3DetectorStatus.h"
#include "dataclasses/status/I3DetectorStatusHeader.h"
#include "dataclasses/StoragePolicy.h"

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

/**
 * @brief Produces I3DetectorStatus and I3DetectorStatus Header
 * objects given a I3Time.  Intended to be an icetray service 
 * which provides the detector status information
 */
class I3DetectorStatusOrigin
{
 public:
  static const char* DefaultName() { return "DetectorStatusOrigin";}
  virtual DetectorStatusPair GetDetectorStatus(I3Time time) = 0;
};

typedef shared_ptr<I3DetectorStatusOrigin> I3DetectorStatusOriginPtr;

#endif
