/*
 * class:  I3FileOMKey2MBID
 *
 * Version: $Id$
 *
 * (c) IceCube Collaboration
 */

#include <phys-services/I3FileOMKey2MBID.h>

#include <fstream>
#include <cassert>

#include <phys-services/I3XMLOMKey2MBID.h>


using namespace std;


I3FileOMKey2MBID::I3FileOMKey2MBID(const string& infile)
{
  ifstream fin(infile.c_str());
  if(!fin)
    {
      log_fatal("Cannot find the DOMId to mainboard mapping file (%s)",
		infile.c_str());
      log_fatal("cannot find the DOMid to mainboard mapping file");
    }
  string omkey;
  string domid;
  string name;
  long long int mbid;
  while(fin.peek()!=EOF)
    if(fin.peek() == '#')
      {
	log_debug("comment line");
	fin.ignore(255,'\n');
      }
    else
      {
	fin>>omkey>>domid>>name>>hex>>mbid;
	log_debug("OMKey:%s DomID: %s, Name:%s, Mainboard ID: %lld",
		  omkey.c_str(),
		  domid.c_str(),
		  name.c_str(),
		  mbid);
	OMKey key = OMKeyize(omkey);
	mbid2omkey_[mbid] = key;
	omkey2mbid_[key] = mbid;
	fin.ignore(255,'\n');
      }
}


I3FileOMKey2MBID::~I3FileOMKey2MBID()
{
}


/**
 * @todo This is an ugly mess.
 */
OMKey I3FileOMKey2MBID::OMKeyize(const string& key) 
{
  assert(key.size() == 5 || key.size() == 4);
  char om_string_array[3];
  om_string_array[0] = key[0];
  om_string_array[1] = key[1];
  om_string_array[2] = '\0';
  int om_string = atoi(om_string_array);
  int om_num= -1;
  if(key.size() == 4)
    {
      if(key[2] == 'A')
	if(key[3] == '1')
	  {
	    om_num = 61;
	  }
	else if(key[3] == '2')
	  {
	    om_num = 62;
	  }
	else
	  {
	    log_fatal("bad om key");
	  }
      else if(key[2] == 'B')
	if(key[3] == '1')
	  {
	    om_num = 63;
	  }
	else if(key[3] == '2')
	  {
	    om_num = 64;
	  }
	else
	  {
	    log_fatal("bad om key");
	  }
    }
  else
    {
      char om_num_array[3];
      om_num_array[0]=key[3];
      om_num_array[1]=key[4];
      om_num_array[2]='\0';
      om_num = atoi(om_num_array);
    }
  assert(om_num > 0);
  //  cout<<"OMString#:"<<om_string<<"   ";
  //   cout<<"DOM#:"<<om_num;
  //   cout<<"   Should correspond to "<<key<<endl;
  return OMKey(om_string,om_num);
}


void I3FileOMKey2MBID::DumpAsXML(const std::string& outfile) const
{
  I3XMLOMKey2MBID::Dump(outfile, mbid2omkey_);
}
