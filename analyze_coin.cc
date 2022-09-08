#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//#include <cmath>

#include "analyze_coin.h"

#include "root_stuff.h"
#include "coin_histos_ext.h"

using namespace std;

void analyze_coin(int iev, unsigned long long adc_ts[2], unsigned long long tdc_ts[2], unsigned int stop_adc[2]
,unsigned int led_trig[2], double edep_adc[2], double edep_adc_bkg[2], double t_peak[2]) {


// Anti-coincidence events with only one channel above threshold
if(edep_adc[0]>coin_edep_min[0]&&edep_adc[1]<=coin_edep_min[1]
  &&fabs(edep_adc_bkg[0])<(3.*edep_noise_rms[0])
  &&fabs(edep_adc_bkg[1])<(3.*edep_noise_rms[1])) edep_xor[0]->Fill(edep_adc[0]);
if(edep_adc[0]<=coin_edep_min[0]&&edep_adc[1]>coin_edep_min[1]
  &&fabs(edep_adc_bkg[0])<(3.*edep_noise_rms[0])
  &&fabs(edep_adc_bkg[1])<(3.*edep_noise_rms[1])) edep_xor[1]->Fill(edep_adc[1]);


// Some Timestamps may be missing, discard these events (cannot be correlated)
//if(adc_ts[0]==0||adc_ts[1]==0||tdc_ts[0]==0||tdc_ts[1]==0) {
if(0) {
 cout<<"miss.TS: "<<iev+1<<" "<<adc_ts[0]<<" "<<adc_ts[1]<<" "<<tdc_ts[0]<<" "<<tdc_ts[1]<<endl;
} else { // there are all 4 timestamps present


// most of events without timestams have problems with both TDCs
if(tdc_ts[0]==0) tdc_ts[0]=adc_ts[0];
if(tdc_ts[1]==0) tdc_ts[1]=adc_ts[1];


//cout<<"coin: "<<iev+1<<" "
//<<(adc_ts[0]-adc_ts[1])<<" "<<dts_adc<<" "
//<<(tdc_ts[0]-tdc_ts[1])<<" "<<dts_tdc<<" "
//<<(tdc_ts[0]-adc_ts[0])<<" "<<dts_tdc_adc_0<<" "
//<<(tdc_ts[1]-adc_ts[1])<<" "<<dts_tdc_adc_1<<" "
//<<adc_ts[0]<<" "<<adc_ts[1]<<" "
//<<tdc_ts[0]<<" "<<tdc_ts[1]<<" "
//<<edep_adc[0]<<" "<<edep_adc[1]<<" "
//<<edep_adc_bkg[0]<<" "<<edep_adc_bkg[1]
//<<endl;

// try to correct
//if(tdc_ts[1]!=tdc_ts[0]&&adc_ts[1]==adc_ts[0]) tdc_ts[1]=tdc_ts[0];

// Timestamps are unsigned long long (data is 48 bits (long is 32 bits, long long is 64 bits))
// assume the difference is less than int size (non-null timestamps only)
int dts_adc=0;
if(adc_ts[0]>adc_ts[1]) dts_adc=(int)(adc_ts[0]-adc_ts[1]);
if(adc_ts[0]<adc_ts[1]) dts_adc=-(int)(adc_ts[1]-adc_ts[0]);
int dts_tdc=0;
if(tdc_ts[0]>tdc_ts[1]) dts_tdc=(int)(tdc_ts[0]-tdc_ts[1]);
if(tdc_ts[0]<tdc_ts[1]) dts_tdc=-(int)(tdc_ts[1]-tdc_ts[0]);
int dts_tdc_adc_0=0;
if(tdc_ts[0]>adc_ts[0]) dts_tdc_adc_0=(int)(tdc_ts[0]-adc_ts[0]);
if(tdc_ts[0]<adc_ts[0]) dts_tdc_adc_0=-(int)(adc_ts[0]-tdc_ts[0]);
int dts_tdc_adc_1=0;
if(tdc_ts[1]>adc_ts[1]) dts_tdc_adc_1=(int)(tdc_ts[1]-adc_ts[1]);
if(tdc_ts[1]<adc_ts[1]) dts_tdc_adc_1=-(int)(adc_ts[1]-tdc_ts[1]);

//cout<<"step1"<<endl;

// time interval between two triggers
// no TDC correction, all timestamps assumed to be the same
//delta_t=(double)led_trig[1]*0.200-(double)led_trig[0]*0.200;
// with timewalk correction
delta_t=((double)led_trig[1]+t_peak[1])*0.200-((double)led_trig[0]+t_peak[0])*0.200;
// no TDC correction, only ADC Timestamps
//delta_t_ts=((double)adc_ts[1]*4.800+(double)led_trig[1]*0.200)-((double)adc_ts[0]*4.800+(double)led_trig[0]*0.200);
//delta_t_ts=-(double)dts_adc*4.800+(double)led_trig[1]*0.200-(double)led_trig[0]*0.200;
// with timewalk correction
delta_t_ts=-(double)dts_adc*4.800+((double)led_trig[1]+t_peak[1])*0.200-((double)led_trig[0]+t_peak[1])*0.200;
// TDC correction: include only stop ADC clock (all timestamps assumed to be the same)
delta_t_gpx_stop=((double)stop_adc[1]*0.027+(double)led_trig[1]*0.200)-((double)stop_adc[0]*0.027+(double)led_trig[0]*0.200);
// TDC correction: include only TDC timestamps
//delta_t_gpx_ts=((double)led_trig[1]*0.200-(double)(tdc_ts[1]+1)*4.800)-((double)led_trig[0]*0.200-(double)(tdc_ts[0]+1)*4.800);
delta_t_gpx_ts=(double)dts_tdc*4.800+
(double)led_trig[1]*0.200-(double)led_trig[0]*0.200;
// TDC correction: include only stop ADC clock and ADC timestamp (TDC timestamps assumed to be the same)
//delta_t_gpx_1=
//((double)adc_ts[1]*4.800+(double)stop_adc[1]*0.027+(double)led_trig[1]*0.200)-
//((double)adc_ts[0]*4.800+(double)stop_adc[0]*0.027+(double)led_trig[0]*0.200);
delta_t_gpx_1=-(double)dts_adc*4.800+
((double)stop_adc[1]*0.027+(double)led_trig[1]*0.200)-
((double)stop_adc[0]*0.027+(double)led_trig[0]*0.200);
// TDC correction: include ADC and TDC timestamps (not TDC Stop)
//delta_t_gpx_2=
//((double)adc_ts[1]*4.800+(double)led_trig[1]*0.200-(double)(tdc_ts[1]+1)*4.800)-
//((double)adc_ts[0]*4.800+(double)led_trig[0]*0.200-(double)(tdc_ts[0]+1)*4.800);
delta_t_gpx_2=((double)dts_tdc-(double)dts_adc)*4.800+
(double)led_trig[1]*0.200-(double)led_trig[0]*0.200;
// TDC correction: final
// t_ext^trig=(T_stamp^TDC+1)*4.8ns - TDC*27ps
// t_ADC^trig=T_stamp^ADC*4.8ns + (N_samp^Prebuf+N_samp^trig)*200ps
// Delta t = (t_ADC^trig - t_ext^trig)
//delta_t_gpx=
//((double)adc_ts[1]*4.800+(double)led_trig[1]*0.200-((double)(tdc_ts[1]+1)*4.800-(double)stop_adc[1]*0.027))-
//((double)adc_ts[0]*4.800+(double)led_trig[0]*0.200-((double)(tdc_ts[0]+1)*4.800-(double)stop_adc[0]*0.027));
// good
//delta_t_gpx=((double)dts_tdc-(double)dts_adc)*4.800+
//((double)led_trig[1]*0.200+(double)stop_adc[1]*0.027)-
//((double)led_trig[0]*0.200+(double)stop_adc[0]*0.027);
// with timewalk correction
delta_t_gpx=((double)dts_tdc-(double)dts_adc)*4.800+
(((double)led_trig[1]+t_peak[1])*0.200+(double)stop_adc[1]*0.027)-
(((double)led_trig[0]+t_peak[0])*0.200+(double)stop_adc[0]*0.027);


if(tdc_ts[1]!=tdc_ts[0]&&adc_ts[1]==adc_ts[0]) cout<<"TDC TS shift: "<<iev+1
<<" "<<(tdc_ts[1]-tdc_ts[0])<<" "<<(adc_ts[0]-tdc_ts[0])
<<" "<<delta_t
<<" "<<delta_t_gpx<<endl;

//cout<<"Timestamps: "<<iev+1<<" "<<adc_ts[0]<<" "<<adc_ts[1]<<" "<<tdc_ts[0]<<" "<<tdc_ts[1]<<endl;

// abs() transforms 64-bit LONG INT into 32-bit INT removing
// if(__gnu_cxx::abs(adc_ts[0]-adc_ts[1])>1||__gnu_cxx::abs(tdc_ts[0]-tdc_ts[1])>1||
// __gnu_cxx::abs(tdc_ts[0]-adc_ts[0])>1||__gnu_cxx::abs(tdc_ts[1]-adc_ts[1])>1) {
 if(abs(dts_adc)>1||abs(dts_tdc)>1||abs(dts_tdc_adc_0)>1||abs(dts_tdc_adc_1)>1) {

cout<<"BAD coincidence: "<<iev+1<<" "<<adc_ts[0]<<" "<<adc_ts[1]<<" "<<tdc_ts[0]<<" "<<tdc_ts[1]<<" "
<<delta_t_gpx<<" "
<<endl;

 } else { // Timestamps within 1 clock tick

//cout<<edep_adc[0]<<" "<<edep_adc[1]<<" "<<edep_adc_bkg[0]<<" "<<edep_adc_bkg[1]
//<<" "<<coin_edep_min[0]<<" "<<coin_edep_min[1]<<" "<<(3.*edep_noise_rms[0])<<" "<<(3.*edep_noise_rms[1])
//<<" "<<fabs(edep_adc_bkg[0])<<" "<<fabs(edep_adc_bkg[1])
//<<endl;

// Take only peak events
  if(edep_adc[0]>coin_edep_min[0]&&edep_adc[1]>coin_edep_min[1]
  &&fabs(edep_adc_bkg[0])<(3.*edep_noise_rms[0])
  &&fabs(edep_adc_bkg[1])<(3.*edep_noise_rms[1])) {

n_coin++;

//edep_coin[0]->Fill(edep_adc[0]);
//edep_coin[1]->Fill(edep_adc[1]);
edep_tot_coin->Fill((edep_adc[0]+edep_adc[1]));
edep_n->Fill((edep_adc[0]+edep_adc[1]-q_tot));

//cout<<"neu: "<<iev+1<<" "<<adc_ts[0]<<" "<<adc_ts[1]<<" "<<tdc_ts[0]<<" "<<tdc_ts[1]
//<<" "<<stop_adc[0]<<" "<<stop_adc[1]<<" "<<led_trig[0]<<" "<<led_trig[1]<<" "<<delta_t_ts<<" "<<delta_t_gpx_stop<<endl;
//<<" "<<stop_adc[0]<<" "<<stop_adc[1]<<" "<<led_trig[0]<<" "<<led_trig[1]<<" "<<delta_t_ts<<" "<<delta_t_gpx_ts<<endl;

//    if((edep_adc[0]+edep_adc[1]-q_tot)>500.&&(edep_adc[0]+edep_adc[1]-q_tot)<1500.) {
//    if((edep_adc[0]+edep_adc[1]-q_tot)>-1500.&&(edep_adc[0]+edep_adc[1]-q_tot)<500.) {
    edep_coin[0]->Fill(edep_adc[0]);
    edep_coin[1]->Fill(edep_adc[1]);
//}

    if(abs(delta_t_gpx-dt_mean)<(3.0*dt_rms)) {
edep_cor->Fill(edep_adc[0],edep_adc[1]);
    }

edep_dt_cor[0]->Fill(edep_adc[0],(delta_t_gpx-dt_mean));
edep_dt_cor[1]->Fill(edep_adc[1],(delta_t_gpx-dt_mean));

//cout<<"fill.dt: "<<delta_t<<endl;
dt->Fill(delta_t);// no TDC correction, all timestamps assumed to be the same
dt_ts->Fill(delta_t_ts);// no TDC correction, only ADC Timestamps
dt_gpx_stop->Fill(delta_t_gpx_stop);// TDC correction: include only stop ADC clock (all timestamps assumed to be the same)
dt_gpx_ts->Fill(delta_t_gpx_ts);// TDC correction: include only TDC timestamps
dt_gpx_1->Fill(delta_t_gpx_1);// TDC correction: include only stop ADC clock and ADC timestamp (TDC timestamps assumed to be the same)
dt_gpx_2->Fill(delta_t_gpx_2);// TDC correction: include ADC and TDC timestamps (not TDC Stop)
dt_gpx->Fill(delta_t_gpx);// TDC correction: final

  } else {
//file_bad_events<<iev+1<<"d;";
  }



 } // end of Timestamp correlation if

} // endif non-null Timestamp check

}
