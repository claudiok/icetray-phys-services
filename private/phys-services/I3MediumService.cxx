/**
 * Implementation of I3MediumService class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id$
 *
 * @file I3MediumService.cxx
 * @version $Revision$
 * @date $Date$
 * @author mribordy (original code of I3Medium)
 * @author tschmidt
 */
 
// class header file

#include <phys-services/I3MediumService.h>

#include <algorithm>
#include <ctype.h>
#include <TFile.h>

#include <boost/version.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <dataclasses/I3Constants.h>
#include <icetray/I3Units.h>

// namespace declarations

using namespace std;
#if BOOST_VERSION >= 103400
using boost::test_tools::percent_tolerance;
#else
#define percent_tolerance
#endif
using boost::test_tools::check_is_close;

// implementation

const double I3MediumService::BULKICE_ABSORPTION_LENGTH = 98.0;
const double I3MediumService::BULKICE_EFF_SCATT_LENGTH = 33.3;
const double I3MediumService::C_VACUUM = I3Constants::c;
const double I3MediumService::EPSILON = 1e-7;
const double I3MediumService::INV_C_VACUUM = 1. / C_VACUUM;
const double I3MediumService::MAX_WAVELENGTH_PRICE = 600.;
const double I3MediumService::MEAN_SCATT_COSINE = 0.8;
const double I3MediumService::MIN_WAVELENGTH_PRICE = 300.;
const double I3MediumService::RECO_WAVELENGTH = 380.;
const double I3MediumService::FP_CMP_TOLERANCE = 1e-6;
const TString I3MediumService::HISTOPREFIX = "I3Medium";
unsigned int I3MediumService::instanceNumber_ = 0;


I3MediumService::I3MediumService()
	: bulkiceAbsorptivity_(1. / BULKICE_ABSORPTION_LENGTH),
		bulkiceInvEffScattLength_(1. / BULKICE_EFF_SCATT_LENGTH),
		hIntAbsLen_(0), hIntEffScattLen_(0),
		hIceLayerAbsorptivity_(0), hIceLayerInvEffScattLen_(0),
		isBulkice_(true), meanScatCosine_(MEAN_SCATT_COSINE){
  TString suffix="";
  suffix+=instanceNumber_;
  nameAbsHisto_ = HISTOPREFIX+"_Absorptivity_"+suffix;
  nameInvScatLenHisto_ = HISTOPREFIX+"_InvScatteringLength_"+suffix;
  nameIntAbsHisto_ = HISTOPREFIX+"_IntAbsorptivity_"+suffix;
  nameIntInvScatLenHisto_ = HISTOPREFIX+"_IntInvScatteringLength_"+suffix;
  ++instanceNumber_;
}


I3MediumService
::I3MediumService(const I3MediumProperties& properties,
                  const string& histoOutFilename)
	: bulkiceAbsorptivity_(1. / BULKICE_ABSORPTION_LENGTH),
		bulkiceInvEffScattLength_(1. / BULKICE_EFF_SCATT_LENGTH),
		hIntAbsLen_(0), hIntEffScattLen_(0),
		hIceLayerAbsorptivity_(0), hIceLayerInvEffScattLen_(0),
		isBulkice_(false), meanScatCosine_(MEAN_SCATT_COSINE){
  TString suffix="";
  suffix+=instanceNumber_;
  nameAbsHisto_ = HISTOPREFIX+"_Absorptivity_"+suffix;
  nameInvScatLenHisto_ = HISTOPREFIX+"_InvScatteringLength_"+suffix;
  nameIntAbsHisto_ = HISTOPREFIX+"_IntAbsorptivity_"+suffix;
  nameIntInvScatLenHisto_ = HISTOPREFIX+"_IntInvScatteringLength_"+suffix;
  ++instanceNumber_;
	try{
		Configure(properties, histoOutFilename);
	}catch(...){
		Release();
	}
}


I3MediumService::~I3MediumService(){
	// Release();
}


void
I3MediumService
::CheckProperties(const I3MediumProperties::Layer& layer) const{
  const I3MediumProperties::Layer::Property& absorption =
    layer.AbsorptionCoefficents();
  const I3MediumProperties::Layer::Property& scattering =
    layer.ScatteringCoefficents();
	if(!check_is_close(layer.UpperEdge() - layer.LowerEdge(), binw_,
                     percent_tolerance(FP_CMP_TOLERANCE)))
		log_fatal("non-constant width of layers");
	if((absorption.Get().size() != nwl_)
     || (scattering.Get().size() != nwl_))
		log_fatal("non-constant wavelength binning");
	if((!check_is_close(absorption.LowestWavelength(), minwl_,
                      percent_tolerance(FP_CMP_TOLERANCE)))
     || (!check_is_close(scattering.LowestWavelength(), minwl_,
                         percent_tolerance(FP_CMP_TOLERANCE)))
     || (!check_is_close(absorption.HighestWavelength(), maxwl_,
                         percent_tolerance(FP_CMP_TOLERANCE)))
     || (!check_is_close(scattering.HighestWavelength(), maxwl_,
                         percent_tolerance(FP_CMP_TOLERANCE))))
		log_fatal("non-constant wavelength interval");
}


void
I3MediumService
::Configure(const I3MediumProperties& properties, const string& histoOutFilename){
	// geometry
	if(!(nlayer_ = properties.Layers().size())) log_fatal("undefined layers");
	minz_ = properties.Layers()[0].LowerEdge();
	binw_ = properties.Layers()[0].UpperEdge() - minz_;
	maxz_ = nlayer_ * binw_ + minz_;
	// wavelength
	if(!(nwl_ = properties.Layers()[0].AbsorptionCoefficents().Get().size()))
		log_fatal("undefined wavelength binning");
	minwl_ = properties.Layers()[0].AbsorptionCoefficents().LowestWavelength();
	maxwl_ = properties.Layers()[0].AbsorptionCoefficents().HighestWavelength();
	wlstep_ = (maxwl_ - minwl_) / nwl_;
	if((RECO_WAVELENGTH < minwl_)
     || (RECO_WAVELENGTH > maxwl_)
     || (minwl_ == maxwl_))
		log_fatal("wavelength interval to small");
  hIceLayerAbsorptivity_ =
      new TH2D(nameAbsHisto_, "absorptivity",
             nlayer_, minz_, maxz_, nwl_, minwl_, maxwl_);
  hIceLayerInvEffScattLen_ =
      new TH2D(nameInvScatLenHisto_, "inverse eff. scatt. length",
             nlayer_, minz_, maxz_, nwl_, minwl_, maxwl_);
  recobinwl_ = hIceLayerAbsorptivity_->GetYaxis()->FindBin(RECO_WAVELENGTH);

	//////////////////////////////////////////////////////////////

  // fill the scatt. and abs. histo, including unfl/ovfl bins
	for(unsigned int i = 1; i <= nlayer_; ++i){
    CheckProperties(properties.Layers()[i-1]);
		for(unsigned int j = 1; j <= nwl_; ++j){
			hIceLayerAbsorptivity_->SetBinContent(i, j,
				properties.Layers()[i - 1].AbsorptionCoefficents().Get()[j - 1]);
			hIceLayerInvEffScattLen_->SetBinContent(i, j,
				properties.Layers()[i - 1].ScatteringCoefficents().Get()[j - 1]);
		}
	}
  for(unsigned int i = 1; i <= nlayer_; ++i){
    hIceLayerInvEffScattLen_->SetBinContent(i, 0,
    	hIceLayerInvEffScattLen_->GetBinContent(i, 1));
    hIceLayerAbsorptivity_->SetBinContent(i, 0,
    	hIceLayerAbsorptivity_->GetBinContent(i, 1));
    hIceLayerInvEffScattLen_->SetBinContent(i, nwl_ + 1,
    	hIceLayerInvEffScattLen_->GetBinContent(i ,nwl_));
    hIceLayerAbsorptivity_->SetBinContent(i, nwl_ + 1,
    	hIceLayerAbsorptivity_->GetBinContent(i, nwl_));
  }
  for(unsigned int j = 1; j <= nwl_; ++j){
    hIceLayerInvEffScattLen_->SetBinContent(0, j,
    	hIceLayerInvEffScattLen_->GetBinContent(1, j));
    hIceLayerAbsorptivity_->SetBinContent(0, j,
    	hIceLayerAbsorptivity_->GetBinContent(1, j));
    hIceLayerInvEffScattLen_->SetBinContent(nlayer_ + 1, j,
    	hIceLayerInvEffScattLen_->GetBinContent(nlayer_, j));
    hIceLayerAbsorptivity_->SetBinContent(nlayer_ + 1, j,
    	hIceLayerAbsorptivity_->GetBinContent(nlayer_, j));
  }

	//////////////////////////////////////////////////////////////

  InitLookupTable();
  DumpLookupTable(histoOutFilename);
  // redefine minz and maxz epsilon different, to have no problem with bounds
  minz_ = minz_ + EPSILON;
  maxz_ = maxz_ - EPSILON;
}


void I3MediumService::DumpLookupTable(const string& histoOutFilename) const{
	if(!histoOutFilename.empty()){
  	TFile* f = new TFile(histoOutFilename.c_str(), "recreate");
  	try{
	    if(!f->IsOpen())
        log_error("cannot open file: %s", histoOutFilename.c_str());
      else{
        hIceLayerAbsorptivity_->Write();
	      hIceLayerInvEffScattLen_->Write();
        hIntAbsLen_->Write();
        hIntEffScattLen_->Write();
        f->Close();
	    }
      delete f;
	  }catch(...){ delete f; }
	}
}


void I3MediumService::InitLookupTable(){
  // save integrated absorptivity and eff. scatt. length
  // (from center of detector) and z in 1D-histo.
  // this is used to introduce ice layering PDF in Amanda/IceCube,
  // with fast computation.

  hIntAbsLen_ =
  	new TH2D(nameIntAbsHisto_,"integrated abs. length",
  		nlayer_, minz_, maxz_, nwl_, minwl_, maxwl_);
  hIntEffScattLen_ =
  	new TH2D(nameIntInvScatLenHisto_,"integrated eff. scatt. length",
  		nlayer_, minz_, maxz_, nwl_, minwl_, maxwl_);

  for(unsigned int j = 1; j <= nwl_; ++j){ // set to 0 integration the depth unfl bin
    hIntAbsLen_->SetBinContent(0, j, 0);
    hIntEffScattLen_->SetBinContent(0, j, 0);
  }

  for(unsigned int j = 0; j <= nwl_ + 1; ++j){ // loop over wavelengths
    for(unsigned int i = 1; i <= nlayer_ + 1; ++i){ // loop over depths
      double cwl = hIntAbsLen_->GetYaxis()->GetBinCenter(j);
      double c = hIntAbsLen_->GetXaxis()->GetBinCenter(i);

      // compute the integral in the bin, considering linear interpolation for the inverse
      // characteristic lengths, and add it (integral of straight line --> 2nd order) 
      double abs1 = Absorptivity(c - binw_, cwl);
      double abs2 = Absorptivity(c, cwl);

      double scat1 = InvEffScattLength(c - binw_, cwl);
      double scat2 = InvEffScattLength(c, cwl);

      double pabs = (abs2 - abs1) / binw_;
      double pscat = (scat2 - scat1) / binw_;
      // so, the equation is: abs1 + pscat * X
      // integral is: abs1 * X + pscat/2 * X^2
      // evaluate at X = binw_
      double iabs = abs1 * binw_ + pabs * 0.5 * binw_ * binw_;
      double iscat = scat1 * binw_ + pscat * 0.5 * binw_ * binw_;

			// k = i - 1, previous bin
      double absvalK = hIntAbsLen_->GetBinContent(i - 1, j);
      double scatvalK = hIntEffScattLen_->GetBinContent(i - 1, j);

      hIntAbsLen_->SetBinContent(i, j, iabs + absvalK);
      hIntEffScattLen_->SetBinContent(i, j, iscat + scatvalK);
    }
  }

  hIntAbsLen_->GetXaxis()->SetTitle("depth");
  hIntAbsLen_->GetYaxis()->SetTitle("wavelength");
  hIntEffScattLen_->GetXaxis()->SetTitle("depth");
  hIntEffScattLen_->GetYaxis()->SetTitle("wavelength");
  hIntAbsLen_->GetZaxis()->SetTitle("[1/m]");
  hIntEffScattLen_->GetZaxis()->SetTitle("[1/m]");
  hIntAbsLen_->SetTitle("integrated absorptivity");
  hIntEffScattLen_->SetTitle("integrated inverse scattering length");
}


void I3MediumService::Release(){
	delete hIceLayerInvEffScattLen_;
	delete hIceLayerAbsorptivity_;
	delete hIntEffScattLen_;
	delete hIntAbsLen_;
	hIceLayerInvEffScattLen_=0;
	hIceLayerAbsorptivity_=0;
	hIntEffScattLen_=0;
	hIntAbsLen_=0;
}


void I3MediumService::CheckWLBounds(double& wavelength) const{
  if(wavelength < MIN_WAVELENGTH_PRICE) wavelength = MIN_WAVELENGTH_PRICE;
  else if(wavelength > MAX_WAVELENGTH_PRICE) wavelength = MAX_WAVELENGTH_PRICE;
}


double I3MediumService::NPhase(double wavelength) const{
  CheckWLBounds(wavelength);

	// here, according to kurt/price article, 300nm<wavelength<600nm  
  double l = wavelength * I3Units::perThousand;
  
  // remove these magic numbers!!!
  return 1.55749-1.57988*l+3.99993*l*l-4.68271*l*l*l+2.09354*l*l*l*l;
}


double I3MediumService::DNPhaseDLambda(double wavelength) const{
  CheckWLBounds(wavelength);
  
	// here, according to kurt/price article, 300nm<wavelength<600nm  
  double l = wavelength * I3Units::perThousand;
  
  // remove these magic numbers!!!
  return -1.57988+2*3.99993*l-3*4.68271*l*l+4*2.09354*l*l*l;
}


double I3MediumService::NGroup(double wavelength) const{
  CheckWLBounds(wavelength);
  
	// here, according to kurt/price article, 300nm<wavelength<600nm  
  // (ng-n)/n = l * dndl /n;
  double dndl = DNPhaseDLambda(wavelength);
  double n = NPhase(wavelength);
  double relng = fabs(wavelength * I3Units::perThousand * dndl / n);
  
  return relng * n + n;
}


void I3MediumService::CheckBounds(double& depth, double& wavelength) const{
  if(depth < minz_) depth = minz_;
  else if(depth > maxz_) depth = maxz_;
  if(wavelength < minwl_) wavelength = minwl_;
  else if(wavelength > maxwl_) wavelength = maxwl_;
}


void
I3MediumService
::GetBin(TAxis* axis, double val, int& bin1, int& bin2, double& delta) const{
  int bin = axis->FindBin(val);
  delta = val - axis->GetBinCenter(bin);

  if(delta < 0){
    bin1 = bin - 1;
    bin2 = bin;
    delta = axis->GetBinWidth(bin) + delta;
  }
  else{
    bin1 = bin;
    bin2 = bin + 1;
  }
}


double
I3MediumService
::Interp2DLin(double& depth, double& wavelength, const TH2D* h) const{
  int depth1, depth2, wl1, wl2;
  double deltaDepth, deltaWl;
  
  CheckBounds(depth, wavelength);

  // bin depth/wl are in the histos
  GetBin(h->GetXaxis(), depth, depth1, depth2, deltaDepth);
  GetBin(h->GetYaxis(), wavelength, wl1, wl2, deltaWl);

	// get the depth slope of inverse length at some wavelength
  double a11 = h->GetBinContent(depth1, wl1);
  double a12 = h->GetBinContent(depth1, wl2);
  double a21 = h->GetBinContent(depth2, wl1);
  double a22 = h->GetBinContent(depth2, wl2);
  // wl: derivative of wl at depth_i
  double dwlDepth1 = (a12 - a11) / wlstep_;
  double dwlDepth2 = (a22 - a21) / wlstep_;
  // value at depth_i, at wavelength
  double v1 = a11 + dwlDepth1 * deltaWl;
  double v2 = a21 + dwlDepth2 * deltaWl;
  double ddepthWl = (v2 - v1) / binw_;
  
  double v = v1 + ddepthWl * deltaDepth;

  return v;
}


double
I3MediumService
::Interp2DIntLin(double& depth, double& wavelength,
                 const TH2D* h, const TH2D* hDeriv) const{
  int depth1, depth2, wl1, wl2;
  double deltaDepth, deltaWl;

  CheckBounds(depth, wavelength);

  // bin depth/wl are in the histos
  GetBin(h->GetXaxis(), depth, depth1, depth2, deltaDepth);
  GetBin(h->GetYaxis(), wavelength, wl1, wl2, deltaWl);

  // get the depth slope of inverse length at some wavelength
  double a11 = hDeriv->GetBinContent(depth1, wl1);
  double a12 = hDeriv->GetBinContent(depth1, wl2);
  double a21 = hDeriv->GetBinContent(depth2, wl1);
  double a22 = hDeriv->GetBinContent(depth2, wl2);
  // wl: derivative of wl at depth_i
  double dwlDepth1 = (a12 - a11) / wlstep_;
  double dwlDepth2 = (a22 - a21) / wlstep_;
  // value at depth_i, at wavelength
  double v1 = a11 + dwlDepth1 * deltaWl;
  double v2 = a21 + dwlDepth2 * deltaWl;
  double ddepthWl = (v2 - v1) / binw_;
  // now, compute the integral up to depth
  double b11 = h->GetBinContent(depth1, wl1);
  double b12 = h->GetBinContent(depth1, wl2);
  // wl: derivative(wl) at depth_1 and value at wavelength and depth1
  double idwlDepth1 = (b12 - b11) / wlstep_;
  double iv1 = b11 + idwlDepth1 * deltaWl;
  double iv = iv1 + (v1 * deltaDepth + ddepthWl * 0.5 * deltaDepth * deltaDepth);

  return iv;
}


double I3MediumService::Absorptivity(double depth, double wavelength) const{
  if(IsBulkiceWithWarning()) return BulkIceAbsorptivity();
  
  return Interp2DLin(depth, wavelength, hIceLayerAbsorptivity_);
}


double I3MediumService::InvEffScattLength(double depth, double wavelength) const{
  if(IsBulkiceWithWarning()) return BulkIceInvEffScattLength();
  
  return Interp2DLin(depth, wavelength, hIceLayerInvEffScattLen_);
}


double
I3MediumService
::AveragedAbsorptivity(double z1, double z2, double wavelength) const{
  if(IsBulkiceWithWarning()) return BulkIceAbsorptivity();
  
  if(z2 < z1) swap(z1, z2);
  double valz1 = Interp2DIntLin(z1, wavelength, hIntAbsLen_, hIceLayerAbsorptivity_);
  double valz2 = Interp2DIntLin(z2, wavelength, hIntAbsLen_, hIceLayerAbsorptivity_);

  if(fabs(z1 - z2) < 0.0001) return Absorptivity(z1, wavelength);
	
	return (valz2 - valz1) / (z2 - z1);
}


double
I3MediumService
::AveragedInvEffScattLength(double z1, double z2, double wavelength) const{
  if(IsBulkiceWithWarning()) return BulkIceInvEffScattLength();
  
  if(z2 < z1) swap(z1, z2);
  double valz1 = Interp2DIntLin(z1, wavelength, hIntEffScattLen_, hIceLayerInvEffScattLen_);
  double valz2 = Interp2DIntLin(z2, wavelength, hIntEffScattLen_, hIceLayerInvEffScattLen_);

  if(fabs(z1 - z2) < 0.0001) return InvEffScattLength(z1, wavelength);

  return (valz2 - valz1) / (z2 - z1);
}

////////////////////////////////////////////////////////////////
// That's Amanda framework stuff
////////////////////////////////////////////////////////////////

// grob description of the ice
const int I3MediumService::N_LAYER = 12;
const char * I3MediumService::DUSTY_LAYER_TYPE[] = {
  "dusty","clear","dusty","clear","dusty","clear","dusty",
  "clear","dusty","clear","dusty","clear"};
const double I3MediumService::DUSTY_LAYER_COO[] = {
  -1000000000,
  1730-2400, 1730-2100, 1730-1960, 1730-1900,
  1730-1850, 1730-1800, 1730-1725, 1730-1650,
  1730-1550, 1730-1500, 1730-1100,
  1000000000
};


int I3MediumService::GetNumberOfLayer(string ltype){
  int ndust = 0;
  int nclear = 0;
  for(int i = 0; i < N_LAYER; ++i){
    if(strcmp(DUSTY_LAYER_TYPE[i], "dusty") == 0) ndust++;
    if(strcmp(DUSTY_LAYER_TYPE[i], "clear") == 0) nclear++;
  }
  transform(ltype.begin(), ltype.end(), ltype.begin(), (int(*)(int))tolower);
  if(ltype.find("all", 0) != string::npos) return nclear + ndust;
  else if(ltype.find("clear", 0) != string::npos) return nclear;
  else if(ltype.find("dust", 0) != string::npos) return ndust;

  return 0;
}


string I3MediumService::GetLayerType(double z){
  string ltype( "N.A." );
  if(N_LAYER <= 1) return ltype;
  for(int i = 0; i < N_LAYER; ++i)
    if((z >= DUSTY_LAYER_COO[i]) && (z < DUSTY_LAYER_COO[i + 1]))
    	return DUSTY_LAYER_TYPE[i];

  return ltype;
}


int I3MediumService::GetLayerNumber(double z){
  if(N_LAYER <= 1)
    log_fatal( "check the ice. Number of layer <= 1\n" );

  for(int i = 0; i < N_LAYER; ++i)
    if((z >= DUSTY_LAYER_COO[i]) && (z < DUSTY_LAYER_COO[i + 1]))
    	return i;

  log_fatal( "check the ice. The entered coo do not enter any of the ice layer\n" );

  return -1; // should never happen
}

////////////////////////////////////////////////////////////////

TH1D*
I3MediumService
::GetAveragedAbsorptionLengthHistogram(const string& name,
                                       int nbin, double from, double min, double max,
                                       double wavelength) const{
  TH1D* h = new TH1D(name.c_str(), "\\int 1/#lambda_{abs}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, AveragedAbsorptionLength(from, c, wavelength));
  }
  
  return h;
}


TH1D*
I3MediumService
::GetAveragedEffScatteringLengthHistogram(const string& name,
                                          int nbin, double from, double min, double max,
                                          double wavelength) const{
  TH1D* h = new TH1D(name.c_str(), "\\int 1/#lambda_{es}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, AveragedEffScattLength(from, c, wavelength));
  }
  
  return h;
}


TH1D*
I3MediumService
::GetAbsorptionLengthHistogram(const string& name,
                               int nbin, double min, double max,
                               double wavelength) const{
  TH1D* h = new TH1D(name.c_str(), "#lambda_{abs}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, AbsorptionLength(c, wavelength));
  }
  
  return h;
}


TH1D*
I3MediumService
::GetEffScatteringLengthHistogram(const string& name,
                                  int nbin, double min, double max,
                                  double wavelength) const{
  TH1D* h = new TH1D(name.c_str(), "#lambda_{es}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, EffScattLength(c, wavelength));
  }
  
  return h;
}
