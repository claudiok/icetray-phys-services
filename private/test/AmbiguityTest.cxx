#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "dataclasses/I3BasicTrack.h"
#include "dataclasses/I3Position.h"

using namespace I3Calculator;

double Time(I3TrackPtr) { return 1; }
double Time(I3CascadePtr) { return 2; }
I3BasicTrackPtr track (new I3BasicTrack);

TEST_GROUP(Ambiguity)

TEST(One)
{
  double t = Time(dynamic_pointer_cast<I3Track>(track));
  cout<<"t="<<t<<endl;
}

TEST(Two)
{
  double t = Time(dynamic_pointer_cast<I3Cascade>(track));
  cout<<"t="<<t<<endl;
}

/*
TEST(Three)
{
  double t = Time(track);
  cout<<"t="<<t<<endl;
}
*/
