/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DetectorStatusService.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3DETECTORSTATUSSERVICE_H
#define I3DETECTORSTATUSSERVICE_H

#include <icetray/I3FrameObject.h>
#include <icetray/I3DefaultName.h>

#include "phys-services/I3TimeRange.h"
#include "dataclasses/status/I3DetectorStatus.h"
#include "dataclasses/Utility.h"

/**
 * @brief Produces I3DetectorStatus and I3DetectorStatus Header
 * objects given a I3Time.  Intended to be an icetray service 
 * which provides the detector status information
 */
class I3DetectorStatusService
{
 public:
  virtual I3DetectorStatusConstPtr GetDetectorStatus(I3Time time) = 0;
};

I3_DEFAULT_NAME(I3DetectorStatusService);
I3_POINTER_TYPEDEFS(I3DetectorStatusService);

#endif
