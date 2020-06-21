/* 
 * File:   DAC_Driver.h
 * Author: Bodnár Benjamin
 *
 * Created on 21 June 2020, 10:28
 */

#ifndef DAC_DRIVER_H
#define	DAC_DRIVER_H

#include "types.h"

extern void DAC_Driver_Init(void);
extern void DAC_Driver_Task(void);
extern void DAC_Driver_Send(uint16 value);

#endif	/* DAC_DRIVER_H */

