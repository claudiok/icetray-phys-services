#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "phys-services/I3Cuts.h"
#include "dataclasses/I3BasicTrack.h"
#include "dataclasses/I3Position.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3OMGeoIceCube.h"
#include "dataclasses/I3OMResponseMap.h"
#include "dataclasses/I3OMResponse.h"

using namespace I3Calculator;
using namespace I3Cuts;

TEST_GROUP(SmoothnessTest);

namespace SmoothnessDirTest{
  void AddHitAtDepth(double depth,
		     I3Geometry& geo,
		     I3OMResponseMap& omr,
		     unsigned position)
  {
    OMKey pos(1,position);
    I3OMGeoIceCubePtr omgeo(new I3OMGeoIceCube());
    omgeo->SetPos(0,0,depth);
    geo.GetInIceGeometry()[pos] = omgeo;
    
    I3OMResponsePtr thisresponse(new I3OMResponse());
    omr[pos] = thisresponse;

    I3RecoHitSeriesPtr rps(new I3RecoHitSeries());
    I3RecoHitPtr hit(new I3RecoHit());
    rps->push_back(hit);
    
    thisresponse->GetRecoHitSeriesDict()["SmoothnessTest"] = rps;
  } 
}

TEST(verysmooth)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  SmoothnessDirTest::AddHitAtDepth(0,geometry,responses,1);
  SmoothnessDirTest::AddHitAtDepth(10,geometry,responses,2);
  SmoothnessDirTest::AddHitAtDepth(20,geometry,responses,3);
  SmoothnessDirTest::AddHitAtDepth(30,geometry,responses,4);
  SmoothnessDirTest::AddHitAtDepth(40,geometry,responses,5);
  SmoothnessDirTest::AddHitAtDepth(50,geometry,responses,6);
  SmoothnessDirTest::AddHitAtDepth(60,geometry,responses,7);
  SmoothnessDirTest::AddHitAtDepth(70,geometry,responses,8);
  SmoothnessDirTest::AddHitAtDepth(80,geometry,responses,9);
  SmoothnessDirTest::AddHitAtDepth(90,geometry,responses,10);
  SmoothnessDirTest::AddHitAtDepth(100,geometry,responses,11);

  ENSURE_DISTANCE(0.0,
		  SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10),
		  0.001,
		  "Smoothness of evenly spaced hits should be 0");


}


TEST(lesssmooth_positive)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  SmoothnessDirTest::AddHitAtDepth(0,geometry,responses,1);
  SmoothnessDirTest::AddHitAtDepth(10,geometry,responses,2);
  SmoothnessDirTest::AddHitAtDepth(20,geometry,responses,3);
  SmoothnessDirTest::AddHitAtDepth(30,geometry,responses,4);
  SmoothnessDirTest::AddHitAtDepth(40,geometry,responses,5);
  SmoothnessDirTest::AddHitAtDepth(45,geometry,responses,6);
  SmoothnessDirTest::AddHitAtDepth(60,geometry,responses,7);
  SmoothnessDirTest::AddHitAtDepth(70,geometry,responses,8);
  SmoothnessDirTest::AddHitAtDepth(80,geometry,responses,9);
  SmoothnessDirTest::AddHitAtDepth(90,geometry,responses,10);
  SmoothnessDirTest::AddHitAtDepth(100,geometry,responses,11);

  ENSURE_DISTANCE(-5./100.,
		  SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10),
		  0.001,
		  "Smoothness of evenly spaced hits should be predictable");


}


TEST(lesssmooth_negative)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  SmoothnessDirTest::AddHitAtDepth(0,geometry,responses,1);
  SmoothnessDirTest::AddHitAtDepth(10,geometry,responses,2);
  SmoothnessDirTest::AddHitAtDepth(20,geometry,responses,3);
  SmoothnessDirTest::AddHitAtDepth(30,geometry,responses,4);
  SmoothnessDirTest::AddHitAtDepth(40,geometry,responses,5);
  SmoothnessDirTest::AddHitAtDepth(55,geometry,responses,6);
  SmoothnessDirTest::AddHitAtDepth(60,geometry,responses,7);
  SmoothnessDirTest::AddHitAtDepth(70,geometry,responses,8);
  SmoothnessDirTest::AddHitAtDepth(80,geometry,responses,9);
  SmoothnessDirTest::AddHitAtDepth(90,geometry,responses,10);
  SmoothnessDirTest::AddHitAtDepth(100,geometry,responses,11);

  ENSURE_DISTANCE(5./100.,
		  SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10),
		  0.001,
		  "Smoothness of evenly spaced hits should be predictable");


}


TEST(orderUnimportant)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  SmoothnessDirTest::AddHitAtDepth(0,geometry,responses,1);
  SmoothnessDirTest::AddHitAtDepth(10,geometry,responses,6);
  SmoothnessDirTest::AddHitAtDepth(20,geometry,responses,5);
  SmoothnessDirTest::AddHitAtDepth(30,geometry,responses,10);
  SmoothnessDirTest::AddHitAtDepth(40,geometry,responses,2);
  SmoothnessDirTest::AddHitAtDepth(50,geometry,responses,7);
  SmoothnessDirTest::AddHitAtDepth(60,geometry,responses,3);
  SmoothnessDirTest::AddHitAtDepth(70,geometry,responses,8);
  SmoothnessDirTest::AddHitAtDepth(80,geometry,responses,9);
  SmoothnessDirTest::AddHitAtDepth(90,geometry,responses,4);
  SmoothnessDirTest::AddHitAtDepth(100,geometry,responses,11);
  
  ENSURE_DISTANCE(0,
		  SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10),
		  0.001,
		  "order shouldn't matter");
}


TEST(nohits)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  ENSURE(isnan(SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10)),
	 "should get NAN if there are no hits");


}


TEST(onehits)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  SmoothnessDirTest::AddHitAtDepth(0,geometry,responses,1);

  ENSURE(isnan(SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10)),
	 "should get NAN if there are no hits");


}


TEST(twohits)
{
  I3BasicTrack bt;
  bt.SetPos(0,0,100);
  bt.SetDir(0,0);

  I3Geometry geometry;

  I3OMResponseMap responses;

  SmoothnessDirTest::AddHitAtDepth(0,geometry,responses,1);
  SmoothnessDirTest::AddHitAtDepth(10,geometry,responses,2);

  ENSURE(isnan(SmoothnessAll(bt,geometry,responses,"SmoothnessTest",-10,10)),
	 "should get NAN if there are no hits");


}
