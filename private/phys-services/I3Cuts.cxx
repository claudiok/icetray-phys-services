#include <vector>
#include "phys-services/I3Cuts.h"
#include "phys-services/I3Calculator.h"
#include "dataclasses/I3Constants.h"

using namespace I3Constants;
using namespace I3Calculator;


//--------------------------------------------------------------
void I3Cuts::CutsCalc(const I3Particle& track, const I3Geometry& geometry, 
		      const I3RecoHitSeriesMap& hitmap, 
		      const double t1, const double t2, 
		      int& Ndir, double& Ldir, double& Sdir, double& Sall)
{
  Ndir = 0;
  int ntot = 0;
  vector<double> lengthAll;
  vector<double> lengthDir;
  double min = 999999;
  double max = -999999;
  double Ttrack = track.GetTime();
  double Thit, Tarr, Tres;

  I3RecoHitSeriesMap::const_iterator hits_i;
  for (hits_i=hitmap.begin(); hits_i!=hitmap.end(); hits_i++) {
    const I3RecoHitSeries& hits = hits_i->second;
    OMKey omkey = hits_i->first;
    I3OMGeoMap::const_iterator geom = geometry.omgeo.find(omkey);
    if (geom==geometry.omgeo.end()) {
      log_debug("Didn't find the current OMKey in Geometry");
      continue;
    }
    const I3Position& ompos = geom->second.position;

    Tarr = CherenkovTime(track, ompos);

    I3RecoHitSeries::const_iterator hit;
    for (hit=hits.begin(); hit!=hits.end(); hit++) {
      Thit = hit->GetTime();
      Tres = Thit - Ttrack - Tarr;
      log_trace("--------------------------");
      log_trace("ompos: %f %f %f",ompos.GetX(),ompos.GetY(),ompos.GetZ());
      log_trace("Thit: %f - Ttrack: %f - Tarr: %f = Tres: %f",
		Thit,Ttrack,Tarr,Tres);

      // calculate projections of hits onto track...
      ntot++; // keep track of total hits
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

    } // end loop over hitseries

  } // end loop over hitseriesmap

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
      double S = (double)j/(double)N - lj/lN;
      log_debug("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(Sall)) Sall = S;
    }
    // calculation is meaningless for less than 3 hits
    if(lengthAll.size() <= 2) Sall = NAN;
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
      double S = (double)j/(double)N - lj/lN;
      log_debug("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(Sdir)) Sdir = S;
    }
    // calculation is meaningless for less than 3 direct hits
    if(lengthDir.size() <= 2) Sdir = NAN;
  }

  Ldir = max-min; // length of event
  log_debug("-----> Ndir: %i",Ndir);
  log_debug("-----> Ldir: %f",Ldir);
  log_debug("-----> Sall: %f",Sall);
  log_debug("-----> Sdir: %f",Sdir);
  return;
}

//--------------------------------------------------------------
int I3Cuts::Ndir(const I3Particle& track, const I3Geometry& geom, 
		 const I3RecoHitSeriesMap& hitmap,
		 double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  CutsCalc(track, geom, hitmap, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Ndir;
}


//--------------------------------------------------------------
double I3Cuts::Ldir(const I3Particle& track, const I3Geometry& geom, 
		    const I3RecoHitSeriesMap& hitmap,
		    double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  CutsCalc(track, geom, hitmap, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Ldir;
}


//--------------------------------------------------------------
double I3Cuts::SmoothAll(const I3Particle& track, const I3Geometry& geom, 
			 const I3RecoHitSeriesMap& hitmap,
			 double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  CutsCalc(track, geom, hitmap, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Sall;
}


//--------------------------------------------------------------
double I3Cuts::SmoothDir(const I3Particle& track, const I3Geometry& geom, 
			 const I3RecoHitSeriesMap& hitmap,
			 double t1, double t2)
{
  int Ndir;
  double Ldir, Sall, Sdir;
  CutsCalc(track, geom, hitmap, t1, t2, Ndir, Ldir, Sall, Sdir);
  return Sdir;
}

//--------------------------------------------------------------
// Computes the size of the "cylinder of closest approach", as defined
// in Kath's thesis appendix A
double I3Cuts::CylinderSize(const I3Particle& track, 
			    //I3Geometry& geom, 
			    //I3OMResponseMap& ommap, 
			    double H0, double R0, double center) {

  I3Direction v = track.GetDir();
  I3Position p = track.GetPos();

  // X, Y, and Z
  double xx = p.GetX();
  double yy = p.GetY();
  double zz = p.GetZ();

  // Theta and Phi must be in RADIANS
  //double px = -cos(phi)*sin(theta);
  //double py = -sin(phi)*sin(theta);
  //double pz = -cos(theta);
  double px = v.GetX();
  double py = v.GetY();
  double pz = v.GetZ();

  double k, r;
  double aa, bb, cc, underroot, root1, root2, z1, z2;
  double bestcorner, bestcyl, zcyl, zprime;

  // Typical values for AMANDA-B10:
  // H0 = 175,
  // R0 = 100,
  // center = 45

  k = R0/H0;

  //###########################################
  // smallest cylindrical volume of radius r and total height h around 
  // (0,0,center), which is proportional to R0, H0 and contains the track 

  // 1) Solve for top/bottom clippers

  zprime = zz - center;

  aa = px*px+py*py-k*k*pz*pz;
  bb = 2*(xx*px + yy*py -k*k*zprime*pz);
  cc = xx*xx + yy*yy-k*k*zprime*zprime;
  underroot = bb*bb - 4*aa*cc;

  if (underroot >= 0.) {
    root1 = 0.5*(-bb + sqrt(underroot))/aa;
    root2 = 0.5*(-bb - sqrt(underroot))/aa;
    z1 = fabs(zprime + root1*pz);
    z2 = fabs(zprime + root2*pz);

    if (z2<z1) {
      bestcorner = z2/H0;
    } else {
      bestcorner = z1/H0;
    }

  } else {
    bestcorner = 1.E9;
  }

  // 2) Solve for cylinder-clipper
  if ((px==0) && (py==0)) {
    //  it's straight vertical
    r = xx*xx + yy*yy;
    if (r > 0) {
      r = sqrt(r);
    } else {
      r = 0.;
    }
    bestcyl = r/R0;
  } else {
    // not straight vertical
    r = (xx*xx + yy*yy -
         ((px*xx + py*yy)*(px*xx + py*yy))/(px*px + py*py));
    if (r > 0) {
      r = sqrt(r);
    } else {
      r = 0.;
    }

    // But wait!  It must have at least the proper r/h ratio
    zcyl = fabs(zprime + (-(px*xx+py*yy)/(px*px+py*py))*pz);
    if (r/zcyl >= k) {
      bestcyl = r/R0;
    } else {
      bestcyl = 1.E9;
    }
  }

  // Which is smaller?
  if (bestcorner<bestcyl) {
    return bestcorner;
  } else {
    return bestcyl;
  }

}


