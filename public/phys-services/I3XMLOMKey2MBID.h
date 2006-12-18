/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3XMLOMKey2MBID.h 13154 2005-12-01 21:45:55Z tschmidt $
 *
 * @file I3XMLOMKey2MBID.h
 * @version $Revision: 1.10 $
 * @date $Date: 2005-12-01 16:45:55 -0500 (Thu, 01 Dec 2005) $
 * @author tschmidt
 */
#ifndef I3XMLOMKEY2MBID_H_INCLUDED
#define I3XMLOMKEY2MBID_H_INCLUDED

// forward declarations


// header files

#include <map>
#include <string>

#include <icetray/I3FrameObject.h>
#include <icetray/I3Logging.h>
#include <phys-services/I3OMKey2MBID.h>

// definitions


/**
 * @brief 
 */
class I3XMLOMKey2MBID : public I3OMKey2MBID
{
 public:
  /** Constructor.
   * 
   * @param infile 
   */
  explicit I3XMLOMKey2MBID(const std::string& infile);
  /** Destructor.
   */
  virtual ~I3XMLOMKey2MBID();
  OMKey GetOMKey(long long int mbid);
  long long int GetMBID(OMKey key);

 private:
  std::map<OMKey,long long int> omkey2mbid_;
  std::map<long long int,OMKey> mbid2omkey_;


  // private copy constructors and assignment
  I3XMLOMKey2MBID(const I3XMLOMKey2MBID&);
  I3XMLOMKey2MBID& operator=(const I3XMLOMKey2MBID&);


  // logging
  SET_LOGGER("I3XMLOMKey2MBID");
};

I3_POINTER_TYPEDEFS(I3XMLOMKey2MBID);


inline
OMKey I3XMLOMKey2MBID::GetOMKey(long long int mbid) 
{
  std::map<long long int,OMKey>::const_iterator iter = mbid2omkey_.find(mbid);
  if(iter == mbid2omkey_.end())
    log_fatal("unknown mainboard ID - %lld", mbid);

  return(iter->second);
}


inline
long long int I3XMLOMKey2MBID::GetMBID(OMKey key) 
{
  std::map<OMKey,long long int>::const_iterator iter = omkey2mbid_.find(key);
  if(iter == omkey2mbid_.end())
    log_fatal("unknown OM key - (%d, %u)", key.GetString(), key.GetOM());

  return(iter->second);
}

#endif /*I3XMLOMKEY2MBID_H_INCLUDED*/
