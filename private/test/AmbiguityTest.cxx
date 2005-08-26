#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "dataclasses/I3BasicTrack.h"
#include "dataclasses/I3CompleteCascade.h"
#include "dataclasses/I3Position.h"

using namespace I3Calculator;

const double TRACK = 1;
const double CASCADE = 2;

TEST_GROUP(Ambiguity);

namespace AmbiguityTests 
{

  double Time(const I3Track& t) { return TRACK; }
  double Time(const I3Cascade& c) { return CASCADE; }

  double TimeFromSharedPtr(I3TrackPtr spt) { return TRACK; }
  double TimeFromSharedPtr(I3CascadePtr spc) { return CASCADE; }

  double TimeFromDumbPtr(I3Track* dpt) { return TRACK; }
  double TimeFromDumbPtr(I3Cascade* dpc) { return CASCADE; }


  TEST(ByReferenceFromAnObject)
  {
    I3BasicTrack bt;
    ENSURE(Time(bt) == TRACK);
    I3CompleteCascade cc;
    ENSURE(Time(cc) == CASCADE);
  }

  TEST(ByDumbPtr)
  {
    I3BasicTrack* btp;
    ENSURE(TimeFromDumbPtr(btp) == TRACK);
    I3CompleteCascade* ccp;
    ENSURE(TimeFromDumbPtr(ccp) == CASCADE);
  }

  TEST(BySharedPtr)
  {
    shared_ptr<I3BasicTrack> btp (new I3BasicTrack);

    // doesn't compile.  Looks like it should.
    // ENSURE(TimeFromSharedPtr(btp) == TRACK);

    // do this instead, it's faster and makes your Time() function signatures clearer.
    ENSURE(Time(*btp) == TRACK);

    shared_ptr<I3CompleteCascade> ccp(new I3CompleteCascade);

    // ditto.  Bad:
    // ENSURE(TimeFromSharedPtr(ccp) == CASCADE);

    // good:
    ENSURE(Time(*ccp) == CASCADE);

  }

}
