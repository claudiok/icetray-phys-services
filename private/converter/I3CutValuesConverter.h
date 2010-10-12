/**
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Jakob van Santen <vansanten@wisc.edu> $LastChangedBy$
 */

#include <tableio/I3ConverterFactory.h>
#include <phys-services/I3CutValues.h>

class I3CutValuesConverter : public I3ConverterImplementation<I3CutValues > {
public:
    I3CutValuesConverter();
private:
    I3TableRowDescriptionPtr CreateDescription(const I3CutValues& cv);
    size_t FillRows(const I3CutValues& cv, I3TableRowPtr rows);
    
};
