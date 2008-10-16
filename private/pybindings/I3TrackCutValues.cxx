//
//   Copyright (c) 2008   Troy D. Straszheim and the IceCube Collaboration 
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

#include <phys-services/I3TrackCutValues.h>

void register_I3TrackCutValues()
{
  class_<I3TrackCutValues, bases<I3FrameObject>, boost::shared_ptr<I3TrackCutValues> >("I3TrackCutValues")
    .def_readwrite("Nchan", &I3TrackCutValues::Nchan)
    .def_readwrite("Nhit", &I3TrackCutValues::Nhit)
    .def_readwrite("NString", &I3TrackCutValues::Nstring)
    .def_readwrite("Ndir", &I3TrackCutValues::Ndir)
    .def_readwrite("Ldir", &I3TrackCutValues::Ldir)
    .def_readwrite("Sdir", &I3TrackCutValues::Sdir)
    .def_readwrite("Sall", &I3TrackCutValues::Sall)
    .def_readwrite("cog", &I3TrackCutValues::cog)
    ;

  register_pointer_conversions<I3TrackCutValues>();
}
