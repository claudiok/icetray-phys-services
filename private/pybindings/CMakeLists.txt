if(SPRNG_FOUND)
  ADD_DEFINITIONS(-DI3_USE_SPRNG)
endif(SPRNG_FOUND)

i3_add_pybindings(phys_services
  I3Calculator.cxx
  I3ScaleCalculator.cxx
  I3CutValues.cxx
  I3CascadeCutValues.cxx
  Converter.cxx
  RandomServices.cxx
  I3Cuts.cxx
  I3Splitter.cxx
  I3XMLOMKey2MBID.cxx
  I3GCDFileService.cxx
  module.cxx
  USE_TOOLS boost python 
  USE_PROJECTS phys-services interfaces
  )
