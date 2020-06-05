/* 
 * File:   MSSP_Types.h
 * Author: Bodnár Benjamin
 *
 * Created on 03 June 2020, 21:24
 */

#ifndef MSSP_TYPES_H
#define	MSSP_TYPES_H

#include "types.h"

typedef union
{
    struct
    {
        uint8 BF    :1;
        uint8 UA    :1;
        uint8 RW    :1;
        uint8 S     :1;
        uint8 P     :1;
        uint8 DA    :1;
        uint8 CKE   :1;
        uint8 SMP   :1;
    } Fields;
    uint8 Byte;
} dtSSPSTAT;

typedef union
{
    struct
    {
        uint8 SSPM :4;
        uint8 CKP   :1;
        uint8 SSPEN :1;
        uint8 SSPOV :1;
        uint8 WCOL  :1;       
    } Fields;
    uint8 Byte;
}dtSSPCON1;

typedef union
{
    struct
    {
        uint8 SEN       :1;
        uint8 RSEN      :1;
        uint8 PEN       :1;
        uint8 RCEN      :1;
        uint8 ACKEN     :1;
        uint8 ACKDT     :1;
        uint8 ACKSTAT   :1;
        uint8 GCEN      :1;
    } Master;
    struct
    {
        uint8 SEN       :1;
        uint8 ADMSK     :5;
        uint8 ACKSTAT   :1;
        uint8 GCEN      :1;      
    } Slave;
    uint8 Byte;
} dtSSPCON2;

typedef enum
{
    WriteSlaveAddress,
            SendAddress,
            SendData,
            Restart,
            SendRxSlaveAdd,
            SetReceiveMode,
            ReadData,
            SendStop,
            Fnished,
            
} dtMSSPState;

#endif	/* MSSP_TYPES_H */

