#include "phys-services/I3FileOMKey2MBID.h"
#include <fstream>
#include <string>

using namespace std;

I3FileOMKey2MBID::I3FileOMKey2MBID(const string& infile)
{
  ifstream fin(infile.c_str());
  if(!fin)
    {
      log_fatal("Cannot find the DOMId to mainboard mapping file %s",
		infile.c_str());
      Fatal("cannot find the DOMid to mainboard mapping file");
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

OMKey I3FileOMKey2MBID::GetOMKey(long long int mbid) 
{
  if(mbid2omkey_.count(mbid)<=0)
    Fatal("Unknown mbid");
  return mbid2omkey_[mbid];
  
}

long long int I3FileOMKey2MBID::GetMBID(OMKey key) 
{
  if(omkey2mbid_.count(key) <= 0)
    Fatal("Unknown omkey");
  return omkey2mbid_[key];
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
	    Fatal("bad om key");
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
	    Fatal("bad om key");
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

void I3FileOMKey2MBID::Fatal(const string& message) 
{
  log_fatal(message.c_str());
}
