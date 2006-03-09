#!/usr/bin/env python
from I3Tray import *

from os.path import expandvars

load("libicetray")
load("libdataclasses")
load("libphys-services")

amageofile = expandvars("$I3_WORK/phys-services/resources/amanda.geo")
icecubegeofile = expandvars("$I3_WORK/phys-services/resources/icecube.geo")

tray = I3Tray()

tray.AddService("I3EmptyStreamsFactory","streams")(
              ("InstallGeometry",False)
                )

tray.AddService("I3TextFileGeometryServiceFactory","geometry")(
              ("AmandaGeoFile",amageofile),
              ("IceCubeGeoFile",icecubegeofile),
              )

tray.AddModule("I3Muxer","muxme")

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("GeometryKeys",
     "I3Geometry"),
    ("CalibrationKeys",
     "I3Calibration "
     "I3Geometry"),
    ("DetectorStatusKeys",
     "I3Calibration "
     "I3Geometry "
     "I3DetectorStatus"),
    ("PhysicsKeys",
     "I3Calibration "
     "I3Geometry "
     "I3DetectorStatus "
     "DrivingTime"),
    )

tray.AddModule("TrashCan","trash")

tray.Execute()
tray.Finish()
