/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3XMLOMKey2MBID.cxx 7629 2005-05-15 15:35:25Z tschmidt $
 *
 * @file I3XMLOMKey2MBID.cxx
 * @brief implementation of the I3XMLOMKey2MBID class
 * @version $Revision:  $
 * @date $Date: 2005-05-15 17:35:25 +0200 (Sun, 15 May 2005) $
 * @author tschmidt
 */

// class header files

#include <phys-services/I3XMLOMKey2MBID.h>

#include <utility>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

// definitions


// namespace declarations

using namespace std;

// implementation

I3XMLOMKey2MBID::I3XMLOMKey2MBID(const string& infile)
  : I3OMKey2MBID()
{
  if(infile.empty()) log_fatal("undefined file name");
  if(!boost::filesystem::exists(infile)
     || boost::filesystem::is_directory(infile))
    log_fatal("cannot find file \"%s\"", infile.c_str());
  
  boost::iostreams::filtering_istream ifs;
  if(infile.rfind(".gz") == (infile.length() - 3))
  {
    ifs.push(boost::iostreams::gzip_decompressor());
    log_info("file \"%s\" ends in .gz - using gzip decompressor", infile.c_str());
  }

  log_info("opening file \"%s\"", infile.c_str());
  ifs.push(boost::iostreams::file_source(infile));
  if(!ifs.good()) log_fatal("cannot open file \"%s\"", infile.c_str());
  boost::archive::xml_iarchive ia(ifs);
  
  ia >> boost::serialization::make_nvp("MBID_OMKey", mbid2omkey_);

  map<long long int, OMKey>::const_iterator iter;
  for(iter = mbid2omkey_.begin(); iter != mbid2omkey_.end(); ++iter)
    if(!(omkey2mbid_.insert(make_pair(iter->second, iter->first))).second)
      log_fatal("duplicated OM key - (%d, %u)",
                iter->second.GetString(), iter->second.GetOM());
}


I3XMLOMKey2MBID::~I3XMLOMKey2MBID()
{
}
