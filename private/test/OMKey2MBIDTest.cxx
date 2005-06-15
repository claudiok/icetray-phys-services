#include <I3Test.h>

#include "phys-services/I3FileOMKey2MBID.h"

#include <sstream>
#include <iostream>

using namespace std;

TEST_GROUP(OMKey2MBIDTest);

TEST(0df7b060acad)
{
  I3OMKey2MBIDPtr service;
  ENSURE(getenv("I3_WORK"));
  string infile(getenv("I3_WORK"));
  infile.append("/phys-services/resources/doms.txt");
  service = I3OMKey2MBIDPtr(new I3FileOMKey2MBID(infile));
  
  istringstream in;  
  long long int innum;
  
    // spot check a few
  in.str("0df7b060acad");
  in>>hex>>innum;
  cout<<service->GetMBID(OMKey(21,28))<<" =?= "<<innum<<endl;
  ENSURE(service->GetMBID(OMKey(21,34)) == innum,"0df7b060acad");
}

TEST(8b9f35308e27)
{
  I3OMKey2MBIDPtr service;
  ENSURE(getenv("I3_WORK"));
  string infile(getenv("I3_WORK"));
  infile.append("/phys-services/resources/doms.txt");
  service = I3OMKey2MBIDPtr(new I3FileOMKey2MBID(infile));
  
  istringstream in;  
  long long int innum;

  in.str("8b9f35308e27");
  in>>hex>>innum;
  cout<<service->GetMBID(OMKey(21,28))<<" =?= "<<innum<<endl;
  ENSURE(service->GetMBID(OMKey(21,28)) == innum,"8b9f35308e27");
}

TEST(d52b66ab6861)
{
  I3OMKey2MBIDPtr service;
  ENSURE(getenv("I3_WORK"));
  string infile(getenv("I3_WORK"));
  infile.append("/phys-services/resources/doms.txt");
  service = I3OMKey2MBIDPtr(new I3FileOMKey2MBID(infile));
  
  istringstream in;  
  long long int innum;
  
  in.str("d52b66ab6861");
  in>>hex>>innum;
  cout<<service->GetMBID(OMKey(21,28))<<" =?= "<<innum<<endl;
  ENSURE(service->GetMBID(OMKey(30,64)) == innum,"d52b66ab6861");
  
}


