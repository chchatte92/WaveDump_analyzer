#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//#include <cmath>

#include "analyze_adc.h"

#include "root_stuff.h"
#include "adc_histos_ext.h"

using namespace std;

void analyze_adc(int iev, unsigned int ich, unsigned int adc_ts, float *adc_val
, unsigned int *trig_val, double *qdc_pc, double *adc_mv) {


//if(iev>10000) return;

// init
int j,k;

trig_val[0]=0; // init trig value


led_trig=0;
cfd_trig=0;
trig=0;
trig_cor=0;
inx_end=0;
stop_adc=0;

edepv=0.0;
adc_max=0.0;
adc_max_mean=0.0;
adc_max_bkg=0.0;
adc_zero_mean=0.0;


// init event
adc_peak_value=0.0;
nsat=0;
nsat_max=0;
nsat_tot=0;
jmax=0;
edep_kev=0.0;
edepv=0.0;
base_line_a=0.0;
jled=0;



//cout<<"step1"<<endl;


jpeak=0;
for(j=0;j<nsamp;j++) {
//clean ADC value (remove baseline and invert if necessary)
//adcv[j]=0.0;
adcv[j]=(double)adc_val[j]-ch_offset[ich];
//adcv[j]=ch_offset-(double)adc_val[j];


baseline[ich]->Fill((double)adcv[j]); // first approx. - including peaks


//if(j<(sync_trig_delay-10)) base_line_a+=adcv[j];

// event histos for examples
if(iev<10&&ich==0) { // for channel 0 only
event[iev]->SetBinContent(j+1,(double)adc_val[j]);
event_r[iev]->SetBinContent(j+1,(double)adcv[j]);
//cout<<"wave: "<< iev<<" "<< ich<<" "<<j<<" "<<adc_val[j] <<" "<<adcv[j]<<endl;
}



  } // sample loop












//cout<<"step2"<<endl;

//base_line_a/=(double)(sync_trig_delay-10);

//if(base_line_a<(-3.0*noise_rms) || base_line_a>(3.0*noise_rms)
//|| adc_peak_value<peak_th 
//|| nsat_max<=ncut_min||nsat_tot>=ncut_max) cout<<"nsat_max: "<<iev+1<<" "
//<<jmax<<" "<<nsat_max<<" "<<nsat_tot<<" "<<base_line_a<<" "<<adc_peak_value<<endl;


//if(base_line_a<(-3.0*noise_rms) || base_line_a>(3.0*noise_rms)) cout<<"noisy baseline: "<<iev+1<<" "
//<<ich<<" "<<base_line_a<<endl;


//if(nsat_tot>=ncut_max) cout<<"noisy signal: "<<iev+1<<" "<<ich<<" "<<nsat_tot<<endl;





//cout<<"step3"<<endl;

//cout<<"step4"<<endl;

//cout<<"step5"<<endl;


//cout<<"step6"<<endl;






// Noise histos
adc_max_bkg=0.0;
nmp=0;
adc_zero_mean=0.0;

for(j=0;j<nsamp;j++) {
noise->Fill(adcv[j]);
//noise_drift->Fill((1.0+((double)n_coin)/((double)n_coin_bin)),adcv[j]);
noise_drift->Fill((1.0+((double)iev)/((double)n_coin_bin)),adcv[j]);
if(adcv[j]>adc_max_bkg) adc_max_bkg=adcv[j];
nmp++;
adc_zero_mean+=adcv[j];
}
if(nmp>0) adc_zero_mean/=(double)nmp;
else adc_zero_mean=0.0;
//cout<<"adc_zero_mean: "<<(i+1)<<" "<<(qdc_sig*mvns2pc*pc2kev/amp_gain_drifted)
//<<" "<<(jted-js)<<" "<<peak_width
//<<" "<<(trig-djt)<<" "<<adc_zero_mean<<endl;

//cout<<"step6"<<endl;






}
