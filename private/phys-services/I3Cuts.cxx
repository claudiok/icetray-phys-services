#include <vector>
#include "phys-services/I3Cuts.h"
#include "phys-services/I3Calculator.h"
#include "dataclasses/I3Constants.h"

using namespace I3Constants;
using namespace I3Calculator;


//--------------------------------------------------------------
void I3Cuts::DirectHits(const I3Track& track, I3Geometry& geom, 
			I3OMResponseMap& ommap, const string hitsName,
			double t1, double t2, 
			int& Ndir, double& Ldir, double& Sall, double& Sdir)
{
  Ndir = 0;
  int ntot = 0;
  vector<double> lengthAll;
  vector<double> lengthDir;
  double min = 999999;
  double max = -999999;
  double Ttrack = track.GetT();
  double Thit, Tarr, Tres;
  I3OMResponseMap::iterator om;
  for (om=ommap.begin(); om!=ommap.end(); om++) 
    {
      I3OMResponsePtr omr = om->second;
      I3RecoHitSeriesDict& hitsDict = omr->GetRecoHitSeriesDict();
      I3RecoPulseSeriesDict& pulsesDict = omr->GetRecoPulseSeriesDict();

      // Check that the RecoHits or RecoPulses is present
      if (hitsDict.find(hitsName) != hitsDict.end())
	Thit = hitsDict[hitsName]->GetFirstHitTime();
      else if (pulsesDict.find(hitsName) != pulsesDict.end())
	Thit = pulsesDict[hitsName]->GetFirstPulseTime();
      else {
	log_info("\n   RecoHitSeries or RecoPulseSeries '%s' is not present "
		 "in the current OM response. ", hitsName.c_str());
	continue;
      }

      I3Position ompos = geom.GetInIceGeometry()[om->first]->GetPos();
      Tarr = CherenkovTime(track, ompos);
      Tres = Thit - Ttrack - Tarr;
      log_debug("--------------------------");
      log_debug("ompos: %f %f %f",ompos.GetX(),ompos.GetY(),ompos.GetZ());
      log_debug("Thit: %f - Ttrack: %f - Tarr: %f = Tres: %f",
		Thit,Ttrack,Tarr,Tres);

      // calculate projections of hits onto track...
      ntot++;
      I3Position pos(ompos);
      pos.ShiftCoordSystem(track.GetPos());
      pos.RotateZ(-track.GetDir().CalcPhi());
      pos.RotateY(-track.GetDir().CalcTheta());
      double dist = pos.GetZ();
      log_debug("dist: %f",dist);
      lengthAll.push_back(dist);        // set up for SmoothnessAll calculation

      // this is a direct hit...
      if (Tres>t1 && Tres<t2) {
	Ndir+=1;                     // add direct hits
	if (dist<min) min = dist;    // set minimum for "event length"
	if (dist>max) max = dist;    // set maximum for "event length"
	lengthDir.push_back(dist);  // set up for SmoothnessDir calculation
      }

    } // end for loop

  // calculate SmoothnessAll...
  {
    sort(lengthAll.begin(),lengthAll.end());
    for (unsigned int i=0; i<lengthAll.size(); i++) 
      log_debug("lengthAll[%i]=%f",i,lengthAll[i]);
    int N = lengthAll.size()-1;
    Sall = 0;
    for (unsigned int j=1; j<lengthAll.size(); j++) {
      double lj = lengthAll[j]-lengthAll[0];
      double lN = lengthAll[N]-lengthAll[0];
      double S = abs((double)j/(double)N - lj/lN);
      log_debug("j: %i  N: %i  S: %f",j,N,S);
      if (S>Sall) Sall = S;
    }
  }

  // calculate SmoothnessDir...
  {
    sort(lengthDir.begin(),lengthDir.end());
    for (unsigned int i=0; i<lengthDir.size(); i++) 
      log_debug("lengthDir[%i]=%f",i,lengthDir[i]);
    int N = lengthDir.size()-1;
    Sdir = 0;
    for (unsigned int j=1; j<lengthDir.size(); j++) {
      double lj = lengthDir[j]-lengthDir[0];
      double lN = lengthDir[N]-lengthDir[0];
      double S = abs((double)j/(double)N - lj/lN);
      log_debug("j: %i  N: %i  S: %f",j,N,S);
      if (S>Sdir) Sdir = S;
    }
  }

  Ldir = max-min; // length of event
  log_debug("-----> Ndir: %i",Ndir);
  log_debug("-----> Ldir: %f",Ldir);
  log_debug("-----> Sall: %f",Sall);
  log_debug("-----> Sdir: %f",Sdir);
  return;
}


//--------------------------------------------------------------
int I3Cuts::Ndir(const I3Track& track, I3Geometry& geom, 
		 I3OMResponseMap& ommap, const string hitsName,	
		 double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  DirectHits(track, geom, ommap, hitsName, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Ndir;
}


//--------------------------------------------------------------
double I3Cuts::Ldir(const I3Track& track, I3Geometry& geom, 
		    I3OMResponseMap& ommap, const string hitsName,
		    double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  DirectHits(track, geom, ommap, hitsName, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Ldir;
}


//--------------------------------------------------------------
double I3Cuts::SmoothnessAll(const I3Track& track, I3Geometry& geom, 
			     I3OMResponseMap& ommap, 
			     const string hitsName, double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  DirectHits(track, geom, ommap, hitsName, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Sall;
}


//--------------------------------------------------------------
double I3Cuts::SmoothnessDir(const I3Track& track, I3Geometry& geom, 
			     I3OMResponseMap& ommap, 
			     const string hitsName, double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  DirectHits(track, geom, ommap, hitsName, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Sdir;
}

