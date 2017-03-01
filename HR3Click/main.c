/*
 * main.c
 */
#include <stdint.h>
#include <stdio.h>
#include "heartrate_3_hal.h"
#include "heartrate_3_hw.h"
#include "heartrate_3.h"

#include "csl_general.h"
#include "cslr_sysctrl.h"
#include "csl_spi.h"
#include "csl_intc.h"
#include "csl_rtc.h"

#include "gpio.h"
#include "peripheral.h"
#include "pll.h"
#include "interrupt.h"
#include "main.h"
#include "stdint.h"
#include "delay.h"
#include "uart.h"

CSL_Status reset_HR3();
void system_setup( void );
uint32_t readReg(uint8_t regAddr);
extern char buf[512];

int main(void) {
	CSL_Status status;
	status = initPllClock();
	if(CSL_SOK != status){
		printf("System Clock init failed \n");
		return -1;
	}

	status = configPeripheral();
	if(CSL_SOK != status){
		printf("System Peripheral configuration failed \n");
		return -1;
	}


	status = CSL_uartInit();
	if(CSL_SOK != status){
			printf("UART configuration failed \n");
			return -1;
		}
	initInterrupt();
	system_setup();
	enableInterrupt();
	while(1){
	}
	return 0;
}
void system_setup( void ){
	//Local Declarations
	dynamic_modes_t dynamic_modes;
	uint8_t         address = 0x58;

	//Set up dynamic modes for Heart Rate 3 Initialization
	dynamic_modes.transmit = trans_dis;                      //Transmitter disabled
	dynamic_modes.curr_range = led_double;                   //LED range 0 - 100
	dynamic_modes.adc_power = adc_on;                        //ADC on
	dynamic_modes.clk_mode = osc_mode;                       //Use internal Oscillator
	dynamic_modes.tia_power = tia_off;                       //TIA off
	dynamic_modes.rest_of_adc = rest_of_adc_off;             //Rest of ADC off
	dynamic_modes.afe_rx_mode = afe_rx_normal;               //Normal Receiving on AFE
	dynamic_modes.afe_mode = afe_normal;                     //Normal AFE functionality

	/*dynamic_modes.transmit = trans_en;                      //Transmitter disabled
	dynamic_modes.curr_range = led_double;                   //LED range 0 - 100
	dynamic_modes.adc_power = adc_on;                        //ADC on
	dynamic_modes.clk_mode = osc_mode;                       //Use internal Oscillator
	dynamic_modes.tia_power = tia_off;                       //TIA off
	dynamic_modes.rest_of_adc = rest_of_adc_on;             //Rest of ADC off
	dynamic_modes.afe_rx_mode = afe_rx_normal;               //Normal Receiving on AFE
	dynamic_modes.afe_mode = afe_normal;                     //Normal AFE functionality
*/
	//Toggle Reset pin
	reset_HR3();

	//I2C Initialize

	//Heart Rate 3 InitializePhotodiodes
	hr3_init( address, &dynamic_modes );
	initStatHRM();
}
uint32_t readReg( uint8_t regAddr ){
	uint8_t temp[3] = { 0 };
	uint32_t retval = 0;

	hr3_hal_read( &regAddr, temp, 3 );

	retval |= (uint32_t)temp[0] << 16;
	retval |= (uint32_t)temp[1] << 8;
	retval |= (uint32_t)temp[2];

	return retval;
}
CSL_Status reset_HR3(){

	CSL_Status status;
	status = set_GPIO(HR3_RST_PIN,GPIO_OP);
	if(CSL_SOK != status){
		printf("GPIO set failed\n");
		return(CSL_TEST_FAILED);
	}

	status = write_GPIO(HR3_RST_PIN,0);
	if(CSL_SOK != status){
		printf("GPIO set failed\n");
		return(CSL_TEST_FAILED);
	}

	delay_us(50);
	wait(0xFFFF);

	status = write_GPIO(HR3_RST_PIN,1);
	if(CSL_SOK != status){
		printf("GPIO set failed\n");
		return(CSL_TEST_FAILED);
	}
	delay_us(50);
	return status;
}


