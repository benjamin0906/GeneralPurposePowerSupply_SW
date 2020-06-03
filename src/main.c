/*
 * File:   main.c
 * Author: Bodnár Benjamin
 *
 * Created on 29 May 2020, 12:51
 */

#pragma config FOSC = INTOSCIO_EC
#pragma config WDT = OFF
#pragma config LVP = OFF

#include "Ports.h"
#include "EUSART.h"
#include "Interrupts.h"

void main(void) 
{
    GpioDir(PINA0,0);
    GpioDir(PINC6, 1);
    GpioDir(PINC7, 1);
    Interrupt_Init();
    dtEUSARTConf Config = {.Sync = 0, .Tx9Bit = 0, .Rx9Bit = 0, .TxInv = 0, .RxInv = 0};
    EUSART_Init(Config,9600);
    uint8 a = 0;
    uint8 a2 = 0;
    uint8 a3 = 0;
    uint8 szia[] = "szia";
    EUSART_Send(szia,4);
    while(1)
    {
        GpioOut(PINA0,1);
        for(a=0;a<200;a++) for(a2=0;a2<200;a2++) for(a3 = 0; a3<0; a3++);
        EUSART_Send(szia,4);
        //EUSART_Send();
        GpioOut(PINA0,0);
    }
    return;
}
