from libithon import *
from os.path import expandvars

load('libicetray')
load('libroot-icetray')
load('libdataclasses')
load('libphys-services')

tray = I3Tray()

AmandaGeometryFile  = expandvars('$I3_WORK/phys-services/resources/amanda.geo')
IceCubeGeometryFile = expandvars('$I3_WORK/phys-services/resources/icecube.geo')
 
tray.AddModule('I3TextFileGeometrySource', 'geometry')
tray.SetParameter('geometry', 'AmandaGeoFile', AmandaGeometryFile)
tray.SetParameter('geometry', 'IceCubeGeoFile', IceCubeGeometryFile)

tray.AddModule("I3DummyPhysicsSource","events")

tray.ConnectBoxes('events', 'OutBox', 'geometry')
 
tray.Execute()
tray.Finish()
