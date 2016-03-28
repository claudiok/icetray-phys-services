#!/usr/bin/env python

from I3Tray import *
from icecube import icetray, dataio, phys_services
import sys

tray = I3Tray()
tray.AddModule('I3Reader', Filename=sys.argv[1])
tray.AddModule('I3GCDAuditor')

tray.Execute()
tray.Finish()
