/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3RandomServiceTest.cxx,v 1.1 2004/11/01 22:06:46 pretz Exp $

    @version $Revision: 1.1 $
    @date $Date: 2004/11/01 22:06:46 $
    @author pretz

    @todo
*/

#include "TUT/tut.h"

#include "phys-services/I3RandomService.h"
#include "phys-services/I3TRandomService.h"

#include <string>
#include <vector>
using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace tut
{
  struct I3RandomServiceTest
  {
  };

  typedef test_group<I3RandomServiceTest> factory;

  typedef factory::object object;
}

namespace
{
  static tut::factory t("I3RandomServiceTest");
}

namespace tut
{ 

  void testMeanStddev(vector<double>& values,
		      double expected_average,
		      double expected_stddev)
  {
    double sum = 0;
    for(int i = 0 ; i < values.size() ; i++)
      {
	sum += values[i];
      }
    double measured_average = sum / (double)values.size();
    ensure_distance("testing mean",measured_average,expected_average,0.01);
    
    vector<double> differences;
    differences.resize(values.size());
    
    for(int i = 0 ; i < values.size() ; i++)
      {
	differences[i] = 
	  (values[i] - measured_average) * 
	  (values[i] - measured_average);
	//	cout<<differences[i]<<"\n";
      }
    
    sum = 0;
    
    for(int i = 0; i < values.size() ; i++)
      {
	sum += differences[i];
      }
    
    double measured_stddev = sqrt(sum / (double) differences.size());
    ensure_distance("testing stdev",measured_stddev,expected_stddev,0.01);
	
	
  }

  template <int samples,class Random>
  void testUniform(Random& r)
  {
    vector<double> values;
    values.resize(samples);
    for(int i = 0 ; i< samples ; i++)
      values[i] = r.Uniform();

    // mean 0.5 and stdev = sqrt( <x^2> - <x> ^ 2);
    testMeanStddev(values,0.5,sqrt(0.3333 - 0.5 * 0.5));
  }

  template <int samples,class Random>
  void testExp(Random& r)
  {
    vector<double> values;
    values.resize(samples);
    for(int i = 0; i< samples ; i++)
      values[i] = r.Exp(1.0);
    testMeanStddev(values,1.0,0.0);
  }

  template <int samples,class Random>
  void testRandomService(Random& random)
  {
    testUniform<samples,Random>(random);
    testExp<samples,Random>(random);
  }

  void object::test<1>()
  {
    I3TRandomService random;
    testRandomService<10000,I3TRandomService>(random);
  }
}
