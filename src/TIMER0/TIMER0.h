/* 
 * File:   TIMER0.h
 * Author: Bodnár Benjamin
 *
 * Created on 05 June 2020, 20:59
 */

#ifndef TIMER0_H
#define	TIMER0_H

#include "types.h"

#define T0_ENABLE       1<<7
#define T0_DISABLE      0<<7
#define T0_8BIT         1<<6
#define T0_16BIT        0<<6
#define T0_CLK_EXT      1<<5
#define T0_CLK_IN       0<<5
#define T0_EXT_HL       1<<4
#define T0_EXT_LH       0<<4
#define T0_PRESC_1      0x8
#define T0_PRESC_2      0x0
#define T0_PRESC_4      0x1
#define T0_PRESC_8      0x2
#define T0_PRESC_16     0x3
#define T0_PRESC_32     0x4
#define T0_PRESC_64     0x5
#define T0_PRESC_128    0x6
#define T0_PRESC_256    0x7

#endif	/* TIMER0_H */

