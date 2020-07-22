#include "INA260_Driver_Types.h"
#include "MSSP.h"
#include "Ports.h"

static dtINA260DriverState State;
static dtStateFlags Flags;
static const uint8 INA260_SlaveAddress = 0x40;
static const uint8 INA260_ConfigReg = 0x00;
static const uint8 INA260_AlertMaskReg = 0x06;
static const uint8 INA260_CurrentReg = 0x01;
static const uint8 INA260_VoltageReg = 0x02;
static const uint8 INA260_PowerReg = 0x03;
static volatile uint8 Data[2];

void INA260_Driver_Init(void);
void INA260_Driver_Task(void);
void INA260_Driver_GetState(void);
uint8 INA260_Driver_GetValues(uint16 *Voltage, uint16 *Current, uint16 *Power);


void INA260_Driver_Init(void)
{
    MSSP_Init();
    GpioDir(PIND1,1);
}

void INA260_Driver_Task(void)
{
    switch(State)
    {
        case INA260_InitAlertMask:
            Data[0] = 0x04;
            Data[1] = 0x00;
            MSSP_Send(I2C_Write,INA260_SlaveAddress,&INA260_AlertMaskReg,1,&Data[0],2);
            State = INA260_InitConfig;
            break;
        case INA260_InitConfig:
            if(MSSP_Ready() != 0)
            {
                Data[0] = 0x07;
                Data[1] = 0x27;
                MSSP_Send(I2C_Write,INA260_SlaveAddress,&INA260_ConfigReg,1,&Data[0],2);
                State = INA260_WaitForConfigWrite;
            }
            break;
        case INA260_WaitForConfigWrite:
            if(MSSP_Ready() != 0)
            {
                Flags.Inited = 1;
                State = INA260_WatchAlert;
            }
            break;
        case INA260_WatchAlert:
            if(GpioIn(PIND1) == 0)
            {
                MSSP_Send(I2C_Read,INA260_SlaveAddress,&INA260_AlertMaskReg,1,&Data[0],2);
                State = INA260_ReadAlertWait;
            }
            break;
        case INA260_ReadAlertWait:
            if(MSSP_Ready() != 0) State = INA260_StartReadCurrent;
            break;
        case INA260_StartReadCurrent:
            MSSP_Send(I2C_Read,INA260_SlaveAddress,&INA260_CurrentReg,1,&Data[0],2);
            State = INA260_WaitForReadCurrent;
            break;
        case INA260_WaitForReadCurrent:
            if(MSSP_Ready() != 0) State = INA260_StartReadVoltage;
            break;
        case INA260_StartReadVoltage:
            MSSP_Send(I2C_Read,INA260_SlaveAddress,&INA260_VoltageReg,1,&Data[0],2);
            State = INA260_WaitForReadVoltage;
            break;
        case INA260_WaitForReadVoltage:
            if(MSSP_Ready() != 0) State = INA260_StartReadPower;
            break;
        case INA260_StartReadPower:
            MSSP_Send(I2C_Read,INA260_SlaveAddress,&INA260_PowerReg,1,&Data[0],2);
            State = INA260_WaitForReadPower;
            break;
        case INA260_WaitForReadPower:
            if(MSSP_Ready() != 0) State = INA260_WatchAlert;
            break;
    }
}