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

/**
 * @brief The base class for source modules which sends out an I3Monitoring 
 *
 * Two virtual methods must be implemented by deriving classes to customize
 * the behavior.
 */
class I3MonitoringSource : public I3Source
{
 public:

  I3MonitoringSource(const I3Context& context);

  void Process();

  /**
   * @brief This method should only be called when
   * I3PhysicsSource::MoreMonitorings() is returning true.  The returned
   * MonitoringPair.header should have a valid start time. 
   *
   * This method should allocate a new I3Monitoring and a new 
   * I3MonitoringHeader and
   * return it filled as the module would like
   */
  virtual MonitoringPair NextMonitoring() = 0;
  
  /**
   * @brief IceTray will continue to run and call 
   * I3MonitoringSource::NextMonitoring()
   * until this method returns false
   */
  virtual bool MoreMonitorings() = 0;

 private:
  void SendMonitoring();

  MonitoringPair currentMonitoring_;
  

};

#endif
