#include <stdio.h>
#include <csl_general.h>
#include <csl_i2c.h>
#include "heartrate_3_hal.h"
#include <stdint.h>

#define CSL_I2C_OWN_ADDR		(0x2F)
#define CSL_I2C_SYS_CLK			(100)
#define CSL_I2C_BUS_FREQ		(400)
#define CSL_I2C_TIMEOUT     (0x00FF)
Uint16 slave_addr;
void hr3_hal_init( uint8_t address_id )
{
	CSL_Status      status;
	CSL_I2cSetup	configI2C;
	slave_addr = (Uint16)address_id;
	/* Initialize I2C module */
	status = I2C_init(CSL_I2C0);
	if(status != CSL_SOK)
	{
		printf("I2C Init Failed!!\n");
		return;
	}

	/* Setup I2C module */
	configI2C.addrMode    = CSL_I2C_ADDR_7BIT;
	configI2C.bitCount    = CSL_I2C_BC_8BITS;
	configI2C.loopBack    = CSL_I2C_LOOPBACK_DISABLE;
	configI2C.freeMode    = CSL_I2C_FREEMODE_DISABLE;
	configI2C.repeatMode  = CSL_I2C_REPEATMODE_DISABLE;
	configI2C.ownAddr     = CSL_I2C_OWN_ADDR;
	configI2C.sysInputClk = CSL_I2C_SYS_CLK;
	configI2C.i2cBusFreq  = CSL_I2C_BUS_FREQ;

	status = I2C_setup(&configI2C);
	if(status != CSL_SOK)
	{
		printf("I2C Setup Failed!!\n");
		return;
	}

	return;
}

void hr3_hal_write( uint8_t *command,uint8_t *buffer,uint16_t count ){

	CSL_Status  status;
	Uint16      startStop;
	Uint16      write_buffer[BUFF_SIZE];
	Uint16 i = 0;
	volatile Uint16    looper;

	startStop = ((CSL_I2C_START) | (CSL_I2C_STOP));
	write_buffer[i++] = (Uint16) *(command);
	while(count --)
		write_buffer[i++] = (Uint16) *(buffer++);

	/* Write data */
	status = I2C_write(write_buffer, i,
			slave_addr, TRUE, startStop,
			CSL_I2C_TIMEOUT);
	if(status != CSL_SOK){
			printf("I2C Write Failed!!\n");
	}
	/* Give some delay */
	for(looper = 0; looper < CSL_I2C_TIMEOUT; looper++){;}

	return;

}

void hr3_hal_read( uint8_t *command, uint8_t *buffer, uint16_t count ){
	CSL_Status  status;
	Uint16      startStop;
	Uint16      read_buffer[BUFF_SIZE];
	Uint16 regAddr = (Uint16) *(command);
	volatile Uint16    looper;
	int i=0;

	startStop = ((CSL_I2C_START) | (CSL_I2C_STOP));

	/* Read data */
	status = I2C_read(read_buffer, count, slave_addr,
			(Uint16 *)&regAddr, 1, TRUE,
			startStop, CSL_I2C_TIMEOUT, FALSE);

	if (status != CSL_SOK) {
		printf("I2C_Read: I2C Read ERROR!\n");
		return ;
	}

	/* Give some delay */
	for(looper = 0; looper < CSL_I2C_TIMEOUT; looper++){;}

	while(count--){
		buffer[ i] = (uint8_t)read_buffer[i];
		i++;
	}
}
