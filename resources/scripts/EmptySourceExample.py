#!/usr/bin/env python

from I3Tray import *

load("libdataclasses")
load("libphys-services")

tray = I3Tray()

tray.AddService("I3EmptyStreamsFactory","emptystreams")

tray.AddModule("I3Muxer","muxer")

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("PhysicsKeys",
     "I3Calibration "
     "I3Geometry "
     "I3DetectorStatus "
     "DrivingTime"),
    )

tray.AddModule("TrashCan","trash")

tray.Execute(10)
tray.Finish()
