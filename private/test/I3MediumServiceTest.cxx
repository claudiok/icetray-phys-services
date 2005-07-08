/**
 * copyright  (C) 2005
 * the icecube collaboration
 * $Id:  $
 * 
 * @file I3MediumService.cxx
 * @version $Revision:  $
 * @date $Date:  $
 * @author tschmidt
*/

#include <string>
#include "I3Test.h"
#include "phys-services/I3MediumService.h"

#define PERCENTAGE 0.000001
#define ICE_PROPERTIES "/phys-services/resources/iceProperties.dat"

TEST_GROUP(I3MediumServiceTest);

TEST(I3MediumService380nmWithoutInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->NPhase(380.), 1.321429e+00, abs(PERCENTAGE * ptr->NPhase(380.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), -1.089763e-01, abs(PERCENTAGE * ptr->DNPhaseDLambda(380.)));
  ENSURE_DISTANCE(ptr->NGroup(380.), 1.362840e+00, abs(PERCENTAGE * ptr->NGroup(380.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), 4.545945e+00, abs(PERCENTAGE * ptr->InvC_ICE(380.)));
  ENSURE_DISTANCE(ptr->C_ICE(380.), 2.199763e-01, abs(PERCENTAGE * ptr->C_ICE(380.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(380.) * ptr->C_ICE(380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->NPhase(380.), ptr->NPhase(), abs(PERCENTAGE * ptr->NPhase()));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), ptr->DNPhaseDLambda(), abs(PERCENTAGE * ptr->DNPhaseDLambda()));
  ENSURE_DISTANCE(ptr->NGroup(380.), ptr->NGroup(), abs(PERCENTAGE * ptr->NGroup()));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), ptr->InvC_ICE(), abs(PERCENTAGE * ptr->InvC_ICE()));
  ENSURE_DISTANCE(ptr->C_ICE(380.), ptr->C_ICE(), abs(PERCENTAGE * ptr->C_ICE()));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 380.), 1.057143e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.8, 380.), 9.459456e-01, abs(PERCENTAGE * ptr->CosThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->ThetaC(0.8, 380.), 3.302983e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 380.), 3.243252e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.8, 380.), 3.083325e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 380.), 3.428582e-01, abs(PERCENTAGE * ptr->TgThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.8, 380.), 2.916658e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 380.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(0.8, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.8, 380.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.8, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.8, 380.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.8, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 380.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(0.8, 380)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 380.) * ptr->CosThetaC(0.8, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 380.) * ptr->InvSinThetaC(0.8, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 380.) * ptr->CtgThetaC(0.8, 380), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 380.) * ptr->AbsorptionLength(0.8, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 380.) * ptr->InvEffScattLength(0.8, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 380.) * ptr->SinThetaC(0.8, 380.) + ptr->CosThetaC(0.8, 380.) * ptr->CosThetaC(0.8, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 380.), 1.189286e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.9, 380.), 8.408406e-01, abs(PERCENTAGE * ptr->CosThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->ThetaC(0.9, 380.), 5.719620e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 380.), 5.412828e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.9, 380.), 1.847463e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 380.), 6.437402e-01, abs(PERCENTAGE * ptr->TgThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.9, 380.), 1.553422e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 380.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(0.9, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.9, 380.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.9, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.9, 380.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.9, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 380.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(0.9, 380)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 380.) * ptr->CosThetaC(0.9, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 380.) * ptr->InvSinThetaC(0.9, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 380.) * ptr->CtgThetaC(0.9, 380), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 380.) * ptr->AbsorptionLength(0.9, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 380.) * ptr->InvEffScattLength(0.9, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 380.) * ptr->SinThetaC(0.9, 380.) + ptr->CosThetaC(0.9, 380.) * ptr->CosThetaC(0.9, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 380.), 1.321429e+00, abs(PERCENTAGE * ptr->InvCosThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->CosThetaC(1., 380.), 7.567565e-01, abs(PERCENTAGE * ptr->CosThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->ThetaC(1., 380.), 7.124593e-01, abs(PERCENTAGE * ptr->ThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->SinThetaC(1., 380.), 6.536968e-01, abs(PERCENTAGE * ptr->ThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(1., 380.), 1.529761e+00, abs(PERCENTAGE * ptr->InvSinThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->TgThetaC(1., 380.), 8.638140e-01, abs(PERCENTAGE * ptr->TgThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->CtgThetaC(1., 380.), 1.157657e+00, abs(PERCENTAGE * ptr->CtgThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->Absorptivity(1., 380.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(1., 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(1., 380.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(1., 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(1., 380.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(1., 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(1., 380.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(1., 380)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 380.) * ptr->CosThetaC(1., 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(1., 380.) * ptr->InvSinThetaC(1., 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(1., 380.) * ptr->CtgThetaC(1., 380), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(1., 380.) * ptr->AbsorptionLength(1., 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(1., 380.) * ptr->InvEffScattLength(1., 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(1., 380.) * ptr->SinThetaC(1., 380.) + ptr->CosThetaC(1., 380.) * ptr->CosThetaC(1., 380.), 1., PERCENTAGE);
}
TEST(I3MediumService460nmWithoutInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->NPhase(460.), 1.315071e+00, abs(PERCENTAGE * ptr->NPhase(460.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(460.), -5.742147e-02, abs(PERCENTAGE * ptr->DNPhaseDLambda(460.)));
  ENSURE_DISTANCE(ptr->NGroup(460.), 1.341485e+00, abs(PERCENTAGE * ptr->NGroup(460.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(460.), 4.474713e+00, abs(PERCENTAGE * ptr->InvC_ICE(460.)));
  ENSURE_DISTANCE(ptr->C_ICE(460.), 2.234780e-01, abs(PERCENTAGE * ptr->C_ICE(460.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(460.) * ptr->C_ICE(460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 460.), 1.052057e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.8, 460.), 9.505187e-01, abs(PERCENTAGE * ptr->CosThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->ThetaC(0.8, 460.), 3.158951e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 460.), 3.106674e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.8, 460.), 3.218877e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 460.), 3.268398e-01, abs(PERCENTAGE * ptr->TgThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.8, 460.), 3.059602e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 460.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(0.8, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.8, 460.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.8, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.8, 460.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.8, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 460.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(0.8, 460)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 460.) * ptr->CosThetaC(0.8, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 460.) * ptr->InvSinThetaC(0.8, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 460.) * ptr->CtgThetaC(0.8, 460), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 460.) * ptr->AbsorptionLength(0.8, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 460.) * ptr->InvEffScattLength(0.8, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 460.) * ptr->SinThetaC(0.8, 460.) + ptr->CosThetaC(0.8, 460.) * ptr->CosThetaC(0.8, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 460.), 1.183564e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.9, 460.), 8.449055e-01, abs(PERCENTAGE * ptr->CosThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->ThetaC(0.9, 460.), 5.644078e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 460.), 5.349156e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.9, 460.), 1.869454e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 460.), 6.331070e-01, abs(PERCENTAGE * ptr->TgThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.9, 460.), 1.579512e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 460.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(0.9, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.9, 460.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.9, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.9, 460.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.9, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 460.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(0.9, 460)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 460.) * ptr->CosThetaC(0.9, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 460.) * ptr->InvSinThetaC(0.9, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 460.) * ptr->CtgThetaC(0.9, 460), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 460.) * ptr->AbsorptionLength(0.9, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 460.) * ptr->InvEffScattLength(0.9, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 460.) * ptr->SinThetaC(0.9, 460.) + ptr->CosThetaC(0.9, 460.) * ptr->CosThetaC(0.9, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 460.), 1.315071e+00, abs(PERCENTAGE * ptr->InvCosThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->CosThetaC(1., 460.), 7.604150e-01, abs(PERCENTAGE * ptr->CosThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->ThetaC(1., 460.), 7.068445e-01, abs(PERCENTAGE * ptr->ThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->SinThetaC(1., 460.), 6.494375e-01, abs(PERCENTAGE * ptr->ThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(1., 460.), 1.539794e+00, abs(PERCENTAGE * ptr->InvSinThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->TgThetaC(1., 460.), 8.540568e-01, abs(PERCENTAGE * ptr->TgThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->CtgThetaC(1., 460.), 1.170882e+00, abs(PERCENTAGE * ptr->CtgThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->Absorptivity(1., 460.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(1., 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(1., 460.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(1., 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(1., 460.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(1., 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(1., 460.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(1., 460)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 460.) * ptr->CosThetaC(1., 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(1., 460.) * ptr->InvSinThetaC(1., 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(1., 460.) * ptr->CtgThetaC(1., 460), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(1., 460.) * ptr->AbsorptionLength(1., 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(1., 460.) * ptr->InvEffScattLength(1., 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(1., 460.) * ptr->SinThetaC(1., 460.) + ptr->CosThetaC(1., 460.) * ptr->CosThetaC(1., 460.), 1., PERCENTAGE);
}
TEST(I3MediumService540nmWithoutInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->NPhase(540.), 1.311391e+00, abs(PERCENTAGE * ptr->NPhase(540.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(540.), -3.776158e-02, abs(PERCENTAGE * ptr->DNPhaseDLambda(540.)));
  ENSURE_DISTANCE(ptr->NGroup(540.), 1.331782e+00, abs(PERCENTAGE * ptr->NGroup(540.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(540.), 4.442347e+00, abs(PERCENTAGE * ptr->InvC_ICE(540.)));
  ENSURE_DISTANCE(ptr->C_ICE(540.), 2.251062e-01, abs(PERCENTAGE * ptr->C_ICE(540.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(540.) * ptr->C_ICE(540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 540.), 1.049113e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.8, 540.), 9.531863e-01, abs(PERCENTAGE * ptr->CosThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->ThetaC(0.8, 540.), 3.071923e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 540.), 3.023835e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.8, 540.), 3.307058e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 540.), 3.172345e-01, abs(PERCENTAGE * ptr->TgThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.8, 540.), 3.152243e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 540.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(0.8, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.8, 540.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.8, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.8, 540.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.8, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 540.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(0.8, 540)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 540.) * ptr->CosThetaC(0.8, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 540.) * ptr->InvSinThetaC(0.8, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 540.) * ptr->CtgThetaC(0.8, 540), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 540.) * ptr->AbsorptionLength(0.8, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 540.) * ptr->InvEffScattLength(0.8, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 540.) * ptr->SinThetaC(0.8, 540.) + ptr->CosThetaC(0.8, 540.) * ptr->CosThetaC(0.8, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 540.), 1.180252e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.9, 540.), 8.472767e-01, abs(PERCENTAGE * ptr->CosThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->ThetaC(0.9, 540.), 5.599593e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 540.), 5.311517e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.9, 540.), 1.882701e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 540.), 6.268928e-01, abs(PERCENTAGE * ptr->TgThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.9, 540.), 1.595169e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 540.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(0.9, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.9, 540.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.9, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.9, 540.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.9, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 540.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(0.9, 540)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 540.) * ptr->CosThetaC(0.9, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 540.) * ptr->InvSinThetaC(0.9, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 540.) * ptr->CtgThetaC(0.9, 540), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 540.) * ptr->AbsorptionLength(0.9, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 540.) * ptr->InvEffScattLength(0.9, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 540.) * ptr->SinThetaC(0.9, 540.) + ptr->CosThetaC(0.9, 540.) * ptr->CosThetaC(0.9, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 540.), 1.311391e+00, abs(PERCENTAGE * ptr->InvCosThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->CosThetaC(1., 540.), 7.625491e-01, abs(PERCENTAGE * ptr->CosThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->ThetaC(1., 540.), 7.035521e-01, abs(PERCENTAGE * ptr->ThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->SinThetaC(1., 540.), 6.469304e-01, abs(PERCENTAGE * ptr->ThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(1., 540.), 1.545761e+00, abs(PERCENTAGE * ptr->InvSinThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->TgThetaC(1., 540.), 8.483787e-01, abs(PERCENTAGE * ptr->TgThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->CtgThetaC(1., 540.), 1.178719e+00, abs(PERCENTAGE * ptr->CtgThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->Absorptivity(1., 540.), 1.020408e-02, abs(PERCENTAGE * ptr->Absorptivity(1., 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(1., 540.), 3.003003e-02, abs(PERCENTAGE * ptr->InvEffScattLength(1., 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(1., 540.), 9.800000e+01, abs(PERCENTAGE * ptr->AbsorptionLength(1., 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(1., 540.), 3.330000e+01, abs(PERCENTAGE * ptr->EffScattLength(1., 540)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 540.) * ptr->CosThetaC(1., 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(1., 540.) * ptr->InvSinThetaC(1., 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(1., 540.) * ptr->CtgThetaC(1., 540), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(1., 540.) * ptr->AbsorptionLength(1., 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(1., 540.) * ptr->InvEffScattLength(1., 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(1., 540.) * ptr->SinThetaC(1., 540.) + ptr->CosThetaC(1., 540.) * ptr->CosThetaC(1., 540.), 1., PERCENTAGE);
}
TEST(I3MediumServiceWithoutInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity(), 1.020408e-02, abs(PERCENTAGE * ptr->BulkIceAbsorptivity()));
  ENSURE_DISTANCE(ptr->BulkIceInvEffScattLength(), 3.003003e-02, abs(PERCENTAGE * ptr->BulkIceInvEffScattLength()));
  ENSURE_DISTANCE(ptr->BulkIceAbsorptionLength(), 9.800000e+01, abs(PERCENTAGE * ptr->BulkIceAbsorptionLength()));
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength(), 3.330000e+01, abs(PERCENTAGE * ptr->BulkIceEffScattLength()));
  ENSURE_DISTANCE(ptr->MeanScatteringCosine(), 8.000000e-01, abs(PERCENTAGE * ptr->MeanScatteringCosine()));

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity() * ptr->BulkIceAbsorptionLength(), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength() * ptr->BulkIceInvEffScattLength(), 1., PERCENTAGE);
}
TEST(I3MediumService380nmWithInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);
  std::string properties(getenv("I3_WORK"));
  ptr->Initialize(properties + ICE_PROPERTIES);

  ENSURE_DISTANCE(ptr->NPhase(380.), 1.321429e+00, abs(PERCENTAGE * ptr->NPhase(380.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), -1.089763e-01, abs(PERCENTAGE * ptr->DNPhaseDLambda(380.)));
  ENSURE_DISTANCE(ptr->NGroup(380.), 1.362840e+00, abs(PERCENTAGE * ptr->NGroup(380.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), 4.545945e+00, abs(PERCENTAGE * ptr->InvC_ICE(380.)));
  ENSURE_DISTANCE(ptr->C_ICE(380.), 2.199763e-01, abs(PERCENTAGE * ptr->C_ICE(380.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(380.) * ptr->C_ICE(380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->NPhase(380.), ptr->NPhase(), abs(PERCENTAGE * ptr->NPhase()));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), ptr->DNPhaseDLambda(), abs(PERCENTAGE * ptr->DNPhaseDLambda()));
  ENSURE_DISTANCE(ptr->NGroup(380.), ptr->NGroup(), abs(PERCENTAGE * ptr->NGroup()));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), ptr->InvC_ICE(), abs(PERCENTAGE * ptr->InvC_ICE()));
  ENSURE_DISTANCE(ptr->C_ICE(380.), ptr->C_ICE(), abs(PERCENTAGE * ptr->C_ICE()));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 380.), 1.057143e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.8, 380.), 9.459456e-01, abs(PERCENTAGE * ptr->CosThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->ThetaC(0.8, 380.), 3.302983e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 380.), 3.243252e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.8, 380.), 3.083325e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 380.), 3.428582e-01, abs(PERCENTAGE * ptr->TgThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.8, 380.), 2.916658e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.8, 380)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 380.), 1.122500e-02, abs(PERCENTAGE * ptr->Absorptivity(0.8, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.8, 380.), 6.246200e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.8, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.8, 380.), 8.908686e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.8, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 380.), 1.600973e+01, abs(PERCENTAGE * ptr->EffScattLength(0.8, 380)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 380.) * ptr->CosThetaC(0.8, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 380.) * ptr->InvSinThetaC(0.8, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 380.) * ptr->CtgThetaC(0.8, 380), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 380.) * ptr->AbsorptionLength(0.8, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 380.) * ptr->InvEffScattLength(0.8, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 380.) * ptr->SinThetaC(0.8, 380.) + ptr->CosThetaC(0.8, 380.) * ptr->CosThetaC(0.8, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 380.), 1.189286e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.9, 380.), 8.408406e-01, abs(PERCENTAGE * ptr->CosThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->ThetaC(0.9, 380.), 5.719620e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 380.), 5.412828e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.9, 380.), 1.847463e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 380.), 6.437402e-01, abs(PERCENTAGE * ptr->TgThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.9, 380.), 1.553422e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.9, 380)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 380.), 1.121250e-02, abs(PERCENTAGE * ptr->Absorptivity(0.9, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.9, 380.), 6.235100e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.9, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.9, 380.), 8.918618e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.9, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 380.), 1.603824e+01, abs(PERCENTAGE * ptr->EffScattLength(0.9, 380)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 380.) * ptr->CosThetaC(0.9, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 380.) * ptr->InvSinThetaC(0.9, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 380.) * ptr->CtgThetaC(0.9, 380), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 380.) * ptr->AbsorptionLength(0.9, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 380.) * ptr->InvEffScattLength(0.9, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 380.) * ptr->SinThetaC(0.9, 380.) + ptr->CosThetaC(0.9, 380.) * ptr->CosThetaC(0.9, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 380.), 1.321429e+00, abs(PERCENTAGE * ptr->InvCosThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->CosThetaC(1., 380.), 7.567565e-01, abs(PERCENTAGE * ptr->CosThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->ThetaC(1., 380.), 7.124593e-01, abs(PERCENTAGE * ptr->ThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->SinThetaC(1., 380.), 6.536968e-01, abs(PERCENTAGE * ptr->ThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(1., 380.), 1.529761e+00, abs(PERCENTAGE * ptr->InvSinThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->TgThetaC(1., 380.), 8.638140e-01, abs(PERCENTAGE * ptr->TgThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->CtgThetaC(1., 380.), 1.157657e+00, abs(PERCENTAGE * ptr->CtgThetaC(1., 380)));
  ENSURE_DISTANCE(ptr->Absorptivity(1., 380.), 1.120000e-02, abs(PERCENTAGE * ptr->Absorptivity(1., 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(1., 380.), 6.224000e-02, abs(PERCENTAGE * ptr->InvEffScattLength(1., 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(1., 380.), 8.928571e+01, abs(PERCENTAGE * ptr->AbsorptionLength(1., 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(1., 380.), 1.606684e+01, abs(PERCENTAGE * ptr->EffScattLength(1., 380)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 380.) * ptr->CosThetaC(1., 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(1., 380.) * ptr->InvSinThetaC(1., 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(1., 380.) * ptr->CtgThetaC(1., 380), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(1., 380.) * ptr->AbsorptionLength(1., 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(1., 380.) * ptr->InvEffScattLength(1., 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(1., 380.) * ptr->SinThetaC(1., 380.) + ptr->CosThetaC(1., 380.) * ptr->CosThetaC(1., 380.), 1., PERCENTAGE);
}
TEST(I3MediumService460nmWithInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);
  std::string properties(getenv("I3_WORK"));
  ptr->Initialize(properties + ICE_PROPERTIES);

  ENSURE_DISTANCE(ptr->NPhase(460.), 1.315071e+00, abs(PERCENTAGE * ptr->NPhase(460.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(460.), -5.742147e-02, abs(PERCENTAGE * ptr->DNPhaseDLambda(460.)));
  ENSURE_DISTANCE(ptr->NGroup(460.), 1.341485e+00, abs(PERCENTAGE * ptr->NGroup(460.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(460.), 4.474713e+00, abs(PERCENTAGE * ptr->InvC_ICE(460.)));
  ENSURE_DISTANCE(ptr->C_ICE(460.), 2.234780e-01, abs(PERCENTAGE * ptr->C_ICE(460.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(460.) * ptr->C_ICE(460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 460.), 1.052057e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.8, 460.), 9.505187e-01, abs(PERCENTAGE * ptr->CosThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->ThetaC(0.8, 460.), 3.158951e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 460.), 3.106674e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.8, 460.), 3.218877e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 460.), 3.268398e-01, abs(PERCENTAGE * ptr->TgThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.8, 460.), 3.059602e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.8, 460)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 460.), 1.307000e-02, abs(PERCENTAGE * ptr->Absorptivity(0.8, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.8, 460.), 5.259800e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.8, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.8, 460.), 7.651109e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.8, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 460.), 1.901213e+01, abs(PERCENTAGE * ptr->EffScattLength(0.8, 460)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 460.) * ptr->CosThetaC(0.8, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 460.) * ptr->InvSinThetaC(0.8, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 460.) * ptr->CtgThetaC(0.8, 460), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 460.) * ptr->AbsorptionLength(0.8, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 460.) * ptr->InvEffScattLength(0.8, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 460.) * ptr->SinThetaC(0.8, 460.) + ptr->CosThetaC(0.8, 460.) * ptr->CosThetaC(0.8, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 460.), 1.183564e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.9, 460.), 8.449055e-01, abs(PERCENTAGE * ptr->CosThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->ThetaC(0.9, 460.), 5.644078e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 460.), 5.349156e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.9, 460.), 1.869454e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 460.), 6.331070e-01, abs(PERCENTAGE * ptr->TgThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.9, 460.), 1.579512e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.9, 460)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 460.), 1.306000e-02, abs(PERCENTAGE * ptr->Absorptivity(0.9, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.9, 460.), 5.250400e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.9, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.9, 460.), 7.656968e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.9, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 460.), 1.904617e+01, abs(PERCENTAGE * ptr->EffScattLength(0.9, 460)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 460.) * ptr->CosThetaC(0.9, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 460.) * ptr->InvSinThetaC(0.9, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 460.) * ptr->CtgThetaC(0.9, 460), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 460.) * ptr->AbsorptionLength(0.9, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 460.) * ptr->InvEffScattLength(0.9, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 460.) * ptr->SinThetaC(0.9, 460.) + ptr->CosThetaC(0.9, 460.) * ptr->CosThetaC(0.9, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 460.), 1.315071e+00, abs(PERCENTAGE * ptr->InvCosThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->CosThetaC(1., 460.), 7.604150e-01, abs(PERCENTAGE * ptr->CosThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->ThetaC(1., 460.), 7.068445e-01, abs(PERCENTAGE * ptr->ThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->SinThetaC(1., 460.), 6.494375e-01, abs(PERCENTAGE * ptr->ThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(1., 460.), 1.539794e+00, abs(PERCENTAGE * ptr->InvSinThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->TgThetaC(1., 460.), 8.540568e-01, abs(PERCENTAGE * ptr->TgThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->CtgThetaC(1., 460.), 1.170882e+00, abs(PERCENTAGE * ptr->CtgThetaC(1., 460)));
  ENSURE_DISTANCE(ptr->Absorptivity(1., 460.), 1.305000e-02, abs(PERCENTAGE * ptr->Absorptivity(1., 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(1., 460.), 5.241000e-02, abs(PERCENTAGE * ptr->InvEffScattLength(1., 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(1., 460.), 7.662835e+01, abs(PERCENTAGE * ptr->AbsorptionLength(1., 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(1., 460.), 1.908033e+01, abs(PERCENTAGE * ptr->EffScattLength(1., 460)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 460.) * ptr->CosThetaC(1., 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(1., 460.) * ptr->InvSinThetaC(1., 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(1., 460.) * ptr->CtgThetaC(1., 460), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(1., 460.) * ptr->AbsorptionLength(1., 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(1., 460.) * ptr->InvEffScattLength(1., 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(1., 460.) * ptr->SinThetaC(1., 460.) + ptr->CosThetaC(1., 460.) * ptr->CosThetaC(1., 460.), 1., PERCENTAGE);
}
TEST(I3MediumService540nmWithInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);
  std::string properties(getenv("I3_WORK"));
  ptr->Initialize(properties + ICE_PROPERTIES);

  ENSURE_DISTANCE(ptr->NPhase(540.), 1.311391e+00, abs(PERCENTAGE * ptr->NPhase(540.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(540.), -3.776158e-02, abs(PERCENTAGE * ptr->DNPhaseDLambda(540.)));
  ENSURE_DISTANCE(ptr->NGroup(540.), 1.331782e+00, abs(PERCENTAGE * ptr->NGroup(540.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(540.), 4.442347e+00, abs(PERCENTAGE * ptr->InvC_ICE(540.)));
  ENSURE_DISTANCE(ptr->C_ICE(540.), 2.251062e-01, abs(PERCENTAGE * ptr->C_ICE(540.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(540.) * ptr->C_ICE(540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 540.), 1.049113e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.8, 540.), 9.531863e-01, abs(PERCENTAGE * ptr->CosThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->ThetaC(0.8, 540.), 3.071923e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 540.), 3.023835e-01, abs(PERCENTAGE * ptr->ThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.8, 540.), 3.307058e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 540.), 3.172345e-01, abs(PERCENTAGE * ptr->TgThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.8, 540.), 3.152243e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.8, 540)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 540.), 4.202800e-02, abs(PERCENTAGE * ptr->Absorptivity(0.8, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.8, 540.), 4.555200e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.8, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.8, 540.), 2.379366e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.8, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 540.), 2.195293e+01, abs(PERCENTAGE * ptr->EffScattLength(0.8, 540)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.8, 540.) * ptr->CosThetaC(0.8, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 540.) * ptr->InvSinThetaC(0.8, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.8, 540.) * ptr->CtgThetaC(0.8, 540), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.8, 540.) * ptr->AbsorptionLength(0.8, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.8, 540.) * ptr->InvEffScattLength(0.8, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.8, 540.) * ptr->SinThetaC(0.8, 540.) + ptr->CosThetaC(0.8, 540.) * ptr->CosThetaC(0.8, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 540.), 1.180252e+00, abs(PERCENTAGE * ptr->InvCosThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->CosThetaC(0.9, 540.), 8.472767e-01, abs(PERCENTAGE * ptr->CosThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->ThetaC(0.9, 540.), 5.599593e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 540.), 5.311517e-01, abs(PERCENTAGE * ptr->ThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(0.9, 540.), 1.882701e+00, abs(PERCENTAGE * ptr->InvSinThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 540.), 6.268928e-01, abs(PERCENTAGE * ptr->TgThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->CtgThetaC(0.9, 540.), 1.595169e+00, abs(PERCENTAGE * ptr->CtgThetaC(0.9, 540)));
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 540.), 4.201900e-02, abs(PERCENTAGE * ptr->Absorptivity(0.9, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0.9, 540.), 4.547100e-02, abs(PERCENTAGE * ptr->InvEffScattLength(0.9, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0.9, 540.), 2.379876e+01, abs(PERCENTAGE * ptr->AbsorptionLength(0.9, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 540.), 2.199204e+01, abs(PERCENTAGE * ptr->EffScattLength(0.9, 540)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(0.9, 540.) * ptr->CosThetaC(0.9, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 540.) * ptr->InvSinThetaC(0.9, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(0.9, 540.) * ptr->CtgThetaC(0.9, 540), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(0.9, 540.) * ptr->AbsorptionLength(0.9, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0.9, 540.) * ptr->InvEffScattLength(0.9, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(0.9, 540.) * ptr->SinThetaC(0.9, 540.) + ptr->CosThetaC(0.9, 540.) * ptr->CosThetaC(0.9, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 540.), 1.311391e+00, abs(PERCENTAGE * ptr->InvCosThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->CosThetaC(1., 540.), 7.625491e-01, abs(PERCENTAGE * ptr->CosThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->ThetaC(1., 540.), 7.035521e-01, abs(PERCENTAGE * ptr->ThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->SinThetaC(1., 540.), 6.469304e-01, abs(PERCENTAGE * ptr->ThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->InvSinThetaC(1., 540.), 1.545761e+00, abs(PERCENTAGE * ptr->InvSinThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->TgThetaC(1., 540.), 8.483787e-01, abs(PERCENTAGE * ptr->TgThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->CtgThetaC(1., 540.), 1.178719e+00, abs(PERCENTAGE * ptr->CtgThetaC(1., 540)));
  ENSURE_DISTANCE(ptr->Absorptivity(1., 540.), 4.201000e-02, abs(PERCENTAGE * ptr->Absorptivity(1., 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(1., 540.), 4.539000e-02, abs(PERCENTAGE * ptr->InvEffScattLength(1., 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(1., 540.), 2.380386e+01, abs(PERCENTAGE * ptr->AbsorptionLength(1., 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(1., 540.), 2.203128e+01, abs(PERCENTAGE * ptr->EffScattLength(1., 540)));

  ENSURE_DISTANCE(ptr->InvCosThetaC(1., 540.) * ptr->CosThetaC(1., 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->SinThetaC(1., 540.) * ptr->InvSinThetaC(1., 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->TgThetaC(1., 540.) * ptr->CtgThetaC(1., 540), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->Absorptivity(1., 540.) * ptr->AbsorptionLength(1., 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(1., 540.) * ptr->InvEffScattLength(1., 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->SinThetaC(1., 540.) * ptr->SinThetaC(1., 540.) + ptr->CosThetaC(1., 540.) * ptr->CosThetaC(1., 540.), 1., PERCENTAGE);
}
TEST(I3MediumServiceWithInit){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);
  std::string properties(getenv("I3_WORK"));
  ptr->Initialize(properties + ICE_PROPERTIES);

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity(), 1.020408e-02, abs(PERCENTAGE * ptr->BulkIceAbsorptivity()));
  ENSURE_DISTANCE(ptr->BulkIceInvEffScattLength(), 3.003003e-02, abs(PERCENTAGE * ptr->BulkIceInvEffScattLength()));
  ENSURE_DISTANCE(ptr->BulkIceAbsorptionLength(), 9.800000e+01, abs(PERCENTAGE * ptr->BulkIceAbsorptionLength()));
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength(), 3.330000e+01, abs(PERCENTAGE * ptr->BulkIceEffScattLength()));
  ENSURE_DISTANCE(ptr->MeanScatteringCosine(), 8.000000e-01, abs(PERCENTAGE * ptr->MeanScatteringCosine()));

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity() * ptr->BulkIceAbsorptionLength(), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength() * ptr->BulkIceInvEffScattLength(), 1., PERCENTAGE);
}
