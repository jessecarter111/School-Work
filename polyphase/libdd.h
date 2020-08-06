/*
                             *******************
******************************* C HEADER FILE *******************************
**                           *******************                           **
**                                                                         **
** filename  : libdd.h                                                     **
** author    : David A. Bardsley                                           **
** created   : 2009-08-19                                                  **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (C) 2009 - 2017, Pantel International Incorporated            **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************

*/

#ifndef __LIBDD_INCLUDED
#define __LIBDD_INCLUDED

/***************************************************************************/
/**                                                                       **/
/**                     MODULES USED                                      **/
/**                                                                       **/
/***************************************************************************/
#include "types_frac.h"

/***************************************************************************/
/**                                                                       **/
/**                     DEFINITIONS AND MACROS                            **/
/**                                                                       **/
/***************************************************************************/
#define __TRUE				1
#define __FALSE				0

#define __SOS_COEF			5

#define	__VOX_THRESH_MIN		0
#define	__VOX_THRESH_MAX		99
#define	__VOX_THRESH_DBFS_MIN		-100.0
#define	__VOX_THRESH_DBFS_MAX		-15.0
#define __VOX_PERIOD_MIN		0
#define	__VOX_PERIOD_MAX		10000

#define __PIE_APROX			3.14159265358979
#define __PI_APPROX			__PIE_APROX

#define __CONFIG_LINE_LENGTH_MAX	80

#define __VOTER_MERIT_SOS		3

enum CfgParameters {
	CONFIG_MINIMUM,
	CONFIG_DEFAULT,
	CONFIG_MAXIMUM,

	CONFIG_VALUES
};

enum EIA_TRC_SAMPLERATE {
	EIA_TRC_SAMPLERATE_8000,

	EIA_TRC_SAMPLERATES
};

enum EIA_TRC_GUARD_TONE {
	EIA_TRC_GUARD_TONE_2175,

	EIA_TRC_GUARD_TONES
};

enum EIA_TRC_FUNCTION_TONE {
	EIA_TRC_FUNCTION_TONE_650,
	EIA_TRC_FUNCTION_TONE_750,
	EIA_TRC_FUNCTION_TONE_850,
	EIA_TRC_FUNCTION_TONE_950,
	EIA_TRC_FUNCTION_TONE_1050,
	EIA_TRC_FUNCTION_TONE_1150,
	EIA_TRC_FUNCTION_TONE_1250,
	EIA_TRC_FUNCTION_TONE_1350,
	EIA_TRC_FUNCTION_TONE_1450,
	EIA_TRC_FUNCTION_TONE_1550,
	EIA_TRC_FUNCTION_TONE_1650,
	EIA_TRC_FUNCTION_TONE_1750,
	EIA_TRC_FUNCTION_TONE_1850,
	EIA_TRC_FUNCTION_TONE_1950,
	EIA_TRC_FUNCTION_TONE_2050,

	/* these are last to keep backwards compatibility */
	EIA_TRC_FUNCTION_TONE_550,
	EIA_TRC_FUNCTION_TONE_450,
	EIA_TRC_FUNCTION_TONE_350,

	EIA_TRC_FUNCTION_TONES
};

enum EIA_TRC_ENCODE_CTRL {
	EIA_TRC_ENCODE_CTRL_STATE,
	EIA_TRC_ENCODE_CTRL_BURST,
	EIA_TRC_ENCODE_CTRL_FT,

	EIA_TRC_ENCODE_CTRLS
};

enum EIA_TRC_ENCODE_STATE_REPORT {
	EIA_TRC_ENCODE_REPORT_STATE_IDLE,
	EIA_TRC_ENCODE_REPORT_STATE_HLGT,
	EIA_TRC_ENCODE_REPORT_STATE_FT,
	EIA_TRC_ENCODE_REPORT_STATE_LLGT,

	EIA_TRC_ENCODE_REPORT_STATES
};

enum DdsAlterAttribute {
	DDS_ATTRIB_PHASE_SET,
	DDS_ATTRIB_PHASE_ADD,
	DDS_ATTRIB_DELTAPHASE_SET,
	DDS_ATTRIB_DELTAPHASE_ADD,
	DDS_ATTRIB_AMPLITUDE_SET,
	DDS_ATTRIB_AMPLITUDE_SCALE,

	DDS_ATTRIBUTES
};

enum SampleRateConvertType {
	SAMPLERATE_CONVERT_INTERPOLATE,
	SAMPLERATE_CONVERT_DECIMATE,
	SAMPLERATE_CONVERT_BIPHASE_INTERPOLATE,
	SAMPLERATE_CONVERT_BIPHASE_DECIMATE,
	SAMPLERATE_CONVERT_DELAY_INTERPOLATE,
	SAMPLERATE_CONVERT_DELAY_DECIMATE,

	SAMPLERATE_CONVERT_TYPES
};

enum SampleRateConvertFilter {
	SAMPLERATE_CONVERT_FILTER_NONE,	/* self-explanatory */

	SAMPLERATE_CONVERT_FILTER_FIR1,	/* 64 tap finite-impulse response
					filter.  passband: edge 0.129167pi rad
					(3.1kHz at 48ksps), ripple 1dB;
					stopband: edge 0.166667pi rad
					(4kHz at 48ksps), attenuation 30dB. */

	SAMPLERATE_CONVERT_FILTER_IIR1,	/* 3 second-ordered sectioned infinite
					impulse response filter.  passband:
					edge 0.129167pi rad (3.1kHz at 48ksps),
					ripple 1dB; */

	SAMPLERATE_CONVERT_FILTER_FIR2,	/* 18 tap finite-impulse response
					filter.  Extant AUDx & QLI I/O filter,
					provides equalization and some stop-
					band attenuation.  Design criteria TBD
					*/

	SAMPLERATE_CONVERT_FILTER_FIR3,	/* 17 tap finite-impulse response
					filter intended for AUDx & QLI
					amplitude equalization and decimation/
					interpolation fitlering */

	SAMPLERATE_CONVERT_FILTER_FIR4,	/* Future expansion */

	SAMPLERATE_CONVERT_FILTERS
};

enum WindowType {
	WINDOW_TYPE_RECT,		// aka boxcar or Dirichlet
	WINDOW_TYPE_TRI,		// aka Bartlett
	WINDOW_TYPE_HANN,		// aka von Hann or raised cosine
	WINDOW_TYPE_HAMMING,		// as the name suggests...

	WINDOW_TYPES
};

enum SampleConvertModify
{
	SAMPLE_CONVERT_MODIFY_DSP_ADJUST_GAIN,
	SAMPLE_CONVERT_MODIFY_SET_MUTE,

	SAMPLE_CONVERT_MODIFY_MAX
};

/***************************************************************************/
/**                                                                       **/
/**                     TYPDEFS AND STRUCTURES                            **/
/**                                                                       **/
/***************************************************************************/
typedef void sosfilter_t;

typedef void firfilter_t;

typedef struct {
	sfrac19q13	*r;	/* result buffer pointer */
	const unsigned	n;	/* result buffer length */
	void		*q;	/* private state variables */
} goertzelpsd_t;

typedef void goertzelpsd_dp_t;	/* double-precision floating point version of
                                   of goertzelpsd_t */

typedef void goertzelpsd_fx_t;	/* 32-bit fixed-point common interface version
                                   of goertzelpsd_t */

typedef void voxapp_t;

struct VoxInitData {
	short		latch;		/* hystersis low threshold */
	short		unlatch;	/* hystersis high threshold */
	unsigned short	period;		/* latch-to-unlatch period */
};

struct VoxInitDbfsData {
	double		latch;		/* hystersis low threshold */
	double		unlatch;	/* hystersis high threshold */
	unsigned short	period;		/* latch-to-unlatch period */
};

struct SynthesizerType { /* *** WARNING *** This data type and the associated
                            functions have been deprecated due to a data type
                            overflow that limits the usable normalized output
                            frequency to 0.39.  All new designs should use
                            "dds_t" and it's associated functions. */
	unsigned long	deltaAngle;
	unsigned long	angle;
	unsigned	quadrant;
};

struct AlcInitType {
	unsigned short	sps;	/* samples per second                   Hz   */
	float		tA;	/* period to shift from max to min gain s    */
	float		tH;	/* constant gain period before increase s    */
	float		tR;	/* period to shift from min to max gain s    */
	float		gMax;	/* maximum gain                         dB   */
	float		gMin;	/* minimum gain                         dB   */
	float		gRun;	/* initial running gain			dB   */
	float		sat;	/* hard-limiter clipping level          dBfs */
	float		high;	/* high-level tracking threshold        dBfs */
	float		low;	/* low-level tracking threshold         dBfs */
	float		min;    /* minimum average magnitude            dBfs */
};

typedef void alc_t;

struct EiaTrcToneData {
	int	freq;	/* standardized frequency, see above             */
	float	level;	/* dB referenced to the nominal level, see below */
	int	period;	/* duration, milliseconds                        */
};

struct EiaTrcEncodeInit {
	enum EIA_TRC_SAMPLERATE	sps;	/* sample rate (Hz)      */
	float			level;	/* nominal level (dBfs)  */
	struct EiaTrcToneData	hlgt;	/* High Level Guard Tone */
	struct EiaTrcToneData	ft;	/* Function Tone         */
	struct EiaTrcToneData	llgt;	/* Low Level Guard Tone  */
};

struct SampleRateConvertInit {
	enum SampleRateConvertType	type;
	enum SampleRateConvertFilter	filter;
	unsigned			n;
	unsigned			m;
	float				delay;
};

struct DynamicRangeCompressorCfg {
	double	vt;	/* threshold, knee of compression (dBfs) */
	double	vol;	/* hard-limit output level (dBfs)        */
	double	ratio;	/* input gain to output gain (dB/dB)     */
};

struct SignalMeasureCfg {
	#if 0				/* TODO future enhancements */
	void            (*fn)(struct SignalMeasureOutput *);
	unsigned	psd_bins;	/* number of frequency bins */
	unsigned	psd_samples;	/* number of samples per window */
	enum WindowType	psd_window;	/* windowing function */
	#endif
	unsigned	sampleRate;	/* (Hz) samples per second */
	double		period;		/* (s) report period */
	const char	*idStr;		/* for disambiguation */
};

typedef void eiatrc_encode_t;

typedef void dds_t;

typedef void dl_list_t;

typedef void sr_convert_t;

typedef void drc_t;

typedef struct signal_measure_t signal_measure_t;

/***************************************************************************/
/**                                                                       **/
/**                     EXPORTED VARIABLES                                **/
/**                                                                       **/
/***************************************************************************/

#ifndef __LIBDD_C_SRC
extern const sfrac2q14 EiaTrc8k1950NotchCoefs[__SOS_COEF];
extern const sfrac2q14 EiaTrc8kNotchCoefs[EIA_TRC_GUARD_TONES][__SOS_COEF];
extern const sfrac2q14 Pilot8k1600NotchCoefs[__SOS_COEF];
extern const sfrac2q14 Pilot8k1950NotchCoefs[__SOS_COEF];
extern const sfrac2q14 Pilot8k2175NotchCoefs[__SOS_COEF];
extern const sfrac2q14 Pilot8k1600BFPCoefs[__SOS_COEF];
extern const sfrac2q14 Pilot8k1950BFPCoefs[__SOS_COEF];
extern const sfrac2q14 Pilot8k2175BFPCoefs[__SOS_COEF];
extern const sfrac2q14 VoterBpfCoefs[__VOTER_MERIT_SOS][__SOS_COEF];
#endif

/***************************************************************************/
/**                                                                       **/
/**                     EXPORTED FUNCTIONS                                **/
/**                                                                       **/
/***************************************************************************/

/***************************************************************************/
int configParser(const char *filename, const double cfgVal[][CONFIG_VALUES],
                 const char **tags, double *cfg, unsigned n);
/***************************************************************************/
/*
 * Configuration file parser.  Standardize the most common read operation of
 * adjustable initialization parameters.  Refer to any one of a host of
 * application examples, "dtmfDecodeConfigParser" in "dtmf.c" for example,
 * for details.
 */

/***************************************************************************/
dl_list_t *listOpen(void);
/***************************************************************************/
/*
 * Create and initialized a new, and empty, list object.  Return a pointer to
 * the object on success or return "NULL" if an error occured.
 */

/***************************************************************************/
int listClose(dl_list_t *list);
/***************************************************************************/
/*
 * Destroy an empty list object created by a previous "listOpen" function
 * call;  Return "0" on success or "-1" if either the list pointer argument
 * is invalid, the list wasn't empty, or the list is busy.
 */

/***************************************************************************/
int listWrite(dl_list_t *list, void *d);
/***************************************************************************/
/*
 * Add a new element with data "p" to the list end.  Return "0" on success or
 * "-1" if an error occured and the list did not add the item.
 */

/***************************************************************************/
int listRead(dl_list_t *list, void **d);
/***************************************************************************/
/*
 * Remove list start element data "d" previously added to the list.  Return
 * "0" on success indicating that "d" was retreived from the list or "-1" if
 * an error occured or that the list was empty, in either of the error cases
 * "d" is undefined. 
 */

/***************************************************************************/
int listSearch(dl_list_t *list, const void *key,
               int (*compar)(const void *, const void *), void **d);
/***************************************************************************/
/*
 * Beginning from the list head, search for the first item matching the
 * object pointed to by "key" according to the comparison function pointed
 * to by "compar" described below.  On the first successful match return "0"
 * indicating that "d" was retrieved from the list.  Otherwise on failure to
 * find a match on the list or if an error was detected return "-1"
 * indicating "d" was unchanged.
 *
 * The comparison function function shall expect its first argument to point
 * to the key object and its second argument to point to a test object of the
 * the same type as the key on the list, and shall return an integer less than
 * zero if the key object is considered less than test object, zero if the
 * objects are considered equal, or greater than zero if the key object is
 * considered greater than the test object.
 */

/***************************************************************************/
int listElementCount(dl_list_t *p, unsigned *n);
/***************************************************************************/
/*
 * Report the number of items on a list, that is to say the net difference
 * between the successful list write and read counts.  On success return "0"
 * and write the number of elements to the location pointed to by "n",
 * otherwise on failure return "-1" and leave the location pointed to by "n"
 * unchanged.
 */

/***************************************************************************/
int goertzelPsdCoefficient(const unsigned int *x, sfrac2q14 *c,
                           unsigned int n, unsigned int sr);
/***************************************************************************/
/*
 * Goertzel power spectral density coefficient generator.
 *
 * From the list of frequencies (Hertz) pointed to by "x" of "n" elements
 * calculate the corresponding goertzel coefficients at the sample rate "sr".
 * Return "0" on success after writing "n" coefficients to "c", otherwise
 * return "-1" if an error was detected leaving the buffer "*c" undefined.
 */

/***************************************************************************/
goertzelpsd_t *goertzelPsdCreate(const sfrac2q14 *c, unsigned int n,
                                 unsigned int m);
/***************************************************************************/
/*
 * Goertzel power spectral density object creator.
 *
 * Create an object for later use with the functions "goertzelPsdDestroy" and
 * "goertzelPsd".  The coefficient array "c" of "n" elements sets the number
 * of energy result elements, while the window length "m" sets the number of
 * samples per result window.  Return a pointer to the newly created object or
 * "NULL" if an error occured.
 */

/***************************************************************************/
void goertzelPsdDestroy(goertzelpsd_t *p);
/***************************************************************************/
/*
 * Goertzel power spectral density object destroyer.
 *
 * Destroy the objects pointed to by "p", i.e. deallocate the resources
 * assigned by a previous create function call.  Note that the result of
 * using "*p" after calling the destroyer are undefined.
 */

/***************************************************************************/
int goertzelPsd(goertzelpsd_t *p, sfrac1q15 x);
/***************************************************************************/
/*
 * Goertzel power spectral density calculator using fixed-point data.
 *
 * Process the linear sample "x" with the Goertzel power spectral density
 * calculator object pointed to by "p".  Return the number of additional
 * input samples required to complete the current calculation, or "-1" if
 * an error was detected.
 *
 * When "0" is returned the power spectral density object result energy bin
 * buffer pointed to by "p->r" shall contain the newly written results,
 * otherwise it remains unchanged.
 */

/***************************************************************************/
goertzelpsd_dp_t *goertzelPsdDpCreate(const double *freq, unsigned n, 
                                      unsigned sampleRate, unsigned m);
/***************************************************************************/
/*
 * Goertzel power spectral density double precision floating-point object
 * creator.
 *
 * Allocate and initialize resources for later use with "goertzelPsdDp" and
 * "goertzelPsdDpDestroy".  "freq" points to the list of "n" frequencies at
 * which power shall be calculated.  "sampleRate" is the number of samples
 * per second (Hz) and "m" is the number of samples over which the power
 * shall be calculated.  Return a pointer to the newly created and
 * intialized object or "NULL" if an error occured.
 */

/***************************************************************************/
int goertzelPsdDp(goertzelpsd_dp_t *p, sfrac1q15 x, double *y, unsigned n);
/***************************************************************************/
/*
 * Goertzel power spectral density calculator using double precision floating
 * point data.
 *
 * Process the linear sample "x" with the Goertzel power spectral density
 * calculator object pointed to by "p".  Return the number of additional
 * input samples required to complete the current calculation, or "0" 
 * if the power calculation is complete and the result buffer pointed to by
 * "y" of "n" elements corresponding to the the frequency points as defined
 * at creation time is defined. Otherwise return "-1" to indicate an error
 * was detected.
 */

/***************************************************************************/
void goertzelPsdDpDestroy(goertzelpsd_dp_t *p);
/***************************************************************************/
/*
 * Goertzel power spectral density object destroyer.
 *
 * Destroy the objects pointed to by "p", i.e. deallocate the resources
 * assigned by a previous create function call.  Note that the result of
 * using "*p" after calling the destroyer are undefined.
 */

/***************************************************************************/
goertzelpsd_fx_t *goertzelPsdFxCreate(const double *freq, unsigned n, 
                                      unsigned sampleRate, unsigned m);
/***************************************************************************/
/*
 * Goertzel power spectral density 32-bit fixed point object creator.
 *
 * Allocate and initialize resources for later use with "goertzelPsdFix" and
 * "goertzelPsdFixDestroy".  "freq" points to the list of "n" frequencies at
 * which power shall be calculated.  "sampleRate" is the number of samples
 * per second (Hz) and "m" is the number of samples over which the power
 * shall be calculated.  Return a pointer to the newly created and
 * intialized object or "NULL" if an error occured.
 */

/***************************************************************************/
int goertzelPsdFx(goertzelpsd_fx_t *p, sfrac1q15 x,
                  sfrac19q13 *y, unsigned n);
/***************************************************************************/
/*
 * Goertzel power spectral density calculator using 32-bit fixed point data.
 *
 * Process the linear sample "x" with the Goertzel power spectral density
 * calculator object pointed to by "p".  Return the number of additional
 * input samples required to complete the current calculation, or "0" 
 * if the power calculation is complete and the result buffer pointed to by
 * "y" of "n" elements corresponding to the the frequency points as defined
 * at creation time is defined. Otherwise return "-1" to indicate an error
 * was detected.
 */

/***************************************************************************/
void goertzelPsdFxDestroy(goertzelpsd_fx_t *p);
/***************************************************************************/
/*
 * Goertzel power spectral density object destroyer.
 *
 * Destroy the objects pointed to by "p", i.e. deallocate the resources
 * assigned by a previous create function call.  Note that the result of
 * using "*p" after calling the destroyer are undefined.
 */

/***************************************************************************/
sosfilter_t *sosFilterCreate(const sfrac2q14 *p, unsigned int i);
/***************************************************************************/
/*
 * Second-Order Section Filter Create
 *
 * Create a filter object from the coefficient array and return its pointer
 * on success, or NULL if an error occured.  The filter shall have "n"
 * second-order sections and the coefficient array pointed to by "p" shall have
 * "i = 5*n" elements arranged as follows:
 *
 *  b(0,0) b(0,1) b(0,2) -a(0,1) -a(0,2) b(1,0) b(1,1) ... -a(n-1,2)
 *
 * Given that each second-order section is in cascade and their output is
 * calculated as:
 *
 *  y(k,m) = b(k,0)*x(m) + b(k,1)*x(m-1) + b(k,2)*x(m-2) +
 *           b(k,3)*y(k,m-1) + b(k,4)*y(k,m-2)
 *
 *  Where k = 0, 1, ... n-1
 *
 * On success the returned pointer may be used by subsequent calls to the
 * function "sosFilter" until it has been destroyed with the function
 * "sosFilterDestroy".
 *
 * FIXME "p is a pointer to an array __SOS_COEFS of sfrac2q14".
 */

/***************************************************************************/
void sosFilterDestroy(sosfilter_t *p);
/***************************************************************************/
/*
 * Second-Order Section Filter Destroy
 *
 * Destroy a filter object, free the allocated memory, created by a previous
 * call to the function "sosFilterCreate".  Note that the results of "p" used
 * by a call to "sosFilter" after having been destroyed are undefined.
 */

/***************************************************************************/
void sosFilterReset(sosfilter_t *p);
/***************************************************************************/
/*
 * Second-Order Section Filter Reset
 *
 * Clear the specified filter object's history, i.e. reset the stored samples.
 */

/***************************************************************************/
int sosFilterModify(sosfilter_t *p, unsigned k, double g);
/***************************************************************************/
/*
 * TODO documention
 */

/***************************************************************************/
int sosFilter(sosfilter_t *p, const sfrac1q15 *x, sfrac1q15 *y,
              unsigned int n);
/***************************************************************************/
/*
 * Second-Order Section Filter.
 *
 * Process the linear input buffer "x" of "n" elements through the filter
 * object created by a previous call to the function "sosFilterCreate" pointed
 * to by "p".  Write the results to the output buffer "y" of "n" elements.
 * Return "0" on success or "-1" if an error occured and the contents of "y"
 * are undefined.
 */

/***************************************************************************/
firfilter_t *firFilterCreate(const sfrac1q15 *p, unsigned int n);
/***************************************************************************/
/*
 * Finite Impulse Response Filter Create
 *
 * Create a filter object from the coefficient array and return its pointer
 * on success, or NULL if an error occured.
 *
 * On success the returned pointer may be used by subsequent calls to the
 * function "firFilter" until it has been destroyed with the function
 * "firFilterDestroy".
 */

/***************************************************************************/
void firFilterDestroy(firfilter_t *p);
/***************************************************************************/
/*
 * Finite Impulse Response Filter Destroy
 *
 * Destroy a filter object, free the allocated memory, created by a previous
 * call to the function "firFilterCreate".  Note that the results of "p" used
 * by a call to "firFilter" after having been destroyed are undefined.
 */

/***************************************************************************/
void firFilterReset(firfilter_t *p);
/***************************************************************************/
/*
 * Finite Impulse Response Filter Reset
 *
 * Clear the specified filter object's history, i.e. reset the stored samples.
 */

/***************************************************************************/
int firFilterModify(sr_convert_t *srData, double dbAdjust);
/***************************************************************************/
/*
 * Modifies the filter levels of a firFilter pointed to by srData by a db
 * amount dbAdjust
 *
 * Expected args
 * sr_convert_t, double
 *
 * Returns a -1 if the Coefficient pointer is null, or if it cannot detect the
 * of fir filter, otherwise returns 0
 */

/***************************************************************************/
int firFilter(firfilter_t *p, const sfrac1q15 *x, sfrac1q15 *y,
              unsigned int n);
/***************************************************************************/
/*
 * Finite Impulse Response Filter
 *
 * Process the linear input buffer "x" of "n" elements through the filter
 * object created by a previous call to the function "firFilterCreate" pointed
 * to by "p".  Write the results to the output buffer "y" of "n" elements.
 * Return "0" on success or "-1" if an error occured and the contents of "y"
 * are undefined.
 */

/***************************************************************************/
voxapp_t *voxCreate(const struct VoxInitData *p);
/***************************************************************************/
/*
 * Create and return a pointer to a new voice activated object for later use
 * with the functions "isVoxActive" and "voxDestroy" from the information
 * provided in the structured pointed to by "p" or NULL if an error occured.
 * The detector implements hystersis and has two distince states, latched and
 * unlatched, that are controlled by the structure's contents as follows:
 *
 *  latch	- While in the unlatched state if the detected energy exceeds
 *                a function of this threshold then the detector enters the
 *                latched state. The range of allowable values are 0 to 99.
 *
 *  unlatch     - While in the latched state if the detected energy recedes
 *                a function of this threshold then the detector enters the
 *                unlatched state.  The range of allowable values are 0 to 99.
 *
 *  period      - while in the latched state a counter is set to a function
 *                of this value, conversely while unlatched this counter is
 *                decremented.  While the counter is not zero the signal is
 *                considered present and the detector reports "1", similarly
 *                while the counter is zero the signal is considered absent
 *                and the detector reports "false". The range of allowable
 *                values are 100 to 10 000 milliseconds.
 *
 * Note: "latch" shall be greater than or equal to "unlatch" and the detector
 * requires 8ksps for correct operation.
 */

/***************************************************************************/
voxapp_t *voxDbfsCreate(const struct VoxInitDbfsData *p);
/***************************************************************************/
/*
 * Create and return a pointer to a new voice activated object for later use
 * with the functions "isVoxActive" and "voxDestroy" from the information
 * provided in the structured pointed to by "p" or NULL if an error occured.
 * The detector implements hystersis and has two distince states, latched and
 * unlatched, that are controlled by the structure's contents as follows:
 *
 *  latch	- While in the unlatched state if the detected energy exceeds
 *                a function of this threshold then the detector enters the
 *                latched state. The range of allowable values are -100 dBfs to
 *                -15 dBfs.
 *
 *  unlatch     - While in the latched state if the detected energy recedes
 *                a function of this threshold then the detector enters the
 *                unlatched state.  The range of allowable values are -100 dBfs 
 *                to -15 dBfs.
 *
 *  period      - while in the latched state a counter is set to a function
 *                of this value, conversely while unlatched this counter is
 *                decremented.  While the counter is not zero the signal is
 *                considered present and the detector reports "1", similarly
 *                while the counter is zero the signal is considered absent
 *                and the detector reports "false". The range of allowable
 *                values are 100 to 10 000 milliseconds.
 *
 * Note: "latch" shall be greater than or equal to "unlatch" and the detector
 * requires 8ksps for correct operation.
 */
 
/***************************************************************************/
void voxDestroy(voxapp_t *p);
/***************************************************************************/
/*
 * Destroy, i.e. return any allocated resources to the operating system, a
 * voice activated object generated by a previous "voxCreate" call.
 *
 * Note: The resulting behavour is undefined if after an object is destroyed
 * an attempt is made to process it with a "isVoxActive" call.
 */

/***************************************************************************/
int isVoxActive(voxapp_t *p, sfrac1q15 x);
/***************************************************************************/
/*
 * Update the voice activated object state variables pointed to by "p" based
 * on the signed fractional 1.15 linear input sample "x".  Return "1" if an
 * audio signal is considered present, "0" if not, or "-1" if an error
 * occured.
 */

/***************************************************************************/
sfrac1q15 sineFirstQuadrant(ufrac1q15 x);
/***************************************************************************/
/*
 *  Return the value of of sin(x) where 0 <= x <= pi/2 and is quantized as
 *  an unsigned fractional Q1.15 number with a five term Taylor series
 *  approximation.  The returned value is a signed Q1.15 number.
 *
 *               x^3   x^5   x^7   x^9
 *  sin(x) = x - --- + --- - --- + --- - ...
 *               3!    5!    7!    9!
 *
 *                   1            3!           5!           7!
 *         = x ( 1 - -- x^2 ( 1 - -- x^2 ( 1 - -- x^2 ( 1 - -- x^2 ( ...
 *                   3!           5!           7!           9!
 */

/***************************************************************************/
sfrac1q15 synthesizer(struct SynthesizerType *dds);
/***************************************************************************/
/*
 *  Return the Q1.15 result of sin(dds->angle) with respect to dds->quadrant.
 *  Add dds->deltaAngle to dds->angle and wrap dds->angle about pi/2 and
 *  dds->quadrant about 0-3.  The instantaneous phase is given by:
 *
 *  phase = pi / 2 * dds->quadrant + dds->angle
 *
 *  The instantaneous rate of change of phase in terms of the desired output
 *  frequency is found according to:
 *
 *                           fo
 *  dds->deltaAngle = 2 * pi --
 *                           fs
 *
 *  Where: fo = output frequency
 *         fs = sample rate
 *
 *  Note:
 *
 *    Quadrant**  sin(pi / 2 * dds->quadrant + dds->angle)
 *    ----------  ---------------------------------------
 *        0        sineFirstQuadrant(dds->angle)
 *        1        sineFirstQuadrant(pi / 2 - dds->angle)
 *        2       -sineFirstQuadrant(dds->angle)
 *        3       -sineFirstQuadrant(pi / 2 - dds->angle)
 *
 *    **Maps one-to-one to the traditional numbering scheme of 1-4.
 *
 *    *** WARNING *** Due to a data type overflow error this function is
 *    deprecated and should not be used in new designs.  For new designs or
 *    fo to fs ratio greater than 0.39 use the "ddsCreate" family of
 *    functions.
 */

/***************************************************************************/
dds_t *ddsCreate(unsigned fs, double fo, double a);
/***************************************************************************/
/*
 * Direct Digital Synthesis object creator.  Allocate resources and
 * initialize a new synthesizer object with sample rate "fs" samples per
 * second, output frequency "fo" cycles per second, and linear amplitude "a"
 * referenced to full-scale (i.e. 0 to 1) for later use with "ddsOperate",
 * "ddsControl", and "ddsDestroy".
 *
 * Return a pointer to the newly created object or "NULL" if an error was
 * detected.
 */

/***************************************************************************/
int ddsOperate(dds_t *dds, sfrac1q15 *y, unsigned n);
/***************************************************************************/
/*
 * Direct Digital Synthesis utility.  Write the synthesizer's signed
 * fractional 1.15 fixed-point output to the buffer pointed to by "y" of "n"
 * elements.  Return "0" on success or "-1" if an error was detected.
 */

/***************************************************************************/
int ddsAlter(dds_t *dds, enum DdsAlterAttribute attrib, double x);
/***************************************************************************/
/*
 * Direct Digital Synthesis object atribute modification utility.  Modify
 * the object state variable referenced by "attrib" associated with the
 * object pointed to by "dds" to reflect the value "x".  Refer to the table
 * below.  Return "0" on success or "-1" if an error occured.
 *
 *  attribute                   x                   description
 *  --------------------------  ------------------  -------------------------
 *  DDS_ATTRIB_PHASE_SET        DBL_MIN to DBL_MAX  phase
 *  DDS_ATTRIB_PHASE_ADD        DBL_MIN to DBL_MAX  phase change
 *  DDS_ATTRIB_DELTAPHASE_SET   DBL_MIN to DBL_MAX  frequency
 *  DDS_ATTRIB_DELTAPHASE_ADD   DBL_MIN to DBL_MAX  freq. change
 *  DDS_ATTRIB_AMPLITUDE_SET    0.0     to 1.0      maximum level change
 *  DDS_ATTRIB_AMPLITUDE_SCALE  DBL_MIN to DBL_MAX  relative level change
 *
 * Notes:
 *  1. Negative frequency (delta phase) is not currently supported.
 *  2. Amplitude saturates to SFRAC1Q15_MAX; this introduces a 1 LSB error but
 *     greatly simplifies usage by allowing "1.0" full scale instead of "-1".
 */

/***************************************************************************/
void ddsDestroy(dds_t *dds);
/***************************************************************************/
/*
 * Deallocate the synthesizer resources associated with pointer "dds"
 * returned by a previous "ddsCreate" function call.  Undefined behaviour
 * will result if after destruction "dds" is used as an argument with
 * "ddsOperate" or "ddsControl" function calls.
 */

/***************************************************************************/
int alcConfigParser(const char *filename, struct AlcInitType *);
/***************************************************************************/
/*
 * Parse the configuration file "filename" capturing the values associated
 * with the initialization structure.
 *
 * If the configuration file cannot be opened, or a given tag cannot be found,
 * or a value cannot be converted, or a converted value is out-of-bounds, then
 * use the default value.
 *
 * Return "0" on success or "-1" if the filename pointer is NULL, of length
 * zero, or the destination initialization structure pointer is NULL.
 *
 * Automatic Level Control configuration
 * -------------------------------------
 * parameter tag                 description
 * ----------------------------  --------------------------------------------
 * ALC_SAMPLERATE                samples per second
 * ALC_TIME_ATTACK               period to shift from max to min gain
 * ALC_TIME_HOLD                 constant gain period before increase
 * ALC_TIME_RELEASE              period to shift from min to max gain
 * ALC_GAIN_MAX                  maximum gain
 * ALC_GAIN_MIN                  minimum gain
 * ALC_GAIN_RUN                  initial running gain
 * ALC_SATURATE                  hard-limiter clipping level
 * ALC_HYSTERESIS_HIGH           high-level tracking threshold
 * ALC_HYSTERESIS_LOW            low-level tracking threshold
 * ALC_MINIMUM_THRESHOLD         minimum average magnitude
 *
 * parameter tag                 variable  units      minimum  maximum  default
 * ----------------------------  --------  ---------  -------  -------  -------
 * ALC_SAMPLERATE                sps       Hz         8000     8000     8000
 * ALC_TIME_ATTACK               tA        s          0.001    5.000    0.050
 * ALC_TIME_HOLD                 tH        s          0.001    5.000    0.250
 * ALC_TIME_RELEASE              tR        s          0.001    5.000    2.000
 * ALC_GAIN_MAX                  gMax      dB         0.0      40.0     36.0
 * ALC_GAIN_MIN                  gMin      dB         -20.0    0.0      -12.0
 * ALC_GAIN_RUN                  gRun      dB         -20.0    40.0     -12.0
 * ALC_SATURATE                  sat       dBfs       -20.0    0.0      -3.0
 * ALC_HYSTERESIS_HIGH           high      dBfs       -40.0    0.0      -9.02
 * ALC_HYSTERESIS_LOW            low       dBfs       -40.0    0.0      -9.04
 * ALC_MINIMUM_THRESHOLD         min       dBfs       -100.0   0.0      -60.0
 */

/***************************************************************************/
alc_t *alcCreate(const struct AlcInitType *p);
/***************************************************************************/
/*
 * Automatic Level Control creator.  Return a pointer to a newly created
 * ALC object, allocate and initialize resources, for later use with the
 * functions "alcDestroy" and "alcOperate" based on the configuration
 * parameters stored within the initialization structure pointed to by "p".
 * Return NULL if an error was detected.
 *
 * To maximize the probability of acceptable performance the following rules
 * and guidelines must be considered:
 *
 * Rules that shall be followed:
 *  1. Sample rate, attack time, hold time, and release times shall be greater
 *     than zero.
 *  2. Maximum gain shall be greater than the minimum gain.
 *  3. Saturation, hystersis high and low, and minimum threshold levels shall
 *     be less than zero.
 *  4. Hysteresis high level shall be greater than or equal to the low level.
 *  5. The initial running gain shall be greater than or equal to the minimum
 *     gain and less than or equal to the maximum gain.
 *
 * Guidelines that should be followed:
 *  1. Attack time should be a small as practical.
 *  2. Hold time should be greater than attack time and less than release time.
 *  3. Release time should be greater than attack time and as large as
 *     practical without making the overall system response too slow.
 *  4. Ratio of the difference between the minimum and maximum gains to attack
 *     time should be significantly less than the minimum gain.
 *  5. Saturation level should be greater than the hysteresis and minimum
 *     threshold levels.
 *
 * Significant effort was invested in developing the default configuration
 * values that should be acceptable for most users.  Due to the non-linear and
 * non-analytic nature of ALC any new set of configuration parameters must
 * tested by methodically varying a test-tone's frequency and amplitude over
 * the band and range, respectively, of interest to ensure the resulting
 * behavour is stable (i.e. does not oscillate).
 */

/***************************************************************************/
void alcDestroy(alc_t *p);
/***************************************************************************/
/*
 * Automatic Level Control destroyer.  Deallocate resources reserved by the
 * ALC object pointed to by "p" crerated by a previous call to "alcCreate".
 */

/***************************************************************************/
int alcModify(alc_t *p, unsigned attr, double y);
/***************************************************************************/
/*
 * Automatic Level Control modification utility function.  Modify the object
 * pointed to by "p" created by a previous "alcCreate" function call
 * altering the attribute identified by "attr" by the value "y" according to
 * the following table.  On success return "0" indicating the requested
 * action was taken otherwise return "-1" if an error was detected and the
 * object was unaffected.
 * 
 *   attribute
 *   -----------------------------
 *   identifier  description        action
 *   ----------  -----------------  ------------------------
 *   0           delta gain enable  boolean value set to "x"
 */

/***************************************************************************/
int alcOperate(alc_t *p, const sfrac1q15 *x, sfrac1q15 *y, unsigned int n);
/***************************************************************************/
/*
 * Process the input data array pointed to by "x" of "n" elements by the
 * Automatic Level Control object pointed to by "p" and write output data
 * array to the buffer space pointed to by "y" also of "n" elements.  Return
 * "0" on success or "-1" if an error was detected.
 *
 * The ALC processes an infinite long input stream by analyzing buffers of
 * finite length on a sample-by-sample basis.  After the DC offset is removed
 * the resulting average magnitude is calculated and gain is applied.  The
 * resulting signal-with-gain is processed by a hard-limiter and the result is
 * written to the output stream finite length buffer.  If the average
 * signal-without-gain magnitude is greater than a threshold then the gain to
 * be applied to the next sample shall be modified as described below,
 * otherwise the gain remains unchanged.
 *
 * If the signal-with-gain-and-saturation is greater than the high hysteresis
 * level then consider the signal "latched" and "attack" (i.e. reduce) the gain
 * unless the gain is already at the minimum value.  Once latched if the signal
 * is less than the low hystersis level and the hold time has expired then
 * consider the signal "unlatched" and "release" the gain inhibit control (i.e.
 * increase) the gain unless already at the maximum value.  If a latched signal
 * is between the hystersis levels then continue to consider the signal latched
 * and do not modify the gain.  If the signal'average magnitude without DC
 * offset and prior to gain is less than a minimum threshold then suspend gain
 * changes.
 *
 * A short attack time suppresses annoying, and potentially uncomfortable,
 * increases in signal level by quickly attenuating the signal.  A long hold
 * time ensures that relatively large amplitude low frequency, potentially
 * inaudiable, components do not cause the gain "pumping".  Release times of
 * long periods ensure the gain is increased relatively slowly that ensures
 * the compression doesn't track the audio enevelop too closely.  Disabling
 * gain adjustment when the signal magnitude is very small supresses noise
 * "hunting" when no signal is present and also guarentees that when an
 * intermittenthe signal resumes that a listener preceives the same apparant
 * volume throughout the entire transmission.
 *
 * When the delta-gain enable is cleared (enabled by default at creation time)
 * by an appropriate "alcModify" function call, all modifications described
 * above are disabled.  This simulates the effect of lowering the input signal
 * below the minimum threshold.
 */

/***************************************************************************/
int eiatrcEncodeConfigParser(const char *filename, struct EiaTrcEncodeInit *);
/***************************************************************************/
/*
 * Parse the configuration file "filename" capturing the values associated
 * with the initialization structure.
 *
 * If the configuration file cannot be opened, or a given tag cannot be found,
 * or a value cannot be converted, or a converted value is out-of-bounds, then
 * use the default value.
 *
 * Return "0" on success or "-1" if the filename pointer is NULL, of length
 * zero, or the destination initialization structure pointer is NULL.
 * 
 * Electronics Industry Association Tone Remote Control encoder configuration
 * --------------------------------------------------------------------------
 * parameter tag                 description
 * ----------------------------  --------------------------------------------
 * EIATRC_ENCODE_SAMPLERATE      samples per second
 * EIATRC_ENCODE_NOMINAL_LEVEL   level to which tone levels are referenced
 * EIATRC_ENCODE_HLGT_LEVEL      High-Level Guard Tone level
 * EIATRC_ENCODE_FT_LEVEL        Function Tone level
 * EIATRC_ENCODE_LLGT_LEVEL      Low-Level Guard Tone level
 * EIATRC_ENCODE_HLGT_FREQ       High-Level Guard Tone frequency
 * EIATRC_ENCODE_FT_FREQ         Function Tone frequency
 * EIATRC_ENCODE_LLGT_FREQ       Low-Level Guard Tone frequency
 * EIATRC_ENCODE_HLGT_PERIOD     High-Level Guard Tone period
 * EIATRC_ENCODE_FT_PERIOD       Function Tone period
 *
 * parameter tag                 variable     units   minimum  maximum  default
 * ----------------------------  --------     ------  -------  -------  -------
 * EIATRC_ENCODE_SAMPLERATE      sps          n.a.    see table below   0
 * EIATRC_ENCODE_NOMINAL_LEVEL   level        dBfs    -20      0        -9.03 
 * EIATRC_ENCODE_HLGT_LEVEL      hlgt.level   dB      -30      +15      +5
 * EIATRC_ENCODE_FT_LEVEL        ft.level     dB      -30      +15      -5
 * EIATRC_ENCODE_LLGT_LEVEL      llgt.level   dB      -30      +15      -25
 * EIATRC_ENCODE_HLGT_FREQ       hlgt.freq    n.a.    see table below   0
 * EIATRC_ENCODE_FT_FREQ         ft.freq      n.a.    see table below   13
 * EIATRC_ENCODE_LLGT_FREQ       llgt.freq    n.a.    see table below   0
 * EIATRC_ENCODE_HLGT_PERIOD     hlgt.period  ms      0        1000     120
 * EIATRC_ENCODE_FT_PERIOD       ft.period    ms      0        500      40
 *
 * Sample Rate table
 * -----------------
 * Frequency (Hz)  Configuration value
 * --------------  -------------------
 * 8000            0
 *
 * High and Low Level Guard Tone frequency table
 * ---------------------------------------------
 * Frequency (Hz)  Configuration value
 * --------------  -------------------
 * 2175            0
 *
 * Function Tone frequency table
 * -----------------------------
 * Frequency (Hz)  Configuration value
 * --------------  -------------------
 *  650             0
 *  750             1
 *  850             2
 *  950             3
 * 1050             4
 * 1150             5
 * 1250             6
 * 1350             7
 * 1450             8
 * 1550             9
 * 1650            10
 * 1750            11
 * 1850            12
 * 1950            13
 * 2050            14
 */

/***************************************************************************/
eiatrc_encode_t *eiatrcEncodeCreate(const struct EiaTrcEncodeInit *p);
/***************************************************************************/
/*
 * Electronics Industry Association Tone Remote Control encoder object
 * creator.  Allocate resources and initialize an object based on the
 * information pointed to by "p" for later use by the functions
 * "eiatrcEncodeDestroy", "eiatrcEncode", and "eiatrcEncodeCtrl". Note: If "p"
 * is "NULL" then the object is created with default values.  A detailed
 * explaination of the initialization structure parameters is next.
 *
 *  sps
 *   The sample rate expressed in samples per second.  Use the supplied
 *   enumeration to provide this value.  The default value is 8ksps.
 *
 *  level
 *   This represents the nominal numeric level to which the encoded tones are
 *   referenced.  With units of decibels full-scale the default value is
 *   -9.03 dBfs.
 *
 *  hlgt, llgt
 *   The High Level Guard Tone (HLGT), and Low Level Guard tone (LLGT) have
 *   three associated parameters:
 *    freq
 *     Use the supplied enumeration to provide this value.  The currently
 *     supported and default figure is 2175Hz.
 *    level
 *     With units of decibels (dB) this value represents the tone's amplitude
 *     referenced to the nominal level (see above).  The default HLGT is +5.0dB,
 *     while LLGT is -25dB.
 *    period
 *     The time to encode the tone measured in milliseconds.  The default for
 *     HLGT is 120ms, while a default value for LLGT is meaningless as LLGT
 *     encoding begins after the function tone is complete and is continuous
 *     until explictly stopped.
 *
 *  ft
 *   The Function Tone (FT) has three associated parameters:
 *    freq
 *     Use the supplied enumeration to provide this value.  The values are
 *     defined by the set { 650, 750, ... , 1950, 2050 } with the default
 *     being 1950.
 *    level
 *     With units of decibels (dB) this value represents the tone's amplitude
 *     referenced to the nominal level (see above).  The default figure is
 *     -5.0dB.
 *    period
 *     The time to encode the tone measured in milliseconds.  The default is
 *     40ms. 
 *
 * Return a pointer to the newly created object or "NULL" if an error was
 * detected.
 * 
 * Refer to "eiatrcEncodeDestroy", "eiatrcEncode", and "eiatrcEncodeCtrl" for
 * more details.
 */

/***************************************************************************/
void eiatrcEncodeDestroy(eiatrc_encode_t *p);
/***************************************************************************/
/*
 * Electronics Industry Association Tone Remote Control encoder object
 * destroyer.  Deallocate resources associated with "p," the pointer returned
 * by a previous call to "eiatrcEncodeCreate".  If "p" is used later as an
 * argument with "eiatrcEncode" or "eiatrcEncodeCtrl" the reulting behaviour
 * is undefined.
 */

/***************************************************************************/
int eiatrcEncode(eiatrc_encode_t *p, const sfrac1q15 *s, sfrac1q15 *t,
                 unsigned n);
/***************************************************************************/
/*
 * Electronics Industry Association Tone Remote Control encoder.  Write to the
 * output buffer "t" of "n" elements the appropriate data based on the input
 * buffer "s", also of "n" elements, and the state variable structure pointed
 * to by "p".
 *
 * The encoder resides in two primary states, idle, and active.  When idle the
 * encoder acts only as a guard tone notch filter.  When active a tone is mixed
 * with the notch-filtered input as a sequential function of three distinct
 * sub-states as follows:
 *
 *  A. High Level Guard Tone (HLGT)
 *  B. Function Tone (FT)
 *  C. Low Level Guard Tone (LLGT)
 *
 * The levels, frequency, and duration of all three are defined at creation
 * time notwithstanding the LLGT duration; it is encoded until explicitly
 * stopped.  Note: the function tone can be changed dynamically.
 *
 * On success while encoding any of the HLGT or FT or LLGT return "1" and if
 * there was nothing to encode return "0" otherwise return "-1" if an error
 * was detected and the output buffer contents are undefined.  Note that LLGT
 * is meant to encode forever.
 *
 * Refer to "eiatrcEncodeCreate", and "eiatrcEncodeCtrl" for more details.
 */

/***************************************************************************/
int eiatrcEncodeCtrl(eiatrc_encode_t *p, enum EIA_TRC_ENCODE_CTRL x, int y);
/***************************************************************************/
/*
 * Electronics Industry Association Tone Remote Control encoder object dynamic
 * controller.  Modify a previously created encoder object to reflect the new
 * state data "y" depending on the context "x" as listed below:
 *
 *  context: EIA_TRC_ENCODE_CTRL_STATE
 *   data: boolean
 *    action: on non-zero data begin encoding a new "HLGT-FT-LLGT" sequence
 *            while on zero data hault encoding a previously started sequence.
 *
 *  context: EIA_TRC_ENCODE_CTRL_BURST
 *   data: boolean
 *    action: on non-zero data begin encoding a new "HLGT-FT" sequence
 *            while on zero data hault encoding a previously started sequence.
 *
 *  context: EIA_TRC_ENCODE_CTRL_FT
 *   data: EIA_TRC_FUNCTION_TONE enumeration
 *    action: change the function tone for future encode sequences to
 *            frequency "X", where "X" is bounded by the set
 *            { 650, 750, ... , 1950, 2050 }.
 *
 * Note after completeing a "HLGT-FT-LLGT" by an explict hault command, or on
 * automatic completion of a "HLGT-FT" sequence the state machine returns to
 * idle requiring a subsequent "eiatrcEncodeCtrl" function call to start a new
 * sequence.
 *
 * Return "0" on success or "-1" if an error was detected.
 *
 * Refer to "eiatrcEncode" for more details.
 */

/***************************************************************************/
int eiatrcEncoderQueryState(eiatrc_encode_t *p,
                            enum EIA_TRC_ENCODE_STATE_REPORT *q);
/***************************************************************************/
/*
 * Electronics Industry Association Tone Remote Control encoder object state
 * reporting mechanism.  Write the current state of the object refered to by
 * "p" to the location pointed to by "q".  Return "0" on success or "-1" if
 * an error was detected and the value pointed to "q" is undefined.
 *
 * The reported state will indicate that the object is idle, or encoding one
 * of either the HLGT, FT, or LLGT; refer to the enumeration.
 */

/***************************************************************************/
sr_convert_t *sampleConvertCreate(const struct SampleRateConvertInit *p);
/***************************************************************************/
/*
 * Sample rate converter object creator.  Allocate and initialize resources
 * for later use with the associated interpolation or decimation, and
 * destroyer functions according to the configuration information pointed to
 * by "p" as follows:
 *
 *  type   - converter method, interpolation or decimation
 *  filter - anti-aliasing/anti-artifact filtering method
 *  n      - expected input buffer element count
 *  m      - expected output buffer element count
 *  delay  - delay line length in ms
 *
 * The element count ratio must be an integer, output to input for
 * interpolation or input to output for decimation.  Observe this quotient
 * defines the sample rate conversion ratio.
 *
 * On success return a pointer to the newly minted object, otherwise on
 * failure return "NULL".
 *
 * Notes:
 *
 * 1. The currently implemented "SAMPLERATE_CONVERT_BIPHASE_INTERPOLATE"
 * and "SAMPLERATE_CONVERT_BIPHASE_DECIMATE" are hard-coded for a resampling
 * ratio of 1:2 and 2:1 respectively, hence their names, and can only be used
 * with the FIR filter types.
 *
 * 2. An excellent discussion of polyphase filter structures can be found at:
 * "http://www.ws.binghamton.edu/fowler/fowler%20personal%20page/EE521_files/
 * IV-05%20Polyphase%20FIlters_2007.pdf"
 *
 */

/***************************************************************************/
void sampleConvertDestroy(sr_convert_t *p);
/***************************************************************************/
/*
 * Sample rate converter object destroyer.  Deallocate any resources
 * associated with the object pointed to by "p" returned by a previous
 * "sampleConvertCreate" call.  Undefined behavour shall result if "p" is
 * subquently used as a function argument.
 */

/***************************************************************************/
int sampleConvertInterpolate(sr_convert_t *p, const sfrac1q15 *s, unsigned n,
                             sfrac1q15 *t, unsigned m);
/***************************************************************************/
/*
 * Interpolator.  Read the input sample buffer contents pointed to by "s"
 * of "n" elements and interpolate according to the object pointed to by "p"
 * writing the results to the output buffer pointed to by "t" of "m"
 * elements.  The values "m" and "n" shall equal those defined at creation
 * time.
 *
 * On success return "0", otherwise if an error was detected return "-1" and
 * the output buffer contents are undefined.
 */

/***************************************************************************/
int sampleConvertDecimate(sr_convert_t *p, const sfrac1q15 *s, unsigned n,
                          sfrac1q15 *t, unsigned m);
/***************************************************************************/
/*
 * Decimator.  Read the input sample buffer contents pointed to by "s" of "n"
 * elements and decimate according to the object pointed to by "p" writing
 * the results to the output buffer pointed to by "t" of "m" elements.  The
 * values "m" and "n" shall equal those defined at creation time.
 *
 * On success return "0", otherwise if an error was detected return "-1" and
 * the destination buffer contents are undefined.
 */

/***************************************************************************/
int sampleConvertModify(sr_convert_t *p, enum SampleConvertModify chx, ...);
/***************************************************************************/
/*
 * Modify, takes the filter object and then based on the enum modifies a
 * property of the object, currently only firFilterAdjust is implemented
 * which modifies the levels.
 *
 * chx                                    expected argument(s)
 * -------------------------------------  --------------------
 * SAMPLE_CONVERT_MODIFY_DSP_ADJUST_GAIN  double (gain in dB)
 * SAMPLE_CONVERT_MODIFY_SET_MUTE         boolean (mute state)
 *
 * Returns a -1 if an invalid choice is given or if the filter is null and 0 
 * on success.
 *
 * Note: The mute state shall only be modified from off to on from the same
 * context as the associated interpolation or decimation operation.  In other
 * words setting the mute state is not thread safe; failure to follow this
 * rule could result in undesirable audio effects such as audiable "pic" or
 * "pop" sounds.
 */

/***************************************************************************/
drc_t *dynamicRangeCompressorCreate(const struct DynamicRangeCompressorCfg *p);
/***************************************************************************/
/*
 * Dynamic range compressor object creator. Allocate and initialize resources
 * for later use with the associated compressor functions according to the
 * configuration information pointed to by "p" as follows:
 *
 *  vt     - linear threshold level above which compression is applied, also
 *           known as the "knee of compression" (dBfs) -DBL_MAX to 0.0.
 *
 *  vol    - hard-limited output level (dBfs) -DBL_MAX to 0.0; must be greater
 *           than the linear threshold level.
 *
 *  ratio  - ratio of input gain to output gain applied above the linear
 *           threshold level and below the hard-limit output level,
 *           dimensionless (dB/dB) 0.0 to DBL_MAX.  Observe that a compression
 *           ratio less than one is by definition gain.
 *
 * If "p" is "NULL" then the object is created using the following default
 * values sutiable for most general purpose applications:
 *
 *  vt    -9.03 dBfs
 *  vol    0.0  dBfs
 *  ratio  2:1
 *
 * On success return a pointer to the newly minted object ready for use as an
 * argument for the compressor functions, otherwise return "NULL" indicating
 * an error occured.
 *
 *              Dynamic Range Compressor transfer function
 *
 *                  Vout
 *                  (dB)
 *                    ^
 *                Vol |                     xxxx...
 *                    |                   x
 *                    |                 x    ---
 *                    |               x       | dVout
 *                    |             x        ---
 *                    |           x
 *                Vt  |         x           ratio = dVin/dVout (dB/dB)
 *                    |        x    |---|
 *                    |       x     dVin 
 *                    |      x
 *                    |     x
 *                    |    x
 *                    |   x
 *                    |  x
 *                    | x
 *                    |x
 *                    +-------------------------> Vin (dB)
 */

/***************************************************************************/
void dynamicRangeCompressorDestroy(drc_t *p);
/***************************************************************************/
/*
 * Dynamic range compressor object destroyer.  Deallocate any resources
 * associated with the object pointed to by "p" returned by a previous
 * "dynamicRangeCompressorCreate" call.  Undefined behavour shall result if
 * the object that was pointed to by "p" is subquently used as a function
 * argument.
 */

/***************************************************************************/
int dynamicRangeCompressorGain(drc_t *p, sfrac1q15 *x, unsigned n, ufrac8q8 g);
/***************************************************************************/
/*
 * Dynamic range compressor with gain. Process the input sample buffer
 * contents pointed to by "x" of "n" elements in situ by first applying the
 * linear gain g then a transfer function characterized by the object pointed
 * to by "p".  Note the gain argument is of type ufrac8q8 thus allowing a
 * positve gain within the range 0.0039 to 255.9961 (-48.2dB to +48.2dB).
 * Observe the 0dB value is equal to 256.  On success return "0", otherwise
 * return "-1" indicating an error was detected and the buffer contents were
 * unchanged.
 */

/***************************************************************************/
int dynamicRangeCompressorMixer(drc_t *p, sfrac1q15 **x, unsigned n,
                                sfrac1q15 *y, unsigned m);
/***************************************************************************/
/*
 * Dynamic range compressor/mixer.  Mix and compress the dynamic range of the
 * audio samples contained within "n" buffers on the list pointed to by "x"
 * writing the results to the output buffer pointed to by "y" according to the
 * object pointed to by "p" leaving the input buffer contents unchanged.  All
 * of the audio buffers shall contain "m" elements.  On success return "0",
 * otherwise return "-1" indicating an error occured and the output buffer
 * contents were unchanged.
 *
 * In other words:
 *
 *  y[i] = f(p, x[0][i] + x[1][i] + x[2][i] + ... + x[n-2][i] + x[n-1][i])
 *
 * Where:
 *
 *  i = 0, 1, ... , m-1
 */

/***************************************************************************/
sfrac1q15 dynamicRangeCompressorSample(drc_t *p, sfrac17q15 x);
/***************************************************************************/
/*
 * Dynamic range compressor.  Compress the dynamic range of the single sample
 * "x" according to the object pointed to by "p" returning the result.
 */

/***************************************************************************/
void **wavread(const char *filename, unsigned *ch, unsigned *sr,
               unsigned *nbits, unsigned *n);
/***************************************************************************/
/*
 * Read a PCM waveform (.wav) sound file named "filename" writing the number
 * of channels to the location pointed to by "ch", the sample rate (ksps) to
 * the location pointed to by "sr", the data size to the location pointed
 * to by "nbits", and the number of samples per channel to the location
 * pointed to by "n".  On success return a pointer associated with the file
 * data, see below, otherwise "NULL" if an error was detected and none of the
 * argument locations pointed to were altered.
 *
 * The returned value points to a dynamically allocated list that contains
 * pointers to dynamically allocated areas that contain the file's data.  Note
 * that eventually both pieces of pointer data must be returned to the heap
 * with "free".
 *
 * The different data types are defined by the following table.  For more
 * details on the integer types refer to "types_frac.h" and "limits_frac.h":
 *
 *                          data range
 * nbits  data type      minimum      maximum
 * -----  ---------  -----------  -----------
 * 8      sfrac1q7          -128         +127	TBD
 * 16     sfrac1q15       -32768       +32767 
 * 24     sfrac9q23     -8388608     +8388607	TBD
 * 32     float             -1.0         +1.0	TBD inconsistent with PCM
 *
 * Example 1: If this function returned a pointer "p" after reading a wavefrom
 * file with 16-bit data the "m"th channel's "k"th sample could be referenced
 * as:
 *
 *   ((sfrac1q15**)p)[m][k]
 *
 * Where "m" is bounded by "0,1,2, ... *ch - 1" and "k" by "0,1,2, ... *n - 1".
 *
 * Example 2: One way to free the provided data pointers could be:
 *
 *  ...
 *  unsigned ch, sr, nbits, n;
 *  p = wavread(filename, &ch, &sr, &nbits, &n);
 *
 *  if (p != NULL && nbits == SFRAC1Q15_BITS) {
 *    unsigned i;
 *    for (i = 0; i < ch; free(((sfrac1q15**)p)[i++]));
 *    free(p);
 *  }
 *  ...
 *
 * Notes:  A (.wav) file is a subset of the Resource Interchange File Format
 * "RIFF", a tagged file type.  The file's various sub-sections are demarked
 * by a four ASCII character tag, an unsigned 32-bit little-endian integer
 * length of section's contents followed by the little-endian section data.
 * At a bare minimum the file contains the "RIFF" definition, a "fmt "section
 * that describes the encoded data, and a "data" holding the data of interest.
 * The read/write functions here support the canonical format and ignore any
 * other sections.
 *
 * Section  Offset  Size  Description
 * -------  ------  ----  ---------------------------------------------------
 * RIFF     0       4     ASCII letters 'R' 'I' 'F' 'F'
 *          4       4     little-endian remaining file length
 *          8       4     ASCII letters 'W' 'A' 'V' 'E'
 * format   x       4     ASCII letters 'f' 'm' 't' ' '
 *          x + 4   4     little-endian remaining section length (0x00000010)
 *          x + 8   2     little-endian quantization type (0x0001 = PCM)
 *          x + 10  2     little-endian channel count (ch)
 *          x + 12  4     little-endian sample rate (sr)
 *          x + 16  4     little-endian byte rate (sr * ch * bps / 8)
 *          x + 20  2     little-endian block align (ch * bps / 8)
 *          x + 22  2     little-endian bits per sample (bps)
 *
 * data     y       4     ASCII letters 'd' 'a' 't' 'a'
 *          y + 4   4     little-endian data (d) length (dlen)
 *          y + 8   dlen  little-endian d(0,0) d(1,0) ... d(ch-1,0) d(0,1) ...
 */

/***************************************************************************/
int wavwrite(const char *filename, unsigned ch, unsigned sr, unsigned nbits,
             unsigned n, void **lst);
/***************************************************************************/
/*
 * Write a PCM waveform (.wav) sound file named "filename" with "ch" channels,
 * "sr" sample rate (ksps), data size "nbits", "n" samples per channel, and
 * the data associated with the pointer "lst".  On success return "0",
 * otherwise return "-1" indicating an error occured.  Note that in either
 * case none of of the data associated with "lst" is altered.
 *
 * The different data types are defined by the following table.  For more
 * details on the integer types refer to "types_frac.h" and "limits_frac.h":
 *
 *                          data range
 * nbits  data type      minimum      maximum
 * -----  ---------  -----------  -----------
 * 8      sfrac1q7          -128         +127	TBD
 * 16     sfrac1q15       -32768       +32767 
 * 24     sfrac9q23     -8388608     +8388607	TBD
 * 32     float             -1.0         +1.0	TBD inconsistent with PCM
 *
 * The area pointed to by "lst" is interpreted as a list of pointers that each
 * point to an individual channel.  For an example illustration of the
 * expected data organization refer to "wavread".
 *
 * If the provided filename already exists it will be overwritten.
 *
 * For more file format details refer to the function "wavread".
 */

/***************************************************************************/
int awgnGeneratorSFRAC1Q15(unsigned n, double mean, double rms,
                           sfrac1q15 *x, unsigned m);
/***************************************************************************/
/*
 * Additive White Gausian Noise Generator using the central limit theorem
 * method.  Calculate and write "m" normally distributed pseudo-random
 * samples to the location originating at "x" based on "n" random variables
 * scaled to have the specified "mean" and "rms". On success return "0"
 * indicating the output samples were written as expected, otherwise return
 * "-1" indicating an error occured and the contents pointed to by "x" were
 * unaffected.
 *
 * The value "mean" defines the output's average value, referenced to the
 * full-scale linear range from -1.0 to +1.0.  The "rms" value defines the
 * time varying component's root-mean squared value.
 *
 * Recall the central limit theorem can be interpreted as stating, among
 * other things, the sum of "n" independent random variables will approach a
 * normal distribution as "n" approaches infinity.  "Simulation of
 * Communication Systems" by M. C. Jeruchim, P. Balaban and K. S. Shanmugan
 * recommend "n" greater than or equal to twenty.
 *
 * Notes:
 * 1. Output saturates at SFRAC1Q15_MIN and SFRAC1Q15_MAX.
 *
 * 2. Recall that uniform distributions in the range [0, 1], mean equals 0.5
 * and the variance 1/12, and the variance is equal to the rms value
 * squared.
 */

/***************************************************************************/
int initWindowDouble(enum WindowType x, double *p, unsigned n);
/***************************************************************************/
/*
 * Initialize a window function of the specified enumerated type associated
 * with rectangular, triangular, hann, or hamming.  Write the window
 * function to the buffer pointed to by "p" with "n" elements.  Each element
 * shall have a magnitude greater than or equal to 0.0 and less than or equal
 * to 1.0.  On success return "0", otherwise return "-1" indicating that an
 * error occured and the area pointed to by "p" was un affected.
 */

/***************************************************************************/
signal_measure_t *signalMeasureCreate(const struct SignalMeasureCfg *cfg);
/***************************************************************************/
/*
 * Signal measurement object creation function.  Based on the configuration
 * information pointed to by "cfg" create a new signal measurement object.
 * On success return a pointer to the newly minted object for use as an
 * argument with the functions "signalMeasureOperate", and
 * "signalMeasureDestroy", otherwise return "NULL" indicating and error
 * occured.
 *
 * Configuration parameters:
 *
 *  sampleRate        Number of samples per second.
 *
 *  period            The time in seconds between signal measurement
 *                    reports.  Internally this is truncated to the nearest
 *                    sample period, assummed to be 1/8000s.  In other words
 *                    the expected sample rate is 8ksps.
 *
 *  id_str            A disambiguation string intended to disambiguate between
 *                    mutliple instances of the measurement object.
 */

/***************************************************************************/
void signalMeasureDestroy(signal_measure_t *p);
/***************************************************************************/
/*
 * Signal measurement object destroyer function.  Deallocate any resources
 * associated with the object pointed to by "p".  Subsequent use of "p" as an
 * argument with the functions "signalMeasureDestroy" or "signalMeasureOperate"
 * will produce undefined behavour.
 */

/***************************************************************************/
int signalMeasureOperate(signal_measure_t *p, const sfrac1q15 *src,
                         unsigned n);
/***************************************************************************/
/*
 * Signal measurement generator function.  Process the input sample buffer
 * pointed to by "src" of "n" elements by the measurement object pointed to
 * by "p" returned by a previous call to "signalMeasureCreate".  After each
 * report period defined at creation time elapses the following line of
 * output is sent to stdout:
 *
 *   "S: mean X XdBfs, max X XdBfs, min X XdBfs, rms X XdBfs, rms ac X XdBfs"
 *
 *   Where:
 *
 *     S      -> disambiguation string set at creation time
 *     X      -> measurement value expressed as raw linear and dBfs as per:
 *       mean   -> average, also known as "DC offset"
 *       max    -> largest
 *       min    -> smallest
 *       rms    -> root-mean-squared
 *       rms ac -> time varying component rms value, i.e. without DC offset
 *
 * On success return "0" otherwise "-1" to indicate an error was detected.
 */

#endif

/***************************************************************************/
/**                                                                       **/
/**                               EOF                                     **/
/**                                                                       **/
/***************************************************************************/
