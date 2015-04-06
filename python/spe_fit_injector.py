import json

from icecube import icetray
from icecube import dataclasses

class I3SPEFitInjector(icetray.I3Module):
    ''' This module loads the structures in dataclasses using values
        in the JSON file provided by the calibration group.
        https://wiki.icecube.wisc.edu/index.php/SPE_recalibration
    '''
    def __init__(self, context):
        icetray.I3Module.__init__(self, context)

        self.AddOutBox("OutBox")
        self.AddParameter("Filename", "JSON file with SPE fit data", "");

    def Configure(self):
        self.filename = self.GetParameter("Filename")
        f = open(self.filename)
        fit_dict = json.load(f)

        self.fit_dict = dict()
        for key, data in fit_dict.iteritems() :

            # we don't really use the validity date in offline anymore
            if key == 'valid_date' : continue

            # we've decided to skip entries that contain invalid data altogether
            if bool(data['JOINT_fit']['valid']) == False : continue;
                
            string = int(key.split(",")[0])
            om = int(key.split(",")[1])

            omkey = icetray.OMKey(string, om)

            atwd_mean = float(data['ATWD_fit']['gaus_mean'])
            fadc_mean = float(data['FADC_fit']['gaus_mean'])
            exp_amp = float(data['JOINT_fit']['exp_norm'])
            exp_width = float(data['JOINT_fit']['exp_scale']) 
            gaus_amp = float(data['JOINT_fit']['gaus_norm'])
            gaus_mean = float(data['JOINT_fit']['gaus_mean'])
            gaus_width = float(data['JOINT_fit']['gaus_stddev'])
                        
            self.fit_dict[omkey] = {'atwd_mean' : atwd_mean,
                                    'fadc_mean' : fadc_mean,
                                    'exp_amp': exp_amp,
                                    'exp_width': exp_width,
                                    'gaus_amp': gaus_amp,
                                    'gaus_mean': gaus_mean,
                                    'gaus_width': gaus_width
                                    }
        
    def Calibration(self, frame):

        cal = frame['I3Calibration']
        domcal = cal.dom_cal

        for omkey, i3domcal in domcal.iteritems() :
            if omkey in self.fit_dict :
                i3domcal.mean_atwd_charge = self.fit_dict[omkey]['atwd_mean']
                i3domcal.mean_fadc_charge = self.fit_dict[omkey]['fadc_mean']

                spe_charge_dist = dataclasses.SPEChargeDistribution()
                spe_charge_dist.exp_amp = self.fit_dict[omkey]['exp_amp']
                spe_charge_dist.exp_width = self.fit_dict[omkey]['exp_width']
                spe_charge_dist.gaus_amp = self.fit_dict[omkey]['gaus_amp']
                spe_charge_dist.gaus_mean = self.fit_dict[omkey]['gaus_mean']
                spe_charge_dist.gaus_width = self.fit_dict[omkey]['gaus_width']

                cal.dom_cal[omkey].combined_spe_charge_distribution = spe_charge_dist
                
        self.PushFrame(frame)
