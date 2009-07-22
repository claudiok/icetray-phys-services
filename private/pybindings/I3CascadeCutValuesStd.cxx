//
//   Copyright (c) 2009   Troy D. Straszheim and the IceCube Collaboration 
//   
//   This file is part of IceTray.
//
//   IceTray is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 3 of the License, or
//   (at your option) any later version.
//
//   IceTray is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

using namespace boost::python;
namespace bp = boost::python;

#include <phys-services/I3CascadeCutValuesStd.h>

void register_I3CascadeCutValuesStd()
{
#define MEMBERS (Nchan)(Nhit)(N_1hit)(Nstring)(NdirA)\
    (NearlyA)(NlateA)(NdirB)(NearlyB)(NlateB)(NdirC)\
    (NearlyC)(NlateC)(NdirD)(NearlyD)(NlateD)(NdirE)\
    (NearlyE)(NlateE)

  class_<I3CascadeCutValuesStd, bases<I3FrameObject>, I3CascadeCutValuesStdPtr>("I3CascadeCutValuesStd")
    BOOST_PP_SEQ_FOR_EACH(WRAP_RO, I3CascadeCutValuesStd, MEMBERS)
    ;

  register_pointer_conversions<I3CascadeCutValuesStd>();
}
