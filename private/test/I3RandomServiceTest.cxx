/**
    copyright  (C) 2004
    the icecube collaboration
    $Id$

    @version $Revision: 1.3 $
    @date $Date$
    @author pretz

    @todo
*/

#include <I3Test.h>

#include "phys-services/I3RandomService.h"
#include "phys-services/I3TRandomService.h"
#include "phys-services/I3GSLRandomService.h"
#include "phys-services/I3SPRNGRandomService.h"

#include <string>
#include <vector>
using std::string;
using std::cout;
using std::endl;
using std::vector;

// tests a random number service that it has the expected mean 
// and std dev.  Theoretically it is possible for a random number
// to fail this test and still be working, so I put healthy tolerances
// on it.
TEST_GROUP(I3RandomServiceTest);

namespace randomServiceTest{
void testMeanStddev(vector<double>& values,
		    double expected_average,
		    double expected_stddev)
{
  double sum = 0;
  for(unsigned int i = 0 ; i < values.size() ; i++)
    {
      sum += values[i];
    }
  double measured_average = sum / (double)values.size();
  ENSURE_DISTANCE(measured_average,expected_average,0.01,"testing mean");
  
  vector<double> differences;
  differences.resize(values.size());
  
  for(unsigned int i = 0 ; i < values.size() ; i++)
    {
      differences[i] = 
	(values[i] - measured_average) * 
	(values[i] - measured_average);
      //	cout<<differences[i]<<"\n";
    }
  
  sum = 0;
  
  for(unsigned int i = 0; i < values.size() ; i++)
    {
      sum += differences[i];
    }
  
  double measured_stddev = sqrt(sum / (double) differences.size());
  ENSURE_DISTANCE(measured_stddev,
		  expected_stddev,
		  0.01,
		  "testing stdev");
  
  
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
  testMeanStddev(values,1.0,1.0);
}

template <int samples,class Random>
void testGaussian(Random& random)
{
  vector<double> values;
  values.resize(samples);
  for(int i = 0 ; i<samples ; i++)
    values[i] = random.Gaus(5,1.0);
  testMeanStddev(values,5,1.0);
}


template <int samples,class Random>
void testRandomService(Random& random)
{
  testUniform<samples,Random>(random);
  testExp<samples,Random>(random);
  testGaussian<samples,Random>(random);
}

}

TEST(TRandomServiceTest)
{
  I3TRandomService random1;
	I3TRandomService random2(666);
  randomServiceTest::testRandomService<100000,I3TRandomService>(random1);
  randomServiceTest::testRandomService<100000,I3TRandomService>(random2);
}

TEST(I3GSLRandomService)
{
  I3GSLRandomService random1;
  I3GSLRandomService random2(666);
  randomServiceTest::testRandomService<100000,I3GSLRandomService>(random1);
  randomServiceTest::testRandomService<100000,I3GSLRandomService>(random2);
}

TEST(I3SPRNGRandomService)
{
  I3SPRNGRandomService random;
  randomServiceTest::testRandomService<100000,I3SPRNGRandomService>(random);
}

