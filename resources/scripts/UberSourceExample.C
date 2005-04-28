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

// Yes, I'm just adding this one module. This is very boring
// output.  If you crank the  verbosity up, you'll see it's working
tray.AddModule("I3UberSource","source");


tray.Execute();
tray.Finish();

exit(0);
}
