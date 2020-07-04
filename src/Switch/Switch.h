/* 
 * File:   Switch.h
 * Author: Bodnár Benjamin
 *
 * Created on 23 June 2020, 18:25
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "types.h"

typedef enum
{
    SwReleased = 0,
    SwPressed,
    SwLongPressed,
} dtSwitchState;

extern void Switch_Init(void);
extern void Switch_Task(void);
extern dtSwitchState Switch_Value(void);

#endif	/* BUTTON_H */

