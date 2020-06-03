
#include "EUSART_Types.h"
#include "EUSART.h"
#include "Interrupts.h"

static dtBAUDCON    *const BaudCon  = (dtBAUDCON*)   (0xFB8);
static dtTXSTA      *const TxSta    = (dtTXSTA*)     (0xFAC);
static dtRCSTA      *const Rcsta    = (dtRCSTA*)     (0xFAB);
static uint8        *const TxReg    = (uint8*)       (0xFAD);
static uint8        *const RxReg    = (uint8*)       (0xFAE);
static uint16       *const Spbrg    = (uint16*)      (0xFAF);
static uint8        *      TxBuff;
static uint8        *      RxBuff;
static uint8               TxLen;
static uint8               RxLen;
uint32 Fosc = 1000000;

void EUSART_Init(dtEUSARTConf Config, uint32 Baud);
void EUSART_Send(uint8 *data, uint8 len);
void IntHandler(void)
{
    if((TxLen != 0) && (TxBuff != 0))
    {
        *TxReg = *(TxBuff++);
        TxLen--;
    }
    else
    {
        Interrupt_Disable(INT_EUSART_TX);
    }
}

void EUSART_Init(dtEUSARTConf Config, uint32 Baud)
{
    uint8 Dividend = 4;
    uint16 Brg = 0;
    uint8 FinalDiv=0;
    int32 CurrDiff = 0;
    int32 PrevDiff = Baud;
    if(Config.Tx9Bit != 0) TxSta->TX9 = 0;
    if(Config.Rx9Bit != 0) Rcsta->RX9 = 0;
    if(Config.Sync == 1) TxSta->SYNC = 1;
    else TxSta->SYNC = 0;
    if(Config.RxInv != 0) BaudCon->RXDTP = 1;
    if(Config.TxInv != 0) BaudCon->TXCKP = 1;
    
    do
    {        
        uint16 TempBrg = (Fosc>>Dividend) / Baud;
        
        if(TempBrg != 0) CurrDiff = Baud - (Fosc>>Dividend)/TempBrg;
        if(CurrDiff < 0) CurrDiff *= -1;
        if(CurrDiff < PrevDiff)
        {
            Brg = TempBrg;
            PrevDiff = CurrDiff;
            FinalDiv = Dividend;
        }
        Dividend -= 2;
    } while(Dividend != 0);
    
    BaudCon->BRG16 = 1;
    TxSta->BRGH = 0;
    
    if(FinalDiv == 2) TxSta->BRGH = 1;
    
    *Spbrg = Brg-1;
    
    
    
    Rcsta->SPEN = 1;
    TxSta->TXEN = 1;
    Rcsta->CREN = 1;
    Rcsta->ADDEN = 0;
}

void EUSART_Send(uint8 *data, uint8 len)
{
    TxBuff = data;
    TxLen = len-1;
    *TxReg = *(TxBuff++);
    Interrupt_SetInt(INT_EUSART_TX,PRIO_HIGH, &IntHandler);
}