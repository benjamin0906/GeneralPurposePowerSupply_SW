#include "Switch_Types.h"
#include "Switch3.h"
#include "Ports.h"
#include "main.h"

#define GPIO    PINC1

static dtSwitchTaskState State;
static dtSwitch3State Switch3State;
static uint8 TimeStamp;
static uint8 TapCounter;
static uint8 PrevState;

void Switch3_Init(void);
void Switch3_Task(void);
dtSwitch3State Switch3_Value(void);

void Switch3_Init(void)
{
    GpioDir(GPIO, 1);
    State = Switch_WaitForAction;
}

void Switch3_Task(void)
{
    uint8 CurrentState = GpioIn(GPIO);
    if(State == Switch_WaitForAction)
    {
        if(CurrentState != PrevState)
        {
            PrevState = CurrentState;
            State = Switch_WaitForTimeout;
            TimeStamp = GetTick();
            if(PrevState == 0) Switch3State = Sw3Pressed;
            else
            {
                TapCounter = 1;
                Switch3State = Sw3Released;
            }
        }
        else
        {
            if((CurrentState == 0) && (TickEllapsed(TimeStamp,10)))
            {
                TimeStamp = GetTick();
                if(TapCounter == 49) Switch3State = Sw3LongPressed;
                else TapCounter++;
            }
        }
    }
    else
    {
        if(TickEllapsed(TimeStamp,5) != 0)
        {
            State = Switch_WaitForAction;
            TimeStamp = GetTick();
        }
    }
}

dtSwitch3State Switch3_Value(void)
{
    return Switch3State;
}