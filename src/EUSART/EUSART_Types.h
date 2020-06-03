/* 
 * File:   EUSART_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 30 May 2020, 19:30
 */

#ifndef EUSART_TYPES_H
#define	EUSART_TYPES_H

#include "../types.h"

typedef struct
{
    uint8 TX9D  :1;
    uint8 TRMT  :1;
    uint8 BRGH  :1;
    uint8 SENDB :1;
    uint8 SYNC  :1;
    uint8 TXEN  :1;
    uint8 TX9   :1;
    uint8 CSRC  :1;
} dtTXSTA;

typedef struct
{
    uint8 RX9D  :1;
    uint8 OERR  :1;
    uint8 FERR  :1;
    uint8 ADDEN :1;
    uint8 CREN  :1;
    uint8 SREN  :1;
    uint8 RX9   :1;
    uint8 SPEN  :1;
} dtRCSTA;

typedef struct
{
    uint8 ABDEN     :1;
    uint8 WUE       :1;
    uint8           :1;
    uint8 BRG16     :1;
    uint8 TXCKP     :1;
    uint8 RXDTP     :1;
    uint8 RCIDL     :1;
    uint8 ABDOVF    :1;
} dtBAUDCON;

#endif	/* EUSART_TYPES_H */

