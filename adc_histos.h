#ifndef ADC_HISTS
#define ADC_HISTS

#include <string>
#include <sstream>

TH1D *event[10];
TH1D *event_r[10];

TH1D *baseline[32+4];
TH1D *hi_qdc_pc[32+4];
TH1D *hi_adc_pc[32+4];
TH1D *hi_peak_qdc_pc[32+4];
TH1D *hi_peak_adc_pc[32+4];

TH1D *trigger;
TH1D *ted;
TH1D *width;

TH1D *noise;
TH1D *noise_mean;
TH2D *noise_drift;

TH1D *edep;
TH1D *edep_bkg;
TH2D *edep_drift;
TH1D *edep_peak;
TH1D *edep_peak_bkg;

TH2D *pulse;
TH1D *pulse_nrm;

TH1D *qdc_sn;
TH1D *qdc_b_l;
TH1D *qdc_b_r;

TH1D *dt_events;

#endif
