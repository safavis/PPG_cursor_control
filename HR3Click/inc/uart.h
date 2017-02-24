#ifndef BB_UART_H_
#define BB_UART_H_

/*
 * Initialises the UART
 * */
CSL_Status CSL_uartInit(void);
/**
 *  \brief  Function to send data
 *
 *  \param    ptr to data buffer , number of bytes to transfer
 *
 *  \return   success of failure
 */
CSL_Status send_data_uart(Char *ptr, Uint16 num_bytes);
#endif /*BB_UART_H_*/
