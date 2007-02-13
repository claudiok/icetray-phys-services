#ifndef PHYSSERVICES_I3EVENTCOUNTER_H
#define PHYSSERVICES_I3EVENTCOUNTER_H

#include "icetray/I3TrayHeaders.h"
#include "icetray/I3Module.h"

class I3EventCounter : public I3Module
{
 public:
  I3EventCounter(const I3Context& ctx);
  ~I3EventCounter() {};
  void Configure();
  void Physics(I3FramePtr frame);
  void Finish();

 private:
  I3EventCounter();
  I3EventCounter(const I3EventCounter& source);
  I3EventCounter& operator=(const I3EventCounter& source);

  /**
   * Parameter: name of output histogram file
   */
  int counterStep_;

  /**
   * Parameter: whether to dump current frame to screen
   */
  bool dump_;

  /**
   * Parameter: how many physics events to process
   */
  int nevents_;

  int count_;

  SET_LOGGER("I3EventCounter");
};

#endif
