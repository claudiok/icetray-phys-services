from libithon import *
from os.path import expandvars

load('libicetray')
load('libroot-icetray')
load('libdataclasses')
load('libphys-services')
load('libamanda-core')

load('libPSInterface')
load('libhit-constructor')
load('libromeo')
load('libromeo-amanda.so')
load('libromeo-interface.so')
load('libDOMsimulator.so')
load('libDOMcalibrator.so')

tray = I3Tray()

F2kCascadeFile = expandvars('$I3_WORK/hit-constructor/resources/gevshower.f2k')

tray.AddService('I3F2kFileFactory', 'f2k')
tray.SetParameter('f2k', 'Infile', F2kCascadeFile)

tray.AddModule('I3F2kEventSource', 'f2kevent')
tray.SetParameter('f2kevent', 'NumberEvents', 2)

tray.AddService('I3PSI_PhotonicsFactory', 'psi_photonics');
tray.AddService('I3TRandomServiceFactory', 'random')

AmandaGeometryFile  = expandvars('$I3_WORK/phys-services/resources/amanda.geo')
IceCubeGeometryFile = expandvars('$I3_WORK/phys-services/resources/icecube.geo')

print AmandaGeometryFile

tray.AddModule('I3TextFileGeometrySource', 'geometry')
tray.SetParameter('geometry', 'AmandaGeoFile', AmandaGeometryFile)
tray.SetParameter('geometry', 'IceCubeGeoFile', IceCubeGeometryFile)

tray.AddModule('I3DefaultCalibrationSource', 'calibration')
tray.AddModule('I3DefaultDetectorStatusSource', 'detectorstatus')
#tray.AddModule('I3DefaultPhysicsSource', 'events')

tray.AddModule('I3MCCalibrationFiller', 'calibfiller')
tray.SetParameter('calibfiller', 'ATWD0gain', -16.0)
tray.SetParameter('calibfiller', 'ATWD1gain', -2.0)
tray.SetParameter('calibfiller', 'ATWD2gain', -0.25)
tray.SetParameter('calibfiller', 'FADCgain', 22.5)

tray.AddModule('I3MCRawDOMStatusFiller', 'domstatusfiller')
tray.SetParameter('domstatusfiller', 'speThreshold', 4.0)

tray.AddModule('I3CalibrateStatusModule', 'calibratestatus')

tray.AddModule('I3TestSources', 'testsources')

tray.AddModule('I3HitConstructor', 'hits')

tray.AddModule('I3RomeoInterfaceModule', 'romeo')
tray.SetParameter('romeo', 'BinSize',
                  1.0e-9)
tray.SetParameter('romeo', 'CEData',
                  expandvars('$I3_WORK/romeo/resources/scripts/TA0532.table'))
tray.SetParameter('romeo', 'QEData',
                  expandvars('$I3_WORK/romeo/resources/scripts/qe_representative.data'))
tray.SetParameter('romeo', 'GainTable',
                  expandvars('$I3_WORK/romeo/resources/scripts/TA0451_gain.table'))
tray.SetParameter('romeo', 'PhotonPropMap_data',
                  expandvars('$I3_WORK/romeo/resources/scripts/QuickPhotonPropagatorMap.data'))
tray.SetParameter('romeo', 'WavelengthAcceptance_data',
                  expandvars('$I3_WORK/romeo/resources/scripts/wavelength_acceptance.data'))
tray.SetParameter('romeo', 'AngleAcceptance_data',
                  expandvars('$I3_WORK/romeo/resources/scripts/angle_acceptance.data'))

tray.AddModule('I3DOMsimulator', 'domsimulator')
tray.AddModule('I3DOMcalibrator', 'domcalibrator')

tray.ConnectBoxes('f2kevent', 'OutBox', 'detectorstatus')
tray.ConnectBoxes('detectorstatus', 'OutBox', 'calibration')
tray.ConnectBoxes('calibration', 'OutBox', 'geometry')
tray.ConnectBoxes('geometry', 'OutBox', 'calibfiller')
tray.ConnectBoxes('calibfiller', 'OutBox', 'domstatusfiller')
tray.ConnectBoxes('domstatusfiller', 'OutBox', 'calibratestatus')
tray.ConnectBoxes('calibratestatus', 'OutBox', 'testsources')
tray.ConnectBoxes('testsources', 'OutBox', 'hits')
tray.ConnectBoxes('hits', 'OutBox', 'romeo')
tray.ConnectBoxes('romeo', 'OutBox', 'domsimulator')
tray.ConnectBoxes('domsimulator', 'OutBox', 'domcalibrator')

tray.Execute()
tray.Finish()
