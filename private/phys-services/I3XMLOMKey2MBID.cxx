/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file phys-services/I3XMLOMKey2MBID.cxx
 * @brief implementation of the I3XMLOMKey2MBID class
 * @version $Revision$
 * @date $Date$
 * @author tschmidt
 */

// class header files

#include <phys-services/I3XMLOMKey2MBID.h>

#include <utility>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
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

void I3XMLOMKey2MBID::Dump(const string& outfile,
                           const map<long long int, OMKey>& conversionTable)
{
  if(outfile.empty()) log_fatal("undefined file name");
  
  boost::iostreams::filtering_ostream ofs;
  log_info("opening file \"%s\"", outfile.c_str());
  ofs.push(boost::iostreams::file_sink(outfile));
  if(!ofs.good()) log_fatal("cannot open file \"%s\"", outfile.c_str());

  if(outfile.rfind(".gz") == (outfile.length() - 3))
  {
    ofs.push(boost::iostreams::gzip_compressor());
    log_info("file \"%s\" ends in .gz - using gzip compressor", outfile.c_str());
  }
  boost::archive::xml_oarchive oa(ofs);
  
  oa << boost::serialization::make_nvp("MBID_OMKey", conversionTable);
}


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
