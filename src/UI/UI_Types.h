/* 
 * File:   UI_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 06 July 2020, 16:25
 */

#ifndef UI_TYPES_H
#define	UI_TYPES_H

#include "types.h"

typedef struct
{
    uint8 Tens          :4;
    uint8 Ones          :4;
    uint8 Tenths        :4;
    uint8 Hundredths    :4;
    uint8 thousandths   :4;
    
} dtDigits;

#endif	/* UI_TYPES_H */

