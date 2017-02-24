#include <stdio.h>

#include "csl_sysctrl.h"

#include "main.h"
#include "peripheral.h"
/*
 * This function sets the External BUS SELECTION (EBSR) register , to enable the required pheripherals 
 * that are being used in this project
 * */
CSL_Status configPeripheral(){
	CSL_Status           status;


    /***********************************************************************
	* Setting up SP0 to MODE1 to use I2S0 , as I2S0 is connected to AIC3204
	***********************************************************************/
	status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE,PP_MODE);

	if(CSL_SOK != status){
		printf("SYS_setEBSR failed\n");
		return(status);
	}

    /***********************************************************************
	* Setting up SP0 to MODE1 to use I2S0 , as I2S0 is connected to AIC3204
	* *********************************************************************/
    status = SYS_setEBSR(CSL_EBSR_FIELD_SP0MODE,SP0_MODE);
    
    if(CSL_SOK != status){
        printf("SYS_setEBSR failed\n");
        return(status);
    }

    /************************************************************
	* Setting SP1 in mode 0 to use MMC1 (Multi media Controller)
	* **********************************************************/
    status = SYS_setEBSR(CSL_EBSR_FIELD_SP1MODE,SP1_MODE);
  
    if(CSL_SOK != status)
    {
        printf("SYS_setEBSR failed\n");
        return(status);
    }
 /*
    status = SYS_setEBSR(CSL_EBSR_FIELD_A17MODE,CSL_EBSR_A_MODE_1);

	if(CSL_SOK != status)
	{
		printf("SYS_setEBSR failed\n");
		return(status);
	}
*/
    return status;
}

