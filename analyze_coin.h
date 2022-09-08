#ifndef ANA_COIN
#define ANA_COIN

/* Constants */
const double coin_edep_min[2]={1000.0,1000.0};
const double edep_noise_rms[2]={220.0,220.0};

const double dt_mean=17.0; // Delta t peak position in ns
const double dt_rms=2.75; // Delta t peak width in ns

const double q_t=2730.; // tritium energy
const double q_a=2060.; // alpha energy
const double q_tot=q_t+q_a; // total Q-value

/* Variables */
double delta_t,delta_t_ts,delta_t_gpx_stop,delta_t_gpx_ts,delta_t_gpx_1,delta_t_gpx_2,delta_t_gpx;

extern int n_coin;

#endif
