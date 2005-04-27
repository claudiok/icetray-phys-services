#include "phys-services/I3Cuts.h"
#include "phys-services/I3Calculator.h"
#include "dataclasses/I3Constants.h"

using namespace I3Constants;
using namespace I3Calculator;

//--------------------------------------------------------------
double I3Cuts::Ndir(I3TrackPtr track, I3OMResponseMap& ommap, 
		    I3Geometry& geom, string hitseries,	
		    double t1, double t2)
{
  int ndir = 0;
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
      Tres = Thit - Tarr - Ttrack;
      log_debug("Tarr: %f  Thit: %f  Tres: %f",Tarr,Thit,Tres);
      if (Tres>t1 && Tres<t2) ndir+=1;
    }
  }

  return ndir;
}

//--------------------------------------------------------------
double I3Cuts::Ndir(I3TrackPtr track, I3OMResponseMap& ommap, 
			  I3Geometry& geom, string hitseries, 
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
  
  return Ndir(track, ommap, geom, hitseries, t1, t2);
}
