I3_PROJECT (phys-services)
USE_PROJECT(icetray)
USE_PROJECT(dataclasses)
USE_TOOL(sprng)
USE_TOOL(gsl)


FILE(GLOB phys-services_lib_source "private/phys-services/*.cxx"
				   "private/phys-source/*.cxx"
				   "private/geo-selector/*.cxx"
				   "private/empty-stream/*.cxx")

ROOTCINT()
ADD_LIBRARY(phys-services ${phys-services_lib_source} ${PROJECT_BINARY_DIR}/___Dict.cxx)

FILE(GLOB phys-services_test_source "private/test/*.cxx")
ADD_TEST(phys-services-test ${phys-services_test_source})


