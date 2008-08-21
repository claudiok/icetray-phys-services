//#include <vector>
#include "phys-services/I3CutsStd.h"
#include "phys-services/I3Cuts.h"
#include "dataclasses/I3Constants.h"
#include "phys-services/Utility.h"
#include "phys-services/I3Calculator.h"
#include <cassert>

#include <TVector3.h>

using namespace I3Constants;
using namespace I3Calculator;


//--------------------------------------------------------------
template<class HitType>
void TrackCutsCalcImpl(const I3Particle& track, const I3Geometry& geometry, 
		  const I3Map<OMKey, vector<HitType> >& hitmap,
		  int& Nchan, int& Nhit, int& Nstring,
		  int& Nearly, int& Nlate,
		  int& NdirA, double& LdirA, double& SdirA,
		  int& NdirB, double& LdirB, double& SdirB,
		  int& NdirC, double& LdirC, double& SdirC,
		  int& NdirD, double& LdirD, double& SdirD,
		  int& NdirE, double& LdirE, double& SdirE, 
          double& Sall, double& Lall)
{
  int StringNumber[120] = {0};
  NdirA=0, NdirB=0, NdirC=0, NdirD=0, NdirE=0;
  Nhit = 0;
  Nstring = 0;
  Nearly = 0;
  Nlate = 0;
  vector<double> lengthAll;
  vector<double> lengthDirA;
  vector<double> lengthDirB;
  vector<double> lengthDirC;
  vector<double> lengthDirD;
  vector<double> lengthDirE;

  double minAll=999999, minA=999999, minB=999999;
  double minC=999999, minD=999999, minE=999999;

  double maxAll=-999999, maxA=-999999, maxB=-999999;
  double maxC=-999999, maxD=-999999, maxE=-999999;

  double dist;

  typename I3Map<OMKey, vector<HitType> >::const_iterator hits_i;
  for (hits_i=hitmap.begin(); hits_i!=hitmap.end(); hits_i++) {
    const vector<HitType>& hits = hits_i->second;
    OMKey omkey = hits_i->first;
    I3OMGeoMap::const_iterator geom = geometry.omgeo.find(omkey);
    if (geom==geometry.omgeo.end()) {
      log_trace("Didn't find the current OMKey in Geometry");
      continue;
    }

    StringNumber[(int) 19+omkey.GetString()] = 1; // "19+" includes AMANDA strings
    const I3Position& ompos = geom->second.position;

    double dist = DistanceAlongTrack(track, ompos);

    // Find max and min dist along track of all hits
    if (dist<minAll) minAll = dist;
    if (dist>maxAll) maxAll = dist;

    // Determine if it is a direct hit according to each window
    // Use only the first pulse in each DOM to calculate
    double Tres = TimeResidual(track, ompos, hits[0].GetTime());

    // Early hits
    if (Tres<-15*I3Units::ns) {
	  Nearly+=1;                    // add direct hit
    }

    // Late hits
    if (Tres>250*I3Units::ns) {
	  Nlate+=1;                    // add direct hit
    }

    // window A:
    if (Tres>-15*I3Units::ns && Tres<15*I3Units::ns) {
	  NdirA+=1;                    // add direct hit
	  if (dist<minA) minA = dist;    // set minimum for dir length
	  if (dist>maxA) maxA = dist;    // set maximum for dir length
	  lengthDirA.push_back(dist);   // set up for Smoothness and length calculation
    }

    // window B:
    if (Tres>-15*I3Units::ns && Tres<25*I3Units::ns) {
	  NdirB+=1;                    // add direct hit
	  if (dist<minB) minB = dist;    // set minimum for dir length
	  if (dist>maxB) maxB = dist;    // set maximum for dir length
	  lengthDirB.push_back(dist);   // set up for Smoothness and length calculation
    }

    // window C:
    if (Tres>-15*I3Units::ns && Tres<75*I3Units::ns) {
	  NdirC+=1;                    // add direct hit
	  if (dist<minC) minC = dist;    // set minimum for dir length
	  if (dist>maxC) maxC = dist;    // set maximum for dir length
	  lengthDirC.push_back(dist);   // set up for Smoothness and length calculation
    }

    // window D:
    if (Tres>-15*I3Units::ns && Tres<150*I3Units::ns) {
	  NdirD+=1;                    // add direct hit
	  if (dist<minD) minD = dist;    // set minimum for dir length
	  if (dist>maxD) maxD = dist;    // set maximum for dir length
	  lengthDirD.push_back(dist);   // set up for Smoothness and length calculation
    }

    // window E:
    if (Tres>-15*I3Units::ns && Tres<250*I3Units::ns) {
	  NdirE+=1;                    // add direct hit
	  if (dist<minE) minE = dist;    // set minimum for dir length
	  if (dist>maxE) maxE = dist;    // set maximum for dir length
	  lengthDirE.push_back(dist);   // set up for Smoothness and length calculation
    }

    lengthAll.push_back(dist);  // set up for SmoothnessAll calculation
                                //  and now Lall also    
    // Iterating over hits/pulses in one DOM
    typename vector<HitType>::const_iterator hit;
    for (hit=hits.begin(); hit!=hits.end(); hit++) {

      Nhit++; // keep track of total hits

      // TODO: Add Npe, total charge, calc somehow

    } // end loop over hitseries

  } // end loop over hitseriesmap

  //calculate Nstring
  for (int i = 0; i < 120; i++) {
    if (StringNumber[i])
      ++Nstring;
  }

  // calculate SmoothnessAll...
  {
    sort(lengthAll.begin(),lengthAll.end());
    for (unsigned int i=0; i<lengthAll.size(); i++) 
      log_trace("lengthAll[%i]=%f",i,lengthAll[i]);
    int N = lengthAll.size()-1;
    Sall = 0;
    for (unsigned int j=1; j<lengthAll.size(); j++) {
      double lj = lengthAll[j]-lengthAll[0];
      double lN = lengthAll[N]-lengthAll[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(Sall)) Sall = S;
    }
    // calculation is meaningless for less than 3 hits
    if(lengthAll.size() <= 2) Sall = NAN;
  }

  // calculate SmoothnessDir for each window...

  // window A:
  {
    sort(lengthDirA.begin(),lengthDirA.end());
    for (unsigned int i=0; i<lengthDirA.size(); i++) 
      log_trace("lengthDirA[%i]=%f",i,lengthDirA[i]);
    int N = lengthDirA.size()-1;
    SdirA = 0;
    for (unsigned int j=1; j<lengthDirA.size(); j++) {
      double lj = lengthDirA[j]-lengthDirA[0];
      double lN = lengthDirA[N]-lengthDirA[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(SdirA)) SdirA = S;
    }
    // calculation is meaningless for less than 3 direct hits
    if(lengthDirA.size() <= 2) SdirA = NAN;
  }

  // window B:
  {
    sort(lengthDirB.begin(),lengthDirB.end());
    for (unsigned int i=0; i<lengthDirB.size(); i++) 
      log_trace("lengthDirB[%i]=%f",i,lengthDirB[i]);
    int N = lengthDirB.size()-1;
    SdirB = 0;
    for (unsigned int j=1; j<lengthDirB.size(); j++) {
      double lj = lengthDirB[j]-lengthDirB[0];
      double lN = lengthDirB[N]-lengthDirB[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(SdirB)) SdirB = S;
    }
    // calculation is meaningless for less than 3 direct hits
    if(lengthDirB.size() <= 2) SdirB = NAN;
  }

  // window C:
  {
    sort(lengthDirC.begin(),lengthDirC.end());
    for (unsigned int i=0; i<lengthDirC.size(); i++) 
      log_trace("lengthDirC[%i]=%f",i,lengthDirC[i]);
    int N = lengthDirC.size()-1;
    SdirC = 0;
    for (unsigned int j=1; j<lengthDirC.size(); j++) {
      double lj = lengthDirC[j]-lengthDirC[0];
      double lN = lengthDirC[N]-lengthDirC[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(SdirC)) SdirC = S;
    }
    // calculation is meaningless for less than 3 direct hits
    if(lengthDirC.size() <= 2) SdirC = NAN;
  }

  // window D:
  {
    sort(lengthDirD.begin(),lengthDirD.end());
    for (unsigned int i=0; i<lengthDirD.size(); i++) 
      log_trace("lengthDirD[%i]=%f",i,lengthDirD[i]);
    int N = lengthDirD.size()-1;
    SdirD = 0;
    for (unsigned int j=1; j<lengthDirD.size(); j++) {
      double lj = lengthDirD[j]-lengthDirD[0];
      double lN = lengthDirD[N]-lengthDirD[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(SdirD)) SdirD = S;
    }
    // calculation is meaningless for less than 3 direct hits
    if(lengthDirD.size() <= 2) SdirD = NAN;
  }

  // window E:
  {
    sort(lengthDirE.begin(),lengthDirE.end());
    for (unsigned int i=0; i<lengthDirE.size(); i++)
      log_trace("lengthDirE[%i]=%f",i,lengthDirE[i]);
    int N = lengthDirE.size()-1;
    SdirE = 0;
    for (unsigned int j=1; j<lengthDirE.size(); j++) {
      double lj = lengthDirE[j]-lengthDirE[0];
      double lN = lengthDirE[N]-lengthDirE[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(SdirE)) SdirE = S;
    } 
    // calculation is meaningless for less than 3 direct hits
    if(lengthDirE.size() <= 2) SdirE = NAN;
  }   

  Lall  = maxAll-minAll; // length of all hits
  if ( lengthAll.size()==0 ) Lall = NAN;

  LdirA = maxA-minA; // length of direct hits
  LdirB = maxB-minB; // length of direct hits
  LdirC = maxC-minC; // length of direct hits
  LdirD = maxD-minD; // length of direct hits
  LdirE = maxE-minE; // length of direct hits
  if (lengthDirA.size()==0) LdirA = NAN;
  if (lengthDirB.size()==0) LdirB = NAN;
  if (lengthDirC.size()==0) LdirC = NAN;
  if (lengthDirD.size()==0) LdirD = NAN;
  if (lengthDirE.size()==0) LdirE = NAN;

  // Calc Nchan 
  Nchan = hitmap.size();

  // Output some select values
  log_debug("-----> Nchan: %i",Nchan);
  log_debug("-----> NdirC: %i",NdirC);
  log_debug("-----> Nhit: %i",Nhit);
  log_debug("-----> Nstring: %i",Nstring);
  log_debug("-----> LdirC: %f",LdirC);
  log_debug("-----> Sall: %f",Sall);
  log_debug("-----> SdirC: %f",SdirC);
  log_debug("-----> Lall: %f",Lall);
  //log_debug("-----> cSize: %f",cSize);
  return;
}


//--------------------------------------------------------------
template<class HitType>
void CascadeCutsCalcImpl(const I3Particle& vertex, const I3Geometry& geometry, 
			 const I3Map<OMKey, vector<HitType> >& hitmap,
			 int& Nchan, int& Nhit, int& N_1hit, int& Nstring,
			 int& NdirA, int& NearlyA, int& NlateA,
			 int& NdirB, int& NearlyB, int& NlateB,
			 int& NdirC, int& NearlyC, int& NlateC,
			 int& NdirD, int& NearlyD, int& NlateD,
			 int& NdirE, int& NearlyE, int& NlateE)
{
  int StringNumber[120] = {0};
  Nhit     = 0;
  N_1hit   = 0;
  Nstring  = 0;
  NdirA    = 0;
  NearlyA  = 0;
  NlateA   = 0;
  NdirB    = 0;
  NearlyB  = 0;
  NlateB   = 0;
  NdirC    = 0;
  NearlyC  = 0;
  NlateC   = 0;
  NdirD    = 0;
  NearlyD  = 0;
  NlateD   = 0;
  NdirE    = 0;
  NearlyE  = 0;
  NlateE   = 0;

  typename I3Map<OMKey, vector<HitType> >::const_iterator hits_i;
  for (hits_i=hitmap.begin(); hits_i!=hitmap.end(); hits_i++) {
    const vector<HitType>& hits = hits_i->second;
    OMKey omkey = hits_i->first;

    if(hits.size()==1){
      log_trace("found a DOM with a single hit...");
      N_1hit++;
    }

    I3OMGeoMap::const_iterator geom = geometry.omgeo.find(omkey);
    if (geom==geometry.omgeo.end()) {
      log_trace("Didn't find the current OMKey in Geometry");
      continue;
    }

    StringNumber[(int) 19+omkey.GetString()] = 1; // "19+" includes AMANDA strings
    const I3Position& ompos = geom->second.position;

    typename vector<HitType>::const_iterator hit;
    for (hit=hits.begin(); hit!=hits.end(); hit++) {
      
      //TimeResidual function checks if the input particle is a cascade or track and then
      //handles the residual calculation appropriately
      double Tres = TimeResidual(vertex, ompos, hit->GetTime());
      log_trace("cascade time: %f",vertex.GetTime());
      log_trace("    hit time: %f",hit->GetTime());
      log_trace("    residual: %f",Tres);

      Nhit++; // keep track of total hits


      //window A
      // this is an early hit...
      if (Tres<-15*I3Units::ns) {
        NearlyA+=1;                     // add early hits
      }

      // this is a direct hit...
      if (Tres>-15*I3Units::ns && Tres<15*I3Units::ns) {
        NdirA+=1;                     // add direct hits
      }

      // this is a late hit...
      if (Tres>75*I3Units::ns) {
        NlateA+=1;                     // add late hits
      }


      //window B
      // this is an early hit...
      if (Tres<-15*I3Units::ns) {
        NearlyB+=1;                     // add early hits
      }

      // this is a direct hit...
      if (Tres>-15*I3Units::ns && Tres<25*I3Units::ns) {
        NdirB+=1;                     // add direct hits
      }

      // this is a late hit...
      if (Tres>25*I3Units::ns) {
        NlateB+=1;                     // add late hits
      }


      //window C
      // this is an early hit...
      if (Tres<-15*I3Units::ns) {
        NearlyC+=1;                     // add early hits
      }

      // this is a direct hit...
      if (Tres>-15*I3Units::ns && Tres<75*I3Units::ns) {
        NdirC+=1;                     // add direct hits
      }

      // this is a late hit...
      if (Tres>75*I3Units::ns) {
        NlateC+=1;                     // add late hits
      }


      //window D
      // this is an early hit...
      if (Tres<-15*I3Units::ns) {
        NearlyD+=1;                     // add early hits
      }

      // this is a direct hit...
      if (Tres>-15*I3Units::ns && Tres<150*I3Units::ns) {
        NdirD+=1;                     // add direct hits
      }

      // this is a late hit...
      if (Tres>150*I3Units::ns) {
        NlateD+=1;                     // add late hits
      }


      //window E
      // this is an early hit...
      if (Tres<-15*I3Units::ns) {
        NearlyE+=1;                     // add early hits
      }

      // this is a direct hit...
      if (Tres>-15*I3Units::ns && Tres<250*I3Units::ns) {
        NdirE+=1;                     // add direct hits
      }

      // this is a late hit...
      if (Tres>250*I3Units::ns) {
        NlateE+=1;                     // add late hits
      }


    } // end loop over hitseries

  } // end loop over hitseriesmap

  //calculate Nstring
  for (int i = 0; i < 120; i++) {
    if (StringNumber[i])
      ++Nstring;
  }

  Nchan = hitmap.size();
  log_debug("-----> Nchan: %i",Nchan);
  log_debug("-----> Nhit: %i",Nhit);
  log_debug("-----> N_1hit: %i",N_1hit);
  log_debug("-----> Nstring: %i",Nstring);
  log_debug("-----> NdirA: %i",NdirA);
  log_debug("-----> NearlyA: %i",NearlyA);
  log_debug("-----> NlateA: %i", NlateA);
  log_debug("-----> NdirB: %i",NdirB);
  log_debug("-----> NearlyB: %i",NearlyB);
  log_debug("-----> NlateB: %i", NlateB);
  log_debug("-----> NdirC: %i",NdirC);
  log_debug("-----> NearlyC: %i",NearlyC);
  log_debug("-----> NlateC: %i", NlateC);
  log_debug("-----> NdirD: %i",NdirD);
  log_debug("-----> NearlyD: %i",NearlyD);
  log_debug("-----> NlateD: %i", NlateD);
  log_debug("-----> NdirE: %i",NdirE);
  log_debug("-----> NearlyE: %i",NearlyE);
  log_debug("-----> NlateE: %i", NlateE);
  return;
}


//--------------------------------------------------------------
template<class HitType>
I3Position COGImpl(const I3Geometry& geometry,
		   const I3Map<OMKey, vector<HitType> >& hitmap)
{
  double ampWeight=1;
  double cog[3];
  cog[0]=0.0;
  cog[1]=0.0;
  cog[2]=0.0;
  double ampsum=0.0;
  
  // I need to loop over all hit OMs, first to calculate the center of 
  // gravity of the hits and then to get the tensor of inertia.  
 
  typename I3Map<OMKey, vector<HitType> >::const_iterator iter;
  iter = hitmap.begin();
  while(iter != hitmap.end()) {
    
    const vector<HitType>& pulsevect = iter->second;

    if(pulsevect.empty()) {
      iter++;
      log_debug("empty RecoHitSeries or RecoPulseSeries!");
      continue;
    }
    
    for (unsigned i=0; i < pulsevect.size(); i++) {
      HitType pulse = pulsevect[i];
      double amp_tmp;
      if(isnan(GetCharge(pulse)) > 0 || isinf(GetCharge(pulse))> 0) {
	log_warn("Got a nan or inf pulse charge.  Setting it to 0 instead.  Something could be screwy with a DOM calibration!!");
  	amp_tmp=0;
      }
      else {
	amp_tmp = GetCharge(pulse);
      }

      double amp = pow(amp_tmp,ampWeight);
      ampsum+=amp;
    
      const OMKey omkey = iter->first;
      I3OMGeoMap::const_iterator geom = geometry.omgeo.find(omkey);
      if (geom==geometry.omgeo.end()) {
	log_trace("Didn't find the current OMKey in Geometry");
	continue;
      }
      const I3Position& ompos = geom->second.position;

      // calculate the center of gravity             
      cog[0] += amp*ompos.GetX();
      cog[1] += amp*ompos.GetY();
      cog[2] += amp*ompos.GetZ();
    }
    iter++;
  }
  
  if (ampsum==0) ampsum=1.0;
  I3Position cogPosition(cog[0]/ampsum, cog[1]/ampsum, cog[2]/ampsum);
  return cogPosition;
}


//--------------------------------------------------------------
I3Position I3CutsStd::COG(const I3Geometry& geometry,
		       const I3RecoHitSeriesMap& hitmap)
{
  I3Position cog(COGImpl<I3RecoHit>(geometry, hitmap));
  return cog;
}


//--------------------------------------------------------------
I3Position I3CutsStd::COG(const I3Geometry& geometry,
		       const I3RecoPulseSeriesMap& pulsemap)
{
  I3Position cog(COGImpl<I3RecoPulse>(geometry, pulsemap));
  return cog;
}


//--------------------------------------------------------------
void I3CutsStd::TrackCutsCalc(const I3Particle& track, const I3Geometry& geometry, 
		      const I3RecoHitSeriesMap& hitmap,
		      int& Nchan, int& Nhit, int& Nstring,
		      int& Nearly, int& Nlate,
		      int& NdirA, double& LdirA, double& SdirA,
		      int& NdirB, double& LdirB, double& SdirB,
		      int& NdirC, double& LdirC, double& SdirC,
		      int& NdirD, double& LdirD, double& SdirD,
		      int& NdirE, double& LdirE, double& SdirE,
              double& Sall, double& Lall)
              //double& Sall, double& Lall, double& cSize)
{
  TrackCutsCalcImpl<I3RecoHit>
    (track, geometry, hitmap,
     Nchan, Nhit, Nstring, 
     Nearly, Nlate,
     NdirA, LdirA, SdirA,
     NdirB, LdirB, SdirB,
     NdirC, LdirC, SdirC,
     NdirD, LdirD, SdirD,
     NdirE, LdirE, SdirE, 
     Sall, Lall);
     //Sall, Lall, cSize);
}


//--------------------------------------------------------------
void I3CutsStd::TrackCutsCalc(const I3Particle& track, const I3Geometry& geometry, 
		      const I3RecoPulseSeriesMap& pulsemap,
		      int& Nchan, int& Nhit, int& Nstring,
		      int& Nearly, int& Nlate,
		      int& NdirA, double& LdirA, double& SdirA,
		      int& NdirB, double& LdirB, double& SdirB,
		      int& NdirC, double& LdirC, double& SdirC,
		      int& NdirD, double& LdirD, double& SdirD,
		      int& NdirE, double& LdirE, double& SdirE,
              double& Sall, double& Lall)
              //double& Sall, double& Lall, double& cSize)
{
  TrackCutsCalcImpl<I3RecoPulse>
    (track, geometry, pulsemap,
     Nchan, Nhit, Nstring, 
     Nearly, Nlate,
     NdirA, LdirA, SdirA,
     NdirB, LdirB, SdirB,
     NdirC, LdirC, SdirC,
     NdirD, LdirD, SdirD,
     NdirE, LdirE, SdirE, 
     Sall, Lall);
     //Sall, Lall, cSize);
}


//--------------------------------------------------------------
void I3CutsStd::CascadeCutsCalc(const I3Particle& vertex, const I3Geometry& geometry, 
				const I3RecoHitSeriesMap& hitmap,
				int& Nchan, int& Nhit, int& N_1hit, int& Nstring,
				int& NdirA, int& NearlyA, int& NlateA,
				int& NdirB, int& NearlyB, int& NlateB,
				int& NdirC, int& NearlyC, int& NlateC,
				int& NdirD, int& NearlyD, int& NlateD,
				int& NdirE, int& NearlyE, int& NlateE)
{
  CascadeCutsCalcImpl<I3RecoHit>
    (vertex, geometry, hitmap, Nchan, Nhit, N_1hit, Nstring, NdirA, NearlyA, NlateA, NdirB, NearlyB, NlateB, NdirC, NearlyC, NlateC, NdirD, NearlyD, NlateD, NdirE, NearlyE, NdirE);
}


//--------------------------------------------------------------
void I3CutsStd::CascadeCutsCalc(const I3Particle& vertex, const I3Geometry& geometry, 
				const I3RecoPulseSeriesMap& pulsemap,
				int& Nchan, int& Nhit, int& N_1hit, int& Nstring,
				int& NdirA, int& NearlyA, int& NlateA,
				int& NdirB, int& NearlyB, int& NlateB,
				int& NdirC, int& NearlyC, int& NlateC,
				int& NdirD, int& NearlyD, int& NlateD,
				int& NdirE, int& NearlyE, int& NlateE)
{
  CascadeCutsCalcImpl<I3RecoPulse>
    (vertex, geometry, pulsemap, Nchan, Nhit, N_1hit, Nstring, NdirA, NearlyA, NlateA, NdirB, NearlyB, NlateB, NdirC, NearlyC, NlateC, NdirD, NearlyD, NlateD, NdirE, NearlyE, NlateE);
}

double I3CutsStd::InIceContainmentSize(I3Geometry geo, I3Particle p) 
{

  //I3OMGeoMap sg = geo->omgeo;
  I3OMGeoMap sg = geo.omgeo;
  // Count strings
  I3OMGeoMap::const_iterator iter;
  map<int,bool> nstringmap;
  for(iter=sg.begin(); iter!=sg.end(); iter++) {
    int st = iter->first.GetString();
    nstringmap[st]=true;
  }
  int nstrings = nstringmap.size();
  //cout << "nstrings: " << nstrings << endl;

  vector<double> x;
  vector<double> y;
  vector<int> strings;
  if ((nstrings == 9)||(nstrings == 28)||(nstrings == 16)||(nstrings == 35)||(nstrings == 59)) {
    log_debug("I found IC-9 or IC-9/AMANDA");
    // For IC-9, the "corner stations" are 21, 50, 59, 39, and 38 (ccw)
    strings.push_back(21);
    strings.push_back(50);
    strings.push_back(59);
    strings.push_back(39);
    strings.push_back(38);
  } else if ((nstrings == 22)||(nstrings == 41)||(nstrings == 26)||(nstrings == 45)) {
    log_debug("I found IC-22 or IC-22/AMANDA");
    // For IC-22: 21, 50, 74, 73, 78, 65,         46, 38
    strings.push_back(21);
    strings.push_back(50);
    strings.push_back(74);
    strings.push_back(73);
    strings.push_back(78);
    strings.push_back(65);
    strings.push_back(46);
    strings.push_back(38);
  } else if (nstrings == 19) {
    log_warn("I found AMANDA only");
    log_warn("This should call CylinderSize, not ContainmentVolume.");
    log_warn("But I'm going to compute this for you anyway.");
    strings.push_back(-12);
    strings.push_back(-13);
    strings.push_back(-14);
    strings.push_back(-15);
    strings.push_back(-16);
    strings.push_back(-17);
    strings.push_back(-18);
    strings.push_back(-19);
  } else {
    // Unknown configuration!
    log_fatal("Unknown In-Ice configuration: Haven't programmed this yet!");
  }

  unsigned int nstr = strings.size();
  x.resize(nstr);
  y.resize(nstr);
  double avgtop = 0;
  double avgbot = 0;
  for (unsigned int i=0; i<nstr; i++) {
    OMKey key(strings[i],30);  // pick the middle of the string
    x[i] = sg[key].position.GetX();
    y[i] = sg[key].position.GetY();
    log_debug("String %d: x=%f y=%f", strings[i], x[i], y[i]);
    // Get coordinates of top and bottom
    OMKey keytop(strings[i],1);  // top of the string
    OMKey keybot(strings[i],60);  // bottom of the string
    avgtop += sg[keytop].position.GetZ();
    avgbot += sg[keybot].position.GetZ();
  }
  avgtop /= nstr;
  avgbot /= nstr;
  log_debug("Average top: %f, Average bottom: %f", avgtop, avgbot);

#ifdef CONTAINMENT_FUNCTIONS_AVAILABLE
  return I3Cuts::ContainmentVolumeSize(p, x, y, avgtop, avgbot);
#else
  return NAN;
#endif

}







