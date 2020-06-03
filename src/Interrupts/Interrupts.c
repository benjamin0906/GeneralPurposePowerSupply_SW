#include "Interrupts.h"
#include "Interrupts_Types.h"

static uint8 *const RCON = (uint8*)(0xFD0);
static uint8 *const INTCON = (uint8*)(0xFF2);
static uint8 *const INTCON2 = (uint8*)(0xFF1);
static uint8 *const INTCON3 = (uint8*)(0xFF0);
static dtPI *const PI1 = (dtPI*)(0xF9D);
static void (*PIHandlers[16])(void);

void Interrupt_Init(void);
void Interrupt_SetInt(uint8 Int, uint8 prio, void (*handler)(void));
void Interrupt_Disable(uint8 Int);

void Interrupt_Init(void)
{
    *RCON |= 0x80;
    *INTCON |= 0xA0;
}

void Interrupt_SetInt(uint8 Int, uint8 prio, void (*handler)(void))
{
    uint8 IntIndex = Int >> 4;
    if(IntIndex < 2)
    {
        uint8 IntMask = 1<<(Int & 0xF);
        IntIndex *= 3;
        if(handler != 0) PIHandlers[((Int>>4)+1)*(Int&0xF)] = handler;
        if(prio == PRIO_HIGH) (*(PI1+IntIndex)).IPR |= IntMask;
        else (*(PI1+IntIndex)).IPR &= ~IntMask;
        (*(PI1+IntIndex)).PIE |= IntMask;
    }
    else
    {
        /**/
    }
}

void Interrupt_Disable(uint8 Int)
{
    uint8 IntIndex = Int >> 4;
    if(IntIndex < 2)
    {
        uint8 IntMask = 1<<(Int & 0xF);
        IntIndex *= 3;
        (*(PI1+IntIndex)).PIE &= ~IntMask;
    }
    else
    {
        /**/
    }
}

void __interrupt(high_priority) ISRHandler(void)
{
    uint8 looper;
    for(looper = 0; looper<16; looper++)
    {
        uint8 PIIndex = 0;
        uint8 PIMask = 1<<looper;
        if(looper > 7)
        {
            PIMask = 1<<(looper-8);
            PIIndex = 1;
        }
        if((((*(PI1+PIIndex)).IPR & PIMask) != 0) && (((*(PI1+ PIIndex)).PIR & PIMask) != 0))
        {
            if(PIHandlers[looper] != 0) PIHandlers[looper]();
            (*(PI1+PIIndex)).PIR = 0;
        }
    }
}

void __interrupt(low_priority) ISRHandler2(void)
{
    
}