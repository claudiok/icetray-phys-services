#ifndef I3SPRNGRANDOMSERVICE_H
#define I3SPRNGRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_test.h>

/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @brief SPRNG Implementation of the I3RandomService interface.  
 * This implementation uses a combination of SPRNG and GSL to generate
 * statistically independent streams of pseudo-random number distributions.
 * See gsl-sprng.h for more details.
 *
 * The code for this class is based on John Pretz's implementation of
 * I3GSLRandomService.
 * 
 * @version $Revision: 1.2 $
 * @date $Date$
 * @author juancarlos
 *
 * @todo Add ability to save state of rng after run is complete
 *  SPRNG has the functions:
 *
 *		int pack_sprng(char *bytes); // returns size of bytes
 *      void unpack_sprng(char bytes[MAX_PACKED_LENGTH]);	
 *
 *  which can be used to save and retrieve the state of an rng
 */

class I3SPRNGRandomService : public I3RandomService{
 public:
  /**
   * default constructor
   */
  I3SPRNGRandomService();

  I3SPRNGRandomService(Int_t seed, Int_t nstreams, Int_t streamnum);

  /**
   * destructor
   */
  virtual ~I3SPRNGRandomService();

  /**
   * Binomial distribution
   */
  virtual Int_t Binomial(Int_t ntot, Double_t prob);

  // As with John Pretz's GSL implementation, I have left this out for now.
  /* virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1)=0; */
  
  /**
   * Exponential distribution
   */
  virtual Double_t Exp(Double_t tau);

  /**
   * Uniform int distribution with range [0,imax)
   */
  virtual UInt_t Integer(UInt_t imax);

  /**
   * Int_t Poisson distribution
   */
  virtual Int_t Poisson(Double_t mean);

  /**
   * Double_t Poisson distribution
   */
  virtual Double_t PoissonD(Double_t mean);

  /**
   * Double_t uniform distribution with range (0,x1)
   */
  virtual Double_t Uniform(Double_t x1 = 1);

  /**
   * Double_t  uniform distribution with range (x1,x2)
   */
  virtual Double_t Uniform(Double_t x1, Double_t x2);

  /**
   * Double_t Gaussian distribution given mean and StdD
   */
  virtual Double_t Gaus(Double_t mean, Double_t stddev);

 private:

  gsl_rng* r;

  ClassDef(I3SPRNGRandomService,0);
};

typedef shared_ptr<I3SPRNGRandomService> I3SPRNGRandomServicePtr;

#endif // I3SPRNGRANDOMSERVICE_H
