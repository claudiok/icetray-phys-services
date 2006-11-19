PROJECT(phys-services)

LIB (phys-services
  private/phys-services/*.cxx
  private/phys-source/*.cxx
  private/geo-selector/*.cxx
  private/empty-stream/*.cxx
  )

USE_TOOLS(sprng gsl log4cplus boost root)

USE_PROJECTS(icetray dataclasses)

ROOTCINT(phys-services/I3Calculator.h
  phys-services/I3Cuts.h
  phys-services/I3CutValues.h)

FILE(GLOB phys-services_test_source private/test/*.cxx)
ADD_TEST(phys-services-test ${phys-services_test_source})


