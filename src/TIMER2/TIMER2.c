#include "TIMER2_Types.h"
#include "TIMER2.h"
#include "Interrupts.h"

static dtT2CON *const T2CON = (dtT2CON*)(0xFCA);
static uint8   *const PR2   = (uint8*)  (0xFCB);
static uint8   *const TMR2  = (uint8*)  (0xFCC);

void TIMER2_Set(uint8 Conf, uint8 Comp, void (*handler)(void));

void TIMER2_Set(uint8 Conf, uint8 Comp, void (*handler)(void))
{
    *PR2 = Comp;
    if(handler != 0)
    {
        Interrupt_SetInt(INT_TIMER2, PRIO_HIGH, handler);
    }
    T2CON->Byte = Conf;
}