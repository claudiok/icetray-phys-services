#ifndef I3GSLRANDOMSERVICE_H
#define I3GSLRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_test.h>

/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3GSLRandomService.h,v 1.1 2004/10/18 14:21:42 pretz Exp $
 *
 * @brief An implementation of the I3RandomService interface.  
 * 
 * Uses the gsl library for the random numbers
 *
 * @version $Revision: 1.1 $
 * @date $Date: 2004/10/18 14:21:42 $
 * @author pretz
 *
 * @todo 
 */
class I3GSLRandomService : public I3RandomService{
 public:
  /**
   * default constructor
   */
  I3GSLRandomService();

  /**
   * destructor
   */
  virtual ~I3GSLRandomService(){};

  /**
   * a number drawn from a binomial distribution
   */
  virtual Int_t Binomial(Int_t ntot, Double_t prob);

  // Apparently, my version of ROOT doesn't have this, so I left it out.
  /* virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1)=0; */
  
  /**
   * A number from an Exponential distribution
   */
  virtual Double_t Exp(Double_t tau);

  /**
   * An integer drawn uniformly from [0,imax)
   */
  virtual UInt_t Integer(UInt_t imax);

  /**
   * An integer drawn from a Poisson distribution
   */
  virtual Int_t Poisson(Double_t mean);

  /**
   * A number drawn from a Poisson distribution, as a double
   */
  virtual Double_t PoissonD(Double_t mean);

  /**
   * a Double_t drawn from a uniform distribution (0,x1)
   */
  virtual Double_t Uniform(Double_t x1 = 1);

  /**
   * a Double_t drawn from a uniform distribution (x1,x2)
   */
  virtual Double_t Uniform(Double_t x1, Double_t x2);
 private:

  gsl_rng* r;

  ClassDef(I3GSLRandomService,0);
};


#endif //I3GSLRANDOMSERVICE_H
