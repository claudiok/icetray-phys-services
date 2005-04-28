/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DummyDetectorStatusOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3DUMMYDETECTORSTATUSORIGIN_H
#define I3DUMMYDETECTORSTATUSORIGIN_H

#include "phys-source/I3DetectorStatusOrigin.h"
#include <cmath>
/**
 * @brief A simple implemetation of the I3DetectorStatusOrigin which serves
 * up one (empty) detector status
 */
class I3DummyDetectorStatusOrigin : public I3DetectorStatusOrigin
{
 public:
  DetectorStatusPair GetDetectorStatus(I3Time time);
};
 
typedef shared_ptr<I3DummyDetectorStatusOrigin> I3DummyDetectorStatusOriginPtr;

#endif
