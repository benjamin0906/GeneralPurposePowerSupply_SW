/* 
 * File:   Control_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 07 July 2020, 17:56
 */

#ifndef CONTROL_TYPES_H
#define	CONTROL_TYPES_H

#include "types.h"

typedef struct
{
    uint16 RequestedVoltage;
    uint16 PrevRequestedVoltage;
} dtControl;

#endif	/* CONTROL_TYPES_H */

