
#include "Encoder_Types.h"
#include "Switch2.h"
#include "Switch3.h"

static int8 Click;
static dtEncoderState EncState;

void Encoder_Init(void)
{
    Switch2_Init();
    Switch3_Init();
}

void Encoder_Task(void)
{
    Switch2_Task();
    Switch3_Task();
    if(EncState.ClickProgress == 0)
    {
        /* Wait for action */
        if(Switch2_Value() == Sw2Pressed)
        {
            EncState.CWoCCW = 1;
            EncState.ClickProgress = 1;
        }
        else if(Switch3_Value() == Sw3Pressed)
        {
            EncState.CWoCCW = 0;
            EncState.ClickProgress = 1;
        }
    }
    else
    {
        /* Wait for idle */
        if((Switch3_Value() == Sw3Released) && (Switch2_Value() == Sw2Released))
        {
            if(EncState.CWoCCW == 1) Click--;
            else Click++;
            EncState.ClickProgress = 0;
        }
    }
}

uint8 Encoder_GetClicks(void)
{
    uint8 ret = Click;
    Click = 0;
    return ret;
}