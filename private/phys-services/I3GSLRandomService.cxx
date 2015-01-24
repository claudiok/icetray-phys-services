#include "phys-services/I3GSLRandomService.h"
#include <cstring>
#include <gsl/gsl_version.h>

I3GSLRandomService::I3GSLRandomService()
{
  // needed call to gsl
  construct();
}

I3GSLRandomService::I3GSLRandomService(unsigned long int seed)
{
  // needed call to gsl.  Then set the seed.
  construct();
  gsl_rng_set(r, seed);
}

int I3GSLRandomService::Binomial(int ntot, double prob)
{
  return gsl_ran_binomial(r,prob,ntot);
}

double I3GSLRandomService::Exp(double tau)
{
  return gsl_ran_exponential(r,tau);
}

unsigned int I3GSLRandomService::Integer(unsigned int imax)
{
  return (unsigned int)Uniform(imax);
}

int I3GSLRandomService::Poisson(double mean)
{
  return gsl_ran_poisson(r,mean);
}

double I3GSLRandomService::PoissonD(double mean)
{
  return gsl_ran_poisson(r,mean);
}

double I3GSLRandomService::Uniform(double x1)
{
  return gsl_ran_flat(r,0.0,x1);
}

double I3GSLRandomService::Uniform(double x1, double x2)
{
  return gsl_ran_flat(r,x1,x2);
}

double I3GSLRandomService::Gaus(double mean,double stddev)
{
  return mean + gsl_ran_gaussian(r,stddev);
}

struct I3GSLRandomServiceState : public I3FrameObject {
  std::string gsl_version_;
  std::string rng_type_;
  std::vector<unsigned char> state_blob_;
  
  friend class boost::serialization::access;
  template <typename Archive>
  void serialize(Archive &ar, unsigned version)
  {
    ar & make_nvp("I3FrameObject", base_object<I3FrameObject>(*this));
    ar & make_nvp("GSLversion", gsl_version_);
    ar & make_nvp("RNGtype", rng_type_);
    ar & make_nvp("State", state_blob_);
  }
};

BOOST_CLASS_VERSION(I3GSLRandomServiceState, 0);
I3_SERIALIZABLE(I3GSLRandomServiceState);

I3FrameObjectPtr I3GSLRandomService::GetState() const
{
  boost::shared_ptr<I3GSLRandomServiceState> state(new I3GSLRandomServiceState);
  state->gsl_version_=GSL_VERSION;
  state->rng_type_=gsl_rng_name(r);
  state->state_blob_.resize(gsl_rng_size(r));
  memcpy(&state->state_blob_.front(),gsl_rng_state(r),state->state_blob_.size());
  return state;
}

void I3GSLRandomService::RestoreState(I3FrameObjectConstPtr vstate)
{
  boost::shared_ptr<const I3GSLRandomServiceState> state;
  if (!(state = boost::dynamic_pointer_cast<const I3GSLRandomServiceState>(vstate)))
    log_fatal("The provided state is not an I3GSLRandomServiceState!");
  
  std::string current_gsl_version=GSL_VERSION;
  if(current_gsl_version!=state->gsl_version_)
    log_fatal_stream("Cowardly refusing to restore an RNG state from a different GSL version\n"
                     << "    Current version: " << current_gsl_version << '\n'
                     << "    Stored state version: " << state->gsl_version_);
  
  if(gsl_rng_name(r)!=state->rng_type_)
    log_fatal_stream("Cannot restore state from an RNG of a different type\n"
                     << "    Current RNG type: " << gsl_rng_name(r) << '\n'
                     << "    Stored state type: " << state->rng_type_);
  
  //final paranoid check: is there really as much space as there should be?
  if(gsl_rng_size(r)!=state->state_blob_.size())
    log_fatal("GSL state sizes do not match; something is horribly wrong!");
  
  //checks seem okay, so nuke and pave
  memcpy(gsl_rng_state(r),&state->state_blob_.front(),state->state_blob_.size());
}