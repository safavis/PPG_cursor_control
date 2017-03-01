#include <stdio.h>

#include "csl_intc.h"
#include "csl_rtc.h"

#include "main.h"
#include "interrupt.h"
#include "heartrate_3_hw.h"
#include "heartrate_3.h"
#include "uart.h"
#include <string.h>

//#define TEST_MATLAB
/* Reference the start of the interrupt vector table */
/* This symbol is defined in file vectors.asm       */
extern void VECSTART(void);


interrupt void int1_isr();
char buf[11] = {0};
//extern volatile int looper;
extern Uint32 test_buf32_ch2[2048];

Int8 ecgflag = 0;

void resetInterrupt(){
    /* Disable CPU interrupts */
    IRQ_globalDisable();

	/* Clear any pending interrupts */
	IRQ_clearAll();

	/* Disable all the interrupts */
	IRQ_disableAll();
}


void initInterrupt(){

	/* Configure and enable the RTC interrupts using INTC module */
    IRQ_globalDisable();

	/* Clear any pending interrupts */
	IRQ_clearAll();

	/* Disable all the interrupts */
	IRQ_disableAll();

	IRQ_setVecs((Uint32)&VECSTART);

	IRQ_clear(INT1_EVENT);
	/* Register the ISR */
	IRQ_plug(INT1_EVENT,&int1_isr);

	IRQ_globalEnable();
}

CSL_Status enableInterrupt(){

	IRQ_enable(INT1_EVENT);
	RTC_start();
	return CSL_SOK;
}
#ifdef TEST_MATLAB
interrupt void int1_isr(){
	static uint32_t i=0;
    static int int_count = 0;
      if(int_count == 600){
    	  printf("+10s \n");
    	  int_count = 0;
      }
      else
      	int_count++;
    hr3_get_led3_val();
    sprintf(buf,"%lu\n",i);
    i++;
    send_data_uart(buf,11);
	return;
}

#else

interrupt void int1_isr(){

    static int int_count = 0;
      if(int_count == 600){
    	  printf("+10s\n");
    	  int_count = 0;
      }
      else
      	int_count++;
    sprintf(buf,"%lu\n",hr3_get_led3_val());
    send_data_uart(buf,11);
	return;
}
#endif
#if 0
interrupt void int1_isr(){

    static int int_count = 0;
    static int time = 1;
      if(int_count == 100){
  		uint8_t hr = hr3_get_heartrate();
  		sprintf(buf,"%u\n",hr);
  		send_data_uart(buf,255);
      	int_count =0;
      }
      else
      	int_count++;

    //sprintf(buf,"%lu\t%lu\t%lu\r\n",hr3_get_led1_val(),hr3_get_led2_val(),hr3_get_led3_val());
    //unsigned long i=hr3_get_led3_val();
    statHRMAlgo(hr3_get_led1_amb1_val());
    //uint8_t i = hr3_get_heartrate();
    //sprintf(buf,"%lu\n",i);
    /*char val[6];
    val[0] = 0x1000 + (i >> 24) & 0xff;
    val[1] = 0x1000 + (i >> 16) & 0xff;
    val[2] = 0x1000 + (i >> 8) & 0xff;
    val[3] = 0x1000 + (i) & 0xff;
    val[4] = '\n';*/
    //send_data_uart(buf,255);
	return;
}
#endif
