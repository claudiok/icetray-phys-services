#include <vector>
#include "phys-services/I3Cuts.h"
#include "phys-services/I3Calculator.h"
#include "dataclasses/I3Constants.h"

using namespace I3Constants;
using namespace I3Calculator;


//--------------------------------------------------------------
int I3Cuts::Ndir(I3TrackPtr track, I3Geometry& geom, 
		 I3OMResponseMap& ommap, string hitseries,	
		 double t1, double t2)
{
  int Ndir;
  double Ldir;
  double Smax;
  DirectHits(track, geom, ommap, hitseries, t1, t2, Ndir, Ldir, Smax);
  return Ndir;
}


//--------------------------------------------------------------
int I3Cuts::Ndir(I3TrackPtr track, I3Geometry& geom, 
		 I3OMResponseMap& ommap, string hitseries, 
		 NdirWindow window)
{
  double t1, t2;
  CalcTimeWindow(window, t1, t2);
  int Ndir;
  double Ldir;
  double Smax;
  DirectHits(track, geom, ommap, hitseries, t1, t2, Ndir, Ldir, Smax);
  return Ndir;
}


//--------------------------------------------------------------
double I3Cuts::Ldir(I3TrackPtr track, I3Geometry& geom, 
		    I3OMResponseMap& ommap, string hitseries,	
		    double t1, double t2)
{
  int Ndir;
  double Ldir;
  double Smax;
  DirectHits(track, geom, ommap, hitseries, t1, t2, Ndir, Ldir, Smax);
  return Ldir;
}


//--------------------------------------------------------------
double I3Cuts::Ldir(I3TrackPtr track, I3Geometry& geom, 
		    I3OMResponseMap& ommap, string hitseries, 
		    NdirWindow window)
{
  double t1, t2;
  CalcTimeWindow(window, t1, t2);
  int Ndir;
  double Ldir;
  double Smax;
  DirectHits(track, geom, ommap, hitseries, t1, t2, Ndir, Ldir, Smax);
  return Ldir;
}


//--------------------------------------------------------------
double I3Cuts::Smoothness(I3TrackPtr track, I3Geometry& geom, 
			  I3OMResponseMap& ommap, string hitseries)
{
  int Ndir;
  double Ldir;
  double Smax;
  DirectHits(track, geom, ommap, hitseries, -15, 15, Ndir, Ldir, Smax);
  return Smax;
}


//--------------------------------------------------------------
void I3Cuts::CalcTimeWindow(NdirWindow window, double& t1, double& t2)
{
  t1 = -15*ns; // this is preset...
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
}


//--------------------------------------------------------------
void I3Cuts::DirectHits(I3TrackPtr track, I3Geometry& geom, 
			I3OMResponseMap& ommap, string hitseries,
			double t1, double t2, 
			int& Ndir, double& Ldir, double& Smax)
{
  Ndir = 0;
  int ntot = 0;
  vector<double> length;
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
      log_debug("--------------------------");
      log_debug("ompos: %f %f %f",ompos.GetX(),ompos.GetY(),ompos.GetZ());
      log_debug("Thit: %f - Ttrack: %f - Tarr: %f = Tres: %f",
		Thit,Ttrack,Tarr,Tres);

      // calculate projections of hits onto track...
      ntot+=1;
      I3Position pos(ompos);
      pos.ShiftCoordSystem(track->GetPos());
      pos.RotateZ(-track->GetDir().CalcPhi());
      pos.RotateY(-track->GetDir().CalcTheta());
      double dist = pos.GetZ();
      log_debug("dist: %f",dist);
      length.push_back(dist);

      // this is a direct hit...
      if (Tres>t1 && Tres<t2) {
	Ndir+=1; // add direct hits
	if (dist<min) min = dist;
	if (dist>max) max = dist;
      }

    }
  }

  // calculate Smoothness...
  sort(length.begin(),length.end());
  for (unsigned int i=0; i<length.size(); i++) 
    log_debug("length[%i]=%f",i,length[i]);
  int N = length.size()-1;
  Smax = 0;
  for (unsigned int j=1; j<length.size(); j++) {
    double lj = length[j]-length[0];
    double lN = length[N]-length[0];
    double S = abs((double)j/(double)N - lj/lN);
    log_debug("j: %i  N: %i  S: %f",j,N,S);
    if (S>Smax) Smax = S;
  }

  Ldir = max-min; // length of event
  log_debug("-----> Ndir: %i",Ndir);
  log_debug("-----> Ldir: %f",Ldir);
  log_debug("-----> Smax: %f",Smax);
}
