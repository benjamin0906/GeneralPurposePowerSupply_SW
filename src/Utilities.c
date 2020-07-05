#include "types.h"

uint8 NumToStr(uint8 num, uint8 *buff)
{
    uint8 index = 0 ;
    uint8 mask = 1;
    uint8 Digit12 = 0;
    uint8 Digit3 = 0;
    for(mask = 1; mask != 0; mask <<= 1)
    {
        if(num&mask != 0)
        {
            switch(mask)
            {
                case 1:
                    Digit12 += 1;
                    break;
                case 2:
                    Digit12 += 2;
                    break;
                case 4:
                    Digit12 += 4;
                    break;
                case 8:
                    Digit12 += 8;
                    break;
                case 16:
                    Digit12 += 6;
                    Digit12 += 0x10;
                    break;
                case 32:
                    Digit12 += 2;
                    Digit12 += 0x30;
                    break;
                case 64:
                    Digit12 += 4;
                    Digit12 += 0x60;
                    break;
                case 128:
                    Digit12 += 8;
                    Digit12 += 0x20;
                    Digit3 += 1;
                    break;
            }
            if((Digit12&0xF) > 9) Digit12 += 6;
            if((Digit12&0xF0) > 0x90)
            {
                Digit12 += 0x60;
                Digit3 += 1;
            }
        }
    }
    buff[0] = 0x30 + (Digit12 & 0xF);
    buff[1] = 0x30 + (Digit12 >> 4);
    buff[2] = 0x30 + (Digit3);
}
