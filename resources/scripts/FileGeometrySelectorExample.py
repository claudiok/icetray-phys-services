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

tray.AddModule("I3GeometrySelector","geo_selector")(
    ("StringsToUse","21,29,39,38,30,40,49"),
    ("StationsToUse","21,29,39,38,30,40,49,50")
    )

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("ensure_physics_has", ["I3Calibration", "I3Geometry", "NewGeometry", "I3DetectorStatus",
                            "DrivingTime"])
    )

tray.AddModule("TrashCan","trash")

tray.Execute()
tray.Finish()
