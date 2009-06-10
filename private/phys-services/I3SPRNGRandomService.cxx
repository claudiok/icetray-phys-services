/*
 * class: I3SPRNGRandomService
 *
 * Version $Id: I3SPRNGRandomService.cxx 21041 2006-06-23 08:37:53Z rfranke $
 *
 * Date: 2 Apr 2005
 *
 * (c) IceCube Collaboration
 */

// Class header files
#include "phys-services/I3SPRNGRandomService.h"
#include "phys-services/gsl-sprng.h" 
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

I3SPRNGRandomService::I3SPRNGRandomService()
{
  gsl_rng_env_setup();
  rng_ = gsl_sprng_init(0, 1, 0);
}


I3SPRNGRandomService::I3SPRNGRandomService(
				int seed,   		
				int nstreams,  // number of rng streams  (nstreams > streamnum)
				int streamnum, // stream number for this process
				string infile, // where state from prev. run is stored
				string outfile // where state for next run will be stored
				): instatefile_(infile),outstatefile_(outfile)
{
  char buffer[MAX_PACKED_LENGTH];
  int size;

  assert(streamnum<nstreams);
  assert(streamnum>=0);
  gsl_rng_env_setup();

  /*if (instatefile_.length() > 0) {*/
  if (!instatefile_.empty()) {
  	ifstream in(instatefile_.c_str()); 
  	in.read((char*) &size,sizeof(int));  // read size of array
  	in.read(buffer,size);		// read array
  	in.close();

  	rng_ = gsl_sprng_init(seed, nstreams, streamnum, buffer);
  } else {
  	rng_ = gsl_sprng_init(seed, nstreams, streamnum);
  }
}

I3SPRNGRandomService::~I3SPRNGRandomService()
{
   /*if (outstatefile_.length() > 0) { //save rng state to file*/
   if ( !outstatefile_.empty() ) { //save rng state to file
	   int size;
	   char *bytes;

	   /*ofstream statefile(outstatefile_.c_str(),ofstream::binary); */
	   ofstream out(outstatefile_.c_str()); 
	   size = gsl_sprng_pack(rng_, &bytes);
	   out.write((char*) &size,sizeof(int)); // write the size of array
	   out.write(bytes,size); // write array
	   out.close(); 
	   free(bytes);
   }
   gsl_sprng_free(rng_);
}

int I3SPRNGRandomService::Binomial(int ntot, double prob)
{
  return gsl_ran_binomial(rng_,prob,ntot);
}

double I3SPRNGRandomService::Exp(double tau)
{
  return gsl_ran_exponential(rng_,tau);
}

unsigned int I3SPRNGRandomService::Integer(unsigned int imax)
{
  return (unsigned int)Uniform(imax);
}

int I3SPRNGRandomService::Poisson(double mean)
{
  return gsl_ran_poisson(rng_,mean);
}

double I3SPRNGRandomService::PoissonD(double mean)
{
  return gsl_ran_poisson(rng_,mean);
}

double I3SPRNGRandomService::Uniform(double x1)
{
  return gsl_ran_flat(rng_,0.0,x1);
}

double I3SPRNGRandomService::Uniform(double x1, double x2)
{
  return gsl_ran_flat(rng_,x1,x2);
}

double I3SPRNGRandomService::Gaus(double mean,double stddev)
{
  return mean + gsl_ran_gaussian(rng_,stddev);
}
