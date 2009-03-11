#include "icetray/serialization.h"
#include "phys-services/I3CutsStd.h"
#include "phys-services/I3CutValuesStd.h"

void I3CutValuesStd::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoHitSeriesMap& hitmap)
{
  I3CutsStd::CutsCalc(track, geometry, hitmap,
		   Nchan, Nhit, Nstring,
           Nearly, Nlate,
           NdirA, LdirA, SdirA,
           NdirB, LdirB, SdirB,
           NdirC, LdirC, SdirC,
           NdirD, LdirD, SdirD,
           NdirE, LdirE, SdirE,
           Sall, Lall);
  cSize = I3CutsStd::InIceContainmentSize(geometry, track);
  cog = I3CutsStd::COG(geometry, hitmap);
}

void I3CutValuesStd::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoPulseSeriesMap& pulsemap)
{
  I3CutsStd::CutsCalc(track, geometry, pulsemap,
		   Nchan, Nhit, Nstring,
           Nearly, Nlate,
           NdirA, LdirA, SdirA,
           NdirB, LdirB, SdirB,
           NdirC, LdirC, SdirC,
           NdirD, LdirD, SdirD,
           NdirE, LdirE, SdirE,
           Sall, Lall);
  cSize = I3CutsStd::InIceContainmentSize(geometry, track);
  cog = I3CutsStd::COG(geometry, pulsemap);
}

I3CutValuesStd::~I3CutValuesStd() { }

template <class Archive>
void I3CutValuesStd::serialize(Archive& ar, unsigned version)
{
  ar & make_nvp("I3FrameObject", base_object<I3FrameObject>(*this));
  ar & make_nvp("Nchan",Nchan);
  ar & make_nvp("Nhit",Nhit);
  ar & make_nvp("Nstring",Nstring);
  ar & make_nvp("Nearly",Nearly);
  ar & make_nvp("Nlate",Nlate);
  ar & make_nvp("NdirA",NdirA);
  ar & make_nvp("LdirA",LdirA);
  ar & make_nvp("SdirA",SdirA);
  ar & make_nvp("NdirB",NdirB);
  ar & make_nvp("LdirB",LdirB);
  ar & make_nvp("SdirB",SdirB);
  ar & make_nvp("NdirC",NdirC);
  ar & make_nvp("LdirC",LdirC);
  ar & make_nvp("SdirC",SdirC);
  ar & make_nvp("NdirD",NdirD);
  ar & make_nvp("LdirD",LdirD);
  ar & make_nvp("SdirD",SdirD);
  ar & make_nvp("NdirE",NdirE);
  ar & make_nvp("LdirE",LdirE);
  ar & make_nvp("SdirE",SdirE);
  ar & make_nvp("Sall",Sall);
  ar & make_nvp("Lall",Lall);
  ar & make_nvp("cSize",cSize);
  ar & make_nvp("cog",cog);
}
  
BOOST_CLASS_VERSION(I3CutValuesStd, 1);
I3_SERIALIZABLE(I3CutValuesStd);
