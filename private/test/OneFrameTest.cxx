#include <I3Test.h>
#include <icetray/I3Module.h>
#include <icetray/I3Tray.h>

TEST_GROUP(OneFrameTest);

class I3OneFrameTester : public I3Module
{
public:
  I3OneFrameTester(const I3Context& context) : I3Module(context)
  {
    ENSURE(!instance);
    instance = this;
    physicsCalls = 0;
    AddOutBox("OutBox");
  }

  virtual ~I3OneFrameTester()
  {
    instance = 0;
  }

  void Physics(I3FramePtr frame)
  {
    physicsCalls++;
    PushFrame(frame,"OutBox");
  }

  int physicsCalls;

  static I3OneFrameTester* instance;
};

I3_MODULE(I3OneFrameTester);

I3OneFrameTester* I3OneFrameTester::instance = 0;

TEST(oneframe)
{
  I3Tray tray;
  tray.AddModule("I3InfiniteSource","empty_streams")
    ("Stream",I3Frame::Physics) 
    ("NFrames",1)

  tray.AddModule("I3OneFrameTester","test");

  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
  ENSURE(I3OneFrameTester::instance);
  ENSURE_EQUAL(I3OneFrameTester::instance->physicsCalls,1);
}
