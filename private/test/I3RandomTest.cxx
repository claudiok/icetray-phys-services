#include "I3RandomTest.h"
#include "phys-services/I3TRandomService.h"

namespace{
  static tut::test_group<I3RandomTest<I3TRandomService> >
    t("I3TRandomTest");
} 
