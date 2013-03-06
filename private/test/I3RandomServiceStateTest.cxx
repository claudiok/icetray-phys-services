
#include <I3Test.h>

#include <phys-services/I3SPRNGRandomService.h>
#include <boost/foreach.hpp>

TEST_GROUP(RandomServiceState);

TEST(I3SPRNGRandomService)
{
	I3SPRNGRandomServicePtr rng(new I3SPRNGRandomService(1,1,0, "", "sprng_outstate"));
	
	typedef std::pair<double, I3FrameObjectPtr> sample_t;
	std::vector<sample_t> states;
	
	for (int i = 0; i < 1000; i++) {
		I3FrameObjectPtr state = rng->GetState();
		double v = rng->Exp(M_PI);
		states.push_back(std::make_pair(v, state));
	}
	
	double chance = 0.1;
	BOOST_FOREACH(const sample_t &sample, states) {
		// Discard random intermediate points, mixing up
		// the RNG state in the process
		if (rng->Uniform() > chance)
			continue;
		rng->RestoreState(sample.second);
		ENSURE_EQUAL(sample.first, rng->Exp(M_PI), "Restored RNG returns the same sample");
	}
	
	// Now, restore from the state from a file, and make sure things still work
	// if we take more samples
	rng.reset();
	rng = I3SPRNGRandomServicePtr(new I3SPRNGRandomService(1,1,0, "sprng_outstate", "sprng_outstate"));
	
	for (int i = 0; i < 1000; i++) {
		I3FrameObjectPtr state = rng->GetState();
		double v = rng->Exp(M_PI);
		states.push_back(std::make_pair(v, state));
	}
	
	BOOST_FOREACH(const sample_t &sample, states) {
		// Discard random intermediate points, mixing up
		// the RNG state in the process
		if (rng->Uniform() > chance)
			continue;
		rng->RestoreState(sample.second);
		ENSURE_EQUAL(sample.first, rng->Exp(M_PI), "Restored RNG returns the same sample");
	}
}
