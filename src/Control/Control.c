#include "Control_Types.h"
#include "DAC_Driver.h"
#include "INA260_Driver.h"

static dtControl Variables;
static int16 Voltage;

void Control_Init(void);
void Control_Task(void);
void Control_ReqVolt(uint16 req);
uint16 Control_GetMeasuredVotlage(void);

void Control_Init(void)
{
    DAC_Driver_Init();
    INA260_Driver_Init();
}

void Control_Task(void)
{
    DAC_Driver_Task();
    INA260_Driver_Task();
    //TODO: ina260 init should be somewhere here
    //MSSP_Send(I2C_Read,sa,&a,1,&dd,2);
    //while(MSSP_Ready() == 0);
    if(Variables.PrevRequestedVoltage != Variables.RequestedVoltage)
    {
        DAC_Driver_Send(Variables.RequestedVoltage);
        Variables.PrevRequestedVoltage = Variables.RequestedVoltage;
    }
    INA260_Driver_GetValues(&Voltage,0,0);
}

void Control_ReqVolt(uint16 req)
{
    uint32 TempFullValue = (uint32)req<<4;
    uint32 TempTruncatedValue = 10*(((uint32)req<<3)/5);
    if((TempFullValue-TempTruncatedValue) >= 5) TempFullValue += 10;
    TempFullValue /= 10;
    Variables.RequestedVoltage = TempFullValue;
}

uint16 Control_GetMeasuredVotlage(void)
{
    uint8 Temp = Voltage*5;
    uint16 ret = Voltage + (Voltage>>2);
    if((Temp & 2) != 0) ret++;
    return ret;
}