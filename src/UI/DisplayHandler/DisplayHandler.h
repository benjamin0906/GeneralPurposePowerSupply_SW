/* 
 * File:   Dys.h
 * Author: Benjamin
 *
 * Created on 2019. március 30., 17:58
 */

#ifndef DYS_H
#define	DYS_H

#include "DisplayHandler_Types.h"

extern void DisplayHandler_Task(void);
extern void LCDInit(void);
extern void PutStr(uint8 *data, uint8 line);
extern void LcdClear(void);


#endif	/* DYS_H */

