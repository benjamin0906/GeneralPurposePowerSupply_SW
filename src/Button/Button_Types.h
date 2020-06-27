/* 
 * File:   Button_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:11
 */

#ifndef BUTTON_TYPES_H
#define	BUTTON_TYPES_H

#include "types.h"

typedef enum
{
    Button_Init,
    Button_WaitForAction,
    Button_WaitForTimeout,
} dtButtonTaskState;

#endif	/* BUTTON_TYPES_H */

