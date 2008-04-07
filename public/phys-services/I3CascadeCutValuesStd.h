/**
    copyright  (C) 2005
    the icecube collaboration
    $Id: I3CascadeCutValues.h 10512 2008-03-16 15:02:51 mdagost $
    @author mdagost
*/

#ifndef I3CASCADECUTVALUESSTD_H
#define I3CASCADECUTVALUESSTD_H

#include "icetray/I3FrameObject.h"
#include "dataclasses/Utility.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/I3Cuts.h"

/**
 * @brief A class to store the basic hit information for cascades from the event
 */
class I3CascadeCutValuesStd : public I3FrameObject
{
 public:
  int Nchan;
  int Nhit;
  int N_1hit;
  int Nstring;
  int NdirA;
  int NearlyA;
  int NlateA;
  int NdirB;
  int NearlyB;
  int NlateB;
  int NdirC;
  int NearlyC;
  int NlateC;
  int NdirD;
  int NearlyD;
  int NlateD;
  int NdirE;
  int NearlyE;
  int NlateE;
  I3Position cog;

  I3CascadeCutValuesStd() :
    Nchan(-1),
    Nhit(-1),
    N_1hit(-1),
    Nstring(-1),
    NdirA(-1),
    NearlyA(-1),
    NlateA(-1),
    NdirB(-1),
    NearlyB(-1),
    NlateB(-1),
    NdirC(-1),
    NearlyC(-1),
    NlateC(-1),
    NdirD(-1),
    NearlyD(-1),
    NlateD(-1),
    NdirE(-1),
    NearlyE(-1),
    NlateE(-1)
    { cog.NullPos(); };

  void Calculate(const I3Particle& vertex, 
		 const I3Geometry& geometry, 
		 const I3RecoHitSeriesMap& hitmap);

  void Calculate(const I3Particle& vertex, 
		 const I3Geometry& geometry, 
		 const I3RecoPulseSeriesMap& pulsemap);

  virtual ~I3CascadeCutValuesStd();

 private:

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive & ar, unsigned version);

};

I3_POINTER_TYPEDEFS(I3CascadeCutValuesStd);

#endif
