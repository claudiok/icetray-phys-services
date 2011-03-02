#!/usr/bin/env python
from I3Tray import *

from os.path import expandvars

load("libicetray")
load("libdataclasses")
load("libphys-services")

amageofile = expandvars("$I3_SRC/phys-services/resources/amanda.geo")
icecubegeofile = expandvars("$I3_SRC/phys-services/resources/icecube.geo")

tray = I3Tray()

tray.AddModule("I3InfiniteSource","streams",stream=icetray.I3Frame.Physics)

tray.AddService("I3TextFileGeometryServiceFactory","geometry")(
              ("AmandaGeoFile",amageofile),
              ("IceCubeGeoFile",icecubegeofile),
              )

tray.AddModule("I3MetaSynth","muxme")

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("ensure_physics_has", ["I3Calibration", "I3Geometry", "I3DetectorStatus", "DrivingTime"])
    )

tray.AddModule("TrashCan","trash")

tray.Execute()
tray.Finish()
