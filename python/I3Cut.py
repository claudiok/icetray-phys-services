import logging
import math

from icecube.icetray import I3Module
from icecube import dataclasses

#===============================================================================
class I3CutModule(I3Module):
    """This module

    """
    #___________________________________________________________________________
    def __init__(self, context):
        # Call __init__ method of the I3ConditionalModule class.
        super(I3CutModule, self).__init__(context)
        self.logger = logging.getLogger(__name__)
        #-----------------------------------------------------------------------
        self.range = (0,10)
        self.AddParameter("Range",
            "The range within events are accepted.",
            self.range
        )
        self.cut = None
        self.AddParameter("Cut",
            "This can either be a frame key to an I3Double or equivalend or a python function that takes a frame and return a double",
            self.cut
        )

        self.output_file = None
        self.AddParameter("OutputPath",
            "",
            self.output_file
        )
        def weight(frame):
            return 1.0
        self.weight = weight
        self.AddParameter("Weight",
            "A python function that takes a frame and calculates the event weight. By default it returns the value 1.0.",
            self.weight
        )
        
        self.dry_run = False
        self.AddParameter("DryRun",
            "If set to false the cut is not applied.",
            self.dry_run
        )
        
        self.AddOutBox("OutBox")
        
        self.n_frames_tot = 0                            
        self.n_frames_pass = 0
        self.n_bins = 50
        self.data = list()
        self.data_weights = list()
        self.weight_sum_passed = 0
        self.weight_sum_tot = 0
        self.xlabel = "x observable"
    #___________________________________________________________________________
    def Configure(self):
        self.range                                = self.GetParameter("Range")
        self.cut                                  = self.GetParameter("Cut")
        self.output_file                          = self.GetParameter("OutputPath")
        self.weight                               = self.GetParameter("Weight")
        self.dry_run                              = self.GetParameter("DryRun")
        if(self.range[0] > self.range[1]):
            self.reverse = True
        else:
            self.reverse = False
        
        if(self.cut == None):
            raise ValueError('%s: Cut not specified! A frame key to an I3Double or a python function must be passed.'%self.name)
        
        if(type(self.cut) == str):
            self.string_cut = True
        else:
            self.string_cut = False
    #___________________________________________________________________________
    def Physics(self, frame):
        
        #Collecting data and weight data
        if(self.string_cut):
            data_tmp = frame[self.cut].value
            
        else:
            data_tmp = self.cut(frame)
            
        weight_tmp = self.weight(frame)
        self.data_weights.append(weight_tmp)
        self.data.append(data_tmp)
        
        #applying the actuall cut
        if(not self.reverse and (data_tmp > self.range[0] and data_tmp < self.range[1])):
            self.n_frames_pass +=1
            self.weight_sum_passed +=weight_tmp
            if(not self.dry_run):
                self.PushFrame(frame)
        elif(self.reverse and (data_tmp > self.range[0] or data_tmp < self.range[1])):
            self.n_frames_pass +=1
            self.weight_sum_passed +=weight_tmp
            if(not self.dry_run):
                self.PushFrame(frame)
                
        if(self.dry_run):
            self.PushFrame(frame)
            
        self.weight_sum_tot +=weight_tmp
        self.n_frames_tot +=1
        
    def Finish(self):
        import numpy as np
        import matplotlib.pyplot as plt

    
        self.data = np.array(self.data)
        self.data_weights = np.array(self.data_weights)
        x_min = np.min(self.data)
        x_max = np.max(self.data)
        
        x = np.linspace(x_min,x_max,self.n_bins)

        if(self.output_file != None):
            bin_values, binEdges = np.histogram(self.data, weights = self.data_weights, bins=self.n_bins,range=(x_min,x_max))
            bincenters = 0.5*(binEdges[1:]+binEdges[:-1])
            bin_values_std = np.sqrt(bin_values)
            plt.figure()
            
            plt.plot(bincenters,bin_values,'bo')
            plt.errorbar(bincenters,bin_values, yerr= bin_values_std,fmt='bo')
            
            plt.axvline(self.range[0], color='k', ls='solid')
            plt.axvline(self.range[1], color='k', ls='solid')
            
            plt.title(self.name)
            plt.xlabel(self.xlabel)
            plt.ylabel("A.U")
            
            if(self.output_file != None):
                import os
                plt.savefig(os.path.join(self.output_file,self.name+".png"))
            else:
                plt.savefig(self.name+".png")
        #Print some stats at the end
        print("#######################################")
        print("I3Cut Module: %s"%self.name)
        print("Acceptance range (%f,%f)"%(self.range[0],self.range[1]))
        print("Frames seen: %d"%self.n_frames_tot)
        print("Frames passed: %d"%self.n_frames_pass)
        print("Frames rejected: %d"%(self.n_frames_tot-self.n_frames_pass))
        print("Fraction passed (weighted): %f"%(self.weight_sum_passed/self.weight_sum_tot))
        print("Mean: %f"%np.average(self.data,weights = self.data_weights))
        #print("Mean: %f"%np.mean(self.data))
        print("RMS: %f"%np.sqrt(sum((self.data-np.mean(self.data))**2)/len(self.data)))
        print("---------------------------------------")