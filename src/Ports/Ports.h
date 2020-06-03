/* 
 * File:   Ports.h
 * Author: BodnárBenjamin
 *
 * Created on 30 January 2020, 21:01
 */

#ifndef PORTS_H
#define	PORTS_H

#include "../types.h"

typedef struct
{
    uint8   Port:4;
    uint8   Pin:4;
} dtGPIO;

extern uint8 GpioIn(dtGPIO GPIO);
extern void GpioOut(dtGPIO GPIO, uint8 State);
extern void GpioDir(dtGPIO GPIO, uint8 Dir);
extern void GpioToggle(dtGPIO GPIO);

extern const dtGPIO PINA0;
extern const dtGPIO PINA1;
extern const dtGPIO PINA2;
extern const dtGPIO PINA3;
extern const dtGPIO PINA4;
extern const dtGPIO PINA5;
extern const dtGPIO PINA6;
extern const dtGPIO PINA7;
extern const dtGPIO PINB0;
extern const dtGPIO PINB1;
extern const dtGPIO PINB2;
extern const dtGPIO PINB3;
extern const dtGPIO PINB4;
extern const dtGPIO PINB5;
extern const dtGPIO PINB6;
extern const dtGPIO PINB7;
extern const dtGPIO PINC0;
extern const dtGPIO PINC1;
extern const dtGPIO PINC2;
extern const dtGPIO PINC3;
extern const dtGPIO PINC4;
extern const dtGPIO PINC5;
extern const dtGPIO PINC6;
extern const dtGPIO PINC7;

#endif	/* PORTS_H */

