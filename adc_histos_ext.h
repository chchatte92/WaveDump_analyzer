#ifndef ADC_HISTS_EXT
#define ADC_HISTS_EXT

extern TH1D *event[10];
extern TH1D *event_r[10];

extern TH1D *baseline[32+4];
extern TH1D *hi_qdc_pc[32+4];
extern TH1D *hi_adc_pc[32+4];
extern TH1D *hi_peak_qdc_pc[32+4];
extern TH1D *hi_peak_adc_pc[32+4];

extern TH1D *trigger;
extern TH1D *ted;
extern TH1D *width;

extern TH1D *noise;
extern TH1D *noise_mean;
extern TH2D *noise_drift;

extern TH1D *edep;
extern TH1D *edep_bkg;
extern TH2D *edep_drift;
extern TH1D *edep_peak;
extern TH1D *edep_peak_bkg;

extern TH2D *pulse;
extern TH1D *pulse_nrm;

extern TH1D *qdc_sn;
extern TH1D *qdc_b_l;
extern TH1D *qdc_b_r;

extern TH1D *dt_events;

//void adc_histos();

#endif
