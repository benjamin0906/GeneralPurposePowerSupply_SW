#include "Switch_Types.h"
#include "Switch2.h"
#include "Ports.h"
#include "main.h"

#define GPIO    PINC0

static dtSwitchTaskState State;
static dtSwitch2State Switch2State;
static uint8 TimeStamp;
static uint8 TapCounter;
static uint8 PrevState;

void Switch2_Init(void);
void Switch2_Task(void);
dtSwitch2State Switch2_Value(void);

void Switch2_Init(void)
{
    GpioDir(GPIO, 1);
    State = Switch_WaitForAction;
}

void Switch2_Task(void)
{
    uint8 CurrentState = GpioIn(GPIO);
    if(State == Switch_WaitForAction)
    {
        if(CurrentState != PrevState)
        {
            PrevState = CurrentState;
            State = Switch_WaitForTimeout;
            TimeStamp = GetTick();
            if(PrevState == 0) Switch2State = Sw2Pressed;
            else
            {
                TapCounter = 1;
                Switch2State = Sw2Released;
            }
        }
        else
        {
            if((CurrentState == 0) && (TickEllapsed(TimeStamp,10)))
            {
                TimeStamp = GetTick();
                if(TapCounter == 49) Switch2State = Sw2LongPressed;
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

dtSwitch2State Switch2_Value(void)
{
    return Switch2State;
}