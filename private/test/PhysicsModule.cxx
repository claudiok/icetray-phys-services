#include <I3Test.h>

#include <dataclasses/I3Event.h>
#include <dataclasses/I3EventHeader.h>
#include <dataclasses/I3MCEvent.h>
#include <dataclasses/I3MCEventHeader.h>
#include <dataclasses/I3Calibration.h>
#include <dataclasses/I3CalibrationHeader.h>
#include <dataclasses/I3Geometry.h>
#include <dataclasses/I3GeometryHeader.h>
#include <dataclasses/I3DetectorStatus.h>
#include <dataclasses/I3DetectorStatusHeader.h>
#include <root-icetray/RootI3Tray.h>
#include <root-icetray/RootI3Stream.h>
#include <root-icetray/RootI3Frame.h>
#include <root-icetray/RootI3Execution.h>
#include <phys-services/I3PhysicsModule.h>

TEST_GROUP(PhysicsModule);

#define TEST_CLASS(C) \
ENSURE(!Has ## C(frame)); I3 ## C ## Ptr C ## ptr(new I3 ## C); \
Put ## C(frame, C ## ptr); ENSURE(Has ## C(frame)); \
try { Put ## C(frame, C ## ptr); FAIL("didn't throw"); } catch (...) { }


namespace PhysicsModuleInterfaceTests 
{
  class testmodule : public I3PhysicsModule
  {
  public:
    testmodule(I3Context& c) : I3PhysicsModule(c) { }
    virtual ~testmodule() { }
    void do_test()
    {
      RootI3Execution execution;
      RootI3Stream::Install();
      I3Stream& stream = I3Stream::AddStream("teststream", "desc");
      {
	RootI3Frame frame(stream, execution);

	TEST_CLASS(Event);
	TEST_CLASS(EventHeader);
      }
      { 
	RootI3Frame frame(stream, execution);
	TEST_CLASS(MCEvent);
	TEST_CLASS(MCEventHeader);

	TEST_CLASS(Calibration); 
	TEST_CLASS(CalibrationHeader);

	TEST_CLASS(Geometry);
	TEST_CLASS(GeometryHeader);

	TEST_CLASS(DetectorStatus);
	TEST_CLASS(DetectorStatusHeader);
      }      
      
      { 
	RootI3Frame frame(stream, execution);
	ENSURE(!HasMCEvent(frame));
	ENSURE(!HasEvent(frame));
	I3MCEventPtr mce(new I3MCEvent);
	ENSURE(PutMCEvent(frame, mce));
	ENSURE(HasMCEvent(frame));
	ENSURE(HasEvent(frame));
	GetMCEvent(frame);
	ENSURE(&(GetEvent(frame)) == mce.get());
	I3Event& e = GetMCEvent(frame);
	ENSURE(&e == mce.get());
      }      

      { 
	RootI3Frame frame(stream, execution);
	TEST_CLASS(Event);
	ENSURE(!HasMCEvent(frame));
      }      
    }
  };

  TEST(frame_access_inconvenience_functions)
  {
    RootI3Context c;
    RootI3ExecutionPtr execptr(new RootI3Execution);
    shared_ptr<I3ContextElement<I3Execution> > ce(new I3ContextElement<I3Execution>(execptr));
    c.PutElement(ce, I3Execution::DefaultName());
    testmodule m(c);
    m.do_test();
  }
}


