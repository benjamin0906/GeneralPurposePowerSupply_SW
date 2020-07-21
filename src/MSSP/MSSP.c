#include "MSSP_Types.h"
#include "MSSP.h"
#include "Ports.h"
#include "Interrupts.h"

static dtSSPSTAT *const SSPSTAT = (dtSSPSTAT*)(0xFC7);
static dtSSPCON1 *const SSPCON1 = (dtSSPCON1*)(0xFC6);
static dtSSPCON2 *const SSPCON2 = (dtSSPCON2*)(0xFC5);
static uint8     *const SSPADD  = (uint8*)(0xFC8);
static uint8     *const SSPBUF  = (uint8*)(0xFC9);

static uint8 SlaveAddress;
static uint8 *Address;
static uint8 *Data;
static uint8 AddressLength;
static uint8 DataLength;
static uint8 Cntr;
static dtMSSPState state;
static uint8 SendType;
static uint8 SignBack;

void MSSP_Init(void);
void MSSPIntHandler(void);
void MSSP_Send(dtMSSPTYPE ComType, uint8 SlaveAdd, uint8 *Add, uint8 AddLen, uint8 *D, uint8 DataLen);
uint8 MSSP_Ready(void);

uint8 a = 0xFE;
uint8 d[10] = {1,2,3,4,5,6,7,8,9,10};
uint8 dd[10];

void MSSP_Init(void)
{   
    GpioDir(PINB0, 1);
    GpioDir(PINB1, 1);
    
    SSPSTAT->Byte = 0x80;
    SSPCON1->Byte = 0x28;
    SSPCON2->Byte = 0;
    *SSPADD = 0x9;
    
    Interrupt_SetInt(INT_SSP,PRIO_HIGH, &MSSPIntHandler);
}

void MSSPIntHandler(void)
{
    switch(state)
    {
        case WriteSlaveAddress:
            *SSPBUF = SlaveAddress;
            state = SendAddress;
            Cntr = 0;
            break;
        case SendAddress:
            if(SSPCON2->Master.ACKSTAT == 0)
            {
                *SSPBUF = Address[Cntr++];
                if(Cntr == AddressLength)
                {
                    Cntr = 0;
                    if(SendType == 0) state = SendData;
                    else state = Restart;
                }
            }
            break;
        case SendData:
            if(SSPCON2->Master.ACKSTAT == 0)
            {
                *SSPBUF = Data[Cntr++];
                if(Cntr == DataLength) state = SendStop;
            }
            else
            {
                state = SendStop;
            }
            break;
        case Restart:
            state = SendRxSlaveAdd;
            SSPCON2->Master.RSEN = 1;
            break;
        case SendRxSlaveAdd:
            *SSPBUF = SlaveAddress | 1;
            state = SetReceiveMode;
            Cntr = 0;
            break;
        case SetReceiveMode:
            SSPCON2->Master.RCEN = 1;
            state = ReadData;
            break;
        case ReadData:
            Data[Cntr++] = *SSPBUF;
            if(Cntr < DataLength)
            {
                SSPCON2->Master.ACKEN = 1;
                state = SetReceiveMode;
            }
            else
            {
                SSPCON2->Master.PEN = 1;
                state = Fnished;
            }
            break;
        case SendStop:
            SSPCON2->Master.PEN = 1;
            state = Fnished;
            break;
        case Fnished:
            SignBack = 1;
            break;
    }
}

void MSSP_Send(dtMSSPTYPE ComType, uint8 SlaveAdd, uint8 *Add, uint8 AddLen, uint8 *D, uint8 DataLen)
{
    SlaveAddress = SlaveAdd<<1;
    Address = Add;
    AddressLength = AddLen;
    Data = D;
    DataLength = DataLen;
    state = WriteSlaveAddress;
    if(ComType == I2C_Write) SendType = 0;
    else if (ComType == I2C_Read) SendType = 1;
    SignBack = 0;
    SSPCON2->Master.SEN = 1;
}

uint8 MSSP_Ready(void)
{
    return SignBack != 0;
}