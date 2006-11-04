#include <I3Test.h>
#include "phys-services/geo-selector/I3GeometrySelectorServiceFactory.h"
#include "phys-services/geo-selector/I3GeoSelTestModule.h"
#include "phys-services/geo-selector/GeoSelUtils.h"
#include "icetray/I3Tray.h"
#include "phys-services/source/I3TextFileGeometryServiceFactory.h"
#include "icetray/modules/TrashCan.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"
#include "phys-services/source/I3Muxer.h"
#include "dataclasses/I3Units.h"

using geo_sel_utils::make_good_strings;
using geo_sel_utils::exists;
using geo_sel_utils::exists_at;
using geo_sel_utils::parse_string_list;
using geo_sel_utils::good_input;


TEST_GROUP(GeometrySelector);

TEST(exists_function){

  int seed = time(0);
  vector<int> vec;
  {
    srand(seed);
    int n_to_find = rand();
    int n_to_load = rand()%10000;
    int position = rand()%n_to_load;
    bool loaded = false;
    for(int i=0; i<n_to_load; i++){
      if(i==position){
	vec.push_back(n_to_find);
	loaded = true;
      }else{
	vec.push_back(rand());
      }
    }
    ENSURE(loaded,"you won't find the number you're looking for");
  }
  {
    srand(seed);
    int n = rand();
    bool found = exists<int>(n,vec);
    ENSURE(found,"didn't find the number.  exists not working.");
  }
}

TEST(parse_string_list){

  string string_list("1,2,3,4,9:11,-8");
  vector<int> parsed_list = parse_string_list(string_list);
  ENSURE(parsed_list.size() == 8);

}

TEST(make_good_strings_simple){

  vector<int> good_strings;
  const string to_use("1,2,3,4");
  const string to_exclude("");

  good_strings = make_good_strings(to_use,to_exclude);
  ENSURE(exists<int>(1,good_strings));
  ENSURE(exists<int>(2,good_strings));
  ENSURE(exists<int>(3,good_strings));
  ENSURE(exists<int>(4,good_strings));
  ENSURE(good_strings.size() == 4);
}

TEST(make_good_strings_more_complex){

  vector<int> good_strings;
  const string to_use("1,2,3,4,84,9:15");
  const string to_exclude("");

  good_strings = make_good_strings(to_use,to_exclude);
  ENSURE(exists<int>(1,good_strings));
  ENSURE(exists<int>(2,good_strings));
  ENSURE(exists<int>(3,good_strings));
  ENSURE(exists<int>(4,good_strings));

  ENSURE(exists<int>(84,good_strings));

  ENSURE(exists<int>(9,good_strings));
  ENSURE(exists<int>(10,good_strings));
  ENSURE(exists<int>(11,good_strings));
  ENSURE(exists<int>(12,good_strings));
  ENSURE(exists<int>(13,good_strings));
  ENSURE(exists<int>(14,good_strings));
  ENSURE(exists<int>(15,good_strings));

  ENSURE(good_strings.size() == 12);
}

TEST(make_good_strings_with_excludes){

  vector<int> good_strings;
  const string to_use("1,2,3,4,84,9:15,-10");
  const string to_exclude("3,11:13,99");

  good_strings = make_good_strings(to_use,to_exclude);
  ENSURE(exists<int>(1,good_strings));
  ENSURE(exists<int>(2,good_strings));
  ENSURE(!exists<int>(3,good_strings));
  ENSURE(exists<int>(4,good_strings));

  ENSURE(exists<int>(84,good_strings));

  ENSURE(exists<int>(9,good_strings));
  ENSURE(exists<int>(10,good_strings));
  ENSURE(!exists<int>(11,good_strings));
  ENSURE(!exists<int>(12,good_strings));
  ENSURE(!exists<int>(13,good_strings));
  ENSURE(exists<int>(14,good_strings));
  ENSURE(exists<int>(15,good_strings));

  ENSURE(exists<int>(-10,good_strings));

  ENSURE(!exists<int>(99,good_strings));

  ENSURE(good_strings.size() == 9);
}

TEST(good_input){
  vector<int> good_strings;
  const string to_use_good("1,2,3,4,84,9:15");
  const string to_exclude_good("3,11:13,99");

  const string to_use_bad("1,2,3,4,#84,9:15");
  const string to_exclude_bad("3,11:13,?99");

  ENSURE(good_input(to_use_good));
  ENSURE(good_input(to_exclude_good));

  ENSURE(!good_input(to_use_bad));
  ENSURE(!good_input(to_exclude_bad));

}

TEST(icetray_test){

  I3Tray tray;

  std::string strings_to_use("21,29,39,38,30,40,49");
  std::string stations_to_use("21,29,30,38,39,40,47,48,49,50,57,58,59,66,67,74");

  string icecube_geo(getenv("I3_WORK"));
  icecube_geo += "/phys-services/resources/icecube.geo";
  string amanda_geo(getenv("I3_WORK"));
  amanda_geo += "/phys-services/resources/amanda.geo";

  tray.AddService("I3TextFileGeometryServiceFactory","geoservice")
    ("IceCubeGeoFile",icecube_geo.c_str())
    ("AmandaGeoFile",amanda_geo.c_str());
  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",1)
    ("InstallGeometry",false);
  tray.AddService("I3GeometrySelectorServiceFactory","geo_selector")
    ("StringsToUse",strings_to_use.c_str())
    ("StationsToUse",stations_to_use.c_str())
    ("GeoSelectorName","I3GeometrySelectorService");
  tray.AddModule("I3Muxer","muxer")
    ("GeometryService","I3GeometrySelectorService");
  //I3GeoSelTestModule contains ENSURE statements
  tray.AddModule("I3GeoSelTestModule","geo_test") 
    ("StringsToUse",strings_to_use.c_str())
    ("StationsToUse",stations_to_use.c_str());
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}

TEST(icetray_test_shift){

  I3Tray tray;

  std::string strings_to_use("21,29,39,38,30,40,49");
  std::string stations_to_use("21,29,30,38,39,40,47,48,49,50,57,58,59,66,67,74");

  std::string strings_to_exclude("-1:20,22:28,31:37,41:48,50:80");
  std::string stations_to_exclude("-1:20,22:28,31:37,41:46,51:56,60:65,68:73,75:80");

  string icecube_geo(getenv("I3_WORK"));
  icecube_geo += "/phys-services/resources/icecube.geo";
  string amanda_geo(getenv("I3_WORK"));
  amanda_geo += "/phys-services/resources/amanda.geo";

  tray.AddService("I3TextFileGeometryServiceFactory","geoservice")
    ("IceCubeGeoFile",icecube_geo.c_str())
    ("AmandaGeoFile",amanda_geo.c_str());
  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",4)
    ("InstallGeometry",false);
  tray.AddService("I3GeometrySelectorServiceFactory","geo_selector")
    ("StringsToUse",strings_to_use.c_str())
    ("StationsToUse",stations_to_use.c_str())
    ("GeoSelectorName","I3GeometrySelectorService")
    ("ShiftX",100*I3Units::m)
    ("ShiftY",100*I3Units::m)
    ("ShiftZ",100*I3Units::m);

  tray.AddModule("I3Muxer","muxer")
    ("GeometryService","I3GeometrySelectorService");
  //I3GeoSelTestModule contains ENSURE statements
  tray.AddModule("I3GeoSelTestModule","geo_test") 
    ("StringsToUse",strings_to_use.c_str())
    ("StringsToExclude",strings_to_exclude.c_str())
    ("StationsToUse",stations_to_use.c_str())
    ("StationsToExclude",stations_to_exclude.c_str())
    ("ShiftX",100*I3Units::m)
    ("ShiftY",100*I3Units::m)
    ("ShiftZ",100*I3Units::m);

  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}

TEST(detector_shift){

  I3Geometry geo;

  OMKey om1(21,1);
  I3Position p1(15.,5.,0.);
  I3OMGeo g1;
  g1.position = p1;

  OMKey om2(29,4);
  I3Position p2(-5.,-15.,0.);
  I3OMGeo g2;
  g2.position = p2;

  OMKey om3(19,8);
  I3Position p3(105.,50.,11.);
  I3OMGeo g3;
  g3.position = p3;

  OMKey om4(32,20);
  I3Position p4(-333.,-18.,400.);
  I3OMGeo g4;
  g4.position = p4;

  geo.omgeo[om1] = g1; 
  geo.omgeo[om2] = g2; 
  geo.omgeo[om3] = g3; 
  geo.omgeo[om4] = g4; 

  vector<int> goodStrings;
  goodStrings.push_back(21);
  goodStrings.push_back(29);

  I3GeometryConstPtr geo_cptr(new I3Geometry(geo));
  std::pair<double,double> c =
    geo_sel_utils::detector_center(geo_cptr,goodStrings);

  ENSURE(c.first==5.);
  ENSURE(c.second==-5.);
}

TEST(icetray_test_center_shift){

  I3Tray tray;

  std::string strings_to_use("21,29,39,38,30,40,49");
  std::string stations_to_use("21,29,30,38,39,40,47,48,49,50,57,58,59,66,67,74");

  std::string strings_to_exclude("-1:20,22:28,31:37,41:48,50:80");
  std::string stations_to_exclude("-1:20,22:28,31:37,41:46,51:56,60:65,68:73,75:80");

  string icecube_geo(getenv("I3_WORK"));
  icecube_geo += "/phys-services/resources/icecube.geo";
  string amanda_geo(getenv("I3_WORK"));
  amanda_geo += "/phys-services/resources/amanda.geo";

  tray.AddService("I3TextFileGeometryServiceFactory","geoservice")
    ("IceCubeGeoFile",icecube_geo.c_str())
    ("AmandaGeoFile",amanda_geo.c_str());
  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",4)
    ("InstallGeometry",false);
  tray.AddService("I3GeometrySelectorServiceFactory","geo_selector")
    ("StringsToUse",strings_to_use.c_str())
    ("StationsToUse",stations_to_use.c_str())
    ("GeoSelectorName","I3GeometrySelectorService")
    ("ShiftToCenter",true);

  tray.AddModule("I3Muxer","muxer")
    ("GeometryService","I3GeometrySelectorService");
  //I3GeoSelTestModule contains ENSURE statements
  tray.AddModule("I3GeoSelTestModule","geo_test") 
    ("StringsToUse",strings_to_use.c_str())
    ("StringsToExclude",strings_to_exclude.c_str())
    ("StationsToUse",stations_to_use.c_str())
    ("StationsToExclude",stations_to_exclude.c_str())
    ("ShiftX",409.*I3Units::m)
    ("ShiftY",-91.1*I3Units::m)
    ("ShiftZ",0.*I3Units::m);

  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}
