/*
 * File:   main.c
 * Author: Bodnár Benjamin
 *
 * Created on 29 May 2020, 12:51
 */

#pragma config FOSC = INTOSCIO_EC
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
#include "DAC_Driver.h"

void HAL_Init(void)
{
    GpioDir(PINA0,0);
    GpioDir(PINC6, 1);
    GpioDir(PINC7, 1);
    GpioDir(PIND2, 0);
    GpioOut(PIND2, 1);
    
    *((uint8*)0xFF1) &= 0x7F;

    Interrupt_Init();
    
    DAC_Driver_Init();
    //MSSP_Init();
}
uint8 a;
void toggle(void)
{
    if(a != 0)
    {
        a= 0;
        GpioOut(PINA0,1);
    }
    else
    {
        a = 1;
        GpioOut(PINA0,0);
    }
}

void main(void) 
{
    HAL_Init();
    
    //TIMER0_Set(T0_ENABLE|T0_16BIT|T0_CLK_IN|T0_PRESC_64, 49, toggle);
    DAC_Driver_Send(0x2345);

    while(1)
    {
        DAC_Driver_Task();
    }
    return;
}
