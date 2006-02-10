/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3MC2Reco.cxx 15487 2006-02-08 20:58:22Z dule $

    @version $Revision: 1.1 $
    @date $Date: 2006-02-08 15:58:22 -0500 (Wed, 08 Feb 2006) $
    @author

    @todo

*/
#include "phys-services/I3MC2Reco.h"

using namespace std;


//--------------------------------------------------------------
void I3MC2Reco::mc2reco(const I3MCHit& src, //input
			I3RecoHit& dst)         //output
{
  dst.SetTime( src.GetTime());
  dst.SetID( src.GetHitID());

  return;
}

//void I3MC2Reco::mc2reco(const I3MC
