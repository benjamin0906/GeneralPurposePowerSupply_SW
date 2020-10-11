#include "Control_Types.h"
#include "DAC_Driver.h"
#include "INA260_Driver.h"
#include "main.h"

static dtControl Variables;
static uint16 MeasuredVoltage;
static int16 MeasuredCurrent;
static int16 IntegratedOutValue;
static int16 PrevIntegratedOutValue;
static uint8 Timestamp;
static uint16 ReqVolt;

void Control_Init(void);
void Control_Task(void);
void Control_ReqVolt(uint16 req);
uint16 Control_GetMeasuredVotlage(void);
int16 Control_GetMeasuredCurrent(void);

void Control_Init(void)
{
    DAC_Driver_Init();
    INA260_Driver_Init();
}

void Control_Task(void)
{
    DAC_Driver_Task();
    INA260_Driver_Task();
    if(PrevIntegratedOutValue != IntegratedOutValue)
    {
        DAC_Driver_Send(IntegratedOutValue);
        PrevIntegratedOutValue = IntegratedOutValue;
    }
    
    if(INA260_Driver_GetValues(&MeasuredVoltage,&MeasuredCurrent,0) != 0)
    {
        MeasuredVoltage = MeasuredVoltage*2;
        MeasuredCurrent = MeasuredCurrent*2;
    }

    if(TickEllapsed(Timestamp,100) != 0)
    {
        Timestamp = GetTick();
        
        /* Calculate the error value */
        int16 error = ReqVolt - MeasuredVoltage;
        IntegratedOutValue += error>>2;
        
        /* Give a lower limit to the integrated value */
        if((IntegratedOutValue) < 0) IntegratedOutValue = 0;
        
        /* Give an upper limit to the Integrated error value */
        IntegratedOutValue &= 0x7FFF;
    }
}

void Control_ReqVolt(uint16 req)
{
    ReqVolt = req;
    //ReqVolt = (req<<3)/5;
}

/*
 * this function give back the measured value in mV dimension.
 */
uint16 Control_GetMeasuredVotlage(void)
{
    uint32 temp = (uint32)MeasuredVoltage*5;
    return (uint16)(temp>>3);
}

int16 Control_GetMeasuredCurrent(void)
{
    uint32 temp = MeasuredCurrent*5;
    return (temp)>>3;
    return temp;
}