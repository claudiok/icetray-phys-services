/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3MC2Reco.cxx 15487 2006-02-08 20:58:22Z dule $

    @version $Revision: 1.1 $
    @date $Date: 2006-02-08 15:58:22 -0500 (Wed, 08 Feb 2006) $
    @author

    @todo

*/

#include "icetray/I3Units.h"
#include "phys-services/I3MC2Reco.h"

using namespace std;


//--------------------------------------------------------------
void I3MC2Reco::mc2reco(const I3MCHit& src, //input
			I3RecoPulse& dst)         //output
{
  dst.SetTime( src.GetTime() );
  dst.SetCharge( src.GetWeight() );
  dst.SetWidth( 3.3 * I3Units::ns /* ATWD bin width */ );

  return;
}

void I3MC2Reco::mc2reco(const I3MCHitSeries& src,
			I3RecoPulseSeries& dst)
{
  dst.resize( src.size() );
  I3MCHitSeries::const_iterator MCiter = src.begin();
  I3RecoPulseSeries::iterator recoiter = dst.begin();
  while(MCiter != src.end()) mc2reco(*MCiter++, *recoiter++);

}
