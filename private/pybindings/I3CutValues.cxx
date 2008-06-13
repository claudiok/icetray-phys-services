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

#include <phys-services/I3CutValues.h>

BOOST_PYTHON_MODULE(phys_services)
{
  class_<I3CutValues, bases<I3FrameObject>, boost::shared_ptr<I3CutValues> >("I3CutValues")
    .def_readwrite("Nchan", &I3CutValues::Nchan)
    .def_readwrite("Nhit", &I3CutValues::Nhit)
    .def_readwrite("NString", &I3CutValues::Nstring)
    .def_readwrite("Ndir", &I3CutValues::Ndir)
    .def_readwrite("Ldir", &I3CutValues::Ldir)
    .def_readwrite("Sdir", &I3CutValues::Sdir)
    .def_readwrite("Sall", &I3CutValues::Sall)
    .def_readwrite("cog", &I3CutValues::cog)
    ;

  register_pointer_conversions<I3CutValues>();
}
