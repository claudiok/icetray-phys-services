/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3OMKey2MBID.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3OMKEY2MBID_H
#define I3OMKEY2MBID_H

#include <icetray/IcetrayFwd.h>
#include <icetray/I3DefaultName.h>

#include "dataclasses/OMKey.h"

#include <map>

using namespace std;

/**
 * @brief This is an icetray service which provides conversions
 * between OMKey and DOM mainboard id.
 *
 */
class I3OMKey2MBID
{
 public:
  virtual ~I3OMKey2MBID(){}

  /**
   * @brief Gets the OMKey for the given mbid.
   */
  virtual OMKey GetOMKey(long long int mbid) = 0;

  /**
   * @brief Gets the mbid for the given OMKey
   */
  virtual long long int GetMBID(OMKey key) = 0;

  SET_LOGGER("I3OMKey2MBID");
};

I3_POINTER_TYPEDEFS(I3OMKey2MBID);
I3_DEFAULT_NAME(I3OMKey2MBID);

#endif
