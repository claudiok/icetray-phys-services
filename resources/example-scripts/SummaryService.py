#!/usr/bin/env python 

from I3Tray import *
from os.path import expandvars

import sys

if len(sys.argv) == 2:
        infile = sys.argv[1]
else:
        print 'Usage: %s <filename>' % sys.argv[0]
        sys.exit(1)
        
load("libicetray")
load("libdataclasses")
load("libphys-services")
load("libdataio")

tray = I3Tray()

tray.AddService("I3ReaderServiceFactory","read")(
    ("FileName",infile),
    ("SkipUnregistered",True))

tray.AddService("I3XMLSummaryServiceFactory","summary") (
    ("OutputFileName","i3summary.xml"),
	)

tray.AddModule("I3Muxer","muxer")

tray.AddModule("I3EventCounter","counter")(
    ("PhysicsCounterName","GeneratedEvents"),
    ("CounterStep",100))

tray.AddModule("TrashCan","last")

tray.Execute()
tray.Finish()