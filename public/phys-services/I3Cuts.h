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
   * Calculate the number of direct hits from a given track.
   * The moethod counts the hits with small time residuals (between t1, t2)
   *  - t1~=-15ns, t2~=15ns..150ns
   */
  double Ndir(I3TrackPtr track, 
	      I3OMResponseMap& ommap, 
	      I3Geometry& geom, 
	      string hitseries,
	      double t1 = -15*ns, 
	      double t2 = +25*ns);

  /**
   * Calculate the number of direct hits from a given track.
   * The moethod counts the hits with small time residuals (between t1, t2)
   *  - t1 is preset to the default, which is -15ns
   *  - t2 can be set as: A, B, C, or D  (A=15ns, B=25ns, C=75ns, D=150ns)
   */
  double Ndir(I3TrackPtr track, 
	      I3OMResponseMap& ommap, 
	      I3Geometry& geom, 
	      string hitseries,
	      NdirWindow window);

}

#endif

