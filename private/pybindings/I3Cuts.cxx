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

#include <phys-services/I3Cuts.h>

void register_I3Cuts()
{
  // map the I3Cuts namespace to a sub-module  
  // make "from phys-services import <whatever>" work  
  bp::object I3CutsModule(bp::handle<>(bp::borrowed(PyImport_AddModule("phys-services.I3Cuts"))));  
  // make "from phys-services import I3Cuts" work  
  bp::scope().attr("I3Cuts") = I3CutsModule;  
  // set the current scope to the new sub-module  
  bp::scope I3Cuts_scope = I3CutsModule;  
  // export stuff in the I3Cuts namespace  
  def("ContainmentAreaSize", I3Cuts::ContainmentAreaSize);
  def("ContainmentVolumeSize", I3Cuts::ContainmentVolumeSize);
}
