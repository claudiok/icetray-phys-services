#include "icetray/serialization.h"
#include "dataclasses/Utility.h"
#include "dataclasses/I3Units.h"
#include "phys-services/Utility.h"
#include "icetray/I3TrayHeaders.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3MCHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3DOMLaunch.h"
#include "dataclasses/physics/I3Waveform.h"
#include <boost/foreach.hpp>

string ToString(shared_ptr<const I3FrameObject> obj)
{
  ostringstream outstring;
  boost::archive::xml_oarchive ar(outstring);
  ar << make_nvp(I3::name_of(typeid(*obj)).c_str(), obj);
  return outstring.str();
}

string ToString(I3FrameObject* obj)
{
  ostringstream outstring;
  boost::archive::xml_oarchive ar(outstring);
  shared_ptr<I3FrameObject> ptr = shared_ptr<I3FrameObject>(new I3FrameObject(*obj));
  ar << make_nvp(I3::name_of(typeid(*obj)).c_str(), ptr);
  return outstring.str();
}

shared_ptr<I3FrameObject> Clone(shared_ptr<const I3FrameObject> ptr)
{
  std::ostringstream oss;
  boost::archive::portable_binary_oarchive boa(oss);
  boa << make_nvp("obj", ptr);
  shared_ptr<I3FrameObject> newptr;
  std::istringstream iss;
  iss.str(oss.str());
  boost::archive::portable_binary_iarchive bia(iss);
  bia >> make_nvp("obj", newptr);
  return newptr;
}

I3FrameObject* Clone(I3FrameObject* ptr)
{
  std::ostringstream oss;
  boost::archive::portable_binary_oarchive boa(oss);
  boa << make_nvp("obj", ptr);
  shared_ptr<I3FrameObject> newptr;
  std::istringstream iss;
  iss.str(oss.str());
  boost::archive::portable_binary_iarchive bia(iss);
  bia >> make_nvp("obj", newptr);
  return newptr.get();
}

void Copy(shared_ptr<const I3FrameObject> oldp,shared_ptr<I3FrameObject>& newp)
{
  std::ostringstream oss;
  boost::archive::portable_binary_oarchive boa(oss);
  boa << make_nvp("obj", oldp);
  std::istringstream iss;
  iss.str(oss.str());
  boost::archive::portable_binary_iarchive bia(iss);
  bia >> make_nvp("obj", newp);
}

void Copy(shared_ptr<const I3FrameObject> oldp, I3FrameObject* newp)
{
  std::ostringstream oss;
  boost::archive::portable_binary_oarchive boa(oss);
  boa << make_nvp("obj", oldp);
  std::istringstream iss;
  iss.str(oss.str());
  boost::archive::portable_binary_iarchive bia(iss);
  bia >> make_nvp("obj", newp);
}

// Functions to get charge from either RecoPulse or RecoHit or MCHit.
double GetCharge(const I3RecoHit& hit)
{ 
  return 1.; 
}

double GetCharge(const I3MCHit& mchit)
{ 
  return 1.; 
}

double GetCharge(const I3RecoPulse& pulse)
{
  //return (pulse.GetCharge() >= 2.0) ? pulse.GetCharge() : 1; 
  return pulse.GetCharge(); 
}

double GetCharge(const I3DOMLaunch& launch)
{ 
  return NAN; 
}

double GetCharge(const I3Waveform& wf)
{
  double charge = 0.;
  vector<double>::const_iterator iter;
  for (iter=wf.GetWaveform().begin(); iter!=wf.GetWaveform().end(); iter++) {
    charge += *iter;
  }
  return charge/I3Units::mV; 
}

double GetCharge(const vector<I3RecoHit>& hit_series)
{
  return hit_series.size();
}

double GetCharge(const vector<I3RecoPulse>& pulse_series)
{
  double charge(0);
  BOOST_FOREACH(I3RecoPulse pulse,pulse_series)
    {
      charge+=pulse.GetCharge();
    }
  return charge;
}

// Functions to get time from either RecoPulse or RecoHit or MCHit.
double GetTime(const I3RecoHit& hit)
{ 
  return hit.GetTime(); 
}

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
