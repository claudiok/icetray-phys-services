#include "TUT/tut.h"

#include "phys-services/I3FileOMKey2MBID.h"

#include <sstream>
#include <iostream>

using namespace std;

namespace tut
{
  struct OMKey2MBIDTest
  {
    I3OMKey2MBIDPtr service;
    OMKey2MBIDTest() 
    {
      ensure(getenv("I3_WORK"));
      string infile(getenv("I3_WORK"));
      infile.append("/phys-services/resources/doms.txt");
      service = I3OMKey2MBIDPtr(new I3FileOMKey2MBID(infile));
    }
  };

  typedef test_group<OMKey2MBIDTest> factory;
  typedef factory::object object;
}

namespace
{
  static tut::factory t("OMKey2MBIDTest");
}

namespace tut
{
  template<> template<>
  void object::test<1>() 
  {
    istringstream in;  
    long long int innum;

    // spot check a few
    in.str("0df7b060acad");
    in>>hex>>innum;
    cout<<service->GetMBID(OMKey(21,28))<<" =?= "<<innum<<endl;
    ensure("0df7b060acad",service->GetMBID(OMKey(21,34)) == innum);
  }

  template<> template<>
  void object::test<3>() 
  {
    istringstream in;  
    long long int innum;

    in.str("8b9f35308e27");
    in>>hex>>innum;
    cout<<service->GetMBID(OMKey(21,28))<<" =?= "<<innum<<endl;
    ensure("8b9f35308e27",service->GetMBID(OMKey(21,28)) == innum);
  }

  template<> template<>
  void object::test<2>() 
  {
    istringstream in;  
    long long int innum;

    in.str("d52b66ab6861");
    in>>hex>>innum;
    cout<<service->GetMBID(OMKey(21,28))<<" =?= "<<innum<<endl;
    ensure("d52b66ab6861",service->GetMBID(OMKey(30,64)) == innum);

  }


}

