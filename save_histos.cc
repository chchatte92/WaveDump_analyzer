#include<TFile.h>
#include "root_stuff.h"
#include "adc_histos_ext.h"

#define nsamp_max 480


void save_histos() {

TFile *hist_file = new TFile("adc_histos.root","recreate");
hist_file->cd();


for(int j=0;j<10;j++) {
event[j]->Write();
event_r[j]->Write();
}

for(int j=0;j<32+4;j++) {
baseline[j]->Write();
hi_qdc_pc[j]->Write();
hi_adc_pc[j]->Write();
hi_peak_qdc_pc[j]->Write();
hi_peak_adc_pc[j]->Write();
}

//edep->Write();

trigger->Write();
ted->Write();
width->Write();

noise->Write();
noise_mean->Write();
noise_drift->Write();


edep->Write();
edep_bkg->Write();
edep_drift->Write();
edep_peak->Write();
edep_peak_bkg->Write();




pulse->Write();
pulse_nrm->Write();



qdc_sn->Write();


qdc_b_l->Write();
qdc_b_r->Write();

dt_events->Write();


hist_file->Close();

}
