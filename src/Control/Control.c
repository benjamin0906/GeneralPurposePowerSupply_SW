#include "Control_Types.h"
#include "DAC_Driver.h"

static dtControl Variables;

void Control_Init(void);
void Control_Task(void);
void Control_ReqVolt(uint16 req);

void Control_Init(void)
{
    DAC_Driver_Init();
}

void Control_Task(void)
{
    DAC_Driver_Task();
    if(Variables.PrevRequestedVoltage != Variables.RequestedVoltage)
    {
        DAC_Driver_Send(Variables.RequestedVoltage);
        Variables.PrevRequestedVoltage = Variables.RequestedVoltage;
    }
}

void Control_ReqVolt(uint16 req)
{
    uint32 TempFullValue = (uint32)req<<4;
    uint32 TempTruncatedValue = 10*(((uint32)req<<3)/5);
    if((TempFullValue-TempTruncatedValue) >= 5) TempFullValue += 10;
    TempFullValue /= 10;
    Variables.RequestedVoltage = TempFullValue;
}