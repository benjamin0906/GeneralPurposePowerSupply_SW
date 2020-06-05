/* 
 * File:   TIMER2_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 05 June 2020, 22:12
 */

#ifndef TIMER2_TYPES_H
#define	TIMER2_TYPES_H

#include "types.h"

typedef union
{
    uint8 Byte;
    struct
    {
        uint8           :1;
        uint8 T2OUTPS   :4;
        uint8 TMR2ON    :1;
        uint8 T2CKPS    :2;
    } Fields;
} dtT2CON;

#endif	/* TIMER2_TYPES_H */

