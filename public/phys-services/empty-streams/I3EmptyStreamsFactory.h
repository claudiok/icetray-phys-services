#ifndef I3EMPTYSTREAMSFACTORY_H
#define I3EMPTYSTREAMSFACTORY_H

#include <icetray/I3ServiceFactory.h>

class I3EventService;
class I3CalibrationService;
class I3DetectorStatusService;
class I3GeometryService;

class I3EmptyStreamsFactory : public I3ServiceFactory
{
 public:
  I3EmptyStreamsFactory(const I3Context& context);
  
  bool InstallService(I3Services& services);

  void Configure();
 private:
  int nframes_;

  shared_ptr<I3EventService> events_;
  shared_ptr<I3CalibrationService> calibrations_;

  // plural of status is status.  But pronounced with a long u
  // so though this looks like 'status', it's pronounced 
  // statoooos
  shared_ptr<I3DetectorStatusService> status_;
  shared_ptr<I3GeometryService> geometries_;
};

#endif
