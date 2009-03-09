#
# $Id$
#
i3_project(phys-services)

if (USE_ROOT)
  # These are the parts of phys-services that absolutely need ROOT to work.
  # For TRandomService, this is intrinsic to being related to TRandom.
  # I3MediumService could perhaps be moved out of this section.
  set(ROOT_SOURCES 
	private/phys-services/I3MediumService.cxx
	private/phys-services/I3MediumServiceFactory.cxx
	private/phys-services/I3TRandomService.cxx
	private/phys-services/I3TRandomServiceFactory.cxx
  )
endif (USE_ROOT)

i3_add_library(phys-services 
  private/empty-streams/I3EmptyCalibrationService.cxx
  private/empty-streams/I3EmptyDetectorStatusService.cxx
  private/empty-streams/I3EmptyEventService.cxx
  private/empty-streams/I3EmptyGeometryService.cxx
  private/empty-streams/I3EmptyStreamsFactory.cxx
  private/geo-selector/GeoSelUtils.cxx
  private/geo-selector/I3GeoTrimmers.cxx
  private/geo-selector/I3GeometrySelectorService.cxx
  private/geo-selector/I3GeometrySelectorServiceFactory.cxx
  private/geo-selector/I3StringAdderService.cxx
  private/geo-selector/I3StringAdderServiceFactory.cxx
  private/phys-services/I3Calculator.cxx
  private/phys-services/I3CascadeCutValues.cxx
  private/phys-services/I3CascadeCutValuesStd.cxx
  private/phys-services/I3CutValues.cxx
  private/phys-services/I3Cuts.cxx
  private/phys-services/I3CutsModule.cxx
  private/phys-services/I3CutsModuleStd.cxx
  private/phys-services/I3CutsStd.cxx
  private/phys-services/I3EventCounter.cxx
  private/phys-services/I3FileOMKey2MBID.cxx
  private/phys-services/I3FileOMKey2MBIDFactory.cxx
  private/phys-services/I3Functions.cxx
  private/phys-services/I3GSLRandomService.cxx
  private/phys-services/I3GSLRandomServiceFactory.cxx
  private/phys-services/I3MC2Reco.cxx
  private/phys-services/I3MediumPropertiesFile.cxx
  private/phys-services/I3SPRNGRandomService.cxx
  private/phys-services/I3SPRNGRandomServiceFactory.cxx
  private/phys-services/I3TrackCutValues.cxx
  private/phys-services/I3TrackCutValuesStd.cxx
  private/phys-services/I3VEMCalManipulator.cxx
  private/phys-services/I3VEMCalManipulatorFactory.cxx
  private/phys-services/I3XMLOMKey2MBID.cxx
  private/phys-services/I3XMLOMKey2MBIDFactory.cxx
  private/phys-services/I3XMLSummaryService.cxx
  private/phys-services/I3XMLSummaryServiceFactory.cxx
  private/phys-services/TWRTWRKey2ChannelID.cxx
  private/phys-services/Utility.cxx
  private/phys-source/I3Muxer.cxx
  private/phys-source/I3TextFileGeometryService.cxx
  private/phys-source/I3TextFileGeometryServiceFactory.cxx
  ${ROOT_SOURCES}

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
  USE_PROJECTS phys-services dataio)

i3_test_scripts(resources/scripts/*.py)

add_subdirectory(private/pybindings)
