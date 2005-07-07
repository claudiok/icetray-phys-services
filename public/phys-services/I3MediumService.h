/**
 * Definition of I3MediumService class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id:  $
 *
 * @file I3MediumService.h
 * @version $Revision:  $
 * @date $Date:  $
 * @author mribordy (original code of I3Medium)
 * @author tschmidt
 */

#ifndef I3_MEDIUM_SERVICE_H_INCLUDED
#define I3_MEDIUM_SERVICE_H_INCLUDED

// forward declarations


// header files

#include <fstream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "TH1D.h"
#include "TH2D.h"
#include "dataclasses/I3Constants.h"
#include "services/I3Logging.h"

// definitions


// namespace declarations

using namespace std;

/**
 * @brief This class describes the medium of the Amanda/IceCube detector.
 * 
 * It might be initialized with an ice properties file.
 * It returns default values (bulk ice), which are independent of the
 * wavelength, if it is not initialized.
 * 
 * About the ice properties file:
 * - it is important that it starts with NLAYER NWVL LAYER ...
 * - layer depth should be ordered with increasing values, with constant widths
 * - if layer widths are not constant or layer depths are not ordered, 
 *   it will work as well, but integration results will be wrong
 * - if argument of depths or wavelengths are out of bounds
 *   (what is defined in the ice properties file) then the results are only
 *   partially correct (depth and wavelength are set to their limits before
 *   calculation)
 * 
 * Possible improvements (?):
 * - allow for other I3dB input
 * - default hardcoded bulk ice: could depend on wavelength
 * - introduce x-y dependence --> simply add methods replacing z with vectors or the like
 * 
 * Measurements of effective scattering and absorption lengths at lambda = 532 nm. Not here ...
 * Here: millenium model Kurt/Buford:
 * - use 380 nm here (in an extended range of depths: measurements at 532 nm
 *   and at different other wavelengths for a more restricted range)
 * - n_group, n, scatt, abs, mean scatt. angle are all functions of frequency.
 */
class I3MediumService{
public:
	static const double RECO_WAVELENGTH = 380.0;


  /**
   * @brief Returns a default name for this service
   * 
   * @return The default name.
   */
  static const char* DefaultName(){ return "MediumService"; }


	/**
	 * @brief Default constructor.
	 */
	I3MediumService();
	
	/**
	 * @brief Destructor.
	 */
  virtual ~I3MediumService();
  
  /**
   * @brief Initialize the medium from an ice properties file.
   * 
   * If the medium is not inititialized, it is supposed to be bulk ice.
   * 
   * @param propInFilename Path/name of an ice properties file.
   * @param histoOutFilename Path/name of a ROOT file to dump
   * lookup tables into (optional).
   * @return True, if the medium is initialized.
   */
  bool Initialize
  	(const string& propInFilename, const string& histoOutFilename = "");
  	
  /**
   * @brief Returns, if the medium is initialized from an ice properties file.
   * 
   * @return True, if the medium is initialized.
   */
  bool IsInitialized();

	/**
	 * @brief Returns NPhase at a given wavelength.
	 * 
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return NPhase.
	 */
  double NPhase(double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns DNPhaseDLambda at a given wavelength.
	 * 
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return DNPhaseDLambda.
	 */
  double DNPhaseDLambda(double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns NGroup at a given wavelength.
	 * 
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return NGroup.
	 */
  double NGroup(double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the inverse speed of light in ice at a given wavelength.
	 * 
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Inverse speed of light in ice.
	 */
  double InvC_ICE(double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the speed of light in ice at a given wavelength.
	 * 
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Speed of light in ice.
	 */
  double C_ICE(double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the inverse CosThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Inverse CosThetaC.
	 */
  double InvCosThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns CosThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return CosThetaC.
	 */
  double CosThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns ThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return ThetaC.
	 */
  double ThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns SinThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return SinThetaC.
	 */
  double SinThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the inverse SinThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Inverse SinThetaC.
	 */
  double InvSinThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns TgThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return TgThetaC.
	 */
  double TgThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns CtgThetaC at a given relativistic beta and wavelength.
	 * 
	 * @param beta Relativistic beta
	 * (optoinal; default <VAR>1</VAR>).
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return CtgThetaC.
	 */
  double CtgThetaC(double beta=1, double wavelength=RECO_WAVELENGTH);


	/**
	 * @brief Returns the absorptivity.
	 * 
	 * Methods for bulk ice (neither depend on wavelength).
	 * @return Absorptivity.
	 */
	double BulkIceAbsorptivity();

	/**
	 * @brief Sets the absorptivity.
	 * 
	 * Methods for bulk ice (neither depend on wavelength).
	 * @param absy Absorptivity.
	 */
  void SetBulkIceAbsorptivity(double absy);

	/**
	 * @brief Returns the inverse effective scattering length.
	 * 
	 * Methods for bulk ice (neither depend on wavelength).
	 * @return The inverse effective scattering length.
	 */
  double BulkIceInvEffScattLength();

	/**
	 * @brief Sets the inverse effective scattering length.
	 * 
	 * Methods for bulk ice (neither depend on wavelength).
	 * @param invlen The inverse effective scattering length.
	 */
  void SetBulkiceInvEffScattLength(double invlen);

	/**
	 * @brief Returns the absorption length.
	 * 
	 * Methods for bulk ice (neither depend on wavelength).
	 * @return The absorption length.
	 */
  double BulkIceAbsorptionLength();

	/**
	 * @brief Returns the effective scattering length.
	 * 
	 * Methods for bulk ice (neither depend on wavelength).
	 * @return The effective scattering length.
	 */
  double BulkIceEffScattLength();

 	/**
	 * @brief Returns the mean scattering cosine.
	 * 
	 * @return The mean scattering cosine.
	 */
  double MeanScatteringCosine();

	/**
	 * @brief Sets the mean scattering cosine.
	 * 
	 * @param cosine The mean scattering cosine.
	 */
  void SetMeanScatteringCosine(double cosine);

	/**
	 * @brief Returns the absorptivity at a given depth and wavelength.
	 * 
	 * @param depth Depth
	 * (optional; default is <VAR>0</VAR>, so that it can be called when medium
	 * is not initialized),
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Absorptivity.
	 */
  double Absorptivity(double depth=0, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the inverse effective scattering length at a given depth and wavelength.
	 * 
	 * @param depth Depth
	 * (optional; default is <VAR>0</VAR>, so that it can be called when medium
	 * is not initialized),
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Inverse effective scattering length.
	 */
  double InvEffScattLength(double depth=0, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the absorption length at a given depth and wavelength.
	 * 
	 * @param depth Depth
	 * (optional; default is <VAR>0</VAR>, so that it can be called when medium
	 * is not initialized),
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Absorption length.
	 */
  double AbsorptionLength(double depth=0, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the effective scattering length at a given depth and wavelength.
	 * 
	 * @param depth Depth
	 * (optional; default is <VAR>0</VAR>, so that it can be called when medium
	 * is not initialized),
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Effective scattering length.
	 */
  double EffScattLength(double depth=0, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the averaged absorptivity at a given depth and wavelength.
	 * 
	 * @param z1
	 * @param z2
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Averaged absorptivity.
	 */
  double AveragedAbsorptivity
  	(double z1, double z2, double wavelength=RECO_WAVELENGTH);
  	
	/**
	 * @brief Returns the averaged inverse effective scattering length at a given depth and wavelength.
	 * 
	 * @param z1
	 * @param z1
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Averaged inverse effective scattering length.
	 */
  double AveragedInvEffScattLength
  	(double z1, double z2, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the averaged absorption length at a given depth and wavelength.
	 * 
	 * @param z1
	 * @param z2
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Averaged absorption length.
	 */
  double AveragedAbsorptionLength
  	(double z1, double z2, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns the averaged effective scattering length at a given depth and wavelength.
	 * 
	 * @param z1
	 * @param z2
	 * @param wavelength Wavelength in nm
	 * (optional; default is RECO_WAVELENGTH).
	 * @return Averaged effective scattering length.
	 */
  double AveragedEffScattLength
  	(double z1, double z2, double wavelength=RECO_WAVELENGTH);
  
private:
	const static int MIN_WAVELENGTH_PRICE = 300;
	const static int MAX_WAVELENGTH_PRICE = 600;
	const static string NLAYER_TOKEN;
	const static string NWVL_TOKEN;
	const static string LAYER_TOKEN;
	const static string ABS_TOKEN;
	const static string SCAT_TOKEN;


	static double C_VACUUM(){ return 2.99792458e-1; }
	static double InvC_VACUUM(){ return 1.0 / C_VACUUM(); }


  // private copy constructors and assignment
  I3MediumService(const I3MediumService& );
  I3MediumService operator=(const I3MediumService& );

  void CheckBounds(double& depth, double& wavelength);
  void CheckWLBounds(double & wavelength); // from Price/Woschnagg analytical formula
	void DumpLookupTable(const string& histoOutFilename);
  void GetBin
  	(TAxis* axis, double val, int& bin1, int& bin2, double& delta);
	int GetNextToken(istream& f, string& token);
  void InitLookupTable(); // initialization of the lookup tables
  double Interp2DLin // to interpolate linear
  	(double& depth, double& wavelength, const TH2D* h); // linear interpolation
  double Interp2DIntLin // interp2D_intlin: given hderiv is lin. interp., h (\int h) is interp. quadratically.
	  (double& depth, double& wavelength, const TH2D* h, const TH2D* hDeriv); // quad. interpolation
	bool IsInitializedWithWarning();

  // instance member data
  double bulkiceAbsorptivity_;
  double bulkiceInvEffScattLength_;
  TH2D* hIntAbsLen_; // histo with integrated abs./scatt. at reco_wavelength, w.r.t. the depth
  TH2D* hIntEffScattLen_;
  TH2D* hIceLayerAbsorptivity_; // histos of abs./scatt. w.r.t. the depth and wavelength 
  TH2D* hIceLayerInvEffScattLen_;
  bool isInitialized_;
  double meanScatCosine_;

  double minz_, maxz_, binw_;
  double wlmin_, wlstep_, minwl_, maxwl_;
  int nlayer_, nwl_, recobinwl_, nbin_;

////////////////////////////////////////////////////////////////
// That's Amanda framework stuff
//
// I do not know, if it is really needed within IceTray.
// Anyway I included it under reserve.
////////////////////////////////////////////////////////////////

private:
  static const int N_LAYER;
  static const char* DUSTY_LAYER_TYPE[];
  static const double DUSTY_LAYER_COO[];

public:

	/**
	 * @brief Returns the number of layers of a specified type.
	 * 
	 * @param ltype The type of the layers (<VAR>clear</VAR>, <VAR>dusty</VAR>
	 * or <VAR>all</VAR>)(optional; default is <VAR>all</VAR>).
	 * @return The number of layers.
	 */
  static int GetNumberOfLayer(string ltype="all");

	/**
	 * @brief Returns the type a the layer at a given z-coordinate.
	 * 
	 * @param z Z-coordinate.
	 * @return The type a the layer.
	 */
  static string GetLayerType(double z);

	/**
	 * @brief Returns the (ordinal) number of the layer at a given z-coordinate.
	 * 
	 * @param z Z-coordinate.
	 * @return The (ordinal) number of the layer.
	 */
  static int GetLayerNumber(double z);


	/**
	 * @brief Returns a histogram of the averaged absorption length.
	 * 
	 * @param name Name (optional; default is <VAR>h</VAR>).
	 * @param nbin Number of bins (optional; default is <VAR>100</Var>).
	 * @param from ... (optional; default is <VAR>0</Var>).
	 * @param min Minimum (optional; default is <VAR>600</Var>).
	 * @param max Maximum (optional; default is <VAR>630</Var>).
	 * @param wavelength Wavelength (optional; default is RECO_WAVELENGTH).
	 * @return Histogram
	 * - The caller takes ownership of the histogram!!!
	 * (Here one should return a smart pointer, but is Amanda software able
	 * to deal with smart pointers?)
	 */
  TH1D* GetAveragedAbsorptionLengthHistogram
  	(const string& name="h", int nbin=100, double from=0,
  	double min=-600, double max=630, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns a histogram of the averaged effective scattering length.
	 * 
	 * @param name Name (optional; default is <VAR>h</VAR>).
	 * @param nbin Number of bins (optional; default is <VAR>100</Var>).
	 * @param from ... (optional; default is <VAR>0</Var>).
	 * @param min Minimum (optional; default is <VAR>600</Var>).
	 * @param max Maximum (optional; default is <VAR>630</Var>).
	 * @param wavelength Wavelength (optional; default is RECO_WAVELENGTH).
	 * @return Histogram
	 * - The caller takes ownership of the histogram!!!
	 * (Here one should return a smart pointer, but is Amanda software able
	 * to deal with smart pointers?)
	 */
  TH1D* GetAveragedEffScatteringLengthHistogram
  	(const string& name="h", int nbin=100, double from=0,
  	double min=-600, double max=630, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns a histogram of the absorption length.
	 * 
	 * @param name Name (optional; default is <VAR>h</VAR>).
	 * @param nbin Number of bins (optional; default is <VAR>100</Var>).
	 * @param min Minimum (optional; default is <VAR>600</Var>).
	 * @param max Maximum (optional; default is <VAR>630</Var>).
	 * @param wavelength Wavelength (optional; default is RECO_WAVELENGTH).
	 * @return Histogram
	 * - The caller takes ownership of the histogram!!!
	 * (Here one should return a smart pointer, but is Amanda software able
	 * to deal with smart pointers?)
	 */
  TH1D* GetAbsorptionLengthHistogram
  	(const string& name="h", int nbin=100,
  	double min=-600, double max=630, double wavelength=RECO_WAVELENGTH);

	/**
	 * @brief Returns a histogram of the effective scattering length.
	 * 
	 * @param name Name (optional; default is <VAR>h</VAR>).
	 * @param nbin Number of bins (optional; default is <VAR>100</Var>).
	 * @param min Minimum (optional; default is <VAR>600</Var>).
	 * @param max Maximum (optional; default is <VAR>630</Var>).
	 * @param wavelength Wavelength (optional; default is RECO_WAVELENGTH).
	 * @return Histogram
	 * - The caller takes ownership of the histogram!!!
	 * (Here one should return a smart pointer, but is Amanda software able
	 * to deal with smart pointers?)
	 */
  TH1D* GetEffScatteringLengthHistogram
  	(const string& name="h", int nbin=100,
  	double min=-600, double max=630, double wavelength=RECO_WAVELENGTH);
  	
////////////////////////////////////////////////////////////////
  	
	// logging
	SET_LOGGER("I3MediumService");
	
	// ROOT macro
  ClassDef(I3MediumService,0);
};

typedef shared_ptr<I3MediumService> I3MediumServicePtr;

// inline methods

inline bool I3MediumService::IsInitialized(){
	return isInitialized_;
}

inline bool I3MediumService::IsInitializedWithWarning(){
	if(!IsInitialized()) log_warn("using bulk ice medium");	
	
	return IsInitialized();
}

inline double I3MediumService::InvC_ICE(double wavelength){
  return InvC_VACUUM() * NGroup(wavelength);
}

inline double I3MediumService::C_ICE(double wavelength){
  return 1.0 / InvC_ICE(wavelength);
}

inline double I3MediumService::InvCosThetaC(double beta, double wavelength){
  return NPhase(wavelength) * beta;
}

inline double I3MediumService::CosThetaC(double beta, double wavelength){
  return 1.0 / InvCosThetaC(beta, wavelength);
}

inline double I3MediumService::ThetaC(double beta, double wavelength){
  return acos(CosThetaC(beta, wavelength));
}

inline double I3MediumService::SinThetaC(double beta, double wavelength){
  return sin(ThetaC(beta, wavelength));
}

inline double I3MediumService::InvSinThetaC(double beta, double wavelength){
  return 1. / sin(ThetaC(beta, wavelength));
}

inline double I3MediumService::TgThetaC(double beta, double wavelength){
  return SinThetaC(beta, wavelength) / CosThetaC(beta, wavelength);
}

inline double I3MediumService::CtgThetaC(double beta, double wavelength){
  return CosThetaC(beta, wavelength) / SinThetaC(beta, wavelength);
}

inline double I3MediumService::BulkIceAbsorptivity(){
	return bulkiceAbsorptivity_;
}

inline void I3MediumService::SetBulkIceAbsorptivity(double absy){
	bulkiceAbsorptivity_ = absy;
}

inline double I3MediumService::BulkIceInvEffScattLength(){
	return bulkiceInvEffScattLength_;
}

inline void I3MediumService::SetBulkiceInvEffScattLength(double invlen){
	bulkiceInvEffScattLength_ = invlen;
}

inline double I3MediumService::BulkIceAbsorptionLength(){
	return 1. / bulkiceAbsorptivity_;
}

inline double I3MediumService::BulkIceEffScattLength(){
	return 1. / bulkiceInvEffScattLength_;
}

inline double I3MediumService::MeanScatteringCosine(){
	return meanScatCosine_;
}

inline void I3MediumService::SetMeanScatteringCosine(double cosine){
  	meanScatCosine_ = cosine;
}

inline double I3MediumService::AbsorptionLength
(double depth, double wavelength){
  return  1. / Absorptivity(depth, wavelength);
}

inline double I3MediumService::EffScattLength
(double depth, double wavelength){
  return 1. / InvEffScattLength(depth, wavelength);
}

inline double I3MediumService::AveragedAbsorptionLength
(double z1, double z2, double wavelength) {
  return 1. / AveragedAbsorptivity(z1, z2, wavelength);
}

inline double I3MediumService::AveragedEffScattLength
(double z1, double z2, double wavelength){
  return 1. / AveragedInvEffScattLength(z1, z2, wavelength);
}

#endif // I3_MEDIUM_SERVICE_H_INCLUDED

