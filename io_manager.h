#ifndef IO_MAN
#define IO_MAN

/* maximum number of bytes in event =1024 samples*4 bytes (corrected) + 6 header words * 4 bytes */
#define EVENT_MAX_BYTES 4120

#define MAX_EVENTS 1000000000

/* maximum number of data blocks */
#define nb_max 1000000

/* block size * queue maximum size */
/* #define WRITE_BUFFER_MAX_BYTES 409600000 */
/* maximum data size */
#define WRITE_BUFFER_MAX_BYTES 409600000

typedef struct wrt_data_buffer{
	int ADC_n_bytes;
	unsigned char ADC_data_block[WRITE_BUFFER_MAX_BYTES];
	int ID_buf;
	unsigned int Ext_Trig_Counter;
	unsigned long long Timestamp;
} wrt_data_buffer_t;

inline void lwtoint(unsigned char *long_word, unsigned char *cvl) {
register const unsigned char *p = long_word+4; /* start from fourth byte and go to the first */
for(int ibyte=0;ibyte<4;ibyte++) *(cvl + ibyte) = *(--p);
}


void analyze_adc(int iev, unsigned int ich, unsigned int adc_ts, float *adc_val
, unsigned int *trig_val, double *edep_val, double *edep_bkg_val);


#endif
