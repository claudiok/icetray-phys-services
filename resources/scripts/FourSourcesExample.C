{
gSystem->Load("libicetray");
gSystem->Load("libdataclasses");
gSystem->Load("libroot-icetray");
gSystem->Load("libphys-services");

RootI3Tray tray;

// Adding the four 'Origin' services required by I3UberSource
tray.AddService("I3DummyEventOriginFactory","events");
tray.AddService("I3DummyDetectorStatusOriginFactory","status");
tray.AddService("I3DummyGeoOriginFactory","geo");
tray.AddService("I3DummyCalibOriginFactory","calib");

// Adding the four modules which will look at these interfaces
// There's nothing here that will output anything.  Crank the
// verbosity up if you want to see something happening
tray.AddModule("I3PhysicsSource","physsource");
tray.AddModule("I3DetectorStatusSource","statussource");
tray.AddModule("I3CalibrationSource","calibsource");
tray.AddModule("I3GeometrySource","geomsource");

tray.ConnectBoxes("physsource","OutBox","statussource");
tray.ConnectBoxes("statussource","OutBox","calibsource");
tray.ConnectBoxes("calibsource","OutBox","geomsource");


tray.Execute();
tray.Finish();

exit(0);
}
