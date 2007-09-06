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
#include "phys-services/I3MediumPropertiesFile.h"
#include "phys-services/I3MediumService.h"

#define PERCENTAGE 0.000001
#define ICE_PROPERTIES "/phys-services/resources/iceProperties.dat"

TEST_GROUP(I3MediumServiceTest);

TEST(I3MediumService380nmWithoutProperties){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->NPhase(380.), 1.321429e+00, fabs(PERCENTAGE * ptr->NPhase(380.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), -1.089763e-01, fabs(PERCENTAGE * ptr->DNPhaseDLambda(380.)));
  ENSURE_DISTANCE(ptr->NGroup(380.), 1.362840e+00, fabs(PERCENTAGE * ptr->NGroup(380.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), 4.545945e+00, fabs(PERCENTAGE * ptr->InvC_ICE(380.)));
  ENSURE_DISTANCE(ptr->C_ICE(380.), 2.199763e-01, fabs(PERCENTAGE * ptr->C_ICE(380.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(380.) * ptr->C_ICE(380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->NPhase(380.), ptr->NPhase(), fabs(PERCENTAGE * ptr->NPhase()));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), ptr->DNPhaseDLambda(), fabs(PERCENTAGE * ptr->DNPhaseDLambda()));
  ENSURE_DISTANCE(ptr->NGroup(380.), ptr->NGroup(), fabs(PERCENTAGE * ptr->NGroup()));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), ptr->InvC_ICE(), fabs(PERCENTAGE * ptr->InvC_ICE()));
  ENSURE_DISTANCE(ptr->C_ICE(380.), ptr->C_ICE(), fabs(PERCENTAGE * ptr->C_ICE()));

  ENSURE_DISTANCE(ptr->ThetaC(0.8, 380.), 3.302983e-01, fabs(PERCENTAGE * ptr->ThetaC(0.8, 380)));


  ENSURE_DISTANCE(ptr->ThetaC(0.9, 380.), 5.719620e-01, fabs(PERCENTAGE * ptr->ThetaC(0.9, 380)));


  ENSURE_DISTANCE(ptr->ThetaC(1.0, 380.), 7.124593e-01, fabs(PERCENTAGE * ptr->ThetaC(1.0, 380)));


  ENSURE_DISTANCE(ptr->Absorptivity(-600, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-600, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-600, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-600, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-600, 380.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-600, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 380.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-600, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-600, -450, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-600, -450, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-600, -450, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-600, -450, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(-600, 380.) * ptr->AbsorptionLength(-600, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 380.) * ptr->InvEffScattLength(-600, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-400, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-400, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-400, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-400, 380.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-400, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 380.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-400, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-400, -250, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-400, -250, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-400, -250, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-400, -250, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 380.) * ptr->AbsorptionLength(-400, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 380.) * ptr->InvEffScattLength(-400, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-200, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-200, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-200, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-200, 380.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-200, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 380.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-200, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-200, -50, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-200, -50, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-200, -50, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-200, -50, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 380.) * ptr->AbsorptionLength(-200, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 380.) * ptr->InvEffScattLength(-200, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(0, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(0, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(0, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0, 380.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(0, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(0, 380.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(0, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(0, 150, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(0, 150, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(0, 150, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(0, 150, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(0, 380.) * ptr->AbsorptionLength(0, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0, 380.) * ptr->InvEffScattLength(0, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(200, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(200, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(200, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(200, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(200, 380.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(200, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(200, 380.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(200, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(200, 350, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(200, 350, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(200, 350, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(200, 350, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(200, 380.) * ptr->AbsorptionLength(200, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(200, 380.) * ptr->InvEffScattLength(200, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(400, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(400, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(400, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(400, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(400, 380.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(400, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(400, 380.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(400, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(400, 550, 380.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(400, 550, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(400, 550, 380.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(400, 550, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(400, 380.) * ptr->AbsorptionLength(400, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(400, 380.) * ptr->InvEffScattLength(400, 380.), 1., PERCENTAGE);
}
TEST(I3MediumService460nmWithoutProperties){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->NPhase(460.), 1.315071e+00, fabs(PERCENTAGE * ptr->NPhase(460.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(460.), -5.742147e-02, fabs(PERCENTAGE * ptr->DNPhaseDLambda(460.)));
  ENSURE_DISTANCE(ptr->NGroup(460.), 1.341485e+00, fabs(PERCENTAGE * ptr->NGroup(460.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(460.), 4.474713e+00, fabs(PERCENTAGE * ptr->InvC_ICE(460.)));
  ENSURE_DISTANCE(ptr->C_ICE(460.), 2.234780e-01, fabs(PERCENTAGE * ptr->C_ICE(460.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(460.) * ptr->C_ICE(460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->ThetaC(0.8, 460.), 3.158951e-01, fabs(PERCENTAGE * ptr->ThetaC(0.8, 460)));


  ENSURE_DISTANCE(ptr->ThetaC(0.9, 460.), 5.644078e-01, fabs(PERCENTAGE * ptr->ThetaC(0.9, 460)));


  ENSURE_DISTANCE(ptr->ThetaC(1.0, 460.), 7.068445e-01, fabs(PERCENTAGE * ptr->ThetaC(1.0, 460)));


  ENSURE_DISTANCE(ptr->Absorptivity(-600, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-600, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-600, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-600, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-600, 460.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-600, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 460.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-600, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-600, -450, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-600, -450, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-600, -450, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-600, -450, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(-600, 460.) * ptr->AbsorptionLength(-600, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 460.) * ptr->InvEffScattLength(-600, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-400, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-400, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-400, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-400, 460.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-400, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 460.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-400, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-400, -250, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-400, -250, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-400, -250, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-400, -250, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 460.) * ptr->AbsorptionLength(-400, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 460.) * ptr->InvEffScattLength(-400, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-200, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-200, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-200, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-200, 460.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-200, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 460.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-200, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-200, -50, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-200, -50, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-200, -50, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-200, -50, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 460.) * ptr->AbsorptionLength(-200, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 460.) * ptr->InvEffScattLength(-200, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(0, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(0, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(0, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0, 460.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(0, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(0, 460.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(0, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(0, 150, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(0, 150, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(0, 150, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(0, 150, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(0, 460.) * ptr->AbsorptionLength(0, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0, 460.) * ptr->InvEffScattLength(0, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(200, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(200, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(200, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(200, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(200, 460.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(200, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(200, 460.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(200, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(200, 350, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(200, 350, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(200, 350, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(200, 350, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(200, 460.) * ptr->AbsorptionLength(200, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(200, 460.) * ptr->InvEffScattLength(200, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(400, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(400, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(400, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(400, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(400, 460.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(400, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(400, 460.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(400, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(400, 550, 460.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(400, 550, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(400, 550, 460.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(400, 550, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(400, 460.) * ptr->AbsorptionLength(400, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(400, 460.) * ptr->InvEffScattLength(400, 460.), 1., PERCENTAGE);
}
TEST(I3MediumService540nmWithoutProperties){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->NPhase(540.), 1.311391e+00, fabs(PERCENTAGE * ptr->NPhase(540.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(540.), -3.776158e-02, fabs(PERCENTAGE * ptr->DNPhaseDLambda(540.)));
  ENSURE_DISTANCE(ptr->NGroup(540.), 1.331782e+00, fabs(PERCENTAGE * ptr->NGroup(540.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(540.), 4.442347e+00, fabs(PERCENTAGE * ptr->InvC_ICE(540.)));
  ENSURE_DISTANCE(ptr->C_ICE(540.), 2.251062e-01, fabs(PERCENTAGE * ptr->C_ICE(540.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(540.) * ptr->C_ICE(540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->ThetaC(0.8, 540.), 3.071923e-01, fabs(PERCENTAGE * ptr->ThetaC(0.8, 540)));


  ENSURE_DISTANCE(ptr->ThetaC(0.9, 540.), 5.599593e-01, fabs(PERCENTAGE * ptr->ThetaC(0.9, 540)));


  ENSURE_DISTANCE(ptr->ThetaC(1.0, 540.), 7.035521e-01, fabs(PERCENTAGE * ptr->ThetaC(1.0, 540)));


  ENSURE_DISTANCE(ptr->Absorptivity(-600, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-600, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-600, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-600, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-600, 540.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-600, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 540.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-600, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-600, -450, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-600, -450, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-600, -450, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-600, -450, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(-600, 540.) * ptr->AbsorptionLength(-600, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 540.) * ptr->InvEffScattLength(-600, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-400, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-400, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-400, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-400, 540.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-400, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 540.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-400, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-400, -250, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-400, -250, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-400, -250, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-400, -250, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 540.) * ptr->AbsorptionLength(-400, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 540.) * ptr->InvEffScattLength(-400, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(-200, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-200, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-200, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-200, 540.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-200, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 540.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(-200, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-200, -50, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-200, -50, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-200, -50, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-200, -50, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 540.) * ptr->AbsorptionLength(-200, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 540.) * ptr->InvEffScattLength(-200, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(0, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(0, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(0, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0, 540.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(0, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(0, 540.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(0, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(0, 150, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(0, 150, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(0, 150, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(0, 150, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(0, 540.) * ptr->AbsorptionLength(0, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0, 540.) * ptr->InvEffScattLength(0, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(200, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(200, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(200, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(200, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(200, 540.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(200, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(200, 540.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(200, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(200, 350, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(200, 350, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(200, 350, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(200, 350, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(200, 540.) * ptr->AbsorptionLength(200, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(200, 540.) * ptr->InvEffScattLength(200, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(400, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->Absorptivity(400, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(400, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(400, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(400, 540.), 9.800000e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(400, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(400, 540.), 3.330000e+01, fabs(PERCENTAGE * ptr->EffScattLength(400, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(400, 550, 540.), 1.020408e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(400, 550, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(400, 550, 540.), 3.003003e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(400, 550, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(400, 540.) * ptr->AbsorptionLength(400, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(400, 540.) * ptr->InvEffScattLength(400, 540.), 1., PERCENTAGE);
}
TEST(I3MediumServiceWithoutProperties){
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService);

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity(), 1.020408e-02, fabs(PERCENTAGE * ptr->BulkIceAbsorptivity()));
  ENSURE_DISTANCE(ptr->BulkIceInvEffScattLength(), 3.003003e-02, fabs(PERCENTAGE * ptr->BulkIceInvEffScattLength()));
  ENSURE_DISTANCE(ptr->BulkIceAbsorptionLength(), 9.800000e+01, fabs(PERCENTAGE * ptr->BulkIceAbsorptionLength()));
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength(), 3.330000e+01, fabs(PERCENTAGE * ptr->BulkIceEffScattLength()));
  ENSURE_DISTANCE(ptr->MeanScatteringCosine(), 8.000000e-01, fabs(PERCENTAGE * ptr->MeanScatteringCosine()));

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity() * ptr->BulkIceAbsorptionLength(), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength() * ptr->BulkIceInvEffScattLength(), 1., PERCENTAGE);
}
TEST(I3MediumService380nmWithProperties){
  std::string works(getenv("I3_SRC"));
  I3MediumPropertiesFile properties(works + ICE_PROPERTIES);
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService(properties));

  ENSURE_DISTANCE(ptr->NPhase(380.), 1.321429e+00, fabs(PERCENTAGE * ptr->NPhase(380.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), -1.089763e-01, fabs(PERCENTAGE * ptr->DNPhaseDLambda(380.)));
  ENSURE_DISTANCE(ptr->NGroup(380.), 1.362840e+00, fabs(PERCENTAGE * ptr->NGroup(380.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), 4.545945e+00, fabs(PERCENTAGE * ptr->InvC_ICE(380.)));
  ENSURE_DISTANCE(ptr->C_ICE(380.), 2.199763e-01, fabs(PERCENTAGE * ptr->C_ICE(380.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(380.) * ptr->C_ICE(380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->NPhase(380.), ptr->NPhase(), fabs(PERCENTAGE * ptr->NPhase()));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(380.), ptr->DNPhaseDLambda(), fabs(PERCENTAGE * ptr->DNPhaseDLambda()));
  ENSURE_DISTANCE(ptr->NGroup(380.), ptr->NGroup(), fabs(PERCENTAGE * ptr->NGroup()));
  ENSURE_DISTANCE(ptr->InvC_ICE(380.), ptr->InvC_ICE(), fabs(PERCENTAGE * ptr->InvC_ICE()));
  ENSURE_DISTANCE(ptr->C_ICE(380.), ptr->C_ICE(), fabs(PERCENTAGE * ptr->C_ICE()));

  ENSURE_DISTANCE(ptr->ThetaC(0.8, 380.), 3.302983e-01, fabs(PERCENTAGE * ptr->ThetaC(0.8, 380)));


  ENSURE_DISTANCE(ptr->ThetaC(0.9, 380.), 5.719620e-01, fabs(PERCENTAGE * ptr->ThetaC(0.9, 380)));


  ENSURE_DISTANCE(ptr->ThetaC(1.0, 380.), 7.124593e-01, fabs(PERCENTAGE * ptr->ThetaC(1.0, 380)));


  ENSURE_DISTANCE(ptr->Absorptivity(-600, 380.), 9.200000e-03, fabs(PERCENTAGE * ptr->Absorptivity(-600, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-600, 380.), 4.330000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-600, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-600, 380.), 1.086957e+02, fabs(PERCENTAGE * ptr->AbsorptionLength(-600, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 380.), 2.309469e+01, fabs(PERCENTAGE * ptr->EffScattLength(-600, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-600, -450, 380.), 8.610833e-03, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-600, -450, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-600, -450, 380.), 3.814833e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-600, -450, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(-600, 380.) * ptr->AbsorptionLength(-600, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 380.) * ptr->InvEffScattLength(-600, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 380.), 9.575000e-03, fabs(PERCENTAGE * ptr->Absorptivity(-400, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-400, 380.), 4.685000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-400, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-400, 380.), 1.044386e+02, fabs(PERCENTAGE * ptr->AbsorptionLength(-400, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 380.), 2.134472e+01, fabs(PERCENTAGE * ptr->EffScattLength(-400, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-400, -250, 380.), 1.661833e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-400, -250, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-400, -250, 380.), 1.118767e-01, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-400, -250, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 380.) * ptr->AbsorptionLength(-400, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 380.) * ptr->InvEffScattLength(-400, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 380.), 8.300000e-03, fabs(PERCENTAGE * ptr->Absorptivity(-200, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-200, 380.), 3.540000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-200, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-200, 380.), 1.204819e+02, fabs(PERCENTAGE * ptr->AbsorptionLength(-200, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 380.), 2.824859e+01, fabs(PERCENTAGE * ptr->EffScattLength(-200, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-200, -50, 380.), 9.509583e-03, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-200, -50, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-200, -50, 380.), 4.659750e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-200, -50, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 380.) * ptr->AbsorptionLength(-200, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 380.) * ptr->InvEffScattLength(-200, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(0, 380.), 1.132500e-02, fabs(PERCENTAGE * ptr->Absorptivity(0, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0, 380.), 6.335000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(0, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0, 380.), 8.830022e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(0, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(0, 380.), 1.578532e+01, fabs(PERCENTAGE * ptr->EffScattLength(0, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(0, 150, 380.), 1.014875e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(0, 150, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(0, 150, 380.), 5.254583e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(0, 150, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(0, 380.) * ptr->AbsorptionLength(0, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0, 380.) * ptr->InvEffScattLength(0, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(200, 380.), 9.025000e-03, fabs(PERCENTAGE * ptr->Absorptivity(200, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(200, 380.), 4.230000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(200, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(200, 380.), 1.108033e+02, fabs(PERCENTAGE * ptr->AbsorptionLength(200, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(200, 380.), 2.364066e+01, fabs(PERCENTAGE * ptr->EffScattLength(200, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(200, 350, 380.), 1.213375e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(200, 350, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(200, 350, 380.), 6.184250e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(200, 350, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(200, 380.) * ptr->AbsorptionLength(200, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(200, 380.) * ptr->InvEffScattLength(200, 380.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(400, 380.), 1.695000e-02, fabs(PERCENTAGE * ptr->Absorptivity(400, 380)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(400, 380.), 1.452750e-01, fabs(PERCENTAGE * ptr->InvEffScattLength(400, 380)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(400, 380.), 5.899705e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(400, 380)));
  ENSURE_DISTANCE(ptr->EffScattLength(400, 380.), 6.883497e+00, fabs(PERCENTAGE * ptr->EffScattLength(400, 380)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(400, 550, 380.), 1.972375e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(400, 550, 380)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(400, 550, 380.), 2.481804e-01, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(400, 550, 380)));

  ENSURE_DISTANCE(ptr->Absorptivity(400, 380.) * ptr->AbsorptionLength(400, 380.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(400, 380.) * ptr->InvEffScattLength(400, 380.), 1., PERCENTAGE);
}
TEST(I3MediumService460nmWithProperties){
  std::string works(getenv("I3_SRC"));
  I3MediumPropertiesFile properties(works + ICE_PROPERTIES);
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService(properties));

  ENSURE_DISTANCE(ptr->NPhase(460.), 1.315071e+00, fabs(PERCENTAGE * ptr->NPhase(460.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(460.), -5.742147e-02, fabs(PERCENTAGE * ptr->DNPhaseDLambda(460.)));
  ENSURE_DISTANCE(ptr->NGroup(460.), 1.341485e+00, fabs(PERCENTAGE * ptr->NGroup(460.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(460.), 4.474713e+00, fabs(PERCENTAGE * ptr->InvC_ICE(460.)));
  ENSURE_DISTANCE(ptr->C_ICE(460.), 2.234780e-01, fabs(PERCENTAGE * ptr->C_ICE(460.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(460.) * ptr->C_ICE(460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->ThetaC(0.8, 460.), 3.158951e-01, fabs(PERCENTAGE * ptr->ThetaC(0.8, 460)));


  ENSURE_DISTANCE(ptr->ThetaC(0.9, 460.), 5.644078e-01, fabs(PERCENTAGE * ptr->ThetaC(0.9, 460)));


  ENSURE_DISTANCE(ptr->ThetaC(1.0, 460.), 7.068445e-01, fabs(PERCENTAGE * ptr->ThetaC(1.0, 460)));


  ENSURE_DISTANCE(ptr->Absorptivity(-600, 460.), 1.195000e-02, fabs(PERCENTAGE * ptr->Absorptivity(-600, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-600, 460.), 3.645000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-600, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-600, 460.), 8.368201e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-600, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 460.), 2.743484e+01, fabs(PERCENTAGE * ptr->EffScattLength(-600, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-600, -450, 460.), 1.142708e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-600, -450, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-600, -450, 460.), 3.212417e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-600, -450, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(-600, 460.) * ptr->AbsorptionLength(-600, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 460.) * ptr->InvEffScattLength(-600, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 460.), 1.207500e-02, fabs(PERCENTAGE * ptr->Absorptivity(-400, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-400, 460.), 3.945000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-400, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-400, 460.), 8.281573e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-400, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 460.), 2.534854e+01, fabs(PERCENTAGE * ptr->EffScattLength(-400, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-400, -250, 460.), 1.773417e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-400, -250, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-400, -250, 460.), 9.423292e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-400, -250, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 460.) * ptr->AbsorptionLength(-400, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 460.) * ptr->InvEffScattLength(-400, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 460.), 1.085000e-02, fabs(PERCENTAGE * ptr->Absorptivity(-200, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-200, 460.), 2.980000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-200, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-200, 460.), 9.216590e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-200, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 460.), 3.355705e+01, fabs(PERCENTAGE * ptr->EffScattLength(-200, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-200, -50, 460.), 1.177917e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-200, -50, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-200, -50, 460.), 3.925417e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-200, -50, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 460.) * ptr->AbsorptionLength(-200, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 460.) * ptr->InvEffScattLength(-200, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(0, 460.), 1.315000e-02, fabs(PERCENTAGE * ptr->Absorptivity(0, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0, 460.), 5.335000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(0, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0, 460.), 7.604563e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(0, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(0, 460.), 1.874414e+01, fabs(PERCENTAGE * ptr->EffScattLength(0, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(0, 150, 460.), 1.215333e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(0, 150, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(0, 150, 460.), 4.426042e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(0, 150, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(0, 460.) * ptr->AbsorptionLength(0, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0, 460.) * ptr->InvEffScattLength(0, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(200, 460.), 1.115000e-02, fabs(PERCENTAGE * ptr->Absorptivity(200, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(200, 460.), 3.565000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(200, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(200, 460.), 8.968610e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(200, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(200, 460.), 2.805049e+01, fabs(PERCENTAGE * ptr->EffScattLength(200, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(200, 350, 460.), 1.361083e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(200, 350, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(200, 350, 460.), 5.209000e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(200, 350, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(200, 460.) * ptr->AbsorptionLength(200, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(200, 460.) * ptr->InvEffScattLength(200, 460.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(400, 460.), 1.747500e-02, fabs(PERCENTAGE * ptr->Absorptivity(400, 460)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(400, 460.), 1.236750e-01, fabs(PERCENTAGE * ptr->InvEffScattLength(400, 460)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(400, 460.), 5.722461e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(400, 460)));
  ENSURE_DISTANCE(ptr->EffScattLength(400, 460.), 8.085709e+00, fabs(PERCENTAGE * ptr->EffScattLength(400, 460)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(400, 550, 460.), 1.967458e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(400, 550, 460)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(400, 550, 460.), 2.238329e-01, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(400, 550, 460)));

  ENSURE_DISTANCE(ptr->Absorptivity(400, 460.) * ptr->AbsorptionLength(400, 460.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(400, 460.) * ptr->InvEffScattLength(400, 460.), 1., PERCENTAGE);
}
TEST(I3MediumService540nmWithProperties){
  std::string works(getenv("I3_SRC"));
  I3MediumPropertiesFile properties(works + ICE_PROPERTIES);
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService(properties));

  ENSURE_DISTANCE(ptr->NPhase(540.), 1.311391e+00, fabs(PERCENTAGE * ptr->NPhase(540.)));
  ENSURE_DISTANCE(ptr->DNPhaseDLambda(540.), -3.776158e-02, fabs(PERCENTAGE * ptr->DNPhaseDLambda(540.)));
  ENSURE_DISTANCE(ptr->NGroup(540.), 1.331782e+00, fabs(PERCENTAGE * ptr->NGroup(540.)));
  ENSURE_DISTANCE(ptr->InvC_ICE(540.), 4.442347e+00, fabs(PERCENTAGE * ptr->InvC_ICE(540.)));
  ENSURE_DISTANCE(ptr->C_ICE(540.), 2.251062e-01, fabs(PERCENTAGE * ptr->C_ICE(540.)));

  ENSURE_DISTANCE(ptr->InvC_ICE(540.) * ptr->C_ICE(540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->ThetaC(0.8, 540.), 3.071923e-01, fabs(PERCENTAGE * ptr->ThetaC(0.8, 540)));


  ENSURE_DISTANCE(ptr->ThetaC(0.9, 540.), 5.599593e-01, fabs(PERCENTAGE * ptr->ThetaC(0.9, 540)));


  ENSURE_DISTANCE(ptr->ThetaC(1.0, 540.), 7.035521e-01, fabs(PERCENTAGE * ptr->ThetaC(1.0, 540)));


  ENSURE_DISTANCE(ptr->Absorptivity(-600, 540.), 4.535000e-02, fabs(PERCENTAGE * ptr->Absorptivity(-600, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-600, 540.), 3.155000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-600, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-600, 540.), 2.205072e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-600, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 540.), 3.169572e+01, fabs(PERCENTAGE * ptr->EffScattLength(-600, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-600, -450, 540.), 4.434625e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-600, -450, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-600, -450, 540.), 2.781292e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-600, -450, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(-600, 540.) * ptr->AbsorptionLength(-600, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-600, 540.) * ptr->InvEffScattLength(-600, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 540.), 4.390000e-02, fabs(PERCENTAGE * ptr->Absorptivity(-400, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-400, 540.), 3.417500e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-400, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-400, 540.), 2.277904e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-400, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 540.), 2.926116e+01, fabs(PERCENTAGE * ptr->EffScattLength(-400, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-400, -250, 540.), 4.812125e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-400, -250, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-400, -250, 540.), 8.158708e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-400, -250, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(-400, 540.) * ptr->AbsorptionLength(-400, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-400, 540.) * ptr->InvEffScattLength(-400, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 540.), 4.145000e-02, fabs(PERCENTAGE * ptr->Absorptivity(-200, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(-200, 540.), 2.580000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(-200, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(-200, 540.), 2.412545e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(-200, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 540.), 3.875969e+01, fabs(PERCENTAGE * ptr->EffScattLength(-200, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(-200, -50, 540.), 4.173042e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(-200, -50, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(-200, -50, 540.), 3.397708e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(-200, -50, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(-200, 540.) * ptr->AbsorptionLength(-200, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(-200, 540.) * ptr->InvEffScattLength(-200, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(0, 540.), 4.210000e-02, fabs(PERCENTAGE * ptr->Absorptivity(0, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(0, 540.), 4.620000e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(0, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(0, 540.), 2.375297e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(0, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(0, 540.), 2.164502e+01, fabs(PERCENTAGE * ptr->EffScattLength(0, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(0, 150, 540.), 4.080333e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(0, 150, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(0, 150, 540.), 3.832375e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(0, 150, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(0, 540.) * ptr->AbsorptionLength(0, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(0, 540.) * ptr->InvEffScattLength(0, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(200, 540.), 3.925000e-02, fabs(PERCENTAGE * ptr->Absorptivity(200, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(200, 540.), 3.087500e-02, fabs(PERCENTAGE * ptr->InvEffScattLength(200, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(200, 540.), 2.547771e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(200, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(200, 540.), 3.238866e+01, fabs(PERCENTAGE * ptr->EffScattLength(200, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(200, 350, 540.), 4.092292e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(200, 350, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(200, 350, 540.), 4.508958e-02, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(200, 350, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(200, 540.) * ptr->AbsorptionLength(200, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(200, 540.) * ptr->InvEffScattLength(200, 540.), 1., PERCENTAGE);

  ENSURE_DISTANCE(ptr->Absorptivity(400, 540.), 4.355000e-02, fabs(PERCENTAGE * ptr->Absorptivity(400, 540)));
  ENSURE_DISTANCE(ptr->InvEffScattLength(400, 540.), 1.080000e-01, fabs(PERCENTAGE * ptr->InvEffScattLength(400, 540)));
  ENSURE_DISTANCE(ptr->AbsorptionLength(400, 540.), 2.296211e+01, fabs(PERCENTAGE * ptr->AbsorptionLength(400, 540)));
  ENSURE_DISTANCE(ptr->EffScattLength(400, 540.), 9.259259e+00, fabs(PERCENTAGE * ptr->EffScattLength(400, 540)));

  ENSURE_DISTANCE(ptr->AveragedAbsorptivity(400, 550, 540.), 4.506917e-02, fabs(PERCENTAGE * ptr->AveragedAbsorptivity(400, 550, 540)));
  ENSURE_DISTANCE(ptr->AveragedInvEffScattLength(400, 550, 540.), 2.053808e-01, fabs(PERCENTAGE * ptr->AveragedInvEffScattLength(400, 550, 540)));

  ENSURE_DISTANCE(ptr->Absorptivity(400, 540.) * ptr->AbsorptionLength(400, 540.), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->EffScattLength(400, 540.) * ptr->InvEffScattLength(400, 540.), 1., PERCENTAGE);
}
TEST(I3MediumServiceWithProperties){
  std::string works(getenv("I3_SRC"));
  I3MediumPropertiesFile properties(works + ICE_PROPERTIES);
  I3MediumServicePtr ptr = I3MediumServicePtr(new I3MediumService(properties));

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity(), 1.020408e-02, fabs(PERCENTAGE * ptr->BulkIceAbsorptivity()));
  ENSURE_DISTANCE(ptr->BulkIceInvEffScattLength(), 3.003003e-02, fabs(PERCENTAGE * ptr->BulkIceInvEffScattLength()));
  ENSURE_DISTANCE(ptr->BulkIceAbsorptionLength(), 9.800000e+01, fabs(PERCENTAGE * ptr->BulkIceAbsorptionLength()));
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength(), 3.330000e+01, fabs(PERCENTAGE * ptr->BulkIceEffScattLength()));
  ENSURE_DISTANCE(ptr->MeanScatteringCosine(), 8.000000e-01, fabs(PERCENTAGE * ptr->MeanScatteringCosine()));

  ENSURE_DISTANCE(ptr->BulkIceAbsorptivity() * ptr->BulkIceAbsorptionLength(), 1., PERCENTAGE);
  ENSURE_DISTANCE(ptr->BulkIceEffScattLength() * ptr->BulkIceInvEffScattLength(), 1., PERCENTAGE);
}
