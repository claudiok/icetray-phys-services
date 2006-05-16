#ifndef PHYS_SERVICES_UTILITY_H
#define PHYS_SERVICES_UTILITY_H

#include "icetray/I3FrameObject.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include <string>
using namespace std;

string ToString(shared_ptr<const I3FrameObject> obj);
string ToString(I3FrameObject* obj);

shared_ptr<I3FrameObject> Clone(shared_ptr<const I3FrameObject> ptr);
I3FrameObject* Clone(I3FrameObject* ptr);

void Copy(shared_ptr<const I3FrameObject> oldp,
	  shared_ptr<I3FrameObject>& newp);

void ENSURE_DISTANCE(double left, double right, double precision, 
		     string message = "Test FAILED");

void ENSURE(bool expression, string message = "Test FAILED");

// Functions to get charge from either RecoPulse or RecoHit.
double GetCharge(const I3RecoHit& hit);

double GetCharge(const I3RecoPulse& pulse);

#endif
