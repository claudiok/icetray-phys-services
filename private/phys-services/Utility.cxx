#include "dataclasses/BoostHeaders.h"
#include "dataclasses/Utility.h"
#include "phys-services/Utility.h"
#include "icetray/I3TrayHeaders.h"

string ToString(shared_ptr<const I3FrameObject> obj)
{
  ostringstream outstring;
  boost::archive::xml_oarchive ar(outstring);
  ar << make_nvp(I3::name_of(typeid(*obj)), obj);
  return outstring.str();
}

string ToString(I3FrameObject* obj)
{
  ostringstream outstring;
  boost::archive::xml_oarchive ar(outstring);
  shared_ptr<I3FrameObject> ptr = shared_ptr<I3FrameObject>(new I3FrameObject(*obj));
  ar << make_nvp(I3::name_of(typeid(*obj)), ptr);
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
