#include "Button_Types.h"
#include "Button.h"
#include "Ports.h"
#include "main.h"

static dtButtonTaskState State;
static dtButtonState ButtonState;
static uint8 TimeStamp;
static uint8 TapCounter;

void Button_Task(void);
dtButtonState Button_Value(void);

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
                if(TapCounter == 50) ButtonState = LongPressed;
                else
                {
                    TapCounter++;
                    ButtonState = Pressed;
                }
                State = Button_WaitForTimeout;
                TimeStamp = GetTick();
            }
            else
            {
                TapCounter = 0;
                ButtonState = Released;
            }
            break;
        case Button_WaitForTimeout:
            if(TickEllapsed(TimeStamp,10) != 0)
            {
                State = Button_WaitForAction;
            }
            break;
    }
}

dtButtonState Button_Value(void)
{
    return ButtonState;
}