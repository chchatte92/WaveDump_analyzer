#include "root_stuff.h"
#include "adc_histos.h"

#define nsamp_max 1024
//#define nsamp_max 520
//#define nsamp_max 

void adc_histos() {

std::ostringstream strstream;
for(int j=0;j<10;j++) {
strstream.str(std::string());
strstream<<(j+1);
std::string ch_file="event"+strstream.str();
const char *h_name=ch_file.c_str();
event[j] = new TH1D(h_name,"",nsamp_max,-0.5,nsamp_max-0.5);
event[j]->GetXaxis()->CenterTitle();
event[j]->GetXaxis()->SetTitle("Sample [0.2 ns]");
event[j]->GetYaxis()->CenterTitle();
event[j]->GetYaxis()->SetTitle("ADC channel [0.244 mV]");

ch_file="event_r"+strstream.str();
h_name=ch_file.c_str();
event_r[j] = new TH1D(h_name,"",nsamp_max,-0.5,nsamp_max-0.5);
event_r[j]->GetXaxis()->CenterTitle();
event_r[j]->GetXaxis()->SetTitle("Sample [0.2 ns]");
event_r[j]->GetYaxis()->CenterTitle();
event_r[j]->GetYaxis()->SetTitle("ADC channel [0.244 mV]");
}

/* Baseline histos */
for(int j=0;j<32+4;j++) {
strstream.str(std::string());
strstream<<j;
std::string ch_file="baseline_ch"+strstream.str();
const char *h_name=ch_file.c_str();
baseline[j] = new TH1D(h_name,"",200,-100.,100.);
baseline[j]->GetXaxis()->CenterTitle();
baseline[j]->GetXaxis()->SetTitle("Offset ch");
baseline[j]->GetYaxis()->CenterTitle();
baseline[j]->GetYaxis()->SetTitle("Events");

ch_file="QDC_ch"+strstream.str();
h_name=ch_file.c_str();
hi_qdc_pc[j] = new TH1D(h_name,"",110,-1.0,10.);
hi_qdc_pc[j]->GetXaxis()->CenterTitle();
hi_qdc_pc[j]->GetXaxis()->SetTitle("QDC [pC]");
hi_qdc_pc[j]->GetYaxis()->CenterTitle();
hi_qdc_pc[j]->GetYaxis()->SetTitle("Events");

ch_file="ADC_ch"+strstream.str();
h_name=ch_file.c_str();
hi_adc_pc[j] = new TH1D(h_name,"",110,-1.0,100.);
hi_adc_pc[j]->GetXaxis()->CenterTitle();
hi_adc_pc[j]->GetXaxis()->SetTitle("ADC [mV]");
hi_adc_pc[j]->GetYaxis()->CenterTitle();
hi_adc_pc[j]->GetYaxis()->SetTitle("Events");

ch_file="QDC_peak_ch"+strstream.str();
h_name=ch_file.c_str();
hi_peak_qdc_pc[j] = new TH1D(h_name,"",110,-1.0,10.);
hi_peak_qdc_pc[j]->GetXaxis()->CenterTitle();
hi_peak_qdc_pc[j]->GetXaxis()->SetTitle("QDC [pC]");
hi_peak_qdc_pc[j]->GetYaxis()->CenterTitle();
hi_peak_qdc_pc[j]->GetYaxis()->SetTitle("Events");

ch_file="ADC_peak_ch"+strstream.str();
h_name=ch_file.c_str();
hi_peak_adc_pc[j] = new TH1D(h_name,"",110,-1.0,100.);
hi_peak_adc_pc[j]->GetXaxis()->CenterTitle();
hi_peak_adc_pc[j]->GetXaxis()->SetTitle("ADC [mV]");
hi_peak_adc_pc[j]->GetYaxis()->CenterTitle();
hi_peak_adc_pc[j]->GetYaxis()->SetTitle("Events");
}

/* Trigger histos */
trigger = new TH1D("trigger","",nsamp_max,-0.5,(nsamp_max-0.5));
trigger->GetXaxis()->CenterTitle();
trigger->GetXaxis()->SetTitle("Sample [0.2 ns]");
trigger->GetYaxis()->CenterTitle();
trigger->GetYaxis()->SetTitle("Events");

ted = new TH1D("ted","",nsamp_max,-0.5,(nsamp_max-0.5));
ted->GetXaxis()->CenterTitle();
ted->GetXaxis()->SetTitle("Sample [0.2 ns]");
ted->GetYaxis()->CenterTitle();
ted->GetYaxis()->SetTitle("Events");

width = new TH1D("width","",nsamp_max,-0.5,(nsamp_max-0.5));
width->GetXaxis()->CenterTitle();
width->GetXaxis()->SetTitle("Sample [0.2 ns]");
width->GetYaxis()->CenterTitle();
width->GetYaxis()->SetTitle("Events");

/* Noise histos */
noise = new TH1D("noise","",200,-100.,100.);
noise->GetXaxis()->CenterTitle();
noise->GetXaxis()->SetTitle("Amplitude ch");
noise->GetYaxis()->CenterTitle();
noise->GetYaxis()->SetTitle("Events");

noise_mean = new TH1D("noise_mean","",100,-100.,100.);
noise_mean->GetXaxis()->CenterTitle();
noise_mean->GetXaxis()->SetTitle("Amplitude ch");
noise_mean->GetYaxis()->CenterTitle();
noise_mean->GetYaxis()->SetTitle("Events");

noise_drift = new TH2D("noise_drift","",300,0.5,300.5,100,-100.,100.);
noise_drift->GetXaxis()->CenterTitle();
noise_drift->GetXaxis()->SetTitle("subset");
noise_drift->GetYaxis()->CenterTitle();
noise_drift->GetYaxis()->SetTitle("Amplitude ch");

/* Edep histos */
edep = new TH1D("edep","",400,0.,10000.);
edep->GetXaxis()->CenterTitle();
edep->GetXaxis()->SetTitle("Edep [keV]");
edep->GetYaxis()->CenterTitle();
edep->GetYaxis()->SetTitle("Events");

edep_bkg = new TH1D("edep_bkg","",80,-400.,400.);
edep_bkg->GetXaxis()->CenterTitle();
edep_bkg->GetXaxis()->SetTitle("E_{dep} [keV]");
edep_bkg->GetYaxis()->CenterTitle();
edep_bkg->GetYaxis()->SetTitle("Events");

edep_drift = new TH2D("edep_drift","",300,0.5,300.5,80,4500.,6500.); // alpha-peak from Am-241
//edep_drift = new TH2D("edep_drift_0","",300,0.5,300.5,80,1500.,3500.); // t-peak from Li-6
edep_drift->GetXaxis()->CenterTitle();
edep_drift->GetXaxis()->SetTitle("subset");
edep_drift->GetYaxis()->CenterTitle();
edep_drift->GetYaxis()->SetTitle("E_{dep} [keV]");

edep_peak = new TH1D("edep_peak","",400,0.,10000.);
edep_peak->GetXaxis()->CenterTitle();
edep_peak->GetXaxis()->SetTitle("E_{dep} [keV]");
edep_peak->GetYaxis()->CenterTitle();
edep_peak->GetYaxis()->SetTitle("Events");

edep_peak_bkg = new TH1D("edep_peak_bkg","",100,0.,1000.);
edep_peak_bkg->GetXaxis()->CenterTitle();
edep_peak_bkg->GetXaxis()->SetTitle("E_{dep} [keV]");
edep_peak_bkg->GetYaxis()->CenterTitle();
edep_peak_bkg->GetYaxis()->SetTitle("Events");


/* Pulse Shape histos */
pulse = new TH2D("pulse","",nsamp_max,-0.5*0.2,(nsamp_max-0.5)*0.2,10,0.,10.); // QDC in [pC]
pulse->GetXaxis()->CenterTitle();
pulse->GetXaxis()->SetTitle("t [ns]");
pulse->GetYaxis()->CenterTitle();
pulse->GetYaxis()->SetTitle("V_{out} [mV]");

pulse_nrm = new TH1D("pulse_nrm","",10,0.,10.); // QDC in [pC]
//pulse_nrm = new TH1D("pulse_nrm","",10,2000.,3000.); // t-peak from Li-6


/* Charge histos */
qdc_sn = new TH1D("qdc_sn","",100,-0.5,10.-0.5);
qdc_sn->GetXaxis()->CenterTitle();
qdc_sn->GetXaxis()->SetTitle("QDC [pC]");
qdc_sn->GetYaxis()->CenterTitle();
qdc_sn->GetYaxis()->SetTitle("Events");


qdc_b_l = new TH1D("qdc_b_l","",100,-0.5,10.-0.5);
qdc_b_r = new TH1D("qdc_b_r","",100,-0.5,10.-0.5);


/* Rate histo */
dt_events = new TH1D("dt_events","",200,-10.,10.); // 1 kHz - dt=+1 ms
dt_events->GetXaxis()->CenterTitle();
dt_events->GetXaxis()->SetTitle("#Deltat [ms]");
dt_events->GetYaxis()->CenterTitle();
dt_events->GetYaxis()->SetTitle("Events");

}
