#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types_frac.h"
#include "polyphase_filter.h"
#include "libdd.h"

#define ERROR(X)	{						\
				fprintf(stderr, "ERROR: %i %s\n",	\
				        __LINE__, X);			\
				exit(-1);				\
			}

#define SAMPLES_16K	16000
#if 0
//#define SAMPLES_8K	8000 //(SAMPLES_16K / 2)	/* 2:1 decimation ratio */
#else
#define SAMPLES_8K	(SAMPLES_16K / 2)	/* 2:1 decimation ratio */
#endif

#define TEST_VARS	20	/* number of variables */
#define TEST_OFFSET	0.0	/* DC bias voltage, 0.0 -> 1.0 */
#define TEST_RMS	0.25	/* RMS voltage, 0.0 -> 1.0 */

#define CHANNELS_16K	1
#define CHANNELS_8K	3

# define SAMPLERATE_CONVERT_FIR3_COEFS 18

sfrac1q15	RawAudio16k[SAMPLES_16K];
sfrac1q15	*BufLst16k[CHANNELS_16K] = {
	RawAudio16k
};

sfrac1q15	CanonicalFirAudio16k[SAMPLES_16K];

sfrac1q15	CanonicalFirAudio8k[SAMPLES_8K];
sfrac1q15	PolyphaseFirAudio8k[SAMPLES_8K];
sfrac1q15	FilterError8k[SAMPLES_8K];
sfrac1q15	*BufLst8k[CHANNELS_8K] = {
	CanonicalFirAudio8k, PolyphaseFirAudio8k, FilterError8k
};

firfilter_t	*FirCanonical = NULL;
polyfilter_t    *PolyFilter = NULL;

/* TODO polyphase filter declaration goes here */

static const sfrac1q15 Fir3LpfCoefs[SAMPLERATE_CONVERT_FIR3_COEFS] = {
/*
 * Cloned from libdd.c plus a zero pad
 */
	-2182,	-588,	2519,	2171,	-2577,	-5361,	196,	11072,
	16677,	11072,	196,	-5361,	-2577,	2171,	2519,	-588,
	-2182,	0
};

void cleanUpOnExit(void);

/**************************************************************************/
int main (void)
/**************************************************************************/
{
	bool		error = false;
	unsigned	i;

	/* register the clean up function(s) called on exit */
	if (atexit(cleanUpOnExit))
		ERROR("atexit");

	/* initalize the raw audio signal -> additive white gausian noise */
	if (awgnGeneratorSFRAC1Q15(TEST_VARS, TEST_OFFSET, TEST_RMS,
	                           RawAudio16k, SAMPLES_16K))
		ERROR("awgnGeneratorSFRAC1Q15");

	/* initalize the filters */
	FirCanonical = firFilterCreate(Fir3LpfCoefs,
	                               SAMPLERATE_CONVERT_FIR3_COEFS);
	if (FirCanonical == NULL)
		ERROR("firFilterCreate");

	PolyFilter = polyFilterCreate(Fir3LpfCoefs,
                                      SAMPLERATE_CONVERT_FIR3_COEFS);
        
        if (PolyFilter == NULL){
            ERROR("Poly Filter Create");
            printf("Do the damn thang\n");
        }

	/* run the filters */
	if (firFilter(FirCanonical, RawAudio16k, CanonicalFirAudio16k,
	              SAMPLES_16K))
		ERROR("firFilter");
        
        for (i = 0; i < SAMPLES_8K; ++i)

		#if 0	// discard odd samples

		CanonicalFirAudio8k[i] = CanonicalFirAudio16k[2 * i];

		#else	// discard even samples

		CanonicalFirAudio8k[i] = CanonicalFirAudio16k[2 * i + 1];
                
		#endif
                
	if (polyFilter(PolyFilter, RawAudio16k, PolyphaseFirAudio8k, 
                       SAMPLES_16K))
                ERROR("polyFilter");
            
	#if 0 /* enable this section to see the successful behaviour */
	{ 
		sfrac1q15	*tmp = malloc(sizeof(sfrac1q15)*SAMPLES_16K);

		if (tmp == NULL)
			ERROR("calloc");

		firFilterReset(FirCanonical);

		if (firFilter(FirCanonical, RawAudio16k, tmp, SAMPLES_16K))
			ERROR("firFilter");

		for (i = 0; i < SAMPLES_8K; i++)
			PolyphaseFirAudio8k[i] = tmp[2 * i];

		free(tmp);
	}
	#endif

	/* calculate and test filter error, this should be all zeros... */
	for (i = 0; i < SAMPLES_8K; i++) {
		FilterError8k[i] =
		  CanonicalFirAudio8k[i] - PolyphaseFirAudio8k[i];

		if (!error && FilterError8k[i]) {
			error = true;
			fprintf(stderr, "WARN: the filter performance is not "
			        "identical\n");
		}
	}
                
	if (!error)
		printf("The filters behave identically, HUZZAH!\n");
	/* write the waveform files */
	if (wavwrite("polyphase_raw.wav", CHANNELS_16K, 16000, 16,
	             SAMPLES_16K, (void**)BufLst16k))
		ERROR("wavewrite");

	if (wavwrite("polyphase_test.wav", CHANNELS_8K, 8000, 16,
	             SAMPLES_8K, (void**)BufLst8k))
		ERROR("wavewrite");

	return 0;
}

void cleanUpOnExit(void)
/**************************************************************************/
/*
 * Deallocate any resources so valgrind's output can solely focus on the
 * code under test rather than being cluttered by the test harness.
 */
{
	if (FirCanonical != NULL)
		firFilterDestroy(FirCanonical);

	/* TODO polyphase filter destroy goes here */

	return;
}

