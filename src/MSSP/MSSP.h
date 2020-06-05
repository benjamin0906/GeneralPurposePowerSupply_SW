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

#endif	/* MSSP_H */

