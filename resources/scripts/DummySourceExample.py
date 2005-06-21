# This is a python script.  
from libithon import *

# required libraries
load("libicetray")
load("libroot-icetray")
load("libdataclasses")
load("libphys-services")

# creating icetray
tray = I3Tray()

# Pay special attention to the order of these modules.  
# It starts with the fastest stream and then works
# to the slowest stream.  This order is important
#
# The 'Dummy' implementations of the source modules
# just issue empty events/statuses/calibrations/geometries
# and functional examples would actually fill important data

# This module spits out 10 events then quits. 
tray.AddModule("I3DummyPhysicsSource","events")

# This module insures that the DetectorStatus is current.
# If it isn't current, it will fill an empty one and issue
# a DetectorStatus frame. Otherwise
# it just ensures that the event frames have DetectorStatuses
# in them
tray.AddModule("I3DummyDetectorStatusSource","status")

# This module functions just the same as the DetectorStatus
# but updates the Calibration
tray.AddModule("I3DummyCalibrationSource","calib")

# Just like the DetectorStatus and Calibration Source modules,
# this module works to ensure that the Geometry is current
tray.AddModule("I3DummyGeometrySource","geometry")

tray.ConnectBoxes("events","OutBox","status")
tray.ConnectBoxes("status","OutBox","calib")
tray.ConnectBoxes("calib","OutBox","geometry")

tray.Execute()
tray.Finish()
