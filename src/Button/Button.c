#include "Button_Types.h"
#include "Ports.h"
#include "main.h"

static dtButtonState State;
static uint8 ButtonState;
static uint8 TimeStamp;

void Button_Task(void);
uint8 Button_Value(void);

void Button_Task(void)
{
    switch(State)
    {
        case Button_Init:
            GpioDir(PINC2, 1);
            State = Button_WaitForAction;
            break;
        case Button_WaitForAction:
            if(GpioIn(PINC2) == 0)
            {
                State = Button_WaitForTimeout;
                ButtonState = 1;
                TimeStamp = GetTick();
            }
            else ButtonState = 0;
            break;
        case Button_WaitForTimeout:
            if(TickEllapsed(TimeStamp,10) != 0)
            {
                State = Button_WaitForAction;
            }
            break;
    }
}

uint8 Button_Value(void)
{
    return ButtonState;
}