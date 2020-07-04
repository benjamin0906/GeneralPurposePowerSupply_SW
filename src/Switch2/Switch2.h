/* 
 * File:   Switch2.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:25
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "types.h"

typedef enum
{
    Sw2Released,
    Sw2Pressed,
    Sw2LongPressed,
} dtSwitch2State;

extern void Switch2_Task(void);
extern dtSwitch2State Switch2_Value(void);

#endif	/* BUTTON_H */

