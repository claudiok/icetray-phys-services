#ifndef ANALYSIS_TREE_UTILITY_H
#define ANALYSIS_TREE_UTILITY_H

#include "icetray/I3FrameObject.h"
#include <string>
using namespace std;

string ToString(shared_ptr<const I3FrameObject> obj);
string ToString(I3FrameObject* obj);

shared_ptr<I3FrameObject> Clone(shared_ptr<const I3FrameObject> ptr);
I3FrameObject* Clone(I3FrameObject* ptr);

void Copy(shared_ptr<const I3FrameObject> oldp,shared_ptr<I3FrameObject>& newp);

#endif
