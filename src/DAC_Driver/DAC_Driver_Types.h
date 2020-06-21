/* 
 * File:   DAC_Driver_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 21 June 2020, 10:39
 */

#ifndef DAC_DRIVER_TYPES_H
#define	DAC_DRIVER_TYPES_H

#include "types.h"

typedef enum
{
    DacIdle,
    CsLow,
    SendValue,
    CsHigh,
} dtDACState;

#endif	/* DAC_DRIVER_TYPES_H */

