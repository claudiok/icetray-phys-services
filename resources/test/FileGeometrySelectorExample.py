#!/usr/bin/env python
from I3Tray import *

from os.path import expandvars

load("libicetray")
load("libdataclasses")
load("libphys-services")

amageofile = expandvars("$I3_SRC/phys-services/resources/amanda.geo")
icecubegeofile = expandvars("$I3_SRC/phys-services/resources/icecube.geo")

tray = I3Tray()

tray.AddService("I3TextFileGeometryServiceFactory","geometry")(
              ("AmandaGeoFile",amageofile),
              ("IceCubeGeoFile",icecubegeofile),
              )

tray.AddService("I3GeometrySelectorServiceFactory","geo_selector")(
    ("StringsToUse","21,29,39,38,30,40,49"),
    ("StationsToUse","21,29,39,38,30,40,49,50"),
    ("GeoSelectorName","I3GeometrySelectorService")
    )

tray.AddModule("I3InfiniteSource","muxme",Stream=icetray.I3Frame.Physics, Nframes=1)

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("ensure_physics_has", ["I3Calibration", "I3Geometry", "I3DetectorStatus",
                            "DrivingTime"])
    )

tray.AddModule("TrashCan","trash")

tray.Execute()
tray.Finish()
