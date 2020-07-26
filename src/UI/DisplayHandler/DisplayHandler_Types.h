/* 
 * File:   DisplayHandler_Types.h
 * Author: Benjamin
 *
 * Created on 2019. március 30., 17:59
 */

#ifndef DISPLAYHANDLER_TYPES_H
#define	DISPLAYHANDLER_TYPES_H

#include "types.h"
#include "Ports.h"

#define LCD_RS  PINE1
#define LCD_RW  PINE0
#define LCD_EN  PINA5
#define LCD_D4  PINA4
#define LCD_D5  PINA3
#define LCD_D6  PINA2
#define LCD_D7  PINA1

#define LCD_BUFFER_SIZE 40

typedef enum eStateMachine
{
    
    LcdSetPinsHighNibble,
    LcdSetPinsLowNibble,
            LcdEnter_WaitBeforeEnable,
            LcdEnter_WaitEnableHoldTime,
} dtStateMachine;

typedef struct sOutputData
{
    uint8   data;
    uint8   DataOrCmd:1;
}dtOutputData;

typedef struct sDisplayHandler
{
    uint8           Timer;
    dtStateMachine  SM;
    dtOutputData    OutputBuffer[LCD_BUFFER_SIZE];
    uint8           OutputNum;
    uint8           OutputCntr;
    uint8           NextSm;
} dtDisplayHandler;

#endif	/* DISPLAYHANDLER_TYPES_H */

