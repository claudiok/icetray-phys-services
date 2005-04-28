/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DummyCalibOrigin.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3DUMMYCALIBORIGIN_H
#define I3DUMMYCALIBORIGIN_H

#include "phys-source/I3CalibrationOrigin.h"
#include <cmath>

/**
 * @brief An implementation of the I3CalibrationOrigin which 
 * just serves up one calibration which is empty.
 */
class I3DummyCalibOrigin : public I3CalibrationOrigin
{
 public:
  CalibrationPair GetCalibration(I3Time time);
};

typedef shared_ptr<I3DummyCalibOrigin> I3DummyCalibOriginPtr;


#endif
