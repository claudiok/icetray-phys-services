#include <I3Test.h>

#include "phys-services/source/I3DefaultPhysicsSource.h"
#include "phys-services/source/I3DefaultCalibrationSource.h"
#include "phys-services/source/I3DefaultGeometrySource.h"
#include "phys-services/source/I3DefaultDetectorStatusSource.h"

#include "root-icetray/RootI3Tray.h"

TEST_GROUP(SourceOrderingTest);

TEST(correct_all4)
{
  RootI3Tray tray;

  tray.AddModule<I3DefaultPhysicsSource>("source");
  tray.AddModule<I3DefaultDetectorStatusSource>("status");
  tray.AddModule<I3DefaultCalibrationSource>("calib");
  tray.AddModule<I3DefaultGeometrySource>("geom");

  tray.ConnectBoxes("source","OutBox","status");
  tray.ConnectBoxes("status","OutBox","calib");
  tray.ConnectBoxes("calib","OutBox","geom");
  
  tray.Execute(10);
  
  tray.Finish();
}

TEST(correct_just3)
{
  RootI3Tray tray;

  tray.AddModule<I3DefaultPhysicsSource>("source");
  tray.AddModule<I3DefaultCalibrationSource>("calib");
  tray.AddModule<I3DefaultGeometrySource>("geom");

  tray.ConnectBoxes("source","OutBox","calib");
  tray.ConnectBoxes("calib","OutBox","geom");
  
  tray.Execute(10);
  
  tray.Finish();
}

TEST(bad_status_ordering)
{
  try
    {
      RootI3Tray tray;
      
      tray.AddModule<I3DefaultPhysicsSource>("source");
      tray.AddModule<I3DefaultDetectorStatusSource>("status");
      tray.AddModule<I3DefaultCalibrationSource>("calib");
      tray.AddModule<I3DefaultGeometrySource>("geom");
      
      tray.ConnectBoxes("source","OutBox","calib");
      tray.ConnectBoxes("calib","OutBox","geom");
      tray.ConnectBoxes("geom","OutBox","status");
      
      tray.Execute(10);
     
      ENSURE(0,"Shouldn't get this far.  This is supposed to be an error");
 
    }
  catch(const std::exception& e)
    {
      // all is well
    }
}


TEST(bad_calib_ordering)
{
  try
    {
      RootI3Tray tray;

      tray.AddModule<I3DefaultPhysicsSource>("source");
      tray.AddModule<I3DefaultDetectorStatusSource>("status");
      tray.AddModule<I3DefaultCalibrationSource>("calib");
      tray.AddModule<I3DefaultGeometrySource>("geom");
      
      tray.ConnectBoxes("source","OutBox","status");
      tray.ConnectBoxes("status","OutBox","geom");
      tray.ConnectBoxes("geom","OutBox","calib");
      
      tray.Execute(10);
    }
  catch(const std::exception& e)
    {
      // nothing to see here.  test passed.
    }
}
