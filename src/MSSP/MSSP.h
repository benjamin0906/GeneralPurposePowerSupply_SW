/* 
 * File:   MSSP.h
 * Author: Bodnár Benjamin
 *
 * Created on 03 June 2020, 21:39
 */

#ifndef MSSP_H
#define	MSSP_H

typedef enum
{
    I2C_Write,
    I2C_Read,
    Spi,
} dtMSSPTYPE;

extern void MSSP_Init(void);
extern void MSSP_Send(dtMSSPTYPE ComType, uint8 SlaveAdd, uint8 *Add, uint8 AddLen, uint8 *D, uint8 DataLen);
extern uint8 MSSP_Ready(void);

#endif	/* MSSP_H */

