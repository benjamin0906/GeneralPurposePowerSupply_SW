/* 
 * File:   Button.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:25
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "types.h"

typedef enum
{
    Released,
    Pressed,
    LongPressed,
} dtButtonState;

extern void Button_Task(void);
extern dtButtonState Button_Value(void);

#endif	/* BUTTON_H */

