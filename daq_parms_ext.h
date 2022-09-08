#ifndef DAQ_PAR_EXT
#define DAQ_PAR_EXT

/* DAQ input parameters used in the analysis */

extern int daq_nb; /* event length ~nblocks */
extern int daq_th[2]; /* base threshold ~threshold[2] */
extern int daq_nsamp[2]; /* minimum number of samples above threshold ~ncut_min[2] */

#endif
