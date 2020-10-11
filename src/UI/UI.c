#include "UI_Types.h"
#include "Encoder.h"
#include "DisplayHandler.h"
#include "Utilities.h"
#include "Switch.h"
#include "Control.h"
#include "main.h"

#define LED PIND0

static uint16 Value = 8000;
static uint16 PrevValue;
static uint8 CoursorIndex = 4;
static uint8 MeasValueTimeStamp;
static uint8 SetValueTimeStamp;

uint8 FormatDispStr(int16 Value, uint8 *digits)
{
    uint8 str[5];
    uint8 len = NumToStr16(Value, str);
    uint8 looper = 4;
    uint8 ret;
    if(len == 5) looper = 5;
    ret = looper+1;
    digits[looper--] = str[--len];
    if(len != 0) digits[looper--] = str[--len];
    else digits[looper--] = '0';
    if(len != 0) digits[looper--] = str[--len];
    else digits[looper--] = '0';
    digits[looper--] = '.';
    if(len != 0) digits[looper--] = str[--len];
    else digits[looper--] = '0';
    if(len != 0) digits[looper--] = str[--len];
    else digits[looper--] = '0';
    if(len != 0) digits[looper--] = str[--len];
    else digits[looper--] = '0';
    return ret;
}

void UI_Init(void)
{
    GpioDir(LED, 0);
    GpioOut(LED, 0);
    Encoder_Init();
    LCDInit();  
}

void UI_Task(void)
{
    DisplayHandler_Task();
    Encoder_Task();
    
    if(TickEllapsed(MeasValueTimeStamp,200) != 0)
    {
        MeasValueTimeStamp = GetTick();
        int16 Temp;
        uint8 InputValueLength;
        uint8 OutputValueLength;
        uint8 Digits[17];
        uint8 OutputStr[8];
        uint8 looper = 0;
        
        //Temp = (((uint32)Value)*5)>>3;
        Temp = (RoundRawToDec((Value)));
        if(Temp < 10000)
        {
            looper = 1;
            Digits[0] = '0';
        }
        InputValueLength = FormatDispStr(Temp,&Digits[looper]) + looper;
        Digits[InputValueLength++] = 'V';
        
        Temp = Control_GetMeasuredVotlage();
        OutputValueLength = FormatDispStr(Temp,OutputStr);
        OutputStr[OutputValueLength++] = 'V'; 
        for(looper = InputValueLength; looper < (16-OutputValueLength); looper++) Digits[looper] = ' ';
        OutputValueLength = 0;
        while(looper < 16)
        {
            Digits[looper] = OutputStr[OutputValueLength++];
            looper++;
        }
        Digits[looper++] = 0;
        looper = 0;
        PutStr(Digits,0);
        Temp = Control_GetMeasuredCurrent();
        if(Temp < 0)
        {
            Temp *= -1;
            Digits[looper++] = '-';
        }
        looper += FormatDispStr(Temp, &Digits[looper]);
        Digits[looper++] = 'A';
        Digits[looper] = 0;
        PutStr(Digits,32-looper);
        DisplayHandler_SetIndex(CoursorIndex,0);
    }
    Control_ReqVolt(Value);
    
    int8 Click = Encoder_GetClicks();
    if(Click != 0)
    {
        if(Switch_Value() != SwReleased)
        {
            Click*=-1;
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
            uint8 Subtract = 0;
            if(Click < 0)
            {
                Subtract = 1;
                Click *= -1;
            }
            uint16 ClickValue;
            switch(CoursorIndex)
            {
                case 0:
                    ClickValue = Click*16000;
                    break;
                case 1:
                    ClickValue = Click*1600;
                    break;
                case 3:
                    ClickValue = Click*160;
                    break;
                case 4:
                    ClickValue = Click*16;
                    break;
                case 5:
                    ClickValue = Click*8;
                    break;

            }
            if(Subtract != 0)
            {
                /* The ClickValue shall be subtract from the desired voltage value */
                if((Value-ClickValue) >= 0) Value -= ClickValue;
            }
            else
            {
                /* the ClickValue shall be added from the desired voltage value */
                if((Value + ClickValue) <= 48000) Value += ClickValue;
            }
        }
    }
}