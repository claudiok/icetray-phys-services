#ifndef ANALYSIS_TREE_UTILITY_H
#define ANALYSIS_TREE_UTILITY_H

#include "icetray/I3FrameObject.h"
#include <string>
using namespace std;

string ToString(shared_ptr<const I3FrameObject> obj);

shared_ptr<I3FrameObject> Clone(shared_ptr<const I3FrameObject> ptr);
I3FrameObject* CloneP(shared_ptr<const I3FrameObject> ptr);

#endif
