{
gSystem->Load("libPhysics.so");
gSystem->Load("libicetray.so");
gSystem->Load("libdataclasses.so");
gSystem->Load("libroot-icetray.so");
gSystem->Load("libphys-services.so");
using namespace I3Units;

cout <<"Creating I3ContainedTrack..."<<endl;
I3DoubleBang track1;
//track1 = I3DoubleBangPtr(new I3DoubleBang);
cout <<"Creating I3BasicTrack..."<<endl;
I3BasicTrack track2;
//track2 = I3BasicTrack(new I3BasicTrack);

cout <<"Setting values for tracks..."<<endl;
track1.SetStartPos(0,0,0);
track1.SetStartT(10);
cout<<"Direction of track1 is 0,0"<<endl;
track1.SetDir(0,0);    // zenith=0 ==> theta=180 ==> going down
track1.SetLength(2);    // track goes only down to the x-y plane

track2.SetPos(0,0,0);
cout<<"Direction of track2 is 45,0"<<endl;
track2.SetDir(45*deg,0);

cout <<"Creating a new I3Calculator object..."<<endl;
I3CalculatorImpl calc;

cout<<"Angle between the tracks: "<<calc.AngleDiff(track1,track2);
cout<<" [should be 45]"<<endl;

}
