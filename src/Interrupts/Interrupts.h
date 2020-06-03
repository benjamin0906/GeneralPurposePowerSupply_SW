/* 
 * File:   Interrupts.h
 * Author: Bodnár Benjamin
 *
 * Created on 03 June 2020, 07:26
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "types.h"

#define PRIO_HIGH   1
#define PRIO_LOW    0

#define INT_EUSART_RX   0<<4|5
#define INT_EUSART_TX   0<<4|4

extern void Interrupt_SetInt(uint8 Int, uint8 prio, void (*handler)(void));
extern void Interrupt_Init(void);
extern void Interrupt_Disable(uint8 Int);

#endif	/* INTERRUPTS_H */

