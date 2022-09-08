#ifndef DAQ_PAR
#define DAQ_PAR

/* DAQ input parameters used in the analysis */

int daq_nb; /* event length ~nblocks */
int daq_th[2]; /* base threshold ~threshold[2] */
int daq_nsamp[2]; /* minimum number of samples above threshold ~ncut_min[2] */

#endif
