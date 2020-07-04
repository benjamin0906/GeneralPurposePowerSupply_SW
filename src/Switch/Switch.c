#include "Switch_Types.h"
#include "Switch.h"
#include "Ports.h"
#include "main.h"

#define GPIO    PINC2

static dtSwitchTaskState State;
static dtSwitchState SwitchState;
static uint8 TimeStamp;
static uint8 TapCounter;
static uint8 PrevState;

void Switch_Init(void);
void Switch_Task(void);
dtSwitchState Switch_Value(void);

void Switch_Init(void)
{
    GpioDir(GPIO, 1);
    State = Switch_WaitForAction;
}

void Switch_Task(void)
{
    uint8 CurrentState = GpioIn(GPIO);
    if(State == Switch_WaitForAction)
    {
        if(CurrentState != PrevState)
        {
            PrevState = CurrentState;
            State = Switch_WaitForTimeout;
            TimeStamp = GetTick();
            if(PrevState == 0) SwitchState = SwPressed;
            else
            {
                TapCounter = 1;
                SwitchState = SwReleased;
            }
        }
        else
        {
            if((CurrentState == 0) && (TickEllapsed(TimeStamp,10)))
            {
                TimeStamp = GetTick();
                if(TapCounter == 49) SwitchState = SwLongPressed;
                else TapCounter++;
            }
        }
    }
    else
    {
        if(TickEllapsed(TimeStamp,10) != 0)
        {
            State = Switch_WaitForAction;
            TimeStamp = GetTick();
        }
    }
}

dtSwitchState Switch_Value(void)
{
    return SwitchState;
}