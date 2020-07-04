/* 
 * File:   Switch3.h
 * Author: Bodnár Benjamin
 *
 * Created on 04 July 2020, 12:23
 */

#ifndef SWITCH3_H
#define	SWITCH3_H

#include "types.h"

typedef enum
{
    Sw3Released = 0,
    Sw3Pressed,
    Sw3LongPressed,
} dtSwitch3State;

extern void Switch3_Init(void);
extern void Switch3_Task(void);
extern dtSwitch3State Switch3_Value(void);

#endif	/* SWITCH3_H */

