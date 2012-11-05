/**
 * $Id$
 */
#ifndef PHYS_SERVICES_UTILITY_H
#define PHYS_SERVICES_UTILITY_H

#include "icetray/I3FrameObject.h"
#include <string>
#include <vector>

// forward declaration
class I3MCHit;
class I3RecoHit;
class I3RecoPulse;
class I3DOMLaunch;
class I3Waveform;

// Functions to get charge from various objects
double GetCharge(const I3MCHit&);
double GetCharge(const I3RecoHit&);
double GetCharge(const I3RecoPulse&);
double GetCharge(const I3DOMLaunch&);
double GetCharge(const I3Waveform&);
double GetCharge(const std::vector<I3RecoPulse>&);

double GetTime(const I3MCHit&);
double GetTime(const I3RecoPulse&);
double GetTime(const I3DOMLaunch&);
double GetTime(const I3Waveform&);

#endif
