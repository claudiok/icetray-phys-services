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

// #include <phys-services/I3TRandomService.h>
#include <phys-services/I3SPRNGRandomService.h>
#include <phys-services/I3GSLRandomService.h>

template <typename T, typename Init>
void
register_randomservice(const char* doc)
{
  class_<T, boost::shared_ptr<T>, boost::noncopyable>(I3::name_of<T>().c_str(),
						      doc,
						      Init())
    .def("Binomial", &T::Binomial)
    .def("Exp", &T::Exp)
    .def("Integer", &T::Integer)
    .def("Poisson", &T::Poisson)
    .def("PoissonD", &T::PoissonD)
    .def("Uniform", (double (T::*)(double)) &T::Uniform)
    .def("Uniform", (double (T::*)(double, double)) &T::Uniform)
    .def("Gaus", &T::Gaus)
    ;
  implicitly_convertible<shared_ptr<T>, shared_ptr<const I3RandomService> >();
  implicitly_convertible<shared_ptr<T>, shared_ptr<I3RandomService> >();
  implicitly_convertible<shared_ptr<T>, shared_ptr<const T> >();
}

void register_RandomServices()
{
  register_randomservice<I3GSLRandomService, init<unsigned long int> >("gsl random goodness");
  register_randomservice<I3SPRNGRandomService, init<int, int, int> >("sprng random goodness");
}
