#ifndef I3RANDOMTEST_H
#define I3RANDOMTEST_H

namespace tut
{
  template <class Type>
  struct I3RandomTest
  {
    Type random;
  };
}
namespace tut
{
  template<class Type>
  void test_group<I3RandomTest<Type> >::object::test<1>(){

  }
} 

#endif
