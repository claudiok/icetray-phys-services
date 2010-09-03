/**
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> $LastChangedBy$
 */

#ifndef TABLEIO_OMBLOCKCONVERTER_H_INCLUDED
#define TABLEIO_OMBLOCKCONVERTER_H_INCLUDED

#include <tableio/I3ConverterFactory.h>
#include "dataclasses/physics/I3RecoPulse.h"

class OMBlockConverter : public I3ConverterImplementation< I3RecoPulseSeriesMap > {
public:
  OMBlockConverter();
  OMBlockConverter(const std::string &reconstruction);
  OMBlockConverter(const std::string &reconstruction, bool MC);

private:
  I3TableRowDescriptionPtr CreateDescription(const I3RecoPulseSeriesMap &pulses);
  size_t FillRows(const I3RecoPulseSeriesMap &pulses, I3TableRowPtr rows);
  size_t GetNumberOfRows(const I3RecoPulseSeriesMap &pulses);

  std::string reconstruction_;
  bool mc_;
};

#endif // TABLEIO_OMBLOCKCONVERTER_H_INCLUDED
