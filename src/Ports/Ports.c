
#include "Ports_Types.h"
#include "Ports.h"

static uint8 *const LATs[4] = {(uint8*)0xF89, (uint8*)0xF8A, (uint8*)0xF8B, (uint8*)0xF8C};
static uint8 *const TRISs[4]= {(uint8*)0xF92, (uint8*)0xF93, (uint8*)0xF94, (uint8*)0xF95};
static uint8 *const PORTs[4]= {(uint8*)0xF80, (uint8*)0xF81, (uint8*)0xF82, (uint8*)0xF83};

const dtGPIO PINA0  = {0x0,0x0};
const dtGPIO PINA1  = {0x0,0x1};
const dtGPIO PINA2  = {0x0,0x2};
const dtGPIO PINA3  = {0x0,0x3};
const dtGPIO PINA4  = {0x0,0x4};
const dtGPIO PINA5  = {0x0,0x5};
const dtGPIO PINA6  = {0x0,0x6};
const dtGPIO PINA7  = {0x0,0x7};
const dtGPIO PINB0  = {0x1,0x0};
const dtGPIO PINB1  = {0x1,0x1};
const dtGPIO PINB2  = {0x1,0x2};
const dtGPIO PINB3  = {0x1,0x3};
const dtGPIO PINB4  = {0x1,0x4};
const dtGPIO PINB5  = {0x1,0x5};
const dtGPIO PINB6  = {0x1,0x6};
const dtGPIO PINB7  = {0x1,0x7};
const dtGPIO PINC0  = {0x2,0x0};
const dtGPIO PINC1  = {0x2,0x1};
const dtGPIO PINC2  = {0x2,0x2};
const dtGPIO PINC3  = {0x2,0x3};
const dtGPIO PINC4  = {0x2,0x4};
const dtGPIO PINC5  = {0x2,0x5};
const dtGPIO PINC6  = {0x2,0x6};
const dtGPIO PINC7  = {0x2,0x7};

const dtGPIO PIND2  = {0x3,0x2};
const dtGPIO PIND4  = {0x3,0x4};

void GpioOut(dtGPIO GPIO, uint8 State);
uint8 GpioIn(dtGPIO GPIO);
void GpioToggle(dtGPIO GPIO);
void GpioDir(dtGPIO GPIO, uint8 Dir);

void GpioOut(dtGPIO GPIO, uint8 State)
{
    if(State != 0)
    {
        /* If the pin should be high one will ORing to the register */
        *LATs[GPIO.Port] |= 1<<GPIO.Pin;
    }
    else
    {
        /* If the pin should be low the desired bit will be set to null. */
        *LATs[GPIO.Port] &= ~(1<<GPIO.Pin);
    }
}

/* This function set the direction of a GPIO pin.
 * @Param GPIO: dtGPIO type variable containing the port and its pin
 * @Param Dir: uint8 type variable, 1: input 0: output */
void GpioDir(dtGPIO GPIO, uint8 Dir)
{
    if(Dir != 0)
    {
        /* If the pin should be input one will ORing to the register */
        *TRISs[GPIO.Port] |= 1<<GPIO.Pin;
    }
    else
    {
        /* If the pin should be output the desired bit will be set to null. */
        *TRISs[GPIO.Port] &= ~(1<<GPIO.Pin);
    }
}

void GpioToggle(dtGPIO GPIO)
{
    if((*PORTs[GPIO.Port] & (1<<GPIO.Pin)) != 0) *LATs[GPIO.Port] &= ~(1<<GPIO.Pin);
    else *LATs[GPIO.Port] |= (1<<GPIO.Pin);
}

uint8 GpioIn(dtGPIO GPIO)
{
    uint8 ret = 0;
    if((*PORTs[GPIO.Port] & (1<<GPIO.Pin)) != 0) ret = 1;
    return ret;
}