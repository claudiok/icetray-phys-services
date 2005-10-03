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

  /**
   * @brief Gets the default name of this service in the context.
   */
  static const char* DefaultName() { return "OMKey2MBID";}

   SET_LOGGER("I3OMKey2MBID");
};

typedef boost::shared_ptr<I3OMKey2MBID> I3OMKey2MBIDPtr;

#endif
