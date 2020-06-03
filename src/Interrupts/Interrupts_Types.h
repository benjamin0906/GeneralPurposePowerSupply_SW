/* 
 * File:   Interrupts_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 03 June 2020, 08:08
 */

#ifndef INTERRUPTS_TYPES_H
#define	INTERRUPTS_TYPES_H

#include "types.h"

typedef struct
{
    uint8 PIE;
    uint8 PIR;
    uint8 IPR;
} dtPI;

#endif	/* INTERRUPTS_TYPES_H */

