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

struct cutvalues
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
};

cutvalues CutsCalc(const I3Particle& track, const I3Geometry& geometry, 
                   const I3RecoPulseSeriesMap& pulsemap, 
                   const double t1, const double t2)
{
  cutvalues cv;
  I3Cuts::CutsCalc(track, geometry, pulsemap, t1, t2, cv.Nchan, cv.Nhit, cv.Nstring, cv.Ndir, cv.Ldir, cv.Sdir, cv.Sall);
  return cv;
}

cutvalues CutsCalc(const I3Particle& track, const I3Geometry& geometry, 
                   const I3RecoHitSeriesMap& hitmap, 
                   const double t1, const double t2)
{
  cutvalues cv;
  I3Cuts::CutsCalc(track, geometry, hitmap, t1, t2, cv.Nchan, cv.Nhit, cv.Nstring, cv.Ndir, cv.Ldir, cv.Sdir, cv.Sall);
  return cv;
}


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
  class_<cutvalues>("cutvalues")
    .def_readwrite("Nchan", &cutvalues::Nchan)
    .def_readwrite("Nhit", &cutvalues::Nhit)
    .def_readwrite("Nstring", &cutvalues::Nstring)
    .def_readwrite("Ndir", &cutvalues::Ndir)
    .def_readwrite("Ldir", &cutvalues::Ldir)
    .def_readwrite("Sdir", &cutvalues::Sdir)
    .def_readwrite("Sall", &cutvalues::Sall)
    ;
  def("COG", (I3Position (*)( const I3Geometry&, const I3RecoPulseSeriesMap&)) &I3Cuts::COG);
  def("COG", (I3Position (*)( const I3Geometry&, const I3RecoHitSeriesMap&)) &I3Cuts::COG);
  def("CutsCalc", (cutvalues (*)( const I3Particle&, const I3Geometry&, const I3RecoHitSeriesMap&, const double, const double)) &CutsCalc);
  def("CutsCalc", (cutvalues (*)( const I3Particle&, const I3Geometry&, const I3RecoPulseSeriesMap&, const double, const double)) &CutsCalc); 
  def("NChan", &I3Cuts::Nchan);		// only takes hitseries
  def("Nhit", &I3Cuts::Nhit);		// only takes hitseries
  def("N_1hit", &I3Cuts::N_1hit);	// only takes hitseries
  def("Nstring", &I3Cuts::Nstring);		// only takes hitseries
  def("Ndir", (int (*)( const I3Particle&, const I3Geometry&, const I3RecoHitSeriesMap&, double, double)) &I3Cuts::Ndir);
  def("Ndir", (int (*)( const I3Particle&, const I3Geometry&, const I3RecoPulseSeriesMap&, double, double)) &I3Cuts::Ndir);
  def("ContainmentAreaSize", I3Cuts::ContainmentAreaSize);
  def("ContainmentVolumeSize", I3Cuts::ContainmentVolumeSize);
}

