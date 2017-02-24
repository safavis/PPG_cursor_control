#include <stdio.h>
#include "csl_uart.h"
#include "csl_uartAux.h"
#include "csl_general.h"
#include "csl_sysctrl.h"
#include "csl_pll.h"

//#define DEBUG
/* Global data definition */
/* UART setup structure */
CSL_UartSetup uartSetup =
{
	/* Input clock freq in MHz */
    60000000,
	/* Baud rate */
    115200,
	/* Word length of 8 */
    CSL_UART_WORD8,
	/* To generate 1 stop bit */
    0,
	/* Disable the parity */
    CSL_UART_DISABLE_PARITY,
	/* Disable fifo */
	/* Enable trigger 14 fifo */
	CSL_UART_FIFO_DMA1_DISABLE_TRIG14,
	/* Loop Back enable */
    CSL_UART_NO_LOOPBACK,
	/* No auto flow control*/
	CSL_UART_NO_AFE ,
	/* No RTS */
	CSL_UART_NO_RTS ,
};

CSL_UartObj uartObj;
CSL_UartHandle    hUart;



/*
 * Sends 'num_bytes' number of bytes from the memory pointed by ptr
 * */
CSL_Status send_data_uart(Char *ptr, Uint16 num_bytes){
    CSL_Status        status;
	//status = UART_write(hUart,ptr,num_bytes,0);
    status = UART_fputs(hUart, ptr,0);
    if(CSL_SOK != status){
        printf("UART_fputs  failed error code %d\n",status);
        return(status);
    }
    return(status);
}

/*Initialises the UART*/
CSL_Status CSL_uartInit(void){
    CSL_Status        status;
	Uint32            sysClk;
#ifdef DEBUG
	char wrbuffer[55] = "\r\nEnter the size of the string(min 01 to max 99)\r\n >> ";
#endif
	sysClk = getSysClk();
    sysClk *= 1000;
	uartSetup.clkInput = sysClk;

    status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE,
                         CSL_EBSR_PPMODE_1);
    if(CSL_SOK != status)
    {
        printf("SYS_setEBSR failed\n");
        return(status);
    }

    /* Loop counter and error flag */
    status = UART_init(&uartObj,CSL_UART_INST_0,UART_POLLED);
    if(CSL_SOK != status)
    {
        printf("UART_init failed error code %d\n",status);
        return(status);
    }
    else
    {
		printf("UART_init Successful\n");
	}

    /* Handle created */
    hUart = (CSL_UartHandle)(&uartObj);

    /* Configure UART registers using setup structure */
    status = UART_setup(hUart,&uartSetup);
    if(CSL_SOK != status)
    {
        printf("UART_setup failed error code %d\n",status);
        return(status);
    }
    else
    {
		printf("UART_setup Successful\n");
	}
#ifdef DEBUG
	/* Send the message to HyperTerminal to Query the string size */
   	status = UART_fputs(hUart,wrbuffer,0);
    if(CSL_SOK != status)
    {
        printf("UART_fputs failed error code %d\n",status);
        return(status);
    }
    else
    {
		printf("\n\nMessage Sent to HyperTerminal : %s\n",wrbuffer);
	}
#endif
	return status;
}

