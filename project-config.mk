TEST_SRCDIR_NAMES := test

# Anything you don't want to compile (must be full path?)
CXX_EXCLUDE_SRCS :=

# public directories for these projects are added to #include path,
# and libraries are added to link.
USES_PROJECTS := dataclasses icetray root-icetray 

# same as above, but for external tools.  Paths found in config.mk
USES_TOOLS := root roost log4cplus TUT gsl boost

ROOT_DICTIONARY_HEADERS := \
phys-services/I3Calculator.h \
phys-services/I3ParticleDataServiceFactory.h\
phys-services/I3CalculatorFactoryImpl.h \
phys-services/I3PhysicsModule.h \
phys-services/I3CalculatorImpl.h \
phys-services/I3RandomService.h \
phys-services/I3GSLRandomService.h \
phys-services/I3TRandomService.h \
phys-services/I3GSLRandomServiceFactory.h \
phys-services/I3TRandomServiceFactory.h\
phys-services/I3ParticleDataService.h \
phys-services/I3FileOMKey2MBIDFactory.h \
phys-source/I3PhysicsSource.h \
phys-source/I3DummyEventOriginFactory.h \
phys-source/I3DummyGeoOriginFactory.h \
phys-source/I3DummyCalibOriginFactory.h \
phys-source/I3FileGeoOriginFactory.h
