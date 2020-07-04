/* 
 * File:   Switch2.h
 * Author: Bodnár Benjamin
 *
 * Created on 04 July 2020, 12:21
 */

#ifndef SWITCH2_H
#define	SWITCH2_H

#include "types.h"

typedef enum
{
    Sw2Released = 0,
    Sw2Pressed,
    Sw2LongPressed,
} dtSwitch2State;

extern void Switch2_Init(void);
extern void Switch2_Task(void);
extern dtSwitch2State Switch2_Value(void);

#endif	/* SWITCH2_H */

