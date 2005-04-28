/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DummyGeoOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3DUMMYGEOORIGIN_H
#define I3DUMMYGEOORIGIN_H

#include "phys-source/I3GeometryOrigin.h"
#include <cmath>
/**
 * @brief A simple implemetation of the I3GeometryOrigin which serves
 * up one (empty) geometry
 */
class I3DummyGeoOrigin : public I3GeometryOrigin
{
 public:
  GeometryPair GetGeometry(I3Time time);
};
 
typedef shared_ptr<I3DummyGeoOrigin> I3DummyGeoOriginPtr;

#endif
