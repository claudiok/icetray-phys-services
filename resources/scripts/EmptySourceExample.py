#!/usr/bin/env python

from I3Tray import *

load("libdataclasses")
load("libphys-services")

tray = I3Tray()

tray.AddService("I3EmptyStreamsFactory","emptystreams")

tray.AddModule("I3Muxer","muxer")

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("ensure_physics_has", ["I3Calibration", "I3Geometry", "I3DetectorStatus", "DrivingTime"]),
    ("ensure_detectorstatus_has", ["I3Calibration", "I3Geometry", "I3DetectorStatus"]),
    ("ensure_calibration_has", ["I3Calibration", "I3Geometry"]),
    ("ensure_geometry_has", ["I3Geometry"])
    )

tray.AddModule("TrashCan","trash")

tray.Execute(10)
tray.Finish()
