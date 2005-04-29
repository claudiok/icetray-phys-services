#ifndef I3CUTS_H
#define I3CUTS_H

#include "dataclasses/I3Units.h"
#include "dataclasses/I3Track.h"
#include "dataclasses/I3OMResponseMap.h"
#include "dataclasses/I3Geometry.h"

using namespace I3Units;

namespace I3Cuts
{
  enum NdirWindow { A, B, C, D };

  /**
   * The method underneath Ndir and Ldir that actually calculates the 
   * direct hits
   */
  void DirectHits(I3TrackPtr track, 
		  I3Geometry& geom, 
		  I3OMResponseMap& ommap, 
		  string hitseries,
		  double t1, 
		  double t2, 
		  int& ndir, 
		  double& ldir);

  /**
   * Calculate the number of direct hits from a given track.
   * The moethod counts the hits with small time residuals (between t1, t2)
   *  - t1~=-15ns, t2~=15ns..150ns
   */
  int Ndir(I3TrackPtr track, 
	   I3Geometry& geom, 
	   I3OMResponseMap& ommap, 
	   string hitseries,
	   double t1 = -15*ns, 
	   double t2 = +25*ns);

  /**
   * Calculate the number of direct hits from a given track.
   * The moethod counts the hits with small time residuals (between t1, t2)
   *  - t1 is preset to the default, which is -15ns
   *  - t2 can be set as: A, B, C, or D  (A=15ns, B=25ns, C=75ns, D=150ns)
   */
  int Ndir(I3TrackPtr track, 
	   I3Geometry& geom, 
	   I3OMResponseMap& ommap, 
	   string hitseries,
	   NdirWindow window);

  /**
   * Calculate the length between the two most extreme projections
   * of the direct hits onto the track.  This gives us a measure of how many 
   * hits the track (muon) is generating along its trajectory.
   * Direct hits are the hits with small time residuals (between t1, t2)
   *  - t1~=-15ns, t2~=15ns..150ns
   */
  double Ldir(I3TrackPtr track, 
	      I3Geometry& geom, 
	      I3OMResponseMap& ommap, 
	      string hitseries,
	      double t1 = -15*ns, 
	      double t2 = +25*ns);

  /**
   * Direct hits are the hits with small time residuals (between t1, t2)
   *  - t1 is preset to the default, which is -15ns
   *  - t2 can be set as: A, B, C, or D  (A=15ns, B=25ns, C=75ns, D=150ns)
   */
  double Ldir(I3TrackPtr track, 
	      I3Geometry& geom, 
	      I3OMResponseMap& ommap, 
	      string hitseries,
	      NdirWindow window);

}

#endif

