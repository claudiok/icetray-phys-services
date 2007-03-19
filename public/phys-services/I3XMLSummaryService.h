/**
 * copyright  (C) 2007
 * the icecube collaboration
 * $Id: $
 *
 * @version $Revision: $
 * @date $Date: $
 * @author juancarlos@icecube.wisc.edu
 *
 */

#ifndef I3XMLSUMMARYSERVICE_H
#define I3XMLSUMMARYSERVICE_H

#include "Rtypes.h"
#include "dataclasses/Utility.h"
#include <icetray/I3DefaultName.h>
#include <icetray/I3FrameObject.h>
#include <dataclasses/I3Map.h>
#include <phys-services/I3SummaryService.h>
#include <iostream>
#include <fstream>

/**
 * @brief This class provides an XML implementation of the I3SummaryService. 
 * It allows collection of job statistics that can be written to xml for other programs 
 * to parse and collect (e.g. sim-prod).
 *
 */

class I3XMLSummaryService: public I3SummaryService {
 public:
  /**
   * constructors
   */
  I3XMLSummaryService();

  I3XMLSummaryService(string filename);

  /**
   * destructor
   */ 
  virtual ~I3XMLSummaryService();


  /**
   * Set filename to save serialized service to
   */
  void SetPath(string filename);

  /**
   * Access dictionary entry
   */
  double& operator[] (const string& key);

  /**
   * Add a value to the value summary map
   */
  void SetValue(string name,double value);

  /**
   * Get value from the value summary map
   */
  double GetValue(string name);

  /**
   * Write an I3XMLSummaryService map to a stream
   */
  void WriteXML(ostream& oss);

  /**
   * Write an I3XMLSummaryService map to a file
   */
  void WriteXML(string outfile);

  /**
   * Load an I3XMLSummaryService map from an iostream
   */
  void ReadXML(istream& iss);

  /**
   * Load an I3XMLSummaryService map from a file
   */
  void ReadXML(string infile);

 private:

  I3Map<string,double> valuemap_;
  string filename_;

  // copy and assignment private
  I3XMLSummaryService(const I3XMLSummaryService&);
  const I3XMLSummaryService& operator=(const I3XMLSummaryService&);

  SET_LOGGER("I3XMLSummaryService");

};

I3_DEFAULT_NAME(I3XMLSummaryService);
I3_POINTER_TYPEDEFS(I3XMLSummaryService);

#endif //I3XMLSUMMARYSERVICE_H
