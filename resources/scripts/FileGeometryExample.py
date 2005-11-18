from I3Tray import *

from os.path import expandvars

load("libicetray")
load("libroot-icetray")
load("libdataclasses")
load("libphys-services")

tray = I3Tray()

tray.AddModule("I3DefaultPhysicsSource","events")

tray.AddModule("I3DefaultDetectorStatusSource","status")

tray.AddModule("I3DefaultCalibrationSource","calib")

tray.AddModule("I3FileGeometrySource","geometry")
amageofile = expandvars("$I3_WORK/phys-services/resources/amanda.geo")
icecubegeofile = expandvars("$I3_WORK/phys-services/resources/icecube.geo")
tray.SetParameter("geometry","AmandaGeoFile",amageofile)
tray.SetParameter("geometry","IceCubeGeoFile",icecubegeofile)

tray.ConnectBoxes("events","OutBox","status")
tray.ConnectBoxes("status","OutBox","calib")
tray.ConnectBoxes("calib","OutBox","geometry")

tray.Execute()
tray.Finish()
