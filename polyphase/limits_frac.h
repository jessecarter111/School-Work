/*
                             *******************
******************************* C HEADER FILE *******************************
**                           *******************                           **
**                                                                         **
** filename  : limits_frac.h                                               **
** author    : David A. Bardsley                                           **
** created   : 2009-09-25                                                  **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (C) 2009-2017, Pantel International Incorporated              **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************

*/

#ifndef __LIMITSFRAC_INCLUDED
#define __LIMITSFRAC_INCLUDED

/***************************************************************************/
/**                                                                       **/
/**                     TYPDEFS AND STRUCTURES                            **/
/**                                                                       **/
/***************************************************************************/

#define SFRAC1Q7_BITS	8
#define SFRAC1Q7_MAX	+127
#define SFRAC1Q7_MIN	-128

#define UFRAC0Q16_BITS	16
#define UFRAC0Q16_MAX	65535
#define UFRAC0Q16_MIN	0

#define UFRAC1Q15_BITS	16
#define UFRAC1Q15_MAX	65535
#define UFRAC1Q15_MIN	0

#define UFRAC8Q8_BITS	16
#define UFRAC8Q8_MAX	65535
#define UFRAC8Q8_MIN	0

#define SFRAC8Q8_BITS	16
#define SFRAC8Q8_MAX	+32767
#define SFRAC8Q8_MIN	-32768

#define SFRAC1Q15_BITS	16
#define SFRAC1Q15_MAX	+32767
#define SFRAC1Q15_MIN	-32768

#define SFRAC2Q14_BITS	16
#define SFRAC2Q14_MAX	+32767
#define SFRAC2Q14_MIN	-32768

#define SFRAC11Q5_BITS	16
#define SFRAC11Q5_MAX	+32767
#define SFRAC11Q5_MIN	-32768

#define UFRAC3Q29_BITS	32
#define UFRAC3Q19_MAX	4294967295
#define UFRAC3Q29_MIN	0

#define UFRAC4Q28_BITS	32
#define UFRAC4Q28_MAX	4294967295
#define UFRAC4Q28_MIN	0

#define SFRAC9Q23_BITS	32
#define SFRAC9Q23_MAX	+8388607	/* TODO re-evaluate this figure */
#define SFRAC9Q23_MIN	-8388608	/* TODO re-evaluate this figure */

#define SFRAC1Q31_BITS	32
#define SFRAC1Q31_MAX	+2147483647
#define SFRAC1Q31_MIN	-2147483648

#define SFRAC2Q30_BITS	32
#define SFRAC2Q30_MAX	+2147483647
#define SFRAC2Q30_MIN	-2147483648

#define SFRAC3Q29_BITS	32
#define SFRAC3Q29_MAX	+2147483647
#define SFRAC3Q29_MIN	-2147483648

#define SFRAC11Q21_BITS	32
#define SFRAC11Q21_MAX	+2147483647
#define SFRAC11Q21_MIN	-2147483648

#define SFRAC16Q16_BITS	32
#define SFRAC16Q16_MAX	+2147483647
#define SFRAC16Q16_MIN	-2147483648

#define SFRAC17Q15_BITS	32
#define SFRAC17Q15_MAX	+2147483647
#define SFRAC17Q15_MIN	-2147483648

#define SFRAC18Q14_BITS	32
#define SFRAC18Q14_MAX	+2147483647
#define SFRAC18Q14_MIN	-2147483648

#define SFRAC19Q13_BITS	32
#define SFRAC19Q13_MAX	+2147483647
#define SFRAC19Q13_MIN	-2147483648


#endif

/***************************************************************************/
/**                                                                       **/
/**                     EOF                                               **/
/**                                                                       **/
/***************************************************************************/
