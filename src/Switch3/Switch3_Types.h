/* 
 * File:   Switch3_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:11
 */

#ifndef BUTTON_TYPES_H
#define	BUTTON_TYPES_H

#include "types.h"

typedef enum
{
    Switch3_Init,
    Switch3_WaitForAction,
    Switch3_WaitForTimeout,
} dtSwitchTaskState;

#endif	/* BUTTON_TYPES_H */

