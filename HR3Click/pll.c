/* *********************************************************************
 * File name: audio_pll.c.c
 * 
 * Configures the system to run on a specific clock frequency
 * This implementation is strictly limited to c5515/05/04
 *  
 * *********************************************************************/

#include <stdio.h>

#include "csl_pllAux.h"
#include "csl_pll.h"

#include "pll.h"

/*variables for PLL*/
PLL_Config pllCfg_12p288MHz = {0x8173, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_40MHz     = {0x8988, 0x8000, 0x0806, 0x0201};
PLL_Config pllCfg_60MHz     = {0x8724, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_75MHz     = {0x88ED, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_100MHz    = {0x8BE8, 0x8000, 0x0806, 0x0000};
PLL_Config pllCfg_120MHz    = {0x8E4A, 0x8000, 0x0806, 0x0000};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Configures the system to run on a  clock frequency as define 
 * Input : None
 * The required frequency should be defined in the header
 * Some standard possible frequency 
 * 
 * Returns: 
 *  CSL_OK - If setting up PLL is sucess
 *  else return respective CSL_errors 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
CSL_Status initPllClock(void){
    CSL_Status status;
    PLL_Obj pllObj;
    PLL_Handle hPll;
    PLL_Config *pConfigInfo;

    status = PLL_init(&pllObj, CSL_PLL_INST_0);
    if(CSL_SOK != status){
       printf("PLL init failed \n");
       return (status);
    }

	hPll = (PLL_Handle)(&pllObj);
	PLL_reset(hPll);
	
	 /* Configure the PLL for 100MHz */
	#if (PLL_120M ==1)		
   		 pConfigInfo = &pllCfg_120MHz;
   		  
	#elif (PLL_100M ==1)		
   		 pConfigInfo = &pllCfg_100MHz;
   	
   	#elif (PLL_75M ==1) 
		pConfigInfo = &pllCfg_75MHz;	
	
	#elif (PLL_60M ==1) 
		pConfigInfo = &pllCfg_60MHz;
	
	#elif (PLL_40M ==1)  
		pConfigInfo = &pllCfg_40MHz;
		
	#elif (PLL_12M ==1)
		pConfigInfo = &pllCfg_12p288MHz;
    
    #endif

	status = PLL_config (hPll, pConfigInfo);
   	if(CSL_SOK != status){
       printf("PLL config failed\n");
       return(status);
   	}

   return(status);
	
}
