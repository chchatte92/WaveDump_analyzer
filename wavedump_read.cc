#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include <unistd.h>
#include <cstdio>
#include <time.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>

//#include <pthread.h>
//#include <limits.h>

#include "io_manager.h"



#include "uti.h"


#include "root_stuff.h"
#include "adc_histos_ext.h"


using namespace std;

// configuration globals
bool save_asci_data=false;

//extern int errno;

bool debug_flag=false;
bool iom_debug_flag=false;
//bool iom_debug_flag=true;


bool count_in_enable=true;
int count_in_first=0;
int count_in_last=0;



// statistics
int ntot_adc_headers=0;
int ntot_adc_complete_events=0;
int ntot_adc_written_events=0;

int ntot_adc_incomplete_events=0;
int nwtot_adc_missing=0;
int ntot_adc_last_events=0;
int ntot_adc_last_recovered_events=0;

int adc_ntot_blocks_got=0;

// event length in terms of 16 32-bit words

int adc_nb_mem_tot[nb_max];
int adc_ext_trig_counter[nb_max];
int adc_count_in[nb_max];
unsigned long long adc_timestamp[nb_max];

// Output files
FILE* pFile_adc_data;
const int n_active_adcs=32+4;  // 32-files for each V1742 channel
//const int n_active_adcs=32;  // 32-files for each V1742 channel
//const int n_active_adcs=8; // now we have 8 active channels
std::ifstream pFile_binary_data[n_active_adcs];




void adc_histos();
void coin_histos();
void save_histos();

//using namespace std;



int main(int argc,char **argv)
{

// book ADC histos
adc_histos();


// Input file Run Summary
//std::ifstream pFile_run_summary("data/run_summary.dat");
long int n_start,n_end,n_launch,n_close;
int n_dif,n_run,run_time_us;
long double hr_start,hr_end,hr_dif,hr_launch,hr_close,hr_run; // Ld
int ACTIVE_ADC,i_sampling_rate,active_channel;
int threshold_sign_adc,trigger_gt_on_adc,trigger_gt_off_adc,nsamp_above_threshold_adc,
mem_event_length,trig_num_event_length,ringbuffer_delay,
veto_enbl,sis3305_veto_len,sis3305_veto_del,
calib_offset_a[4],calib_offset_b[4];
int ntot_adc_headers_exp,
ntot_adc_complete_events_exp,
ntot_adc_written_events_exp;

// Acquisition time in s and ns
/*pFile_run_summary>>n_start>>n_end>>n_dif;
pFile_run_summary>>hr_start>>hr_end>>hr_dif;
// Program run time in s and ns
pFile_run_summary>>n_launch>>n_close>>n_run;
pFile_run_summary>>hr_launch>>hr_close>>hr_run;
// Program run time in us from LDT
pFile_run_summary>>run_time_us;
// Event statistics
pFile_run_summary>>ntot_adc_headers_exp;
pFile_run_summary>>ntot_adc_complete_events_exp;
pFile_run_summary>>ntot_adc_written_events_exp;

// input file parameters
pFile_run_summary>>ACTIVE_ADC>>i_sampling_rate>>active_channel;

pFile_run_summary>>threshold_sign_adc>>trigger_gt_on_adc>>trigger_gt_off_adc>>nsamp_above_threshold_adc;
pFile_run_summary>>mem_event_length>>trig_num_event_length>>ringbuffer_delay;

pFile_run_summary>>veto_enbl>>sis3305_veto_len>>sis3305_veto_del;

pFile_run_summary>>calib_offset_a[0]>>calib_offset_a[1]>>calib_offset_a[2]>>calib_offset_a[3];
pFile_run_summary>>calib_offset_b[0]>>calib_offset_b[1]>>calib_offset_b[2]>>calib_offset_b[3];

pFile_run_summary.close();*/








// init again






int ib[n_active_adcs];





//  const int header_bufferSize = 8; // header =8 32-bit (4 bytes = int)
  const int header_bufferSize = 6; // looks like we have only 6 words
  unsigned int* header_buffer = new unsigned int[header_bufferSize];
//   int* header_buffer = new int[header_bufferSize];
  const int nsamp = 1024; // In Case of x742 Digitizers: 1024, 520, 256 and 136
//  const int nsamp = 520; // In Case of x742 Digitizers: 1024, 520, 256 and 136
// if corrections are enabled ADC data (sample) is modified by applying the corrections
// and then supplied as a float on 4 bytes.
  float* sample_buffer = new float[nsamp];

int event_bytes = header_bufferSize*sizeof(int) + nsamp * sizeof(float);
cout<<"1-ch Event size: "<<event_bytes<<" bytes"<<endl;

int n_events[n_active_adcs];

// read all the data
for(int iadc=0;iadc<n_active_adcs;iadc++) {
//pFile_binary_data[iadc].open((std::string("data/wave_") + itoa(iadc) + ".dat").c_str(), std::ios::in | std::ios::binary);
 ostringstream filename;
 if(iadc<32) filename << "data/wave_" << iadc <<".dat";
 else {
  if(iadc<34) filename << "data/TR_0_" << (iadc-32) <<".dat";
  else filename << "data/TR_1_" << (iadc-32) <<".dat";
 }
 pFile_binary_data[iadc].open(filename.str().c_str(), std::ios::in | std::ios::binary);
 pFile_binary_data[iadc].seekg (0, ios::end);
 ib[iadc]=pFile_binary_data[iadc].tellg(); // number of bytes in file
//cout<<"file: "<<(std::string("data/wave_") + itoa(iadc) + ".dat").c_str()<<" has: "<<ib<<" bytes, mem.fill: "<<((double)ib/WRITE_BUFFER_MAX_BYTES)<<endl;
 n_events[iadc]=ib[iadc]/event_bytes;
 cout<<"file: "<<filename.str()<<" has: "<<ib[iadc]<<" bytes, or "<<((double)ib[iadc]/event_bytes)<<" events"<<endl;
 pFile_binary_data[iadc].seekg (0, ios::beg);
 if(iadc>0&&ib[iadc]!=ib[0]) cout<<"ERROR.Nevents-diff.file: "<<filename.str()<<endl;
}

//exit(0);


  unsigned int e_lng;
  unsigned int brd_id,cell_index;
  unsigned int ch_id;
  unsigned int n_evt;
  unsigned int dac_offset;
  unsigned int pattern;
  unsigned int ts=0;
  unsigned int ts_previous=0;
  unsigned int ts_ch[n_active_adcs];

unsigned int trig_sample[n_active_adcs];
double qdc[n_active_adcs];
double adc[n_active_adcs];

//for(int iev=0;iev<MAX_EVENTS;iev++) {
for(int iev=0;iev<10;iev++) {
//for(int iev=0;iev<114907;iev++) {
for(int iadc=0;iadc<n_active_adcs;iadc++) {
//cout<<"step.0" <<endl;

/*
For the 742 digitizers family, the HEADER is so composed:
<header0> Record Length
<header1> Board ID
<header2> Channel
<header3> Event Counter
<header4> Pattern (meaningful only for VME boards)
<header5> Trigger Time Tag
<header6> DC offset (DAC)
<header7> Start Index Cell

BUT BINARY format is not the same as ASCII format:
1) we have 6 words only
2) j=3 - channel ID
3) 

*/
pFile_binary_data[iadc].read( (char*)header_buffer, header_bufferSize*sizeof(int)); // read header = 8 words of 32-bits --> in practice only 6 words, why?
for (int j=0;j<header_bufferSize;j++) {
//    cout<<"Header: " << *(header_buffer++) << endl;
    cout<<"Header: " <<iev<<" "<<iadc<<" "<<j<<" "<< header_buffer[j] << endl;
    if(j==0) e_lng=header_buffer[j]; // Record Length - this gives wrong value: 2104 instead of 520
//    else if(j==1) brd_id=header_buffer[j]; // Board ID
    else if(j==1) {
     cell_index=header_buffer[j]& 0x3FF; // First cell index
//     cell_index=header_buffer[j]; // First cell index
     brd_id=(header_buffer[j]>>28)& 0xF; // Board ID
//    else if(j==2) // Pattern=0
    } else if(j==3) ch_id=header_buffer[j]; // Channel
    else if(j==4) {
      n_evt=header_buffer[j]; // Event Counter
     if(iev>0&&n_evt!=(iev+1)) cout<<"ERROR.Counter.file: "<<iadc<<" , event "<<iev<<" , counter "<< n_evt<<endl; // check event counter
    }
//    if(j==4) // Pattern: 0x0000
    else if(j==5) {
     ts=header_buffer[j]; // Trigger Time Tag [8.5 ns for 742] - becomes negative - format is wrong
     ts_ch[iadc]=ts;
    }
//    if(j==6) // DC offset (DAC): 0x7FFF=32767
//    if(j==7) // Start Index Cell: 98
}

cout<<"step.1, ch: "<<ch_id <<" "<<cell_index <<endl;

pFile_binary_data[iadc].read( (char*)sample_buffer, nsamp*sizeof(float)); // read samples = Nsample words of 32-bits
for (int j=0;j<nsamp;j++){
//   cout<<"data: " << *(sample_buffer++) << endl;
//   cout<<"data: " <<j+1<<" "<< sample_buffer[j] << endl;
//   adc_val[j]=sample_buffer[j];
}

//cout<<"step.2, ch: "<<ch_id <<endl;

// analyze ADC waveform for current channel/event
trig_sample[iadc]=0;
qdc[iadc]=0;
adc[iadc]=0;
analyze_adc(iev, ch_id, ts, sample_buffer, &trig_sample[iadc], &qdc[iadc], &adc[iadc]);

//cout<<"step.3" <<endl;

//cout<<"ts: "<<iev <<" "<< ch_id <<" "<< ts <<endl; // timestamp is the same for 8 channels


/*if(pFile_binary_data[iadc]) pFile_binary_data[iadc].read((char*)(wrt_buffer->ADC_data_block),ib[0]);
wrt_buffer->ADC_n_bytes=pFile_binary_data[iadc].gcount();
pFile_binary_data[iadc].close();
cout<<"raw_data.dat read: "<<pFile_binary_data[iadc].gcount()<<" bytes"<<endl;

if(save_asci_data) {
pFile_adc_data = fopen("out_data/adc_data.dat","w");
}
// decode the data
io_manager();

if(save_asci_data) {
fclose(pFile_adc_data);
}*/

} // next ADC channel



// analyze coincidences of >1 ADC channel
double qdc_min=1.0; // threshold QDC > 1 pC
int id_qdc[n_active_adcs];
int n_qdc=0;
for (int k=0;k<n_active_adcs;k++){
 if(qdc[k]>qdc_min) {
  id_qdc[n_qdc]=k;
  n_qdc++;
 }
}
if(n_qdc>1) {
// analyze_coin(iev, ts, trig_sample, qdc, adc, id_qdc, n_qdc);
}

for (int k=1;k<n_active_adcs;k++){
 if(ts_ch[k]!=ts_ch[0]) cout<<"ERROR.ts: event "<<iev<<" , channel "<< k << " ts "<<ts_ch[k] <<" "<< ts_ch[0] <<endl; // check event counter
}
dt_events->Fill((ts-ts_previous)*8.5e-6); // assume rate 1 kHz, dt=1 ms, use units ms, ns=1.e-6 ns
//if(((ts-ts_previous)*8.5e-6)<0.1) cout<<"zero.ts: event "<<iev<<" , "<<ts_ch[1] <<" "<< ts_previous <<" "<< ((ts-ts_previous)*8.5e-6) <<endl;
//if(1) cout<<"zero.ts: event "<<iev<<" , "<<ts_ch[1] <<" "<< ts_previous <<" "<< ((ts-ts_previous)*8.5e-6) <<endl;
if(iev>0&&((ts-ts_previous)*8.5e-6)>0.6) cout<<"zero.ts: event "<<iev<<" , "<<ts_ch[1] <<" "<< ts_previous <<" "<< ((ts-ts_previous)*8.5e-6) <<endl;
ts_previous=ts; // all ADC channels seem to have the same TS, last is OK
}// next event


//exit(0);


/*double tdiff=(hr_end-hr_start)/1000000.;
double trigg_rate=1/tdiff;
double event_rate=ntot_adc_headers/tdiff;



cout<<"number of triggers: "<<1<<endl;
cout<<"run time: "<<tdiff<<" ms"<<endl;
cout<<"event rate: "<<event_rate<<" kHz"<<endl;
cout<<"trigger rate: "<<trigg_rate<<" kHz"<<endl;


cout<<"ADC Headers: "<<ntot_adc_headers<<"/"<<ntot_adc_headers_exp
<<" , Complete Events: "<<ntot_adc_complete_events<<"/"<<ntot_adc_complete_events_exp<<endl;

cout<<"ADC Written Events: "<<ntot_adc_written_events<<"/"<<ntot_adc_written_events_exp<<endl;

cout<<"ADC Incomplete Events: "<<ntot_adc_incomplete_events<<" , lost words: "<<(nwtot_adc_missing/(ntot_adc_incomplete_events+1))<<endl;

cout<<"ADC last Events: "<<ntot_adc_last_events<<" , recovered: "<<ntot_adc_last_recovered_events<<endl;

cout<<"********** Finished read loop\n";*/

// save ADC histos
save_histos();

   cout<<"\n\n";
}
