TEST_SRCDIR_NAMES := test new-test

CXX_BIN_SRCDIR_NAMES := 

USES_PROJECTS := dataclasses icetray root-icetray 

USES_TOOLS := root log4cplus TUT gsl boost sprng

ROOT_DICTIONARY_HEADERS := \
phys-services/I3Calculator.h \
phys-services/I3ParticleDataServiceFactory.h\
phys-services/I3PhysicsModule.h \
phys-services/I3RandomService.h \
phys-services/I3GSLRandomService.h \
phys-services/I3TRandomService.h \
phys-services/I3GSLRandomServiceFactory.h \
phys-services/I3TRandomServiceFactory.h\
phys-services/I3SPRNGRandomService.h \
phys-services/I3SPRNGRandomServiceFactory.h \
phys-services/I3ParticleDataService.h \
phys-services/I3FileOMKey2MBIDFactory.h \
phys-source/I3UberSource.h \
phys-source/I3DummyEventOriginFactory.h \
phys-source/I3DummyMonitoringOriginFactory.h \
phys-source/I3DummyGeoOriginFactory.h \
phys-source/I3DummyDetectorStatusOriginFactory.h \
phys-source/I3DummyCalibOriginFactory.h \
phys-source/I3FileGeoOriginFactory.h \
phys-source/I3PhysicsSource.h \
phys-source/I3GeometrySource.h \
phys-source/I3DetectorStatusSource.h \
phys-source/I3CalibrationSource.h \
phys-services/I3SPRNGRandomServiceFactory.h \
phys-services/I3SPRNGRandomService.h
