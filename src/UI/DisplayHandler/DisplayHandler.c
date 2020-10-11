#include "DisplayHandler_Types.h"
#include "main.h"

dtDisplayHandler DisplayHandler;

void LCDInit(void);
void DisplayHandler_Task(void);
void LCDSendByte(uint8 data, uint8 CoM);
void PutStr(uint8 *data, uint8 line);
void LcdClear(void);

void LCDSendByte(uint8 data, uint8 CoM)
{
    DisplayHandler.OutputBuffer[DisplayHandler.OutputNum].data=data;
    DisplayHandler.OutputBuffer[DisplayHandler.OutputNum].DataOrCmd = CoM;
    DisplayHandler.OutputNum++;
    if(DisplayHandler.OutputNum >= LCD_BUFFER_SIZE) DisplayHandler.OutputNum=0; 
}

void DisplayHandler_SetIndex(uint8 column, uint8 row)
{
    if(row != 0) LCDSendByte(0xA8+column,1);
    else LCDSendByte(0x80+column,1);
}

void PutStr(uint8 *data, uint8 line)
{
    uint8 looper = 0x80 + line;
    if(line >= 16) looper += 48;
    LCDSendByte(looper,1);
    for(looper = 0; (data[looper] != 0)&& (looper < 16); looper++) LCDSendByte(data[looper],0);
}

void LcdClear(void)
{
    LCDSendByte(0x01,1);
}

void LCDInit(void)
{
    GpioDir(LCD_RS,0);
    GpioDir(LCD_RW,0);
    GpioDir(LCD_EN,0);
    GpioDir(LCD_D4,0);
    GpioDir(LCD_D5,0);
    GpioDir(LCD_D6,0);
    GpioDir(LCD_D7,0);
    
    GpioOut(LCD_RS,0);
    GpioOut(LCD_RW,0);
    GpioOut(LCD_EN,1);
    
    DisplayHandler.OutputCntr=0;
    DisplayHandler.OutputNum=0;
    
    LCDSendByte(0x02,1);    //set to 4-bit mode if the display is in 8-bit mode
    LCDSendByte(0x28,1);    //set 4-bit mode with two line functionality
    LCDSendByte(0x08,1);    // turn off display
    LCDSendByte(0x0F,1);    // turn on display with cursor
    LCDSendByte(0x01,1);    //clear display
}

void DisplayHandler_Task(void)
{
    switch(DisplayHandler.SM)
    {
        case LcdEnter_WaitBeforeEnable:
            if(TickEllapsed(DisplayHandler.Timer,1) != 0)
            {
                GpioOut(LCD_EN,0);
                DisplayHandler.SM = LcdEnter_WaitEnableHoldTime;
                DisplayHandler.Timer = GetTick();
            }
            break;
        case LcdEnter_WaitEnableHoldTime:
            if(TickEllapsed(DisplayHandler.Timer,1) != 0)
            {
                GpioOut(LCD_EN,1);
                DisplayHandler.SM = DisplayHandler.NextSm;
            }
            break;
            
        case LcdSetPinsHighNibble:
            if(DisplayHandler.OutputCntr != DisplayHandler.OutputNum)
            {
                if(DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].DataOrCmd != 0) GpioOut(LCD_RS,0);
                else GpioOut(LCD_RS,1);

                if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x80)!=0) GpioOut(LCD_D7,1);
                else GpioOut(LCD_D7,0);
                if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x40)!=0) GpioOut(LCD_D6,1);
                else GpioOut(LCD_D6,0);
                if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x20)!=0) GpioOut(LCD_D5,1);
                else GpioOut(LCD_D5,0);
                if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x10)!=0) GpioOut(LCD_D4,1);
                else GpioOut(LCD_D4,0);
                
                DisplayHandler.NextSm = LcdSetPinsLowNibble;
                //GpioOut(LCD_EN,1);
                DisplayHandler.SM = LcdEnter_WaitBeforeEnable;
                DisplayHandler.Timer = GetTick();
            }
            break;
            
        case LcdSetPinsLowNibble:
            if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x8)!=0) GpioOut(LCD_D7,1);
            else GpioOut(LCD_D7,0);
            if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x4)!=0) GpioOut(LCD_D6,1);
            else GpioOut(LCD_D6,0);
            if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x2)!=0) GpioOut(LCD_D5,1);
            else GpioOut(LCD_D5,0);
            if((DisplayHandler.OutputBuffer[DisplayHandler.OutputCntr].data&0x1)!=0) GpioOut(LCD_D4,1);
            else GpioOut(LCD_D4,0);
            
            DisplayHandler.OutputCntr++;
            if(DisplayHandler.OutputCntr >= LCD_BUFFER_SIZE) DisplayHandler.OutputCntr=0;
            DisplayHandler.NextSm = LcdSetPinsHighNibble;
            //GpioOut(LCD_EN,1);
            DisplayHandler.SM = LcdEnter_WaitBeforeEnable;
            DisplayHandler.Timer = GetTick();
            
            break;
    }
}