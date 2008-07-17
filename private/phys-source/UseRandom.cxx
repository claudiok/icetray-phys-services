#include <icetray/I3Frame.h>
#include <icetray/I3Logging.h>
#include <icetray/I3Module.h>

#include <dataclasses/I3Time.h>
#include <dataclasses/I3Double.h>
#include <phys-services/I3RandomService.h>


class UseRandom : public I3Module
{
 public:

  UseRandom(const I3Context& ctx);

  void Process();
  
  void Configure();

  I3RandomServicePtr rs;
  std::string key;
  // logging
  SET_LOGGER ("UseRandom");
};


I3_MODULE(UseRandom);


UseRandom::UseRandom(const I3Context& context) : I3Module(context)
{
  AddParameter("I3RandomService",
               "my random service",
               rs);

  AddParameter("PutWhere",
               "where the doubles go",
               key);

  AddOutBox("OutBox");
}

void UseRandom::Configure()
{
  GetParameter("I3RandomService", rs);
  log_debug("rndserv is at %p", rs.get());
  GetParameter("PutWhere", key);
}


void UseRandom::Process()
{
  log_debug("rndserv is at %p", rs.get());
  double d = rs->Uniform(1);
  I3DoublePtr dp(new I3Double(d));
  I3FramePtr frame = PopFrame();
  frame->Put(key, dp);
  PushFrame(frame, "OutBox");
}

