/* 
 * File:   Control.h
 * Author: Bodn�r Benjamin
 *
 * Created on 07 July 2020, 17:38
 */

#ifndef CONTROL_H
#define	CONTROL_H

#include "types.h"

extern void Control_Init(void);
extern void Control_Task(void);
extern void Control_ReqVolt(uint16 req);
extern uint16 Control_GetMeasuredVotlage(void);
extern int16 Control_GetMeasuredCurrent(void);

#endif	/* CONTROL_H */

