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

from icecube import icetray
from icecube.phys_services import I3MuxerModule
from icecube.interfaces import I3EventService, I3GeometryService, I3CalibrationService, I3DetectorStatusService, I3MetaService

class I3Muxer(I3MuxerModule):
	"""A stand-alone wrapper for the I3Muxer module."""
	def __init__(self, event_service, geo_service=None, calibration_service=None, status_service=None):
		# Build up a fake context for module instantiation.
		context = icetray.I3Context()
		
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
		return pop_frame()
		
	def iterframes(self, stream = icetray.I3Frame.Physics):
		while self.more():
			frame = icetray.I3Frame()
			while frame.GetStop != stream:
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
	