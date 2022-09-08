#ifndef ANA_ADC
#define ANA_ADC

/* Constants */

// Digitizer settings
//const int nsamp=520; 
const int nsamp=1024; // V1742 default/max number of samples
const int n_adc_ch=32+4; // 32-input channels + 4 TR0,1 fast trigger inputs

// Digitizer baseline levels
const double bln_cor=0.;

// baseline in the 32+4 V1742 channels
const double ch_offset[n_adc_ch]={
2174.46,2192.86,2182.47,2649.0,2600.0,2650.0,2594.0,2600.0,
2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,
2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,
2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,2500.0,2500.0
,2500.0,2500.0,2500.0,2500.0 // TR0,1
};

// expected pre-trigger number of samples (from LASER - fixed w.r.t. LASER sync, used as trigger)
const int sync_trig_delay=100; 

const int peak_width=15; // LAPPD signal: 15 smaples first peak (then there are trailing peaks)

const int n_adc_chn=4096; // 12-bit V1742 ADC
const double V_pp_adc=1.e3; // ADC range: 1 Vpp

const double ch_to_mv=V_pp_adc/(double)n_adc_chn; // convertion ch-->mV

const double dt_sample=0.2000000000000000; // sampling period 0.2 ns



// Units
const double R=50.; // input impedance
const double mvns2pc=0.4/R; // convertion 2mV*0.2ns/R --> pC
const double mvns2fc=mvns2pc*1.e3; // convertion 2mV*0.2ns/R --> fC

const double pc2kev=13.e-3/1.60217646e-7; // convertion 1 e --> 13 eV
const double fc2kev=13.e-3/1.60217646e-4; // convertion 1 e --> 13 eV


/* Amplifier gain */
const double peak_to_charge=1.76*4.0*4.00; // mV/fC R. Cardarelli X P/S 771 gain x4

const double amp_gain=667.0*4.0*4.93292268/7.2;

/* Trigger parameters */
const int threshold=20; // base threshold
const int ncut_min=5; // minimum number of channels above threshold in one pulse
const double peak_th=25.0; // peak threshold
const double noise_rms=1.5; // RMS of noise in channels

const int led_th=20; // base threshold
const double cfd_th=0.30; // base threshold

const double edep_min=500.0; // cut on minimum energy

/* Noise parameters */

const int threshold_nr=250; // noise rejection threshold
const int ncut_max=150*4; // maximum number of channels above threshold in entire event

/* Signal parameters */
//const int djt=30; // LE Discriminator trigger delay in terms of samples
const int djt=5; // LE Discriminator trigger delay in terms of samples
//const int peak_width=250; // best sandwich Ibis


const double energy_res=400.0; // 3x(sigma=54.0 keV, 91.5 keV)







const int n_coin_bin=1600;


/* Variables */

double amp_gain_drifted;

extern int n_coin;


int nsat;
int nsat_max;
int nsat_tot;
int jled,jted;

double start_adc_mean;

int chid[nsamp];
int nx[nsamp];
int nmp;
double adcv[nsamp];
double adc_peak_value;
double adc_max;
double adc_max_mean;
double adc_max_bkg;
double adc_zero_mean;
double base_line_a,base_line_b;

int jmax;
int js,jt,jct,jpeak;
int djs;
int dw;
double qdc_sig;
double qdc_sig_refl;
double qdc_bkg_lhs;
double qdc_bkg_rhs;
double qdc_clean;
double edep_kev;
double qdc_bkg;
double edep_bkg_kev;


double edepv;

unsigned int led_trig;
unsigned int ted_trig;
unsigned int cfd_trig;

unsigned int trig;
unsigned int trig_cor;
unsigned int stop_adc;

int inx_end;

bool slpc;


//void analyze_adc(int i_event, int i_adc, unsigned long long adc_ts, unsigned int *adc_val, unsigned int trig_val, double edep_val, double edep_bkg_val);

#endif
