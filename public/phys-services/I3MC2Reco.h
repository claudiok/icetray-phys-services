/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3MC2Reco.h 15405 2006-02-06 23:47:26Z dule $
 *
 * @file I3MC2Reco.h
 * @version $Revision: 1.16 $
 * @date $Date: 2006-02-06 18:47:26 -0500 (Mon, 06 Feb 2006) $
 * @author proth
 */
#ifndef I3MCTORECO_H
#define I3MCTORECO_H

#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3MCHit.h"

/**
 * @brief This service is to be used for converting MC objects into
 * their respective reco objects.
 *
 */
namespace I3MC2Reco
{
  /**
   * Copies the data members from the I3MCHit into the destination
   * I3RecoHit.  Only the data memebers that are shared between the two
   * classes are copied.
   *
   */
  void mc2reco(const I3MCHit& src, I3RecoHit& dst);

  void mc2reco(const I3MCHitSeries& src, I3RecoHitSeries& dst);

}

#endif
