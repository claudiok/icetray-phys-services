/**
 * copyright  (C) 2007
 * the icecube collaboration
 * $Id: $
 *
 * @version $Revision: $
 * @date $Date: $
 * @author juancarlos
 *
 * @todo 
 */
//#include <iostream>

#include <fstream>

#include <phys-services/I3XMLSummaryService.h>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

/**
 * @brief This class provides an interface to write job statistics
 * by icetray modules.
 *
 */

using namespace boost::archive;

istream& operator >>(istream &is, I3MapStringDouble& i3obj)
{
	shared_ptr<I3MapStringDouble> spt;
	try { 
			boost::archive::xml_iarchive xia(is);
			xia >> BOOST_SERIALIZATION_NVP(i3obj);
	} catch (const boost::archive::archive_exception& e) { 
			log_fatal("Archive error: %s ", e.what() ); 
	} 
	return is;
}

istream& operator >>(istream &is, I3MapStringDoublePtr i3objptr)
{
		is >> *i3objptr;
		return is;
}


ostream& operator <<(ostream &os, const I3MapStringDouble& i3obj)
{
	try { 
			const I3MapStringDouble *tobj_p = &i3obj;
			boost::archive::xml_oarchive xoa(os);
			xoa << make_nvp("I3XMLSummaryService", tobj_p); 
	} catch (const boost::archive::archive_exception& e) { 
			log_fatal("Archive error: %s ", e.what() ); 
	} 
	return os;
}

ostream& operator <<(ostream &os, const I3MapStringDoublePtr i3objptr)
{
	os << *i3objptr;
	return os;
}

I3XMLSummaryService::I3XMLSummaryService(string filename)
{
		filename_ = filename;
}

I3XMLSummaryService::I3XMLSummaryService():
		filename_("i3summary.xml")
{
    	start_real_ = time(NULL);
    	fail_ = (getrusage(RUSAGE_SELF, &start_) == -1);
}

void
I3XMLSummaryService::SetPath(string filename) {
		filename_= filename;
}

/**
 * Access dictionary entry
 */
double& I3XMLSummaryService::operator[] (const string& key)
{
	return valuemap_[key];
}


/**
 * Add a value to the value summary map
 */
void 
I3XMLSummaryService::SetValue(string name,double value) 
{
  valuemap_[name]= value;
}

/**
 * Get value from the value summary map
 */
double
I3XMLSummaryService::GetValue(string name)
{
  return valuemap_[name];
}


void
I3XMLSummaryService::WriteXML(ostream& oss)
{ 
	oss << valuemap_; 
}

void
I3XMLSummaryService::WriteXML(string outfile)
{ 
	ofstream oss(outfile.c_str(), ios::out);
	log_trace("Writting: map to %s", outfile.c_str() ); 
	oss << valuemap_; 
}

void
I3XMLSummaryService::ReadXML(istream& iss)
{ 
	iss >> valuemap_; 
}

void
I3XMLSummaryService::ReadXML(string infile)
{ 
	ifstream iss(infile.c_str(), ios::in);
	iss >> valuemap_; 
}

I3XMLSummaryService::~I3XMLSummaryService()
{
    // Compute CPU and real time
    if (getrusage(RUSAGE_SELF, &stop_) != -1 && !fail_) { 
		double user = (stop_.ru_utime.tv_sec - start_.ru_utime.tv_sec); 
		user += double(stop_.ru_utime.tv_usec - start_.ru_utime.tv_usec) / 10E+06; 
		valuemap_["user_time"] += user;
		
		double sys = (stop_.ru_stime.tv_sec - start_.ru_stime.tv_sec); 
		sys += double(stop_.ru_stime.tv_usec - start_.ru_stime.tv_usec) / 10E+06; 
		valuemap_["sys_time"] += sys;

        // integral shared text memory size 
        valuemap_["shared memory"]+=stop_.ru_ixrss;

        // ru_idrss integral unshared data size 
        // ru_isrss integral unshared stack size 
        valuemap_["unshared memory"]+=stop_.ru_idrss+stop_.ru_isrss;

        // swaps
        valuemap_["memory swaps"] += stop_.ru_nswap;

        // context switches
        valuemap_["context switches"] += stop_.ru_nvcsw + stop_.ru_nivcsw;
	}
   	stop_real_ = time(NULL);
	valuemap_["real_time"] += difftime(stop_real_, start_real_);

	// print the xml
	WriteXML(filename_);
}
