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

#include <phys-services/I3CutValuesStd.h>

void register_I3CutValuesStd()
{
#define MEMBERS (Nchan)(Nhit)(Nstring)(Nearly)(Nlate)(NdirA)(LdirA)(SdirA) \
    (NdirB)(LdirB)(SdirB)(NdirC)(LdirC)(SdirC)(NdirD)(LdirD)(SdirD)(NdirE)(LdirE) \
    (SdirE)(Sall)(Lall)(cSize)(cog)

  class_<I3CutValuesStd, bases<I3FrameObject>, I3CutValuesStdPtr>("I3CutValuesStd")
    BOOST_PP_SEQ_FOR_EACH(WRAP_RO, I3CutValuesStd, MEMBERS)
    ;

  register_pointer_conversions<I3CutValuesStd>();
}
