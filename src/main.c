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

#include "Ports.h"
#include "EUSART.h"
#include "Interrupts.h"
#include "MSSP.h"
#include "TIMER2.h"

void HAL_Init(void)
{
    GpioDir(PINA0,0);
    GpioDir(PINC6, 1);
    GpioDir(PINC7, 1);
    
    *((uint8*)0xFF1) &= 0x7F;

    Interrupt_Init();
    dtEUSARTConf Config = {.Sync = 0, .Tx9Bit = 0, .Rx9Bit = 0, .TxInv = 0, .RxInv = 0};
    EUSART_Init(Config,9600);
    
    MSSP_Init();
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
    uint8 szia[] = "szia";
    HAL_Init();
    
    //TIMER2_Set(T2_POST_10|T2_ON|T2_PRE_1, 100, toggle);
    
    EUSART_Send(szia,4);
    while(1)
    {
        
        
    }
    return;
}
