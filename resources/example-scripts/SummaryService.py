#!/usr/bin/env python 

from I3Tray import *
from os.path import expandvars

import sys

if len(sys.argv) == 2:
        infile = sys.argv[1]
else:
        print('Usage: %s <filename>' % sys.argv[0])
        sys.exit(1)
        
from icecube import icetray 
from icecube import dataclasses 
from icecube import phys_services 
from icecube import dataio 

tray = I3Tray()

tray.AddService("I3XMLSummaryServiceFactory","summary") (
    ("OutputFileName","i3summary.xml"),
	)

tray.AddModule("I3Reader","reader",FileName=infile)

tray.AddModule("I3EventCounter","counter")(
    ("PhysicsCounterName","GeneratedEvents"),
    ("CounterStep",100))

tray.AddModule("TrashCan","last")

tray.Execute()
tray.Finish()
