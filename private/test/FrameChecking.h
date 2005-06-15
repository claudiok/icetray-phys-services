#ifndef FRAMECHECKING_H
#define FRAMECHECKING_H

#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3GeometryHeader.h"

#include "dataclasses/I3Monitoring.h"
#include "dataclasses/I3MonitoringHeader.h"

#include "dataclasses/I3Event.h"
#include "dataclasses/I3EventHeader.h"

#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3CalibrationHeader.h"

#include "dataclasses/I3DetectorStatus.h"
#include "dataclasses/I3DetectorStatusHeader.h"

inline
string DumpStop(I3Frame& frame)
{
  vector<string> possibleNames;
  possibleNames.push_back("Geometry");
  possibleNames.push_back("DetectorStatus");
  possibleNames.push_back("Calibration");
  possibleNames.push_back("Physics");
  possibleNames.push_back("Monitor");
  
  for(vector<string>::iterator iter = possibleNames.begin() ; 
      iter != possibleNames.end() ;
      iter++)
    {
      if(frame.GetStop() == I3Stream::FindStream(*iter))
	return *iter;
    }
  return "UNKNOWN STREAM";
   
}

inline bool GeometryPresent(I3Frame& frame)
{
  if(I3FrameAccess<I3Geometry>::Exists(frame,"Geometry") &&
     I3FrameAccess<I3GeometryHeader>::Exists(frame,"GeometryHeader"))
    return true;
  return false;
}

inline bool EventPresent(I3Frame& frame)
{
  if(I3FrameAccess<I3Event>::Exists(frame,"Physics") &&
     I3FrameAccess<I3EventHeader>::Exists(frame,"PhysicsHeader"))
    return true;
  return false;
}

inline bool CalibrationPresent(I3Frame& frame)
{
  if(I3FrameAccess<I3Calibration>::Exists(frame,"Calibration") &&
     I3FrameAccess<I3CalibrationHeader>::Exists(frame,"CalibrationHeader"))
    return true;
  return false;
}

inline bool DetectorStatusPresent(I3Frame& frame)
{
  if(I3FrameAccess<I3DetectorStatus>::Exists(frame,"DetectorStatus") &&
     I3FrameAccess<I3DetectorStatusHeader>::Exists(frame,"DetectorStatusHeader"))
    return true;
  return false;
}

inline bool MonitoringPresent(I3Frame& frame)
{
  if(I3FrameAccess<I3Monitoring>::Exists(frame,"Monitoring") &&
     I3FrameAccess<I3MonitoringHeader>::Exists(frame,"MonitoringHeader"))
    return true;
  return false;
}

#endif
