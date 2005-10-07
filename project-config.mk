TEST_SRCDIR_NAMES := test 

CXX_BIN_SRCDIR_NAMES := 

USES_PROJECTS := dataclasses icetray root-icetray 

USES_TOOLS := root log4cplus gsl boost sprng

ROOT_DICTIONARY_HEADERS := \
phys-services/I3Calculator.h \
phys-services/I3PhysicsModule.h \
phys-services/I3RandomService.h \
phys-services/I3GSLRandomService.h \
phys-services/I3TRandomService.h \
phys-services/I3GSLRandomServiceFactory.h \
phys-services/I3TRandomServiceFactory.h\
phys-services/I3SPRNGRandomService.h \
phys-services/I3SPRNGRandomServiceFactory.h \
phys-services/I3FileOMKey2MBIDFactory.h \
phys-services/I3MediumServiceFactory.h \
phys-source/I3DefaultDetectorStatusSource.h \
phys-source/I3DefaultCalibrationSource.h \
phys-source/I3DefaultMonitoringSource.h \
phys-source/I3DefaultPhysicsSource.h \
phys-source/I3DefaultGeometrySource.h \
phys-source/I3PhysicsSource.h \
phys-source/I3MonitoringSource.h \
phys-source/I3GeometrySource.h \
phys-source/I3DetectorStatusSource.h \
phys-source/I3CalibrationSource.h \
phys-services/I3SPRNGRandomServiceFactory.h \
phys-services/I3SPRNGRandomService.h \
phys-source/I3CalibrateStatusModule.h \
phys-source/I3TextFileGeometrySource.h \
phys-source/I3MCCalibrationFiller.h \
phys-source/I3MCRawDOMStatusFiller.h 


