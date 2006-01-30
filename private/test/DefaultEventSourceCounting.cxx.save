#include <I3Test.h>

#include "root-icetray/RootI3Tray.h"

#include "phys-services/source/I3DefaultPhysicsSource.h"
#include "phys-services/source/I3DefaultCalibrationSource.h"
#include "phys-services/source/I3DefaultGeometrySource.h"
#include "phys-services/source/I3DefaultDetectorStatusSource.h"
#include "phys-services/source/I3DefaultMonitoringSource.h"

#include "FrameChecking.h"

// testing that if we ask the source for n events that
// we actually get n out of the other end
TEST_GROUP(DefaultEventSourceCounting);

struct count_events : public I3PhysicsModule
{
  int physicsCount;
  int expectedEvents;
  count_events(const I3Context& context) : I3PhysicsModule(context)
  {
    physicsCount = 0;
    expectedEvents = -1;
    AddOutBox("OutBox");
    AddParameter("expectedNumEvents","",expectedEvents);
  }

  void Configure()
  {
    GetParameter("expectedNumEvents",expectedEvents);
  }

  void Physics(I3Frame& frame)
  {
    physicsCount++;
  }

  void Finish()
  {
    ENSURE(expectedEvents==physicsCount);
  }
}; 

I3_MODULE(count_events);


inline void runTheCountingTest(int input,int output)
{
  RootI3Tray tray;
  
  tray.AddModule("I3DefaultPhysicsSource","eventssource");
  tray.SetParameter("eventssource","EventsToReturn",input);
  tray.AddModule("I3DefaultDetectorStatusSource","statussource");
  tray.AddModule("I3DefaultCalibrationSource","calibsource");
  tray.AddModule("I3DefaultGeometrySource","geomsource");
  tray.AddModule("count_events","count");
  tray.SetParameter("count","expectedNumEvents",output);
  
  tray.ConnectBoxes("eventssource","OutBox","statussource");
  tray.ConnectBoxes("statussource","OutBox","calibsource");
  tray.ConnectBoxes("calibsource","OutBox","geomsource");
  tray.ConnectBoxes("geomsource","OutBox","count");
  
  tray.Execute();
  tray.Finish();
}

TEST(test_1_event)
{
runTheCountingTest(1,1);
}

TEST(test_2_event)
{
runTheCountingTest(2,2);
}

TEST(test_25_event)
{
runTheCountingTest(25,25);
}

