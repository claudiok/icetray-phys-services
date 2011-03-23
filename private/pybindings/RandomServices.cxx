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

#ifdef I3_USE_ROOT
#include <phys-services/I3TRandomService.h>
#endif
#ifdef I3_USE_SPRNG
#include <phys-services/I3SPRNGRandomService.h>
#endif
#include <phys-services/I3GSLRandomService.h>

using namespace boost::python;
namespace bp = boost::python;

struct I3RandomServiceWrapper : I3RandomService, wrapper<I3RandomService>
{
  int Binomial(int ntot, double prob) { return this->get_override("Binomial")(ntot, prob); }
  double Exp(double tau) { return this->get_override("Exp")(tau); }
  unsigned int Integer(unsigned int imax) { return this->get_override("Integer")(imax); }
  int Poisson(double mean) { return this->get_override("Poisson")(mean); }
  double PoissonD(double mean) { return this->get_override("PoissonD")(mean); }
  double Uniform(double x1) { return this->get_override("Uniform")(x1); }
  double Uniform(double x1, double x2) { return this->get_override("Uniform")(x1, x2 ); }
  double Gaus(double mean, double stddev) { return this->get_override("Gaus")(mean, stddev); }
};

template <typename T, typename Init>
scope
register_randomservice(const char* name, const char* doc, const Init& init)
{
  implicitly_convertible<shared_ptr<T>, shared_ptr<const I3RandomService> >();
  implicitly_convertible<shared_ptr<T>, shared_ptr<I3RandomService> >();
  implicitly_convertible<shared_ptr<T>, shared_ptr<const T> >();

  return class_<T, boost::shared_ptr<T>, boost::noncopyable>(name,
							     doc,
							     init)
    .def("Binomial", &T::Binomial)
    .def("Exp", &T::Exp)
    .def("Integer", &T::Integer)
    .def("Poisson", &T::Poisson)
    .def("PoissonD", &T::PoissonD)
    .def("Uniform", (double (T::*)(double)) &T::Uniform)
    .def("Uniform", (double (T::*)(double, double)) &T::Uniform)
    .def("Gaus", &T::Gaus)
    ;
  
}

namespace bp = boost::python;

void register_RandomServices()
{
  register_randomservice<I3GSLRandomService>("I3GSLRandomService", "gsl random goodness",
					     init<unsigned long int>(bp::arg("seed")));

#ifdef I3_USE_ROOT
  register_randomservice<I3TRandomService>("I3TRandomService", "ROOT random badness",
					     init<unsigned long int>(bp::arg("seed")));
#endif

#ifdef I3_USE_SPRNG
  register_randomservice<I3SPRNGRandomService>("I3SPRNGRandomService", "sprng random goodness",
					       init<int, int, int>((bp::arg("seed"), 
								    bp::arg("nstreams"),
								    bp::arg("streamnum"))));
#endif

  register_randomservice<I3RandomServiceWrapper>("I3RandomService", "base class for python impls",
						 init<>());
}
