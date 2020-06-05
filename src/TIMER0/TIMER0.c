#include "TIMER0_Types.h"

static dtT0CON  *const T0CON = (dtT0CON*)(0xFD5);
static uint16   *const TMR0  = (uint16*) (0xFD6);

void TIMER0_Set(uint8 Conf, void (*Handler)(void));

void TIMER0_Set(uint8 Conf, void (*Handler)(void))
{
    T0CON->Byte = Conf;
    
}