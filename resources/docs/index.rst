Phys-Services Documentation
===========================
The phys-services project is a collection of IceTray services and other
utilities common to all or most of icetray-based software.

Also see the `doxygen <../../doxygen/phys-services/index.html>`_ docs.

I3SPEFitInjector
^^^^^^^^^^^^^^^^
This class simply loads SPE fit values from a JSON file (provided by the 
Calibration Group) into the I3DOMCalibration class.  I3DOMCalibration has 
both a struct with combined fit values (SPEChargeDistribution) and mean
values for the FADC and ATWD channels and accessed via C++ as follows :

* I3DOMCalibration::GetMeanATWDCharge()
* I3DOMCalibration::GetMeanFADCCharge()
* I3DOMCalibration::GetCombinedSPEChargeDistribution()

Caveats
!!!!!!! 

* Invalid fits are simply skipped and no record of them will exist in the I3Calibration: domCal map.
* The mean ATWD and FADC charges are initialized to NAN, but should always be set to a valid number, typically 0.  So downstream code (to be doubly-safe) should check std::isfinite(value) is *true*.  The following methods are provided as a convenience :
 - I3DOMCalibration::IsMeanATWDChargeValid
 - I3DOMCalibration::IsMeanFADCChargeValid

For more information :
https://wiki.icecube.wisc.edu/index.php/SPE_recalibration

Code Review
^^^^^^^^^^^
.. toctree::
   :titlesonly:

   spe_fit_injector_code_review

