/* 
 * File:   Encoder.h
 * Author: Bodnár Benjamin
 *
 * Created on 04 July 2020, 13:05
 */

#ifndef ENCODER_H
#define	ENCODER_H

#include "types.h"

extern void Encoder_Init(void);
extern void Encoder_Task(void);
extern uint8 Encoder_GetClicks(void);

#endif	/* ENCODER_H */

