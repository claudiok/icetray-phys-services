/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3MonitoringSource.cxx 9191 2005-06-16 02:53:36Z pretz $
 *
 * @file 
 * @version $Revision:$
 * @date $Date: 2005-06-15 22:53:36 -0400 (Wed, 15 Jun 2005) $
 * @author pretz
 */


#include "phys-services/source/I3MonitoringSource.h"
#include "icetray/I3Context.h"
#include "icetray/I3TrayHeaders.h"

//I3_MODULE(I3MonitoringSource);

I3MonitoringSource::I3MonitoringSource(const I3Context& context) : I3Source(context)
{
  AddOutBox("OutBox");
  NoActiveInBox();
  if(!I3Stream::StreamExists("Monitor"))
    I3Stream::AddStream("Monitor","Monitoring Stream");



}

void I3MonitoringSource::Process()
{
    log_debug("Entering I3MonitoringSource::Process()");
    if(MoreMonitorings())
      SendMonitoring();
    else
      RequestSuspension();
}

void I3MonitoringSource::SendMonitoring()
{
  log_debug("Entering I3MonitoringSource::SendMonitoring()");
  currentMonitoring_ = NextMonitoring();
  assert(currentMonitoring_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Monitor"));
  frame.Put("Monitoring", currentMonitoring_.monitoring );
  frame.Put("MonitoringHeader", currentMonitoring_.header );
 
  shared_ptr<I3Time> 
    eventTime(new I3Time(currentMonitoring_.header->GetStartTime()));;

  frame.Put("DrivingTime", eventTime);

  PushFrame(frame,"OutBox");
}

