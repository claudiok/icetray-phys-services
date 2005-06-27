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

tray.AddModule('I3DefaultCalibrationSource', 'calibration')
tray.AddModule('I3DefaultDetectorStatusSource', 'detectorstatus')
tray.AddModule('I3DefaultPhysicsSource', 'events')

tray.AddModule('I3MCCalibrationFiller', 'calibfiller')
tray.SetParameter('calibfiller', 'ATWD0gain', -16.0)
tray.SetParameter('calibfiller', 'ATWD1gain', -2.0)
tray.SetParameter('calibfiller', 'ATWD2gain', -0.25)
tray.SetParameter('calibfiller', 'FADCgain', 22.5)

tray.AddModule('I3MCRawDOMStatusFiller', 'domstatusfiller')
tray.SetParameter('domstatusfiller', 'speThreshold', 4.0)

tray.AddModule('I3CalibrateStatusModule', 'calibratestatus')

tray.ConnectBoxes('events', 'OutBox', 'detectorstatus')
tray.ConnectBoxes('detectorstatus', 'OutBox', 'calibration')
tray.ConnectBoxes('calibration', 'OutBox', 'geometry')
tray.ConnectBoxes('geometry', 'OutBox', 'calibfiller')
tray.ConnectBoxes('calibfiller', 'OutBox', 'domstatusfiller')
tray.ConnectBoxes('domstatusfiller', 'OutBox', 'calibratestatus')
 
tray.Execute()
tray.Finish()
