/**
 * Implementation of I3MediumService class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id:  $
 *
 * @file I3MediumService.cxx
 * @version $Revision:  $
 * @date $Date:  $
 * @author mribordy (original code of I3Medium)
 * @author tschmidt
 */
 
// Class header file

#include "phys-services/I3MediumService.h"

ClassImp(I3MediumService);

// Other header files

#include <algorithm>
#include <ctype.h>
#include "TFile.h"
#include "dataclasses/I3Units.h"

// Implementation

const string I3MediumService::NLAYER_TOKEN = "NLAYER";
const string I3MediumService::NWVL_TOKEN = "NWVL";
const string I3MediumService::LAYER_TOKEN = "LAYER";
const string I3MediumService::ABS_TOKEN = "ABS";
const string I3MediumService::SCAT_TOKEN = "SCAT";


I3MediumService::I3MediumService()
	: bulkiceAbsorptivity_(1. / 98.0), bulkiceInvEffScattLength_(1. / 33.3),
		hIntAbsLen_(0), hIntEffScattLen_(0),
		hIceLayerAbsorptivity_(0), hIceLayerInvEffScattLen_(0),
		isInitialized_(false), meanScatCosine_(0.8){ // remove these magic numbers!!!
}


I3MediumService::~I3MediumService() {
  delete hIntAbsLen_;
  delete hIntEffScattLen_;
  delete hIceLayerAbsorptivity_;
  delete hIceLayerInvEffScattLen_;
}


int I3MediumService::GetNextToken(istream& f, string& token){
  token.clear();
  while(!f.eof()){
    f >> token;
    if(!token.empty() && (token[0] == '#')){
    	getline(f, token);
    	token.clear();
    }
    else break;
  }

  return token.size();
}


bool I3MediumService::Initialize
(const string& propInFilename, const string& histoOutFilename){
  if(isInitialized_) return isInitialized_;
	else if(propInFilename.empty()){
		log_warn("using bulk ice medium");
		return isInitialized_;
	}

  log_info("using ice properties file: %s", propInFilename.c_str());
  ifstream propInFile(propInFilename.c_str());
  if (propInFile.fail())
    log_fatal("cannot open file: %s", propInFilename.c_str());

	//////////////////////////////////////////////////////////////

  string token;
  while(GetNextToken(propInFile, token)){
    if(token == NLAYER_TOKEN){
      propInFile >> nlayer_;
      nbin_ = nlayer_;
      break;
    }
    else log_fatal("problem reading ice properties file, token %s\n",
    	NLAYER_TOKEN.c_str());
  }

  while(GetNextToken(propInFile, token)){
    if(token == NWVL_TOKEN){
      propInFile >> nwl_ >> wlmin_ >> wlstep_;
      break;
    }
    else log_fatal("problem reading ice properties file, token %s\n",
    	NWVL_TOKEN.c_str());
  }
  minwl_ = wlmin_;
  maxwl_ = wlmin_ + wlstep_ * nwl_;

  int currentlayer = 0;
  while(GetNextToken(propInFile, token)){
    if(token == LAYER_TOKEN){
      double z1, z2;
      propInFile >> z1 >> z2;
	    ++currentlayer;
      minz_ = z1;
      binw_ = z2 - z1;
      maxz_ = minz_ + nlayer_ * binw_;
      break;
    }
    else log_fatal("problem reading ice propertyies file, token %s: %f %f",
    	LAYER_TOKEN.c_str(), minz_, binw_);
  }

	//////////////////////////////////////////////////////////////

	delete hIceLayerAbsorptivity_; hIceLayerAbsorptivity_ = 0;
  hIceLayerAbsorptivity_ =
  	new TH2D("hIceLayerAbsorptivity_", "absorptivity", nbin_, minz_, maxz_,
  		nwl_, wlmin_, wlmin_ + nwl_ * wlstep_);
	delete hIceLayerInvEffScattLen_; hIceLayerInvEffScattLen_ = 0;
  hIceLayerInvEffScattLen_ =
  	new TH2D("hIceLayerInvEffScattLen_", "inverse eff. scatt. length", nbin_,
  		minz_, maxz_, nwl_, wlmin_, wlmin_ + nwl_ * wlstep_);
  recobinwl_ = hIceLayerAbsorptivity_->GetYaxis()->FindBin(RECO_WAVELENGTH);

  // fill the scatt. and abs. histo, including unfl/ovfl bins (copy first/last bin content)
  while(GetNextToken(propInFile, token)){
    if(token == LAYER_TOKEN) ++currentlayer;
    else if(token == ABS_TOKEN){
      for(int i = 1; i <= nwl_; ++i){
				double val;
				propInFile >> val;
				hIceLayerAbsorptivity_->SetBinContent(currentlayer, i, val);
				if(currentlayer == 1) hIceLayerAbsorptivity_->SetBinContent(0, i, val);
				else if(currentlayer == nlayer_)
					hIceLayerAbsorptivity_->SetBinContent(nlayer_ + 1, i, val);
      }
    }
    else if(token == SCAT_TOKEN){
      for(int i = 1; i <= nwl_; ++i){
				double val;
				propInFile >> val;
				hIceLayerInvEffScattLen_->SetBinContent(currentlayer, i, val);
				if(currentlayer == 1) hIceLayerInvEffScattLen_->SetBinContent(0, i, val);
				else if(currentlayer == nlayer_)
					hIceLayerInvEffScattLen_->SetBinContent(nlayer_ + 1, i, val);
      }
    }
  }
  for(int i = 1; i <= nlayer_; ++i){
    hIceLayerInvEffScattLen_->SetBinContent(i, 0,
    	hIceLayerInvEffScattLen_->GetBinContent(i, 1));
    hIceLayerAbsorptivity_->SetBinContent(i, 0,
    	hIceLayerAbsorptivity_->GetBinContent(i, 1));
    hIceLayerInvEffScattLen_->SetBinContent(i, nwl_ + 1,
    	hIceLayerInvEffScattLen_->GetBinContent(i ,nwl_));
    hIceLayerAbsorptivity_->SetBinContent(i, nwl_ + 1,
    	hIceLayerAbsorptivity_->GetBinContent(i, nwl_));
  }

	//////////////////////////////////////////////////////////////

  propInFile.close();

  InitLookupTable();
  DumpLookupTable(histoOutFilename);
  // redefine minz and maxz epsilon different, to have no problem with bounds
  minz_ = minz_ + 1e-7;
  maxz_ = maxz_ - 1e-7;

  isInitialized_ = true;
  return isInitialized_;
}

void I3MediumService::InitLookupTable(){
  // save integrated absorptivity and eff. scatt. length
  // (from center of detector) and z in 1D-histo.
  // This is used to introduce ice layering PDF in Amanda/IceCube,
  // with fast computation

	delete hIntAbsLen_; hIntAbsLen_ = 0;
  hIntAbsLen_ =
  	new TH2D("hintabslen","integrated abs. length",
  		nbin_, minz_, maxz_, nwl_, wlmin_, wlmin_ + nwl_ * wlstep_);
	delete hIntEffScattLen_; hIntEffScattLen_ = 0;
  hIntEffScattLen_ =
  	new TH2D("hIntEffScattLen_","integrated eff. scatt. length",
  		nbin_, minz_, maxz_, nwl_, wlmin_, wlmin_ + nwl_ * wlstep_);

  for(int j = 1; j <= nwl_; ++j){ // set to 0 integration the depth unfl bin
    hIntAbsLen_->SetBinContent(0, j, 0);
    hIntEffScattLen_->SetBinContent(0, j, 0);
  }

  for(int j = 0;j <= nwl_ + 1; ++j){ // loop over wavelengths
    for(int i = 1; i <= nbin_ + 1; ++i){ // loop over depths
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


void I3MediumService::DumpLookupTable(const string& histoOutFilename){
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


void I3MediumService::CheckWLBounds(double & wavelength){
  if(wavelength < MIN_WAVELENGTH_PRICE) wavelength = MIN_WAVELENGTH_PRICE;
  else if(wavelength > MAX_WAVELENGTH_PRICE) wavelength = MAX_WAVELENGTH_PRICE;
}


double I3MediumService::NPhase(double wavelength){
  CheckWLBounds(wavelength);

	// here, according to kurt/price article, 300nm<wavelength<600nm  
  double l = wavelength * I3Units::perThousand;
  
  // remove these magic numbers!!!
  return 1.55749-1.57988*l+3.99993*l*l-4.68271*l*l*l+2.09354*l*l*l*l;
}


double I3MediumService::DNPhaseDLambda(double wavelength){
  CheckWLBounds(wavelength);
  
	// here, according to kurt/price article, 300nm<wavelength<600nm  
  double l = wavelength * I3Units::perThousand;
  
  // remove these magic numbers!!!
  return -1.57988+2*3.99993*l-3*4.68271*l*l+4*2.09354*l*l*l;
}


double I3MediumService::NGroup(double wavelength){
  CheckWLBounds(wavelength);
  
	// here, according to kurt/price article, 300nm<wavelength<600nm  
  // (ng-n)/n = l * dndl /n;
  double dndl = DNPhaseDLambda(wavelength);
  double n = NPhase(wavelength);
  double relng = fabs(wavelength * I3Units::perThousand * dndl / n);
  
  return relng * n + n;
}


void I3MediumService::CheckBounds(double& depth, double& wavelength){
  if(depth < minz_) depth = minz_;
  else if(depth > maxz_) depth = maxz_;
  if(wavelength < minwl_) wavelength = minwl_;
  else if(wavelength > maxwl_) wavelength = maxwl_;
}


void I3MediumService::GetBin
(TAxis* axis, double val, int& bin1, int& bin2, double& delta){
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


double I3MediumService::Interp2DLin
(double& depth, double& wavelength, const TH2D* h){
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


double I3MediumService::Interp2DIntLin
(double& depth, double& wavelength, const TH2D* h, const TH2D* hDeriv){
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


double I3MediumService::Absorptivity(double depth, double wavelength){
  if(!IsInitializedWithWarning()) return BulkIceAbsorptivity();
  
  return Interp2DLin(depth, wavelength, hIceLayerAbsorptivity_);
}


double I3MediumService::InvEffScattLength(double depth, double wavelength){
  if(!IsInitializedWithWarning()) return BulkIceInvEffScattLength();
  
  return Interp2DLin(depth, wavelength, hIceLayerInvEffScattLen_);
}


double I3MediumService::AveragedAbsorptivity
(double z1, double z2, double wavelength){
  if(!IsInitializedWithWarning()) return BulkIceAbsorptivity();
  
  double valz1 = Interp2DIntLin(z1, wavelength, hIntAbsLen_, hIceLayerAbsorptivity_);
  double valz2 = Interp2DIntLin(z2, wavelength, hIntAbsLen_, hIceLayerAbsorptivity_);

  if(fabs(z1 - z2) < 0.0001) return Absorptivity(z1, wavelength);
	
	return (valz2 - valz1) / (z2 - z1);
}


double I3MediumService::AveragedInvEffScattLength
(double z1, double z2, double wavelength){
  if(!IsInitializedWithWarning()) return BulkIceInvEffScattLength();
  
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
    if(DUSTY_LAYER_TYPE[i] == "dusty") ndust++;
    if(DUSTY_LAYER_TYPE[i] == "clear") nclear++;
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

TH1D* I3MediumService::GetAveragedAbsorptionLengthHistogram
(const string& name, int nbin, double from,
double min, double max, double wavelength){
  TH1D* h = new TH1D(name.c_str(), "\\int 1/#lambda_{abs}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, AveragedAbsorptionLength(from, c, wavelength));
  }
  
  return h;
}


TH1D* I3MediumService::GetAveragedEffScatteringLengthHistogram
(const string& name, int nbin, double from,
double min, double max, double wavelength){
  TH1D* h = new TH1D(name.c_str(), "\\int 1/#lambda_{es}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, AveragedEffScattLength(from, c, wavelength));
  }
  
  return h;
}


TH1D* I3MediumService::GetAbsorptionLengthHistogram
(const string& name, int nbin, double min, double max, double wavelength){
  TH1D* h = new TH1D(name.c_str(), "#lambda_{abs}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, AbsorptionLength(c, wavelength));
  }
  
  return h;
}


TH1D* I3MediumService::GetEffScatteringLengthHistogram
(const string& name, int nbin, double min, double max, double wavelength){
  TH1D* h = new TH1D(name.c_str(), "#lambda_{es}", nbin, min, max);
  for(int i = 1; i <= nbin; ++i){
    double c = h->GetBinCenter(i);
    h->SetBinContent(i, EffScattLength(c, wavelength));
  }
  
  return h;
}
