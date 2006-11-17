PROJECT (phys-services)

include_directories(public private ${CMAKE_SOURCE_DIR}/icetray/public ${CMAKE_SOURCE_DIR}/dataclasses/public)

FILE(GLOB phys-services_lib_source "private/phys-services/*.cxx"
				   "private/phys-source/*.cxx"
				   "private/geo-selector/*.cxx"
				   "private/empty-stream/*.cxx")

ADD_LIBRARY(phys-services ${phys-services_lib_source})

FILE(GLOB phys-services_test_source "private/test/*.cxx")
ADD_TEST(phys-services-test ${phys-services_test_source})

USE_TOOL(sprng)
USE_TOOL(gsl)

