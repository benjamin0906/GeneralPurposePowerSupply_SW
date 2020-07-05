#include "types.h"
#include "Encoder.h"
#include "DisplayHandler.h"
#include "Utilities.h"

void UI_Init(void)
{
    Encoder_Init();
    LCDInit();
    
    PutStr("Sziaa",0);
}

int8 t[] = "A";
int8 PrevClick = 0;
int8 Click = 0;

void UI_Task(void)
{
    DisplayHandler_Task();
    Encoder_Task();
    Click = Encoder_GetClicks();
    if(Click != 0)
    {
        uint8 buff[4] = {0,0,0,0};
        PrevClick += Click;
        uint8 length = NumToStr(PrevClick, buff);
        buff[length] = 0;
        LcdClear();
        PutStr(&buff,0);
    }
}