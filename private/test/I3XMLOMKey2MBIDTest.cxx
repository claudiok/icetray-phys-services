/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3XMLOMKey2MBIDTest.cxx 9281 2005-06-19 17:06:10Z tschmidt $

    @version $Revision: 1.3 $
    @date $Date: 2005-06-19 19:06:10 +0200 (Sun, 19 Jun 2005) $
    @author tschmidt
*/

#include <I3Test.h>

#include <exception>
#include <string>

#include <interfaces/I3OMKey2MBID.h>
#include <phys-services/I3XMLOMKey2MBID.h>


using namespace std;


void initI3XMLOMKey2MBIDTest(I3OMKey2MBIDPtr& omkey2mbid,
                             const string& omkey2mbidFile)
{
  ENSURE(getenv("I3_WORK"));
  string infile(getenv("I3_WORK"));
  ENSURE(!infile.empty());
  infile.append("/phys-services/resources/");
  infile.append(omkey2mbidFile);
  omkey2mbid = I3OMKey2MBIDPtr(new I3XMLOMKey2MBID(infile));
  ENSURE(omkey2mbid);
}


TEST_GROUP(I3XMLOMKey2MBIDTest);


TEST(a_ctor)
{
  I3OMKey2MBIDPtr omkey2mbid;

  try{ 
    I3XMLOMKey2MBID tmp(""); 
    FAIL("didn't throw!");
  } catch(...) { }
  
  try { 
    I3XMLOMKey2MBID tmp("UnKNowNFiLE"); 
    FAIL("didnt' throw");
  } catch(...) { }
  
  try{ 
    initI3XMLOMKey2MBIDTest(omkey2mbid, "test_duplicated_OMKey_mainboard_ids.xml"); 
    FAIL("Didn't throw");
  } catch(...) { }
}


TEST(b_operations)
{
  I3OMKey2MBIDPtr omkey2mbid;
  OMKey key;
  long long int mbid;
  
  initI3XMLOMKey2MBIDTest(omkey2mbid, "test_basic_operations_mainboard_ids.xml");
  
  key = omkey2mbid->GetOMKey(3); 
  ENSURE_EQUAL(key.GetString(), 1);
  ENSURE_EQUAL(static_cast<int>(key.GetOM()), 3);

  try { 
    key = omkey2mbid->GetOMKey(33); 
    FAIL("didn't throw");
  } catch(...) { }
  
  key = OMKey(1, 3);
  mbid = omkey2mbid->GetMBID(key);
  ENSURE_EQUAL(mbid, 3);

  key = OMKey(1, 33);
  try { 
    mbid = omkey2mbid->GetMBID(key); 
    FAIL("didn't throw!");
  } catch(...) { }
}
