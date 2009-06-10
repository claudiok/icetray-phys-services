#!/usr/bin/env python
#
#  use the standard messy monolith reader to get some data going.
#
from I3Tray import *

from os.path import expandvars

import os
import sys

#warning the semantics of I3Tray::Execute have changed from N-events
#to n-frames.  

load("libdataclasses")
load("libphys-services")
load("libdataio")

tray = I3Tray()

tray.AddService("I3ReaderServiceFactory","readerfactory")(
    ("Filename", expandvars("$I3_PORTS/test-data/string-21/MacOSX-libstdc++6-ppc.i3.gz"))
    )

tray.AddModule("I3Muxer","muxme")

tray.AddModule("Dump","dump")

tray.AddModule("CountFrames", "countem")(
    ("physics", 10),
    ("geometry", 1),
    ("calibration", 1),
    ("detectorstatus", 1)
    )

tray.AddModule("TrashCan", "the can");

tray.Execute(14)
tray.Finish()
