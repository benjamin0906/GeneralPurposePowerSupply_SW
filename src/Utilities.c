#include "types.h"

void Dabler8Bit(uint8 value, char *Digits)
{
    uint32 bcd = 0;
    uint8 DigitNum = 8;
    uint8 looper = 0;
    for(looper = 0; looper < 8; looper++)
    {
        if((bcd & 0xF) >= 5) bcd += 3;
        if((bcd & 0xF0) >= 0x50) bcd += 0x30;
        if((bcd & 0xF00) >= 0x500) bcd += 0x300;
        bcd<<=1;
        if((value&0x80) != 0) bcd |= 1;
        value <<= 1;

    }

    if((bcd&0xF0000000) == 0)
    {
        DigitNum--;
        if((bcd&0x0F000000) == 0)
        {
            DigitNum--;
            if((bcd&0x00F00000) == 0)
            {
                DigitNum--;
                if((bcd&0x000F0000) == 0)
                {
                    DigitNum--;
                    if((bcd&0x0000F000) == 0)
                    {
                        DigitNum--;
                        if((bcd&0x00000F00) == 0)
                        {
                            DigitNum--;
                            if((bcd&0x000000F0) == 0) DigitNum--;
                        }
                    }
                }
            }
        }
    }

    looper = 0;
    do
    {
        Digits[looper] = '0';
        switch (DigitNum)
        {
        case 8:
            Digits[looper] += bcd>>28;
            break;
        case 7:
            Digits[looper] += (bcd>>24)&0xF;
            break;
        case 6:
            Digits[looper] += (bcd>>20)&0xF;
            break;
        case 5:
            Digits[looper] += (bcd>>16)&0xF;
            break;
        case 4:
            Digits[looper] += (bcd>>12)&0xF;
            break;
        case 3:
            Digits[looper] += (bcd>>8)&0xF;
            break;
        case 2:
            Digits[looper] += (bcd>>4)&0xF;
            break;
        case 1:
            Digits[looper] += (bcd)&0xF;
            break;
        }
        looper++;
        DigitNum--;
    } while(DigitNum != 0);
    Digits[looper] = 0;
}

uint8 Dabler16Bit(uint16 value, char *Digits)
{
    uint32 bcd = 0;
    uint8 DigitNum = 8;
    uint8 looper = 0;
    for(looper = 0; looper < 16; looper++)
    {
        if((bcd & 0xF) >= 5) bcd += 3;
        if((bcd & 0xF0) >= 0x50) bcd += 0x30;
        if((bcd & 0xF00) >= 0x500) bcd += 0x300;
        if((bcd & 0xF000) >= 0x5000) bcd += 0x3000;
        if((bcd & 0xF0000) >= 0x50000) bcd += 0x30000;
        if((bcd & 0xF00000) >= 0x500000) bcd += 0x300000;
        bcd<<=1;
        if((value&0x8000) != 0) bcd |= 1;
        value <<= 1;
    }

    if((bcd&0xF0000000) == 0)
    {
        DigitNum--;
        if((bcd&0x0F000000) == 0)
        {
            DigitNum--;
            if((bcd&0x00F00000) == 0)
            {
                DigitNum--;
                if((bcd&0x000F0000) == 0)
                {
                    DigitNum--;
                    if((bcd&0x0000F000) == 0)
                    {
                        DigitNum--;
                        if((bcd&0x00000F00) == 0)
                        {
                            DigitNum--;
                            if((bcd&0x000000F0) == 0) DigitNum--;
                        }
                    }
                }
            }
        }
    }

    looper = 0;
    do
    {
        Digits[looper] = '0';
        switch (DigitNum)
        {
        case 8:
            Digits[looper] += bcd>>28;
            break;
        case 7:
            Digits[looper] += (bcd>>24)&0xF;
            break;
        case 6:
            Digits[looper] += (bcd>>20)&0xF;
            break;
        case 5:
            Digits[looper] += (bcd>>16)&0xF;
            break;
        case 4:
            Digits[looper] += (bcd>>12)&0xF;
            break;
        case 3:
            Digits[looper] += (bcd>>8)&0xF;
            break;
        case 2:
            Digits[looper] += (bcd>>4)&0xF;
            break;
        case 1:
            Digits[looper] += (bcd)&0xF;
            break;
        }
        looper++;
        DigitNum--;
    } while(DigitNum != 0);
    Digits[looper] = 0;
    return looper;
}

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

uint8 NumToStr16(uint16 num, uint8 *buff)
{
    uint16 mask = 1;
    uint8 index = 0;
    uint8 Digits[5] = {0,0,0,0,0};
    for(mask = 1; mask != 0; mask <<= 1)
    {
        if((num&mask) != 0)
        {
            switch(mask)
            {
                case 1:
                case 2:
                case 4:
                case 8:
                    Digits[0] += mask;
                    break;
                case 16:
                    Digits[0] += 0x6;
                    Digits[1] += 0x1;
                    break;
                case 32:
                    Digits[0] += 0x2;
                    Digits[1] += 0x3;
                    break;
                case 64:
                    Digits[0] += 0x4;
                    Digits[1] += 0x6;
                    break;
                case 128:
                    Digits[0] += 0x8;
                    Digits[1] += 0x2;
                    Digits[2] += 0x1;
                    break;
                case 256:
                    Digits[0] += 0x6;
                    Digits[1] += 0x5;
                    Digits[2] += 0x2;
                    break;
                case 512:
                    Digits[0] += 0x2;
                    Digits[1] += 0x1;
                    Digits[2] += 0x5;
                    break;
                case 1024:
                    Digits[0] += 0x4;
                    Digits[1] += 0x2;
                    Digits[2] += 0x0;
                    Digits[3] += 0x1;
                    break;
                case 2048:
                    Digits[0] += 0x8;
                    Digits[1] += 0x4;
                    Digits[2] += 0x0;
                    Digits[3] += 0x2;
                    break;
                case 4096:
                    Digits[0] += 0x6;
                    Digits[1] += 0x9;
                    Digits[2] += 0x0;
                    Digits[3] += 0x4;
                    break;
                case 8192:
                    Digits[0] += 0x2;
                    Digits[1] += 0x9;
                    Digits[2] += 0x1;
                    Digits[3] += 0x8;
                    break;
                case 16384:
                    Digits[0] += 0x4;
                    Digits[1] += 0x8;
                    Digits[2] += 0x3;
                    Digits[3] += 0x6;
                    Digits[4] += 0x1;
                    break;
                case 32768:
                    Digits[0] += 0x8;
                    Digits[1] += 0x6;
                    Digits[2] += 0x7;
                    Digits[3] += 0x2;
                    Digits[4] += 0x3;
                    break;
            }
            if((Digits[0]) > 0x9)
            {
                Digits[0] += 0x6;
                Digits[1] += Digits[0]>>4;
                Digits[0] &= 0xF;
            }
            if((Digits[1]) > 0x9)
            {
                Digits[1] += 0x6;
                Digits[2] += Digits[1]>>4;
                Digits[1] &= 0xF;
            }
            if((Digits[2]) > 0x9)
            {
                Digits[2] += 0x6;
                Digits[3] += Digits[2]>>4;
                Digits[2] &= 0xF;
            }
            if((Digits[3]) > 0x9)
            {
                Digits[3] += 0x6;
                Digits[4] += Digits[3]>>4;
                Digits[3] &= 0xF;
            }
            if((Digits[4]) > 0x9)
            {
                Digits[4] += 0x6;
                Digits[4] &= 0xF;
            }
        }
    }
    for(mask = 4; mask != 0; mask--)
    {
        if((Digits[mask] != 0) || (index != 0))
        {
            buff[index++] = '0'+Digits[mask];
        }
    }
    buff[index++] = '0'+Digits[mask];
    return index;
}

void MemCpy(uint8 *src, uint8 *dst, uint8 length)
{
    uint8 looper;
    for(looper = 0; looper<length; looper++)
    {
        dst[looper] = src[looper];
    }
}

uint32 RoundIntermediate(uint32 value)
{
    uint32 temp = value>>2;
    temp = value-(temp<<2);
    if(temp >= 4) value += 1;
    return value;
}