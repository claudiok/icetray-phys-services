#ifndef I3RANDOMSERVICE_H
#define I3RANDOMSERVICE_H

#include "Rtypes.h"
/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3RandomService.h,v 1.3 2004/05/10 15:57:54 pretz Exp $
 *
 * @brief This class provides an interface to random numbers suitable for use by
 * icetray modules.  
 *
 * This class is just the interface.  The names chosen
 * reflect ROOT's TRandom interface.  Indeed TRandom could be used to 
 * trivially fill this interface
 *
 * @version $Revision: 1.3 $
 * @date $Date: 2004/05/10 15:57:54 $
 * @author pretz
 *
 * @todo 
 */
class I3RandomService {
 public:
  /**
   * constructor
   */
  I3RandomService(){}

  /**
   * destructor
   */ 
  virtual ~I3RandomService(){};

  /**
   * a number drawn from a binomial distribution
   */
  virtual Int_t Binomial(Int_t ntot, Double_t prob)=0;

  // Apparently, my version of ROOT doesn't have this, so I left it out.
  /* virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1)=0; */
  
  /**
   * A number from an Exponential distribution
   */
  virtual Double_t Exp(Double_t tau)=0;

  /**
   * An integer drawn uniformly from [0,imax)
   */
  virtual UInt_t Integer(UInt_t imax)=0;

  /**
   * a number drawn from a Landau distribution
   */
  virtual Double_t Landau(Double_t mean = 0, Double_t sigma = 1)=0;

  /**
   * An integer drawn from a Poisson distribution
   */
  virtual Int_t Poisson(Double_t mean)=0;

  /**
   * A number drawn from a Poisson distribution, as a double
   */
  virtual Double_t PoissonD(Double_t mean)=0;

  /**
   * Uniform Double_t on the interval (0,1).  You got me what that integer
   * is for.  Near as I can figure it's useless, and the ROOT doc's don't say
   */
  virtual Double_t Rndm(Int_t i = 0)=0;

  /**
   * a Double_t drawn from a uniform distribution (0,x1)
   */
  virtual Double_t Uniform(Double_t x1 = 1)=0;

  /**
   * a Double_t drawn from a uniform distribution (x1,x2)
   */
  virtual Double_t Uniform(Double_t x1, Double_t x2)=0;

  /**
   * gives a default name for this service
   */
  static const Char_t* DefaultName(){return "RandomService";}

 private:
  // copy and assignment private
  I3RandomService(const I3RandomService&);
  const I3RandomService& operator=(const I3RandomService&);

  //ROOT macro
  ClassDef(I3RandomService,0);
};


#endif //I3RANDOMSERVICE_H
