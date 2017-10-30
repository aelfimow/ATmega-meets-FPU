#ifdef USART_DRIVER_IFC_H
#error Already included
#else
#define USART_DRIVER_IFC_H

extern void UsartInit(void);
extern void UsartTx(uint8_t data);
extern void UsartTxStr(const char *data);
extern uint8_t UsartRx(void);
extern uint8_t UsartRxDataAvail(void);
extern uint8_t UsartRead(uint8_t *data);

#endif

