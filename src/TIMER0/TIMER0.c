#include "TIMER0_Types.h"
#include "Interrupts.h"

static dtT0CON  *const T0CON = (dtT0CON*)(0xFD5);
static uint8   *const TMR0L  = (uint8*) (0xFD6);
static uint8   *const TMR0H  = (uint8*) (0xFD7);
static __bank(0) dtTMR    *TMR   = (dtTMR*) (0xFD6);
static void (*ExtIntHandler)(void);
static uint16 InitValue; 

void TIMER0_Set(uint8 Conf, uint16 Init, void (*Handler)(void));
void TIMER0_IntHandler(void);

void TIMER0_Set(uint8 Conf, uint16 Init, void (*Handler)(void))
{
    InitValue = Init;
    T0CON->Byte = Conf;
    dtTMR Temp = {.TMR0 = 0-InitValue};
    TMR->Fields.TMR0H = Temp.Fields.TMR0H;
    TMR->Fields.TMR0L = Temp.Fields.TMR0L;
    Interrupt_SetInt(INT_TIMER0, PRIO_LOW, TIMER0_IntHandler);
    if(Handler != 0) ExtIntHandler = Handler;
}


void TIMER0_IntHandler(void)
{
    dtTMR Temp = {.TMR0 = TMR->TMR0-InitValue};
    TMR->Fields.TMR0H = Temp.Fields.TMR0H;
    TMR->Fields.TMR0L = Temp.Fields.TMR0L;
    if(ExtIntHandler != 0) ExtIntHandler();
}