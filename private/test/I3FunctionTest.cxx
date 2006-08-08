/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorTest.cxx 9161 2005-06-14 16:44:58Z pretz $

    @version $Revision: 1.2 $
    @date $Date: 2005-06-14 12:44:58 -0400 (Tue, 14 Jun 2005) $
    @author dule

    @todo
*/

#include <I3Test.h>

#include "phys-services/I3Functions.h"
#include <string>
using namespace std;

TEST_GROUP(I3Functions)

TEST(ParseFilename)
{
  string searchpattern(getenv("I3_TOOLS"));
  searchpattern.append("/test-data/amanda/*.f2k");  //4
  searchpattern.append(";");
  searchpattern.append(getenv("I3_TOOLS"));
  searchpattern.append("/test-data/ama-*.*"); // 4

  vector<string> v = I3Functions::ParseFilename(searchpattern);
  for(vector<string>::iterator iter=v.begin(); iter!=v.end(); iter++)
  {
    cout<<*iter<<endl;
  }

  ENSURE(v.size()==8,"Didn't find the expected number of files");
}
