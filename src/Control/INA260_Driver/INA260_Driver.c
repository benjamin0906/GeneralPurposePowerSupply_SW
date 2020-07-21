#include "INA260_Driver_Types.h"

void INA260_Driver_Init(void);
void INA260_Driver_Task(void);
void INA260_Driver_GetState(void);
uint8 INA260_Driver_GetValues(uint16 *Voltage, uint16 *Current, uint16 *Power);
