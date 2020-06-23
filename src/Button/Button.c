#include "Button_Types.h"
#include "Ports.h"

static dtButtonState State;
static uint8 ButtonState;

void Button_Task(void);

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
            }
            break;
        case Button_WaitForTimeout:
           /* if()
            {
                
            }*/
            break;
    }
}

