#!/usr/bin/env python
from I3Tray import *

from os.path import expandvars

load("libicetray")
load("libdataclasses")
load("libdataio")
load("libphys-services")


tray = I3Tray()

tools  = expandvars("$I3_PORTS")
infile = tools + "/test-data/2006data/Run00089508.i3.gz"
nevent = -1

if(len(sys.argv)>=2):
    infile=sys.argv[1]
    nevent=int(sys.argv[2])
    
print "Input file:       ", infile
print "Number of frames: ", nevent


#**************************************************
#                 Reader & Muxer 
#**************************************************
tray.AddModule("I3Reader","reader")(
    ("Filename", infile)
    )

tray.AddService("I3VEMCalManipulatorFactory","vemcal")(
    ("OutputCalibrationService","CalibrationWithVEMCal"),
    ("Directory",""),
    ("File",""),
    ("UseDefaults", True), # If no directory or file are specified and "UseDefaults" is enabled default values will be used for all IceTop DOMs.
    )

tray.AddModule("I3MetaSynth","muxme")(
    ("CalibrationService","CalibrationWithVEMCal")
    )

tray.AddModule("Dump","dump")

tray.AddModule("FrameCheck","check")(
    ("ensure_physics_has", ["I3Calibration", "I3Geometry", "I3DetectorStatus",
                            "DrivingTime"])
    )

tray.AddModule("TrashCan","trash")

tray.Execute()
tray.Finish()
