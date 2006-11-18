PROJECT(phys-services)

LIB (phys-services
  private/phys-services/*.cxx
  private/phys-source/*.cxx
  private/geo-selector/*.cxx
  private/empty-stream/*.cxx
  )

USE_TOOL(sprng)
USE_TOOL(gsl)
USE_TOOL(log4cplus)
USE_TOOL(boost)
USE_TOOL(root)

USE_PROJECT(icetray)
USE_PROJECT(dataclasses)

FILE(GLOB phys-services_test_source private/test/*.cxx)
ADD_TEST(phys-services-test ${phys-services_test_source})


