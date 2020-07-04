/* 
 * File:   Switch2_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:11
 */

#ifndef BUTTON_TYPES_H
#define	BUTTON_TYPES_H

#include "types.h"

typedef enum
{
    Switch2_Init,
    Switch2_WaitForAction,
    Switch2_WaitForTimeout,
} dtSwitch2TaskState;

#endif	/* BUTTON_TYPES_H */

