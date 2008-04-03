/**
    copyright  (C) 2008
    the icecube collaboration
    $Id: I3CutValuesVe.h 10512 2008-03-17 jdumm $
    @author J.Dumm, plagiarizing from dule
*/

#ifndef I3TRACKCUTVALUESSTD_H
#define I3TRACKCUTVALUESSTD_H

#include "icetray/I3FrameObject.h"
#include "dataclasses/Utility.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/I3CutsStd.h"

/**
 * @brief A class to store the basic hit information from the event
 */
class I3TrackCutValuesStd : public I3FrameObject
{
 public:
  int Nchan;
  int Nhit;
  int Nstring;
  int Nearly;
  int Nlate;
  int NdirA;
  double LdirA;
  double SdirA;
  int NdirB;
  double LdirB;
  double SdirB;
  int NdirC;
  double LdirC;
  double SdirC;
  int NdirD;
  double LdirD;
  double SdirD;
  int NdirE;
  double LdirE;
  double SdirE;
  double Sall;
  double Lall;
  double cSize;
  I3Position cog;

  I3TrackCutValuesStd() :
    Nchan(-1),
    Nhit(-1),
    Nstring(-1),
    Nearly(-1),
    Nlate(-1),
    NdirA(-1),
    LdirA(NAN),
    SdirA(NAN),
    NdirB(-1),
    LdirB(NAN),
    SdirB(NAN),
    NdirC(-1),
    LdirC(NAN),
    SdirC(NAN),
    NdirD(-1),
    LdirD(NAN),
    SdirD(NAN),
    NdirE(-1),
    LdirE(NAN),
    SdirE(NAN),
    Sall(NAN),
    Lall(NAN),
    cSize(NAN)
    { cog.NullPos(); };

  void Calculate(const I3Particle& track, 
		 const I3Geometry& geometry, 
		 const I3RecoHitSeriesMap& hitmap);

  void Calculate(const I3Particle& track, 
		 const I3Geometry& geometry, 
		 const I3RecoPulseSeriesMap& pulsemap);

  virtual ~I3TrackCutValuesStd();

 private:

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive & ar, unsigned version);

};

I3_POINTER_TYPEDEFS(I3TrackCutValuesStd);

#endif
