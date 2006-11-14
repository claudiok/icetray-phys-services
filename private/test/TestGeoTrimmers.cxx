#include <I3Test.h>

#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/geo-selector/I3GeoTrimmers.h"

// Create a phony geometry
static I3OMGeoMapPtr geo() {
  I3OMGeoMapPtr g = I3OMGeoMapPtr(new I3OMGeoMap());
  OMKey dom1(1,1);
  OMKey dom2(1,2);
  OMKey dom3(1,3);
  OMKey dom4(1,4);
  OMKey dom5(2,4);
  OMKey dom6(2,5);
  OMKey dom7(2,61);
  OMKey dom8(2,62);
  OMKey dom9(2,63);
  (*g)[dom1].position.SetPosition(0,0,0);
  (*g)[dom2].position.SetPosition(0,0,50);
  (*g)[dom3].position.SetPosition(0,0,100);
  (*g)[dom4].position.SetPosition(0,0,500);
  (*g)[dom5].position.SetPosition(0,50,500);
  (*g)[dom6].position.SetPosition(20,50,500);
  (*g)[dom7].position.SetPosition(20,50,400);
  (*g)[dom8].position.SetPosition(20,50,300);
  (*g)[dom9].position.SetPosition(20,50,200);
  return g;
}

static I3RecoPulseSeriesMapPtr rpsm() {
  // Create a phony pulse series
  // Hits on DOM's 1-5 only
  I3RecoPulseSeriesMapPtr rp(new I3RecoPulseSeriesMap);
  I3RecoPulse p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11;
  p0.SetTime(1650);   p0.SetWidth(100);  p0.SetID(0);   //close to #1       //coincidence with #1
  p1.SetTime(1850);   p1.SetWidth(100);  p1.SetID(1);   //close to #0       //coincidence with #0
  p2.SetTime(0);      p2.SetWidth(100);  p2.SetID(2);   //close to #3       //coincidence with #3
  p3.SetTime(550);    p3.SetWidth(0);    p3.SetID(3);   //close to #2, #4   //coincidence with #2, #4
  p4.SetTime(800);    p4.SetWidth(0);    p4.SetID(4);   //close to #3       //coincidence with #3
  p5.SetTime(3500);   p5.SetWidth(100);  p5.SetID(5);   //isolated          //coincidence with #6, #7
  p6.SetTime(3500);   p6.SetWidth(100);  p6.SetID(6);   //close to #7, #8   //coincidence with #5, #7
  p7.SetTime(3500);   p7.SetWidth(100);  p7.SetID(7);   //close to #6, #8   //coincidence with #5, #6
  p8.SetTime(3500);   p8.SetWidth(100);  p8.SetID(8);   //close to #6, #7   //isolated
  p9.SetTime(8000);   p9.SetWidth(3000); p9.SetID(9);   //close to #10, #11 //coincidence with #10, #11
  p10.SetTime(9000);  p10.SetWidth(100); p10.SetID(10); //close to #9, #11  //coincidence with #9, #11
  p11.SetTime(9500);  p11.SetWidth(100); p11.SetID(11); //close to #9, #10  //coincidence with #9, #10
  OMKey dom1(1,1);
  OMKey dom2(1,2);
  OMKey dom3(2,63);
  OMKey dom4(1,4);
  OMKey dom5(2,4);
  (*rp)[dom1].push_back(p0);
  (*rp)[dom1].push_back(p1);
  (*rp)[dom1].push_back(p2);
  (*rp)[dom2].push_back(p3);
  (*rp)[dom3].push_back(p4);
  (*rp)[dom3].push_back(p5);
  (*rp)[dom4].push_back(p6);
  (*rp)[dom4].push_back(p7);
  (*rp)[dom5].push_back(p8);
  (*rp)[dom5].push_back(p9);
  (*rp)[dom5].push_back(p10);
  (*rp)[dom5].push_back(p11);
  return rp;
}

static I3VectorOMKey badoms() {
  // Create a phony bad OM list
  I3VectorOMKey bad;
  bad.push_back(OMKey(1,3));
  bad.push_back(OMKey(2,5));
  bad.push_back(OMKey(2,62));
  return bad;
}

TEST_GROUP(GeoTrimmers)

TEST(FromRecoPulses)
{
  I3OMGeoMapPtr g = geo();
  I3RecoPulseSeriesMapPtr rp = rpsm();
  I3OMGeoMapPtr result = I3GeoTrimmers::GeoFromPulseSeries(*g, *rp);
  int sz = (int)result->size();
  ENSURE_EQUAL(sz,5,"Wrong number of OM's");
  ENSURE(result->find(OMKey(1,1)) != result->end(), "1-1 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,2)) != result->end(), "1-2 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,63)) != result->end(), "2-63 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,4)) != result->end(), "1-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,4)) != result->end(), "2-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,5)) == result->end(), "2-5 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,61)) == result->end(), "2-61 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,62)) == result->end(), "2-62 Exists but shouldn't");
  ENSURE(result->find(OMKey(1,3)) == result->end(), "1-3 Exists but shouldn't");

}

TEST(FromRecoPulsesWithNeighbors)
{
  I3OMGeoMapPtr g = geo();
  I3RecoPulseSeriesMapPtr rp = rpsm();
  I3OMGeoMapPtr result = I3GeoTrimmers::GeoFromPulseSeriesWithNeighbors(*g, *rp);
  int sz = (int)result->size();
  ENSURE_EQUAL(sz,8,"Wrong number of OM's");
  ENSURE(result->find(OMKey(1,1)) != result->end(), "1-1 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,2)) != result->end(), "1-2 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,3)) != result->end(), "1-3 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,4)) != result->end(), "1-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,4)) != result->end(), "2-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,5)) != result->end(), "2-5 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,61)) == result->end(), "2-61 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,62)) != result->end(), "2-62 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,63)) != result->end(), "2-63 Doesn't exist but should");

}

TEST(NoBadOMs)
{
  I3OMGeoMapPtr g = geo();
  I3VectorOMKey bad = badoms();
  I3OMGeoMapPtr result = I3GeoTrimmers::GeoWithoutBadOMs(*g, bad);
  int sz = (int)result->size();
  ENSURE_EQUAL(sz,6,"Wrong number of OM's");
  ENSURE(result->find(OMKey(1,1)) != result->end(), "1-1 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,2)) != result->end(), "1-2 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,3)) == result->end(), "1-3 Exists but shouldn't");
  ENSURE(result->find(OMKey(1,4)) != result->end(), "1-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,4)) != result->end(), "2-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,5)) == result->end(), "2-5 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,61)) != result->end(), "2-61 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,62)) == result->end(), "2-62 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,63)) != result->end(), "2-63 Doesn't exist but should");

}

TEST(NoIceTop)
{
  I3OMGeoMapPtr g = geo();
  I3OMGeoMapPtr result = I3GeoTrimmers::GeoWithoutIceTop(*g);
  int sz = (int)result->size();
  ENSURE_EQUAL(sz,6,"Wrong number of OM's");
  ENSURE(result->find(OMKey(1,1)) != result->end(), "1-1 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,2)) != result->end(), "1-2 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,3)) != result->end(), "1-3 Doesn't exist but should");
  ENSURE(result->find(OMKey(1,4)) != result->end(), "1-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,4)) != result->end(), "2-4 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,5)) != result->end(), "2-5 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,61)) == result->end(), "2-61 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,62)) == result->end(), "2-62 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,63)) == result->end(), "2-63 Exists but shouldn't");

}

TEST(AllIceTop)
{
  I3OMGeoMapPtr g = geo();
  I3OMGeoMapPtr result = I3GeoTrimmers::GeoIceTopOnly(*g);
  int sz = (int)result->size();
  ENSURE_EQUAL(sz,3,"Wrong number of OM's");
  ENSURE(result->find(OMKey(1,1)) == result->end(), "1-1 Exists but shouldn't");
  ENSURE(result->find(OMKey(1,2)) == result->end(), "1-2 Exists but shouldn't");
  ENSURE(result->find(OMKey(1,3)) == result->end(), "1-3 Exists but shouldn't");
  ENSURE(result->find(OMKey(1,4)) == result->end(), "1-4 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,4)) == result->end(), "2-4 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,5)) == result->end(), "2-5 Exists but shouldn't");
  ENSURE(result->find(OMKey(2,61)) != result->end(), "2-61 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,62)) != result->end(), "2-62 Doesn't exist but should");
  ENSURE(result->find(OMKey(2,63)) != result->end(), "2-63 Doesn't exist but should");

}

TEST(Combo1)
{
  I3OMGeoMapPtr g = geo();
  I3RecoPulseSeriesMapPtr rp = rpsm();
  I3VectorOMKey bad = badoms();
  I3OMGeoMapPtr r1 = I3GeoTrimmers::GeoWithoutBadOMs(*g,bad);
  I3OMGeoMapPtr r2 = I3GeoTrimmers::GeoFromPulseSeries(*r1,*rp);
  int sz = (int)r2->size();
  ENSURE_EQUAL(sz,5,"Wrong number of OM's");
  ENSURE(r2->find(OMKey(1,1)) != r2->end(), "1-1 Doesn't exist but should");
  ENSURE(r2->find(OMKey(1,2)) != r2->end(), "1-2 Doesn't exist but should");
  ENSURE(r2->find(OMKey(1,3)) == r2->end(), "1-3 Exists but shouldn't");
  ENSURE(r2->find(OMKey(1,4)) != r2->end(), "1-4 Doesn't exist but should");
  ENSURE(r2->find(OMKey(2,4)) != r2->end(), "2-4 Doesn't exist but should");
  ENSURE(r2->find(OMKey(2,5)) == r2->end(), "2-5 Exists but shouldn't");
  ENSURE(r2->find(OMKey(2,61)) == r2->end(), "2-61 Exists but shouldn't");
  ENSURE(r2->find(OMKey(2,62)) == r2->end(), "2-62 Exists but shouldn't");
  ENSURE(r2->find(OMKey(2,63)) != r2->end(), "2-63 Doesn't exist but should");

}

TEST(Combo2)
{
  I3OMGeoMapPtr g = geo();
  I3RecoPulseSeriesMapPtr rp = rpsm();
  I3VectorOMKey bad = badoms();
  I3OMGeoMapPtr r1 = I3GeoTrimmers::GeoFromPulseSeries(*g,*rp);
  I3OMGeoMapPtr r2 = I3GeoTrimmers::GeoWithoutBadOMs(*r1,bad);
  int sz = (int)r2->size();
  ENSURE_EQUAL(sz,5,"Wrong number of OM's");
  ENSURE(r2->find(OMKey(1,1)) != r2->end(), "1-1 Doesn't exist but should");
  ENSURE(r2->find(OMKey(1,2)) != r2->end(), "1-2 Doesn't exist but should");
  ENSURE(r2->find(OMKey(1,3)) == r2->end(), "1-3 Exists but shouldn't");
  ENSURE(r2->find(OMKey(1,4)) != r2->end(), "1-4 Doesn't exist but should");
  ENSURE(r2->find(OMKey(2,4)) != r2->end(), "2-4 Doesn't exist but should");
  ENSURE(r2->find(OMKey(2,5)) == r2->end(), "2-5 Exists but shouldn't");
  ENSURE(r2->find(OMKey(2,61)) == r2->end(), "2-61 Exists but shouldn't");
  ENSURE(r2->find(OMKey(2,62)) == r2->end(), "2-62 Exists but shouldn't");
  ENSURE(r2->find(OMKey(2,63)) != r2->end(), "2-63 Doesn't exist but should");

}
