#include <I3Test.h>

#include "module-test/TestClientModule.h"

struct DummyMonitoringFactoryClient
{
};


typedef TestClientModule<DummyMonitoringFactoryClient> Client;

inline
string DumpStop(I3Frame& frame)
{
  vector<string> possibleNames;
  possibleNames.push_back("Geometry");
  possibleNames.push_back("DetectorStatus");
  possibleNames.push_back("Calibration");
  possibleNames.push_back("Monitor");
  possibleNames.push_back("Physics");
  
  for(vector<string>::iterator iter = possibleNames.begin() ; 
      iter != possibleNames.end() ;
      iter++)
    {
      if(frame.GetStop() == I3Stream::FindStream(*iter))
	return *iter;
    }
  return "UNKNOWN STREAM";
  
  
}

template<> template<>
inline void Client::CheckFrame<0>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Geometry");
  ENSURE(I3FrameAccess<I3Geometry>::Exists(frame,
					   "Geometry"));
  ENSURE(I3FrameAccess<I3GeometryHeader>::Exists(frame,
						 "GeometryHeader"));

  cout<<I3FrameAccess<I3GeometryHeader>::Get(frame,"GeometryHeader")<<endl;
  cout<<I3FrameAccess<I3GeometryHeader>::Get(frame,"Geometry")<<endl;
}

inline void Client::CheckFrame<1>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Calibration");
  ENSURE(I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
  ENSURE(I3FrameAccess<I3CalibrationHeader>::
	 Exists(frame,
		"CalibrationHeader"));
  ENSURE(I3FrameAccess<I3Geometry>::Exists(frame,
						"Geometry"));
  ENSURE(I3FrameAccess<I3GeometryHeader>::Exists(frame,
						 "GeometryHeader"));
  cout<<I3FrameAccess<I3CalibrationHeader>::Get(frame,
						"CalibrationHeader")
      <<endl;
  cout<<I3FrameAccess<I3Calibration>::Get(frame,
					  "Calibration")
      <<endl;
}

inline void Client::CheckFrame<2>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "DetectorStatus");
  ENSURE(I3FrameAccess<I3Geometry>::Exists(frame,
					   "Geometry"));
  ENSURE(I3FrameAccess<I3GeometryHeader>::Exists(frame,
						 "GeometryHeader"));
  ENSURE(I3FrameAccess<I3DetectorStatus>::
	 Exists(frame,"DetectorStatus"));
  ENSURE(I3FrameAccess<I3DetectorStatusHeader>::
	 Exists(frame,"DetectorStatus"));
  ENSURE(I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
  ENSURE(I3FrameAccess<I3CalibrationHeader>::
	      Exists(frame,
		     "CalibrationHeader"));
  
  cout<<I3FrameAccess<I3DetectorStatusHeader>::Get(frame,
						   "DetectorStatusHeader")
      <<endl;
  cout<<I3FrameAccess<I3DetectorStatus>::Get(frame,
					     "DetectorStatus")
      <<endl;
  
}



inline void Client::CheckFrame<3>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Monitor");
  ENSURE(I3FrameAccess<I3Geometry>::Exists(frame,"Geometry"));
  ENSURE(I3FrameAccess<I3GeometryHeader>::
	      Exists(frame,"GeometryHeader"));
  ENSURE(I3FrameAccess<I3Calibration>::Exists(frame,
						   "Calibration"));
  ENSURE(I3FrameAccess<I3CalibrationHeader>
	      ::Exists(frame,
		       "CalibrationHeader"));
  ENSURE(I3FrameAccess<I3Monitoring>::Exists(frame,"Monitor"));
  ENSURE(I3FrameAccess<I3MonitoringHeader>::Exists(frame,"MonitorHeader"));
  cout<<I3FrameAccess<I3MonitoringHeader>::Get(frame,"MonitorHeader")<<endl;
  cout<<I3FrameAccess<I3Monitoring>::Get(frame,"Monitor")<<endl;

}

inline void Client::CheckFrame<4>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Monitor");
  ENSURE(I3FrameAccess<I3Geometry>::Exists(frame,"Geometry"));
  ENSURE(I3FrameAccess<I3GeometryHeader>::
		Exists(frame,"GeometryHeader"));
  ENSURE(I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
  ENSURE(I3FrameAccess<I3CalibrationHeader>::
	      Exists(frame,
		     "CalibrationHeader"));
  ENSURE(I3FrameAccess<I3DetectorStatus>::
	      Exists(frame,"DetectorStatus"));
  ENSURE(I3FrameAccess<I3DetectorStatusHeader>::
	      Exists(frame,"DetectorStatus"));
  ENSURE(I3FrameAccess<I3Monitoring>::Exists(frame,"Monitor"));
  ENSURE(I3FrameAccess<I3MonitoringHeader>::Exists(frame,"MonitorHeader"));
  cout<<I3FrameAccess<I3MonitoringHeader>::Get(frame,"MonitorHeader")<<endl;
  cout<<I3FrameAccess<I3Monitoring>::Get(frame,"Monitor")<<endl;
}
