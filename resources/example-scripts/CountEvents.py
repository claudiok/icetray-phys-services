#!/usr/bin/env python 

from I3Tray import *
from os.path import expandvars

import sys

if len(sys.argv) == 2:
        infile = sys.argv[1]
else:
        print 'Usage: CountEvents <filename>'
        sys.exit(1)
        
load("libicetray")
load("libdataclasses")
load("libphys-services")
load("libdataio")

tray = I3Tray()

tray.AddService("I3ReaderServiceFactory","read")(
    ("FileName",infile),
    ("SkipUnregistered",True))

tray.AddModule("I3Muxer","muxer")

tray.AddModule("I3EventCounter","counter")(
    ("EventHeaderName","I3EventHeader"),
    ("CounterStep",100))

tray.AddModule("TrashCan","last")

tray.Execute()
tray.Finish()
