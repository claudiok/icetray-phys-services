/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3CalibrateStatusModule.h 6290 2005-04-18 21:12:56Z pretz $
 *
 * @file I3CalibrateStatusModule.h
 * @brief Declaration of the I3CalibrateStatus class
 * @version $Revision: 1.2 $
 * @date $Date: 2005-04-18 17:12:56 -0400 (Mon, 18 Apr 2005) $
 * @author pretz
 */

#ifndef I3CALIBRATESTATUSMODULE_H
#define I3CALIBRATESTATUSMODULE_H

#include "icetray/I3Module.h"
#include "dataclasses/status/I3RawDOMStatus.h"
#include "dataclasses/status/I3CalibratedDOMStatus.h"
#include "dataclasses/calibration/I3DOMCalibration.h"

/**
 * @brief Small icetray module which takes the calibration and the 
 * detector status and assigns some values to the I3CalibratedDOMStatus
 * structures based on the I3DOMCalibration and the I3RawDOMStatus
 */
class I3CalibrateStatusModule : public I3Module
{
 public:
  I3CalibrateStatusModule(const I3Context& context);

  void DetectorStatus(I3FramePtr frame);

  static void DoTheCalibration(I3RawDOMStatusPtr rawstatus,
			       I3CalibratedDOMStatusPtr calibratedstatus,
			       I3DOMCalibrationPtr calib);
};

#endif
