/**
    copyright  (C) 2005
    the icecube collaboration
    $Id: I3CutValues.h 10512 2005-08-03 19:04:51Z dule $
    @author dule
*/

#ifndef I3CUTVALUES_H
#define I3CUTVALUES_H

#include "icetray/I3FrameObject.h"
#include "dataclasses/Utility.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/geometry/I3Geometry.h"

/**
 * @brief A class to store the basic hit information from the event
 */
class I3CutValues : public I3FrameObject
{
 public:
  int Nhit;
  int Ndir;
  double Ldir;
  double Sdir;
  double Sall;

  I3CutValues() :
    Nhit(-1),
    Ndir(-1),
    Ldir(NAN),
    Sdir(NAN),
    Sall(NAN)
    {};

  void Calculate(const I3Particle& track, 
		 const I3Geometry& geometry, 
		 const I3RecoHitSeriesMap& hitmap,
		 const double& begTWindow = -15.*I3Units::ns,
		 const double& endTWindow = +25.*I3Units::ns);

  virtual ~I3CutValues();

 private:

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive & ar, unsigned version);

};

I3_POINTER_TYPEDEFS(I3CutValues);

#endif
