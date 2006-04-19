#!/usr/bin/env python
#
#  photonics example
#
from I3Tray import *

from os.path import expandvars

import os
import sys

load("libdataclasses")
load("libphys-services")
load("libdataio")

amageofile = expandvars("$I3_WORK/phys-services/resources/amanda.geo")
icecubegeofile = expandvars("$I3_WORK/phys-services/resources/icecube.geo")

tray = I3Tray()

tray.AddService("I3EmptyStreamsFactory","empty_streams")( 
	("InstallGeometry",False),
	("InstallStatus",False),
	("InstallCalibration",False),
   	("NFrames",2))

tray.AddService("I3TextFileGeometryServiceFactory","geometry")(
              ("AmandaGeoFile",amageofile),
              ("IceCubeGeoFile",icecubegeofile))

tray.AddService("I3MCSourceServiceFactory","mcsource")

tray.AddModule("I3Muxer","muxer")

tray.AddModule("TrashCan", "the can")

tray.Execute()
tray.Finish()
