/* 
 * File:   EUSART.h
 * Author: Bodnár Benjamin
 *
 * Created on 30 May 2020, 19:30
 */

#ifndef EUSART_H
#define	EUSART_H

#include "types.h"

typedef struct
{
    uint8 Sync  :1;
    uint8 Tx9Bit:1;
    uint8 Rx9Bit:1;
    uint8 RxInv :1;
    uint8 TxInv :1;
} dtEUSARTConf;

extern void EUSART_Init(dtEUSARTConf Config, uint32 Baud);
extern void EUSART_Send(uint8 *data, uint8 len);

#endif	/* EUSART_H */

