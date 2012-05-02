#!/usr/bin/env python

from I3Tray import *
from icecube import icetray, dataio, phys_services
import sys

tray = I3Tray()
tray.AddModule('I3Reader', 'reader', FilenameList=sys.argv[1:])
#tray.AddModule('I3GCDAuditor', 'gcdaudit')
tray.AddModule('I3BadDOMAuditor', 'audit', Pulses=['OfflinePulses', 'OfflineIceTopHLCTankPulses'])
tray.AddModule('TrashCan', 'can')

tray.Execute()
tray.Finish()
