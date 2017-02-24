/*
 * GPIO.c
 *
 *  Created on: Apr 14, 2016
 *      Author: subbu
 */
#include <stdio.h>
#include "csl_gpio.h"
#include "csl_error.h"
#include "main.h"


/*-------------------------------------------------------------------------------**
** 	Function Name : Wait()                                                       **
** 	Description  : 	- The function gives a delay of n CPU cycles where n is the  **
** 					  parameter Count                                            **
** 	Parameters	:	- Count - In - no of delay cycles                            **
** 	Return		: none                                                           **
**-------------------------------------------------------------------------------*/

void wait(Uint32 count)
{
	Int32 i;

	for(i=0;i<count;i++)
	asm("	nop");
}

/*
 * Sets the direction of GPIO pin
 * Arguments:
 * pin - the GPIO pin
 * is_op - is output or not
 *  */
CSL_Status set_GPIO(Int16 pin , Int16 dir){

	CSL_Status           status;
    CSL_GpioPinConfig    config;
    CSL_GpioObj    gpioObj;
    CSL_GpioObj    *hGpio;

	 /* Open GPIO module */
    hGpio = GPIO_open(&gpioObj, &status);
    if((NULL == hGpio) || (CSL_SOK != status)){
        printf("GPIO_open failed\n");
        return(CSL_ESYS_FAIL);
    }

	/* Configure GPIO pin 0 as output pin */
    config.pinNum    = (CSL_GpioPinNum) pin;
    config.direction = (CSL_GpioDirection) dir;
    config.trigger   = CSL_GPIO_TRIG_CLEAR_EDGE;

    status = GPIO_configBit(hGpio, &config);
    if(CSL_SOK != status){
        printf("GPIO_configBit failed\n");
        return(CSL_ESYS_FAIL);
    }


    /* Close the GPIO module */
    status = GPIO_close(hGpio);
    if(CSL_SOK != status){
        printf("GPIO_close failed\n");
        return(CSL_ESYS_FAIL);
    }

    return(CSL_SOK);

}

/*Write the given value (HIGH or LOW) to the GPIO pin*/
CSL_Status write_GPIO(Int16 pin, Int16 val){
	CSL_Status           status;
	CSL_GpioObj    gpioObj;
	CSL_GpioObj    *hGpio;

		 /* Open GPIO module */
    hGpio = GPIO_open(&gpioObj, &status);
    if((NULL == hGpio) || (CSL_SOK != status)) {
        printf("GPIO_open failed\n");
        return(CSL_ESYS_FAIL);
    }

	status = GPIO_write(hGpio, (CSL_GpioPinNum)pin, val);
    if(CSL_SOK != status){
        printf("GPIO_write Failed\n");
        return(CSL_ESYS_FAIL);
    }

    /* Close the GPIO module */
	status = GPIO_close(hGpio);
	if(CSL_SOK != status){
		printf("GPIO_close failed\n");
		return(CSL_ESYS_FAIL);
	}

	return status;
}
