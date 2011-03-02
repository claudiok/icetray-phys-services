#!/usr/bin/env python

from icecube import icetray, dataclasses, dataio, phys_services
from icecube.icetray import I3Units
import I3Tray
import os, unittest

# The test to run:
phys_frames = 0
max_phys_frames = 3
class DAQFrameSplitting(unittest.TestCase):
	def testPhysFrame(self):
		global phys_frames
		self.assert_("I3Geometry" in self.frame)
		self.assert_("I3Calibration" in self.frame)
		self.assert_("I3DetectorStatus" in self.frame)
		self.assert_("InIceRawData" in self.frame)
		self.assert_(len(self.frame["InIceRawData"]) == 1)
		self.assert_("DrivingTime" in self.frame)
		self.assert_("I3EventHeader" in self.frame)
		self.assertEquals(self.frame["I3EventHeader"].SubEventID, phys_frames)
		self.assertEquals(self.frame["I3EventHeader"].SubEventID, self.frame["TriggerID"].value)
		self.assertEquals(self.frame["I3EventHeader"].EventID, frame["I3EventHeader"].EventID)
		self.assertEquals(self.frame["I3EventHeader"].RunID, frame["I3EventHeader"].RunID)
		phys_frames += 1
	def Finish(self):
		self.assertEquals(phys_frames, max_phys_frames)

# Manufacture a file. 
fname = os.environ["I3_BUILD"] + "/daq_frame_test.i3.gz"
if os.path.exists(fname):
	os.unlink(fname)
the_time = dataclasses.I3Time()
the_time.SetUTCCalDate(1919, 1, 15, 0, 0, 0, 0)
f = dataio.I3File(fname, "w")
geo = dataclasses.I3Geometry()
geo.startTime = the_time - 100
geo.endTime = the_time + 100
calib = dataclasses.I3Calibration()
calib.startTime = the_time - 100
calib.endTime = the_time + 100
status = dataclasses.I3DetectorStatus()
status.startTime = the_time - 100
status.endTime = the_time + 100
frame = icetray.I3Frame(icetray.I3Frame.Geometry)
frame['I3Geometry'] = geo
f.push(frame)
frame = icetray.I3Frame(icetray.I3Frame.Calibration)
frame['I3Calibration'] = calib
f.push(frame)
frame = icetray.I3Frame(icetray.I3Frame.DetectorStatus)
frame['I3DetectorStatus'] = status
f.push(frame)
frame = icetray.I3Frame(icetray.I3Frame.DAQ)
dlsm = dataclasses.I3DOMLaunchSeriesMap()
dlsm[icetray.OMKey(7,42)] = dataclasses.I3DOMLaunchSeries()
frame['InIceRawData'] = dlsm
t = dataclasses.I3Time()
t.SetUTCCalDate(1919, 1, 15, 0, 0, 0, 0)
frame['DrivingTime'] = t
header = dataclasses.I3EventHeader()
header.RunID = 7
header.EventID = 42
header.SubEventID = 0
header.StartTime = t
header.EndTime = t+10*I3Units.microsecond
frame['I3EventHeader'] = header
f.push(frame)
f.close()

class FrameSplitter(icetray.I3Module,phys_services.I3Splitter):
	def __init__(self, context):
		icetray.I3Module.__init__(self, context)
		phys_services.I3Splitter.__init__(self, context)
		self.AddOutBox('OutBox')
	def Configure(self):
		pass
	def DAQ(self, frame):
		print 'DAQ Frame'
		self.PushFrame(frame)
		for i in range(0, max_phys_frames):
			subframe = self.GetNextSubEvent(frame)
			subframe['TriggerID'] = icetray.I3Int(i)
			self.PushFrame(subframe)
		return True
		
# 
tray = I3Tray.I3Tray()
tray.AddModule('I3Reader', 'reader', filename=fname)
tray.AddModule(FrameSplitter, 'splitter')
tray.AddModule(icetray.I3TestModuleFactory(DAQFrameSplitting), 'testy')
tray.AddModule('TrashCan', "yeswecan")
tray.Execute()
tray.Finish()

