#include "icetray/serialization.h"
#include "phys-services/I3Cuts.h"
#include "phys-services/I3CascadeCutValues.h"

void I3CascadeCutValues::Calculate(const I3Particle& vertex, 
			    const I3Geometry& geometry, 
			    const I3RecoHitSeriesMap& hitmap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::CascadeCutsCalc(vertex, geometry, hitmap, begTWindow, endTWindow,
		   Nchan, Nhit, N_1hit, Nstring, Ndir, Nearly, Nlate);
  cog = I3Cuts::COG(geometry, hitmap);
}

void I3CascadeCutValues::Calculate(const I3Particle& vertex, 
			    const I3Geometry& geometry, 
			    const I3RecoPulseSeriesMap& pulsemap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::CascadeCutsCalc(vertex, geometry, pulsemap, begTWindow, endTWindow,
		   Nchan, Nhit, N_1hit, Nstring, Ndir, Nearly, Nlate);
  cog = I3Cuts::COG(geometry, pulsemap);
}

I3CascadeCutValues::~I3CascadeCutValues() { }

template <class Archive>
void I3CascadeCutValues::serialize(Archive& ar, unsigned version)
{
  ar & make_nvp("I3FrameObject", base_object<I3FrameObject>(*this));
  ar & make_nvp("Nchan",Nchan);
  ar & make_nvp("Nhit",Nhit);
  ar & make_nvp("N_1hit",N_1hit);
  ar & make_nvp("Nstring",Nstring);
  ar & make_nvp("Ndir",Ndir);
  ar & make_nvp("Nearly",Nearly);
  ar & make_nvp("Nlate",Nlate);
  ar & make_nvp("cog",cog);
}
  
BOOST_CLASS_VERSION(I3CascadeCutValues, 0);
I3_SERIALIZABLE(I3CascadeCutValues);