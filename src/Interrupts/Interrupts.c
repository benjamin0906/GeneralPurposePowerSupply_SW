#include "Interrupts.h"
#include "Interrupts_Types.h"

static uint8 *const RCON = (uint8*)(0xFD0);
static uint8 *const INTCON = (uint8*)(0xFF2);
static uint8 *const INTCON2 = (uint8*)(0xFF1);
static uint8 *const INTCON3 = (uint8*)(0xFF0);
static dtPI *const PI1 = (dtPI*)(0xF9D);
static dtPI *const PI2 = (dtPI*)(0xFA0);
static uint8 HighPrioIntReg;
static uint8 HighPrioIntClearMask;
static uint8 LowPrioIntReg;
static uint8 LowPrioIntClearMask;
static void (*HighPrioIntHandler)(void);
static void (*LowPrioIntHandler)(void);

void Interrupt_Init(void);
void Interrupt_SetInt(uint8 Int, uint8 prio, void (*handler)(void));
void Interrupt_Disable(uint8 Int);

void Interrupt_Init(void)
{
    *RCON |= 0x80;
    *INTCON = 0xC0;
    *INTCON2 &= 0x80;
    *INTCON3  = 0;
    PI1->PIE = 0;
    PI2->PIE = 0;
}

void Interrupt_SetInt(uint8 Int, uint8 prio, void (*handler)(void))
{
    uint8 IntReg = Int >> 4;
    if(IntReg < 2)
    {
        volatile uint8 IntMask = 1<<(Int & 0xF);
        volatile uint8 IntIndex = 3 * IntReg;
        if(prio == PRIO_HIGH)
        {
            HighPrioIntReg = IntReg;
            HighPrioIntClearMask = ~IntMask;
            if(handler != 0) HighPrioIntHandler = handler;
            (*(PI1+IntIndex)).IPR |= IntMask;
        }
        else
        {
            LowPrioIntReg = IntReg;
            LowPrioIntClearMask = ~IntMask;
            if(handler != 0) LowPrioIntHandler = handler;
            (*(PI1+IntIndex)).IPR &= ~IntMask;
        }
        (*(PI1+IntIndex)).PIE |= IntMask;
    }
    else
    {
        /**/
        uint8 IntMask = 1<<(Int & 0xF);
        if(prio == PRIO_HIGH)
        {
            HighPrioIntReg = IntReg;
            HighPrioIntClearMask = ~IntMask;
            if(handler != 0) HighPrioIntHandler = handler;
            *INTCON2 |= IntMask;
        }
        else
        {
            LowPrioIntClearMask = ~IntMask;
            LowPrioIntReg = IntReg;
            if(handler != 0) LowPrioIntHandler = handler;
            *INTCON2 &= ~IntMask;
        }
        *INTCON |= IntMask<<3;
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
    /* Clear the interrupt flag */
    if(HighPrioIntReg == 0) PI1->PIR &= HighPrioIntClearMask;
    else if(HighPrioIntReg == 1) PI2->PIR &= HighPrioIntClearMask;
    else *INTCON &= HighPrioIntClearMask;
    
    /* Calling the interrupt handler function */
    if(HighPrioIntHandler != 0) HighPrioIntHandler();

}

void __interrupt(low_priority) ISRHandler2(void)
{
    /* Clear the interrupt flag */
    if(LowPrioIntReg == 0) PI1->PIR &= LowPrioIntClearMask;
    else if(LowPrioIntReg == 1) PI2->PIR &= LowPrioIntClearMask;
    else *INTCON &= LowPrioIntClearMask;
    
    /* Calling the interrupt handler function */
    if(LowPrioIntHandler != 0) LowPrioIntHandler();
}