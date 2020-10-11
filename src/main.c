/*
 * File:   main.c
 * Author: Bodnár Benjamin
 *
 * Created on 29 May 2020, 12:51
 */

#pragma config FOSC = HSPLL_HS
#pragma config PLLDIV = 4
#pragma config CPUDIV = OSC1_PLL2
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

#include "Ports.h"
#include "EUSART.h"
#include "Interrupts.h"
#include "MSSP.h"
#include "TIMER2.h"
#include "TIMER0.h"
#include "Switch.h"
#include "UI.h"
#include "Control.h"

uint8 GetTick(void);
uint8 TickEllapsed(uint8 TimeStamp, uint8 Timeout);

uint8 Ticks;
void Ticker(void)
{
    Ticks++;
}
uint8 GetTick(void)
{
    return Ticks;
}

uint8 TickEllapsed(uint8 TimeStamp, uint8 Timeout)
{
    uint8 ret = 0;
    if((uint8)(Ticks-TimeStamp) >= Timeout) ret = 1;
    return ret;
}

void HAL_Init(void)
{
    GpioDir(PINA0,0);
    GpioDir(PINC6, 1);
    GpioDir(PINC7, 1);
    GpioDir(PIND2, 0);
    GpioOut(PIND2, 1);
    
    
    
    *((uint8*)0xFF1) &= 0x7F;

    Interrupt_Init();
    
    //
    //MSSP_Init();
}

void main(void) 
{
    HAL_Init();
    TIMER0_Set(T0_ENABLE|T0_16BIT|T0_CLK_IN|T0_PRESC_1, 11999, Ticker);
    while(GetTick() < 150);
    
    
    
    Switch_Init();
    Control_Init();
    UI_Init();

    while(1)
    {
        Switch_Task();
        Control_Task();
        UI_Task();
    }
    return;
}
