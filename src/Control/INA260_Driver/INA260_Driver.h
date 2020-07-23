/* 
 * File:   INA260_Driver.h
 * Author: Bodnár Benjamin
 *
 * Created on 21 July 2020, 19:48
 */

#ifndef INA260_DRIVER_H
#define	INA260_DRIVER_H

#include "types.h"

extern void INA260_Driver_Init(void);
extern void INA260_Driver_Task(void);
extern void INA260_Driver_GetState(void);
extern uint8 INA260_Driver_GetValues(uint16 *VoltagePtr, int16 *CurrentPtr, uint16 *PowerPtr);

#endif	/* INA260_DRIVER_H */

