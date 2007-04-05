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

#include <icetray/I3Logging.h>
#include <icetray/I3PointerTypedefs.h>
#include <icetray/OMKey.h>
#include <interfaces/I3OMKey2MBID.h>

// definitions


/**
 * @brief An implementation of I3OMKey2MBID that reads the conversions from a XML file
 */
class I3XMLOMKey2MBID : public I3OMKey2MBID
{
 public:
  /** Constructor.
   * 
   * @param infile Name of the XML file.
   */
  explicit I3XMLOMKey2MBID(const std::string& infile);
  /** Destructor.
   */
  virtual ~I3XMLOMKey2MBID();
  bool OMKeyExists(long long int mbid) const;
  OMKey GetOMKey(long long int mbid) const;
  bool MBIDExists(OMKey key) const;
  long long int GetMBID(OMKey key) const;

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
bool I3XMLOMKey2MBID::OMKeyExists(long long int mbid) const
{
  return(mbid2omkey_.count(mbid));
}


inline
OMKey I3XMLOMKey2MBID::GetOMKey(long long int mbid) const
{
  std::map<long long int,OMKey>::const_iterator iter = mbid2omkey_.find(mbid);
  if(iter == mbid2omkey_.end())
    log_fatal("unknown mainboard ID - %lld", mbid);

  return(iter->second);
}


inline
bool I3XMLOMKey2MBID::MBIDExists(OMKey key) const
{
  return(omkey2mbid_.count(key));
}


inline
long long int I3XMLOMKey2MBID::GetMBID(OMKey key) const
{
  std::map<OMKey,long long int>::const_iterator iter = omkey2mbid_.find(key);
  if(iter == omkey2mbid_.end())
    log_fatal("unknown OM key - (%d, %u)", key.GetString(), key.GetOM());

  return(iter->second);
}

#endif /*I3XMLOMKEY2MBID_H_INCLUDED*/
