#!/usr/bin/env python

from I3Tray import *
from icecube import icetray, dataio, phys_services
import sys

tray = I3Tray()
tray.AddModule('I3Reader', 'reader', Filename=sys.argv[1])
tray.AddModule('I3GCDAuditor', 'audit')#, AMANDAIsAnError=False)
tray.AddModule('TrashCan', 'can')

tray.Execute()
tray.Finish()
