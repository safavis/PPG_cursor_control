/*
 * gpio.h
 *
 *  Created on: Apr 14, 2016
 *      Author: subbu
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "csl_types.h"

void wait(Uint32 count);
CSL_Status set_GPIO();
CSL_Status write_GPIO(Int16 pin, Int16 val);
#define GPIO_IN 0
#define GPIO_OP 1
#endif /* BLUEBOX_BACKUP_INC_GPIO_H_ */
