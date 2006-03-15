/**
 * Definition of I3MCCalibrationFiller class
 *
 * copyright  (C) 2004
 * the IceCube collaboration
 * $Id: I3MCCalibrationFiller.h 6917 2005-04-26 02:56:37Z tmccauley $
 *
 * @file I3MCCalibrationFiller.h
 * @version $Revision: 1.14 $
 * @date $Date: 2005-04-25 22:56:37 -0400 (Mon, 25 Apr 2005) $
 * @author T. McCauley <tpmccauley@lbl.gov>
 */

#ifndef I3MCCALIBRATIONFILLER_H
#define I3MCCALIBRATIONFILLER_H

#include "phys-services/I3PhysicsModule.h"

/**
 * @brief This module fills the 
 * I3Calibration for each 
 * DOM that it finds in the in ice geometry.
 * THIS IS MEANT TO BE A SHORT-TERM FIX.
 */
class I3MCCalibrationFiller : public I3PhysicsModule
{
public:
    I3MCCalibrationFiller(const I3Context&);

    void Configure();
    void Calibration(I3Frame& frame);

    SET_LOGGER("I3MCCalibrationFiller");

private:
    double atwd0gain_;
    double atwd1gain_;
    double atwd2gain_;

    double fadcGain_;
    double fadcPedestal_;
};

#endif
