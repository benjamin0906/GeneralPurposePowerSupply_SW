#include "UI_Types.h"
#include "Encoder.h"
#include "DisplayHandler.h"
#include "Utilities.h"
#include "Switch.h"

static uint16 Value = 100;
static uint16 PrevValue;
static uint8 CoursorIndex = 4;

void SetDigits(void)
{
    if(PrevValue != Value)
    {
        PrevValue = Value;
        
        DisplayHandler_SetIndex(0,0);
        
        uint8 str[7] = {'0','0','.','0','0','0',0};
        
        uint8 len = NumToStr16(Value, str);
        switch(len)
        {
            case 5:
                str[5] = str[4];
                str[4] = str[3];
                str[3] = str[2];
                str[2] = '.';
                break;
            case 4:
                str[5] = str[3];
                str[4] = str[2];
                str[3] = str[1];
                str[2] = '.';
                str[1] = str[0];
                str[0] = '0';
                break;
            case 3:
                str[5] = str[2];
                str[4] = str[1];
                str[3] = str[0];
                str[2] = '.';
                str[1] = '0';
                str[0] = '0';
                break;
            case 2:
                str[5] = str[1];
                str[4] = str[0];
                str[3] = '0';
                str[2] = '.';
                str[1] = '0';
                str[0] = '0';
                break;
            case 1:
                str[5] = str[0];
                str[4] = '0';
                str[3] = '0';
                str[2] = '.';
                str[1] = '0';
                str[0] = '0';
                break;
        }
        
        PutStr(&str,0);
        DisplayHandler_SetIndex(CoursorIndex,0);
    }
}

void UI_Init(void)
{
    Encoder_Init();
    LCDInit();
}

int8 t[] = "A";
int8 PrevClick = 0;
int8 Click = 0;

void UI_Task(void)
{
    DisplayHandler_Task();
    Encoder_Task();
    
    SetDigits();
    
    Click = Encoder_GetClicks();
    if(Click != 0)
    {
        if(Switch_Value() != SwReleased)
        {
            uint8 PrevIndex = CoursorIndex;
            if(((CoursorIndex + Click) >= 0) && ((CoursorIndex + Click) <= 5))
            {
                CoursorIndex += Click;
                if((CoursorIndex == 2))
                {
                    if(PrevIndex > CoursorIndex) CoursorIndex--;
                    else CoursorIndex++;
                }
            }
            DisplayHandler_SetIndex(CoursorIndex,0);
        }
        else
        {
            uint16 ClickValue;
            switch(CoursorIndex)
            {
                case 0:
                    ClickValue = Click*10000;
                    break;
                case 1:
                    ClickValue = Click*1000;
                    break;
                case 3:
                    ClickValue = Click*100;
                    break;
                case 4:
                    ClickValue = Click*10;
                    break;
                case 5:
                    ClickValue = Click;
                    break;

            }
            if(((Value + ClickValue) >= 0) && ((Value + ClickValue) <= 30000)) Value += ClickValue;
        }
    }
}