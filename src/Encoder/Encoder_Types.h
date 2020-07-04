/* 
 * File:   Encoder_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 04 July 2020, 11:20
 */

#ifndef ENCODER_TYPES_H
#define	ENCODER_TYPES_H

#include "types.h"

typedef struct
{
    uint8 ClickProgress :1;
    uint8 CWoCCW           :1;
} dtEncoderState;

#endif	/* ENCODER_TYPES_H */

