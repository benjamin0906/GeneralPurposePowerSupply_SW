/* 
 * File:   Utilities.h
 * Author: Bodnár Benjamin
 *
 * Created on 05 July 2020, 12:47
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

#include "types.h"

extern uint8 Dabler16Bit(uint16 value, char *Digits);
extern uint8 NumToStr(uint8 num, uint8 *buff);
extern uint8 NumToStr16(uint16 num, uint8 *buff);
extern void MemCpy(uint8 *src, uint8 *dst, uint8 length);

#endif	/* UTILITIES_H */

