/*
 * main.h
 *
 *  Created on: Nov 1, 2016
 *      Author: subbu
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_
#define CSL_TEST_FAILED  (-1)
#define CSL_TEST_PASSED  (0)

#define HR3_RST_PIN   7 //TODO

//TODO
/*External Bus selection modes - refer document SPRS645F - page-62 , table-3.6*/
#define PP_MODE CSL_EBSR_PPMODE_1//for SPI at lcd9,10,11 bits

/*serial port gpio */
#define SP0_MODE CSL_EBSR_SP0MODE_0

/*serial port gpio */
#define SP1_MODE CSL_EBSR_SP1MODE_2



#endif /* INC_MAIN_H_ */
