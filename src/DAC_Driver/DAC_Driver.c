#include "DAC_Driver_Types.h"
#include "Ports.h"
#include "EUSART.h"

#define DAC_CS  PIND4

static dtDACState State;
static uint8 DacValue[2];

void DAC_Driver_Init(void);
void DAC_Driver_Task(void);
void DAC_Driver_Send(uint16 value);

void DAC_Driver_Init(void)
{
    GpioDir(DAC_CS,0);
    GpioOut(DAC_CS,1);
    dtEUSARTConf Config = {.Sync = 1, .Master = 1, .Tx9Bit = 0, .Rx9Bit = 0, .TxInv = 1, .RxInv = 0};
    EUSART_Init(Config,9600);
}

void DAC_Driver_Task(void)
{
    switch(State)
    {
        case DacIdle:
            break;
        case CsLow:
            GpioOut(DAC_CS,0);
            State = SendValue;
            break;
        case SendValue:
            EUSART_Send(DacValue,2);
            State = CsHigh;
            break;
        case CsHigh:
            GpioOut(DAC_CS,1);
            State = DacIdle;
            break;
    }
}

void DAC_Driver_Send(uint16 value)
{
    if(State == DacIdle)
    {
        /* Change the bit endianness */
        uint8 High = 0;
        uint8 Low = 0;
        asm("MOVLB 1");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),7,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),0,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),6,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),1,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),5,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),2,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),4,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),3,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),3,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),4,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),2,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),5,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),1,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),6,b");
        asm("BTFSC (DAC_Driver_Send@value+1)& (0+255),0,b");
        asm("BSF (DAC_Driver_Send@Low)& (0+255),7,b");
        
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),7,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),0,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),6,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),1,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),5,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),2,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),4,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),3,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),3,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),4,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),2,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),5,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),1,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),6,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),0,b");
        asm("BSF (DAC_Driver_Send@High)& (0+255),7,b");
        
        DacValue[0] = Low;
        DacValue[1] = High;
        
        State = CsLow;
    }
}
