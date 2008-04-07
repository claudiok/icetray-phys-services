#include "icetray/serialization.h"
#include "phys-services/I3CutsStd.h"
#include "phys-services/I3CascadeCutValuesStd.h"

void I3CascadeCutValuesStd::Calculate(const I3Particle& vertex, 
			    const I3Geometry& geometry, 
			    const I3RecoHitSeriesMap& hitmap)
{
  I3CutsStd::CascadeCutsCalc(vertex, geometry, hitmap, Nchan, Nhit, N_1hit, Nstring, 
			     NdirA, NearlyA, NlateA,
			     NdirB, NearlyB, NlateB,
			     NdirC, NearlyC, NlateC,
			     NdirD, NearlyD, NlateD,
			     NdirE, NearlyE, NlateE);
  cog = I3CutsStd::COG(geometry, hitmap);
}

void I3CascadeCutValuesStd::Calculate(const I3Particle& vertex, 
			    const I3Geometry& geometry, 
			    const I3RecoPulseSeriesMap& pulsemap)
{
  I3CutsStd::CascadeCutsCalc(vertex, geometry, pulsemap, Nchan, Nhit, N_1hit, Nstring, 
			     NdirA, NearlyA, NlateA,
			     NdirB, NearlyB, NlateB,
			     NdirC, NearlyC, NlateC,
			     NdirD, NearlyD, NlateD,
			     NdirE, NearlyE, NlateE);
  cog = I3CutsStd::COG(geometry, pulsemap);
}

I3CascadeCutValuesStd::~I3CascadeCutValuesStd() { }

template <class Archive>
void I3CascadeCutValuesStd::serialize(Archive& ar, unsigned version)
{
  ar & make_nvp("I3FrameObject", base_object<I3FrameObject>(*this));
  ar & make_nvp("Nchan",Nchan);
  ar & make_nvp("Nhit",Nhit);
  ar & make_nvp("N_1hit",N_1hit);
  ar & make_nvp("Nstring",Nstring);
  ar & make_nvp("NdirA",NdirA);
  ar & make_nvp("NearlyA",NearlyA);
  ar & make_nvp("NlateA",NlateA);
  ar & make_nvp("NdirB",NdirB);
  ar & make_nvp("NearlyB",NearlyB);
  ar & make_nvp("NlateB",NlateB);
  ar & make_nvp("NdirC",NdirC);
  ar & make_nvp("NearlyC",NearlyC);
  ar & make_nvp("NlateC",NlateC);
  ar & make_nvp("NdirD",NdirD);
  ar & make_nvp("NearlyD",NearlyD);
  ar & make_nvp("NlateD",NlateD);
  ar & make_nvp("NdirE",NdirD);
  ar & make_nvp("NearlyE",NearlyD);
  ar & make_nvp("NlateE",NlateD);
  ar & make_nvp("cog",cog);
}
  
BOOST_CLASS_VERSION(I3CascadeCutValuesStd, 0);
I3_SERIALIZABLE(I3CascadeCutValuesStd);
