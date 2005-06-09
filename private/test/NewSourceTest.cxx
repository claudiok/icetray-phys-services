#include "TUT/tut.h"

#include "root-icetray/RootI3Tray.h"
#include "phys-source/I3DummyPhysicsSource.h"
#include "phys-source/I3DummyGeometrySource.h"
#include "phys-source/I3DummyCalibrationSource.h"
#include "phys-source/I3DummyDetectorStatusSource.h"


namespace tut
{
  struct NewSourceTest
  {
  };

  typedef test_group<NewSourceTest> factory;
  typedef factory::object object;

}

namespace
{
  static tut::factory t("NewSourceTest");
}

namespace tut
{
  struct PrintingModule : public I3PhysicsModule
  {
    PrintingModule(I3Context& c) : I3PhysicsModule(c)
    {
      AddOutBox("OutBox");
    }

    void Physics(I3Frame& frame) 
    { 
      cout<<GetEventHeader(frame)<<endl;
      cout<<GetEvent(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
    
    void Geometry(I3Frame& frame)
    {
      cout<<GetGeometryHeader(frame)<<endl;
      cout<<GetGeometry(frame)<<endl;
      PushFrame(frame,"OutBox");
    }

    void DetectorStatus(I3Frame& frame)
    {
      cout<<GetDetectorStatusHeader(frame)<<endl;
      cout<<GetDetectorStatus(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
    
    void Calibration(I3Frame& frame)
    {
      cout<<GetCalibrationHeader(frame)<<endl;
      cout<<GetCalibration(frame)<<endl;
      PushFrame(frame,"OutBox");
    }

  };

  template<> template<>
  void object::test<1>() 
  {
    RootI3Tray tray;
    tray.AddModule<I3DummyPhysicsSource>("physics");
    tray.AddModule<I3DummyGeometrySource>("geometry");
    tray.AddModule<I3DummyCalibrationSource>("calib");
    tray.AddModule<I3DummyDetectorStatusSource>("status");
    tray.AddModule<PrintingModule>("print");
      
    tray.ConnectBoxes("physics","OutBox","geometry");
    tray.ConnectBoxes("geometry","OutBox","calib");
    tray.ConnectBoxes("calib","OutBox","status");
    tray.ConnectBoxes("status","OutBox","print");

    tray.Execute();

    tray.Finish();
      
      
  }
}
