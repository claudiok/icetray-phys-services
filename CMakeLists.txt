PROJECT(phys-services)

LIB (private/phys-services/*.cxx
  private/phys-source/*.cxx
  private/geo-selector/*.cxx
  private/empty-streams/*.cxx
  )

USE_TOOLS(sprng gsl log4cplus boost root)

USE_PROJECTS(icetray dataclasses)

ROOTCINT(phys-services/I3Calculator.h
  phys-services/I3Cuts.h
  phys-services/I3CutValues.h)

TEST_EXECUTABLE(test private/test/*.cxx)


