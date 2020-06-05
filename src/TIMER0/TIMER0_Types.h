/* 
 * File:   TIMER0_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 05 June 2020, 20:59
 */

#ifndef TIMER0_TYPES_H
#define	TIMER0_TYPES_H

#include "types.h"

typedef union
{
    uint8 Byte;
    struct
    {
        uint8 T0PS  :3;
        uint8 PSA   :1;
        uint8 T0SE  :1;
        uint8 T0CS  :1;
        uint8 T08BIT:1;
        uint8 TMR0ON:1;
    } Fields;
} dtT0CON;

#endif	/* TIMER0_TYPES_H */

