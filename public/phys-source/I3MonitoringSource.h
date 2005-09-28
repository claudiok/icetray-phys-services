/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3MonitoringSource.h 9162 2005-06-14 17:57:44Z pretz $
 *
 * @file I3MonitoringSource.h
 * @version $Revision:$
 * @date $Date: 2005-06-14 13:57:44 -0400 (Tue, 14 Jun 2005) $
 * @author pretz
 */

#ifndef I3MONITORINGSOURCE_H
#define I3MONITORINGSOURCE_H

#include "dataclasses/I3Event.h"
#include "dataclasses/I3EventHeader.h"

#include "icetray/I3Source.h"
#include "I3MonitoringPair.h"

class I3MonitoringSource : public I3Source
{
 public:
  I3MonitoringSource(const I3Context& context);

  void Process();

  virtual MonitoringPair NextMonitoring() = 0;
  
  virtual bool MoreMonitorings() = 0;

 private:
  void SendMonitoring();

  MonitoringPair currentMonitoring_;
  

};

#endif
