/* 
 * File:   Switch3.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:25
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "types.h"

typedef enum
{
    Sw3Released,
    Sw3Pressed,
    Sw3LongPressed,
} dtSwitch3State;

extern void Switch3_Task(void);
extern dtSwitch3State Switch3_Value(void);

#endif	/* BUTTON_H */

