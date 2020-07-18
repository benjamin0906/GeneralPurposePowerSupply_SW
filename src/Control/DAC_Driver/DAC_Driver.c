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
    EUSART_Task();
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
            State = WaitForSend;
            break;
        case WaitForSend:
            if(EUSART_Ready() != 0)
            {
                State = CsHigh;
            }
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
        volatile uint8 HByte = 0;
        volatile uint8 Low = 0;
        
        if((value & 0x8000) != 0) Low |= 0x1;
        if((value & 0x4000) != 0) Low |= 0x2;
        if((value & 0x2000) != 0) Low |= 0x4;
        if((value & 0x1000) != 0) Low |= 0x8;
        if((value & 0x0800) != 0) Low |= 0x10;
        if((value & 0x0400) != 0) Low |= 0x20;
        if((value & 0x0200) != 0) Low |= 0x40;
        if((value & 0x0100) != 0) Low |= 0x80;
        if((value & 0x0080) != 0) HByte |= 0x1;
        if((value & 0x0040) != 0) HByte |= 0x2;
        if((value & 0x0020) != 0) HByte |= 0x4;
        if((value & 0x0010) != 0) HByte |= 0x8;
        if((value & 0x0008) != 0) HByte |= 0x10;
        if((value & 0x0004) != 0) HByte |= 0x20;
        if((value & 0x0002) != 0) HByte |= 0x40;
        if((value & 0x0001) != 0) HByte |= 0x80;
        
        /*asm("MOVLB 1");
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
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),0,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),6,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),1,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),5,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),2,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),4,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),3,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),3,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),4,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),2,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),5,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),1,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),6,b");
        asm("BTFSC (DAC_Driver_Send@value)& (0+255),0,b");
        asm("BSF (DAC_Driver_Send@HByte)& (0+255),7,b");*/
        
        DacValue[0] = Low;
        DacValue[1] = HByte;
        
        State = CsLow;
    }
}
