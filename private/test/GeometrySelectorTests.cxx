#include <I3Test.h>
#include "phys-services/geo-selector/I3GeometrySelector.h"
#include "phys-services/geo-selector/I3GeoSelTestModule.h"
#include "phys-services/geo-selector/GeoSelUtils.h"
#include "root-icetray/RootI3Tray.h"
#include "phys-services/source/I3DefaultPhysicsSource.h"
#include "phys-services/source/I3DefaultGeometrySource.h"


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

TEST(icetray_test_soon){

  RootI3Tray tray;

  std::string to_use("21,29,39");

  string icecube_geo(getenv("I3_WORK"));
  icecube_geo += "/phys-services/resources/icecube.geo";
  string amanda_geo(getenv("I3_WORK"));
  amanda_geo += "/phys-services/resources/amanda.geo";

  cout<<icecube_geo<<endl;
  cout<<amanda_geo<<endl;

  tray.AddModule("I3DefaultPhysicsSource","physsource")
    ("EventsToReturn",1);
  tray.AddModule("I3FileGeometrySource","geosource")
    ("IceCubeGeoFile",icecube_geo.c_str())
    ("AmandaGeoFile",amanda_geo.c_str());
  tray.AddModule("I3GeometrySelector","geo_selector")
    ("StringsToUse",to_use.c_str());
  //I3GeoSelTestModule contains ENSURE statements
  tray.AddModule("I3GeoSelTestModule","geo_test") 
    ("StringsToUse",to_use.c_str());
  tray.Execute();
  tray.Finish();
}