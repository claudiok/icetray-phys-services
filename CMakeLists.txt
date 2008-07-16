#
# $Id$
#
i3_project(phys-services)

i3_add_library(phys-services 
  private/phys-services/*.cxx
  private/phys-source/*.cxx
  private/geo-selector/*.cxx
  private/empty-streams/*.cxx

  USE_PROJECTS icetray dataclasses interfaces

  USE_TOOLS sprng gsl log4cplus boost root python

  ROOTCINT public/phys-services/I3Calculator.h
  public/phys-services/I3Cuts.h
  public/phys-services/I3CutsStd.h
  public/phys-services/I3TrackCutValues.h
  public/phys-services/I3CascadeCutValues.h
  public/phys-services/I3TrackCutValuesStd.h
  public/phys-services/I3CascadeCutValuesStd.h
  )

i3_executable(CreateXMLOMKey2MBIDConversionTable
  private/CreateXMLOMKey2MBIDConversionTable/*.cxx
  USE_PROJECTS phys-services)

i3_test_executable(test private/test/*.cxx
  USE_PROJECTS phys-services)


i3_test_scripts(resources/scripts/*.py)

add_subdirectory(private/pybindings)
