/*                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** filename  : polyphase_filter.c                                          **
** author    : Jesse Carter                                                **
** created   : 2018-07-13                                                  **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (C) 2009 - 2017, Pantel International Incorporated            **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************
*/

/***************************************************************************/
/**                                                                       **/
/**                     MODULES USED                                      **/
/**                                                                       **/
/***************************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "libdd.h"
#include "polyphase_filter.h"
#include "limits_frac.h"
#include "types_frac.h"

/***************************************************************************/
/**                                                                       **/
/**                     TYPDEFS AND STRUCTURES                            **/
/**                                                                       **/
/***************************************************************************/
struct PolyFilterData {
    unsigned n;
    struct FirFilterData *evenCoefs;
    struct FirFilterData *oddCoefs;
};

/***************************************************************************/
polyfilter_t *polyFilterCreate(const sfrac1q15 *p, unsigned int n)
/***************************************************************************/
{
        struct PolyFilterData    *q;
        unsigned                  m = n/2;
        sfrac1q15 evenCoefs[m], oddCoefs[m];
        unsigned j = 0;
        
	if (p == NULL || !n ||
	   (q = malloc(sizeof(struct PolyFilterData))) == NULL)
                return NULL;
        
        for (unsigned i = 0; i < n; i++){
            if (i%2 == 0){
                evenCoefs[j] = p[i];
            }
            else{
                oddCoefs[j] = p[i];
                j++;
            }
        }
        
        if ((q->evenCoefs = firFilterCreate(evenCoefs, m)) == NULL) {
            free(q);
            return NULL;
        }
        if ((q->oddCoefs = firFilterCreate(oddCoefs, m)) == NULL) {
            free(q->evenCoefs);
            free(q);
            return NULL;
        }
        return q;
}

/***************************************************************************/
void polyFilterDestroy(polyfilter_t *p)
/***************************************************************************/
{
    struct PolyFilterData *q;
    
    if ((q = p) != NULL){
        firFilterDestroy(q->evenCoefs);
        firFilterDestroy(q->oddCoefs);
        free(q);
    }
    return;
}
/***************************************************************************/
int polyFilter(polyfilter_t *p, const sfrac1q15 *x, sfrac1q15 *y,
               unsigned int n)
/***************************************************************************/
{
    struct PolyFilterData *q;
    sfrac1q15 *temp1 = malloc(sizeof(sfrac1q15)*n);
    sfrac1q15 *temp2 = malloc(sizeof(sfrac1q15)*n);
    
    if ((q = p) == NULL || ((x == NULL || y == NULL) && n))
		return -1;
    
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < 2; j++){
            if (j%2 == 0){
                if(!firFilter(q->oddCoefs, x, temp1, 1))
                x++;
            else
                return -1;
            }
            else {
            if (!firFilter(q->evenCoefs, x, temp2, 1)) {
                x++;
            }
            else
               return -1;
            }
        }
        *y++ += *temp1++ + *temp2++;
    }
    return 0;
}