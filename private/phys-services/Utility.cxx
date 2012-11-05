/**
 * $Id$
 * (c) 2005 IceCube Collaboration
 */

#include <string>
#include "icetray/serialization.h"
#include "dataclasses/Utility.h"
#include "icetray/I3Units.h"
#include "phys-services/Utility.h"
#include "icetray/I3TrayHeaders.h"
#include "dataclasses/physics/I3MCHit.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3DOMLaunch.h"
#include "dataclasses/physics/I3Waveform.h"
#include <boost/foreach.hpp>

double GetCharge(const I3RecoHit& mchit)
{
  return 1.;
}

double GetCharge(const I3MCHit& mchit)
{
  double w(mchit.GetWeight());
  return isnan(w) ? 1. : mchit.GetWeight();
}

double GetCharge(const I3RecoPulse& pulse)
{
  return pulse.GetCharge();
}

double GetCharge(const I3DOMLaunch& launch)
{
  return NAN;
}

double GetCharge(const I3Waveform& wf)
{
  double charge = 0.;
  std::vector<double>::const_iterator iter;
  for (iter=wf.GetWaveform().begin(); iter!=wf.GetWaveform().end(); iter++) {
    charge += *iter;
  }
  return charge/I3Units::mV;
}

double GetCharge(const std::vector<I3RecoHit>& hit_series)
{
  return hit_series.size();
}

double GetCharge(const std::vector<I3RecoPulse>& pulse_series)
{
  double charge(0);
  BOOST_FOREACH(I3RecoPulse pulse,pulse_series)
    {
      charge+=pulse.GetCharge();
    }
  return charge;
}

// Functions to get time from either RecoPulse or MCHit.
double GetTime(const I3MCHit& mchit)
{
  return mchit.GetTime();
}

double GetTime(const I3RecoPulse& pulse)
{
  return pulse.GetTime();
}

double GetTime(const I3DOMLaunch& launch)
{
  return launch.GetStartTime();
}

double GetTime(const I3Waveform& wf)
{
  return wf.GetStartTime();
}
