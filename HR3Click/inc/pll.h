/*
 * bb_pll.h
 *
 *  Created on: Apr 12, 2016
 *      Author: SUBRAMANIAN
 */

#ifndef INC_PLL_H_
#define INC_PLL_H_
#include "csl_types.h"

#define PLL_120M  1

/*Configures the system to run on a  clock frequency as define */
CSL_Status initPllClock(void);

#endif /*INC_PLL_H_*/
