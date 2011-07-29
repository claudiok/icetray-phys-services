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

#include <phys-services/I3Calculator.h>

void register_I3Calculator()
{
  // map the I3Calculator namespace to a sub-module  
  // make "from phys-services import <whatever>" work  
  bp::object I3CalculatorModule(bp::handle<>(bp::borrowed(PyImport_AddModule("phys-services.I3Calculator"))));  
  // make "from phys-services import I3Calculator" work  
  bp::scope().attr("I3Calculator") = I3CalculatorModule;  
  // set the current scope to the new sub-module  
  bp::scope I3Calculator_scope = I3CalculatorModule;  
  // export stuff in the I3Calculator namespace  
  def("closest_approach_distance", I3Calculator::ClosestApproachDistance);
  def("closesqt_approach_position", I3Calculator::ClosestApproachPosition);
  def("distance_along_track", I3Calculator::DistanceAlongTrack);
  def("is_on_track", I3Calculator::IsOnTrack);
  def("time_residual", (double (*)( const I3Particle&, const I3Position&,  double, const double, const double)) &I3Calculator::TimeResidual);
  def("angle", I3Calculator::Angle);
  def("distance", I3Calculator::Distance);
  def("four_distance", I3Calculator::FourDistance);


}
