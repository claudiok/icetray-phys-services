#include <I3Test.h>

#include "root-icetray/RootI3Tray.h"

#include "phys-source/I3DummyPhysicsSource.h"
#include "phys-source/I3DummyCalibrationSource.h"
#include "phys-source/I3DummyGeometrySource.h"
#include "phys-source/I3DummyDetectorStatusSource.h"
#include "phys-source/I3DummyMonitoringSource.h"

#include "FrameChecking.h"

// testing that if we ask the source for n events that
// we actually get n out of the other end
TEST_GROUP(DummyEventSourceCounting);

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
  
  tray.AddModule("I3DummyPhysicsSource","eventssource");
  tray.SetParameter("eventssource","EventsToReturn",input);
  tray.AddModule("I3DummyDetectorStatusSource","statussource");
  tray.AddModule("I3DummyCalibrationSource","calibsource");
  tray.AddModule("I3DummyGeometrySource","geomsource");
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

