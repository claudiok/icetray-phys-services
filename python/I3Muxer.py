# -*- coding: utf-8 -*-
#
# copyright  (C) 2010
# The Icecube Collaboration
# 
# $Id$
# 
# @version $Revision$
# @date $LastChangedDate$
# @author Jakob van Santen <vansanten@wisc.edu> Last changed by: $LastChangedBy$

from icecube import icetray, dataio
from icecube.phys_services import I3MuxerModule
from icecube.interfaces import I3EventService, I3GeometryService, I3CalibrationService, I3DetectorStatusService, I3MetaService
import types, operator

class I3Muxer(I3MuxerModule):
	"""
A stand-alone wrapper for the I3Muxer module.

The I3Muxer wrapper may be configured by explicitly passing the Event, Geometry,
Calibration, and Status services, or by passing a list of I3 files to be read.

Explicit services:

	reader = dataio.I3ReaderService(['GCD.i3.gz', 'foo.i3.gz'], [], True)
	muxer = phys_services.I3Muxer(reader)

List of files (implicitly creates an I3ReaderService):

	muxer = phys_services.I3Muxer(['GCD.i3.gz', 'foo.i3.gz'])

List of lists of files (implicitly creates an I3MuxingReaderService):

	muxer = phys_services.I3Muxer([['GCD.i3.gz'], ['run1.i3'], ['run2_part1.i3', 'run2_part2.i3']])

	"""
	def __init__(self, event_service, geo_service=None, calibration_service=None, status_service=None):
		# Build up a fake context for module instantiation.
		context = icetray.I3Context()
		
		# If the event service is not an I3EventService, try to construct one.
		if not isinstance(event_service, I3EventService):
			listlike = (types.ListType, types.TupleType)
			if not isinstance(event_service, listlike):
				raise TypeError, "event_service must be a list or an instance of I3EventService"
			if reduce(operator.and_, map(lambda i: isinstance(i, listlike), event_service)):
				# a list-of-lists: employ the muxing reader
				event_service = dataio.I3MuxingReaderService(event_service, [], True)
			else:
				# vanilla reader
				event_service = dataio.I3ReaderService(event_service, [], True)
		
		# Install services.
		for ptr, klass in [(event_service, I3EventService),
						   (event_service, I3MetaService),
						   (geo_service, I3GeometryService),
						   (calibration_service, I3CalibrationService),
						   (status_service, I3DetectorStatusService)]:
			if ptr is None:
				ptr = event_service
			klass.Install(ptr, context, klass.__name__)
		
		# Module configuration parameters go here.
		config = icetray.I3Configuration()
		context['I3Configuration'] = config
		
		# Fake outboxes.
		outboxes = icetray.Connections()
		context['OutBoxes'] = outboxes
		
		I3MuxerModule.__init__(self, context)
		self.Configure()
		
		self.next_frame = I3MuxerModule.PopFrame(self)
	
	def __iter__(self):
		return self
	
	def next(self):
		if self.next_frame is None:
			raise StopIteration
		return self.pop_frame()
		
	def iterframes(self, stream = icetray.I3Frame.Physics):
		while self.more():
			frame = icetray.I3Frame()
			while frame.GetStop() != stream:
				frame = self.next()
			yield frame
	
	def more(self):
		return (self.next_frame is not None)
			
	def pop_frame(self):
		frame = self.next_frame
		self.next_frame = I3MuxerModule.PopFrame(self)
		return frame
		
	def pop_physics(self):
		frame = icetray.I3Frame()
		while frame.GetStop != icetray.I3Frame.Physics:
			frame = self.next()
		return frame
	