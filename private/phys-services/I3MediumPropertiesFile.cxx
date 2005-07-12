/**
 * Implementation of I3MediumPropertiesFile class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id:  $
 *
 * @file I3MediumPropertiesFile.cxx
 * @version $Revision:  $
 * @date $Date:  $
 * @author tschmidt
 */
 
// class header file

#include "phys-services/I3MediumPropertiesFile.h"

// ClassImp(I3MediumPropertiesFile);

// other header files

#include <algorithm>

// implementation

const char I3MediumPropertiesFile::COMMENT_TOKEN = '#';
const string I3MediumPropertiesFile::NLAYER_TOKEN = "NLAYER";
const string I3MediumPropertiesFile::NWVL_TOKEN = "NWVL";
const string I3MediumPropertiesFile::LAYER_TOKEN = "LAYER";
const string I3MediumPropertiesFile::ABS_TOKEN = "ABS";
const string I3MediumPropertiesFile::SCAT_TOKEN = "SCAT";


I3MediumPropertiesFile::I3MediumPropertiesFile(){
	layers_.clear();
}


I3MediumPropertiesFile::I3MediumPropertiesFile(const string& propInFilename){
	Configure(propInFilename);
}


I3MediumPropertiesFile::~I3MediumPropertiesFile(){
}


inline I3MediumPropertiesPtr
I3MediumPropertiesFile::Clone() const{
	I3MediumPropertiesFilePtr clone =
		I3MediumPropertiesFilePtr(new I3MediumPropertiesFile);
	clone->layers_ = layers_;
		
	return clone;
}


void I3MediumPropertiesFile::Configure(const string& propInFilename){
	if(propInFilename.empty()) log_fatal("undefined path/file name");
		
  log_info("using ice properties file: %s", propInFilename.c_str());
  ifstream propInFile(propInFilename.c_str());
  if (propInFile.fail())
    log_fatal("cannot open file: %s", propInFilename.c_str());

	//////////////////////////////////////////////////////////////

  string token;
  STLVectorStoragePolicy<Layer> layers;
  double minwl, maxwl, wlstep;
  
  int nwl = -1;
  int nlayers = -1;
  
  // reading header NLAYER
  while(GetNextToken(propInFile, token)){
    if(token == NLAYER_TOKEN){
      propInFile >> nlayers;
      if(propInFile.fail() || (nlayers < 0))
      	log_fatal("undefined %s", NLAYER_TOKEN.c_str());
	    if(nlayers) layers.resize(nlayers);
      break;
    } // if(token == NLAYER_TOKEN)
    else log_fatal("cannot read ice properties file, token %s",
    	NLAYER_TOKEN.c_str());
  } // while(GetNextToken(propInFile, token))
  if(nlayers < 0)
  	log_fatal("cannot read ice properties file, token %s",
    	NLAYER_TOKEN.c_str());

	//////////////////////////////////////////////////////////////

	if(layers.size()){
		
  	// reading header NWL
	  while(GetNextToken(propInFile, token)){
  	  if(token == NWVL_TOKEN){
    	  propInFile >> nwl >> minwl >> wlstep;
      	if(propInFile.fail() || (nwl < 0) || (minwl <= 0) || (wlstep < 0)
      		|| (!wlstep && nwl))
	      	log_fatal("undefined %s", NWVL_TOKEN.c_str());
  	    maxwl = minwl + wlstep * nwl;
    	  break;
	    } // if(token == NWVL_TOKEN)
  	  else log_fatal("cannot read ice properties file, token %s",
    		NWVL_TOKEN.c_str());
	  } // while(GetNextToken(propInFile, token))
	  if(nwl < 0)
	  	log_fatal("cannot read ice properties file, token %s",
	    	NWVL_TOKEN.c_str());

		//////////////////////////////////////////////////////////////

		// reading layers
  	unsigned int currentLayer = 0;

	  while(GetNextToken(propInFile, token)){
  	  if(token == LAYER_TOKEN){
  	  	if(++currentLayer > layers.size())
  	  		log_fatal("to much layers defined");
    	  double le, ue;
	      propInFile >> le >> ue;
	      if(propInFile.fail() || (le >= ue))
	      	log_fatal("undefined %s", LAYER_TOKEN.c_str());
	    	layers[currentLayer - 1].SetLowerEdge(le);
	    	layers[currentLayer - 1].SetUpperEdge(ue);
	    	layers[currentLayer - 1].AbsorptionCoefficents().SetLowestWavelength(minwl);
	    	layers[currentLayer - 1].AbsorptionCoefficents().SetHighestWavelength(maxwl);
	    	layers[currentLayer - 1].ScatteringCoefficents().SetLowestWavelength(minwl);
	    	layers[currentLayer - 1].ScatteringCoefficents().SetHighestWavelength(maxwl);
	    } // if(token == LAYER_TOKEN)
	    else if(token == ABS_TOKEN){
      	if(!currentLayer)
      		log_fatal("cannot read ice properties file, token %s",
      			LAYER_TOKEN.c_str());
      	if(layers[currentLayer - 1].AbsorptionCoefficents().Get().size())
      		log_fatal("duplicated %s", ABS_TOKEN.c_str());
	      for(int i = 1; i <= nwl; ++i){
					double val;
					propInFile >> val;
					if(propInFile.fail()) log_fatal("undefined %s", ABS_TOKEN.c_str());
					layers[currentLayer - 1].AbsorptionCoefficents().Get().push_back(val);
	      } // for(int i = 1; i <= nwl; ++i)
	    } // else if(token == ABS_TOKEN)
	    else if(token == SCAT_TOKEN){
      	if(!currentLayer)
      		log_fatal("cannot read ice properties file, token %s",
      			LAYER_TOKEN.c_str());
      	if(layers[currentLayer - 1].ScatteringCoefficents().Get().size())
      		log_fatal("duplicated %s", SCAT_TOKEN.c_str());
	      for(int i = 1; i <= nwl; ++i){
					double val;
					propInFile >> val;
					if(propInFile.fail()) log_fatal("undefined %s", SCAT_TOKEN.c_str());
					layers[currentLayer - 1].ScatteringCoefficents().Get().push_back(val);				
	      } // for(int i = 1; i <= nwl; ++i)
	    } // else if(token == SCAT_TOKEN)
	  } // while(GetNextToken(propInFile, token))

		if(currentLayer != layers.size()) log_fatal("to less layers defined");
		
		sort(layers.begin(), layers.end(), LayerLower());
		if(!Contiguous(layers)) log_fatal("discontiguous layers");
	} // if(layers.size())

	//////////////////////////////////////////////////////////////

  propInFile.close();
	
	layers_ = layers;
}


bool I3MediumPropertiesFile::Contiguous(STLVectorStoragePolicy<Layer> layers){
	for(unsigned int i = 1; i < layers.size(); ++i){
		if(layers[i - 1].UpperEdge() != layers[i].LowerEdge()) return false;
	} // for(unsigned int i = 0; i < layers.size(); ++i)
	return true;
}


unsigned int I3MediumPropertiesFile::GetNextToken(istream& f, string& token){
  token.clear();
  while(!f.eof()){
    f >> token;
    if(!token.empty() && (token[0] == COMMENT_TOKEN)){
    	getline(f, token);
    	token.clear();
    } // if(!token.empty() && (token[0] == COMMENT_TOKEN))
    else break;
  } // while(!f.eof())

  return token.size();
}
