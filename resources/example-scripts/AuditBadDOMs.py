#!/usr/bin/env python

from I3Tray import I3Tray
from icecube import icetray, dataio, phys_services
import sys

tray = I3Tray()
tray.AddModule('I3Reader', FilenameList=sys.argv[1:])
tray.AddModule('I3BadDOMAuditor', Pulses=['OfflinePulses', 'OfflineIceTopHLCTankPulses'])
tray.Execute()
tray.Finish()
