/* 
 * File:   TIMER2.h
 * Author: Bodnár Benjamin
 *
 * Created on 05 June 2020, 22:17
 */

#ifndef TIMER2_H
#define	TIMER2_H

#include "types.h"

#define T2_POST_1   0
#define T2_POST_2   0x8
#define T2_POST_3   0x10
#define T2_POST_4   0x18
#define T2_POST_5   0x20
#define T2_POST_6   0x28
#define T2_POST_7   0x30
#define T2_POST_8   0x38
#define T2_POST_9   0x40
#define T2_POST_10  0x48
#define T2_POST_11  0x50
#define T2_POST_12  0x58
#define T2_POST_13  0x60
#define T2_POST_14  0x68
#define T2_POST_15  0x70
#define T2_POST_16  0x78

#define T2_ON       0x04
#define T2_OFF      0

#define T2_PRE_1    0x00
#define T2_PRE_4    0x01
#define T2_PRE_16   0x02

extern void TIMER2_Set(uint8 Conf, uint8 Comp, void (*handler)(void));

#endif	/* TIMER2_H */

