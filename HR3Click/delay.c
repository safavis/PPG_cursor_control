/*
 * delay.c
 *
 *  Created on: Nov 7, 2016
 *      Author: subbu
 */

#include <stdint.h>
#include <stdio.h>
#include "delay.h"
#include "pll.h"

uint32_t clkFreq;
void delay_us(uint32_t delay){
	clkFreq = getClockFreq();
	uint32_t numClk = clkFreq/1000000;
	uint32_t i;
	while(delay--){
		for(i=0;i<numClk;i++)
			asm("	nop");
	}
}

void delay_ms(uint32_t delay){
	clkFreq = getClockFreq();
	uint32_t numClk = clkFreq/1000;
	uint32_t i;
	while(delay--){
		for(i=0;i<numClk;i++)
			asm("	nop");
	}
}
void delay1us(){


}

uint32_t getClockFreq(){
	uint32_t clkFreq;
#if (PLL_120M ==1)
	clkFreq = 120000000; //120*10^6

#elif (PLL_100M ==1)
	clkFreq = 100000000; // 100*10^6

#elif (PLL_75M ==1)
	clkFreq = 75000000;

#elif (PLL_60M ==1)
	clkFreq = 60000000;

#elif (PLL_40M ==1)
	clkFreq = 40000000;

#elif (PLL_12M ==1)
	clkFreq =12288000;

#endif
	return clkFreq;
}
