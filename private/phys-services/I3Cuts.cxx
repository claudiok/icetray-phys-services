#include <vector>
#include "phys-services/I3Cuts.h"
#include "phys-services/I3Calculator.h"
#include "dataclasses/I3Constants.h"

using namespace I3Constants;
using namespace I3Calculator;

//--------------------------------------------------------------
void I3Cuts::DirectHits(I3TrackPtr track, I3Geometry& geom, 
			I3OMResponseMap& ommap, string hitseries,
			double t1, double t2, int& ndir, double& ldir)
{
  ndir = 0;
  double min = 999999;
  double max = -999999;
  double Ttrack = track->GetT();
  double Thit, Tarr, Tres;
  I3OMResponseMap::iterator om;
  for (om=ommap.begin(); om!=ommap.end(); om++) {
    I3OMResponsePtr omr = om->second;
    I3RecoHitSeriesDict& dict = omr->GetRecoHitSeriesDict();
    if (dict.find(hitseries)!=dict.end()) {
      I3RecoHitSeriesPtr hits = dict[hitseries];
      I3Position ompos = geom.GetInIceGeometry()[om->first]->GetPos();
      Tarr = CherenkovTime(track, ompos);
      Thit = hits->GetFirstHitTime();
      Tres = Thit - Ttrack - Tarr;
      log_debug("\nThit: %f - Ttrack: %f - Tarr: %f = Tres: %f",
		Thit,Ttrack,Tarr,Tres);
      log_debug("\nompos: %f %f %f",ompos.GetX(),ompos.GetY(),ompos.GetZ());

      // this is a direct hit...
      if (Tres>t1 && Tres<t2) {
	ndir+=1;
	I3Position pos(ompos);
	pos.ShiftCoordSystem(track->GetPos());
	pos.RotateZ(-track->GetDir().CalcPhi());
	pos.RotateY(-track->GetDir().CalcTheta());
	double dist = pos.GetZ();
	cout<<dist<<endl;//####
	if (dist<min) min = dist;
	if (dist>max) max = dist;
      }
      // ...end of direct hit

    }
  }
  ldir = max-min;
}

//--------------------------------------------------------------
int I3Cuts::Ndir(I3TrackPtr track, I3Geometry& geom, 
		 I3OMResponseMap& ommap, string hitseries,	
		 double t1, double t2)
{
  int ndir;
  double ldir;
  DirectHits(track, geom, ommap, hitseries, t1, t2, ndir, ldir);
  return ndir;
}

//--------------------------------------------------------------
int I3Cuts::Ndir(I3TrackPtr track, I3Geometry& geom, 
		 I3OMResponseMap& ommap, string hitseries, 
		 NdirWindow window)
{
  double t1 = -15*ns;
  double t2;
  switch (window) {
  case A:
    t2 = 15*ns;
    break;
    
  case B:
    t2 = 25*ns;
    break;
    
  case C:
    t2 = 75*ns;
    break;
    
  case D:
    t2 = 150*ns;
    break;

  default:
    t2 = 25*ns; // this is B
    break;
  }

  int ndir;
  double ldir;
  DirectHits(track, geom, ommap, hitseries, t1, t2, ndir, ldir);
  return ndir;
}

//--------------------------------------------------------------
double I3Cuts::Ldir(I3TrackPtr track, I3Geometry& geom, 
		    I3OMResponseMap& ommap, string hitseries,	
		    double t1, double t2)
{
  int ndir;
  double ldir;
  DirectHits(track, geom, ommap, hitseries, t1, t2, ndir, ldir);
  return ldir;
}

//--------------------------------------------------------------
double I3Cuts::Ldir(I3TrackPtr track, I3Geometry& geom, 
		    I3OMResponseMap& ommap, string hitseries, 
		    NdirWindow window)
{
  double t1 = -15*ns;
  double t2;
  switch (window) {
  case A:
    t2 = 15*ns;
    break;
    
  case B:
    t2 = 25*ns;
    break;
    
  case C:
    t2 = 75*ns;
    break;
    
  case D:
    t2 = 150*ns;
    break;

  default:
    t2 = 25*ns; // this is B
    break;
  }
  
  int ndir;
  double ldir;
  DirectHits(track, geom, ommap, hitseries, t1, t2, ndir, ldir);
  return ldir;
}
