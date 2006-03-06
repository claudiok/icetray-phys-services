// LinkDef.h
// $Id: LinkDef.h 15229 2006-02-02 20:58:21Z pretz $
// $Date: 2006-02-02 15:58:21 -0500 (Thu, 02 Feb 2006) $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// classes

#pragma link C++ namespace I3CutValues+;

// namespaces

#pragma link C++ namespace I3Calculator;
#pragma link C++ namespace I3Cuts;

// functions

#pragma link C++ function I3Calculator::CherenkovCalc; //
#pragma link C++ function I3Calculator::IsOnTrack; //
#pragma link C++ function I3Calculator::ClosestApproachPosition; //
#pragma link C++ function I3Calculator::ClosestApproachDistance; //
#pragma link C++ function I3Calculator::CherenkovPosition; //
#pragma link C++ function I3Calculator::CherenkovTime; //
#pragma link C++ function I3Calculator::CherenkovDistance; //
#pragma link C++ function I3Calculator::CherenkovApproachAngle; //
#pragma link C++ function I3Calculator::TimeResidual; //
#pragma link C++ function I3Calculator::Angle; //
#pragma link C++ function I3Calculator::Distance; //
#pragma link C++ function I3Calculator::InTrackSystem; //
#pragma link C++ function I3Calculator::InNominalSystem; //

#pragma link C++ function I3Cuts::CutsCalc; //
#pragma link C++ function I3Cuts::Ndir; //
#pragma link C++ function I3Cuts::Ldir; //
#pragma link C++ function I3Cuts::SmoothAll; //
#pragma link C++ function I3Cuts::SmoothDir; //
#pragma link C++ function I3Cuts::CylinderSize; //

#endif




