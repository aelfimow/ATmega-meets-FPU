#include "UsartDriver.h"
#include "UsartDriver_par.h"

static void UsartWriteData(uint8_t data);

void UsartInit(void)
{
    /* Set baudrate */
    UBRR0H = (uint8_t)((USART_DRIVER_BAUDRATE / 256u) & 0xFFu);
    UBRR0L = (uint8_t)(USART_DRIVER_BAUDRATE & 0xFFu);

#if 0
    UCSR0B = (uint8_t)((uint8_t)(1u << TXEN0) | (uint8_t)(1u << RXEN0));
#else
    UCSR0B = (uint8_t)(1U << TXEN0);
#endif

    UCSR0C = (uint8_t)((uint8_t)(3u << UCSZ00));

    return;
}

void UsartTx(uint8_t data)
{
    UsartWriteData(data);
    return;
}

void UsartTxStr(const char *data)
{
    uint8_t i = 0u;
    const uint8_t max = 64u;
    uint8_t c = 0;

    for (i = 0u; i < max; ++i)
    {
        c = (uint8_t)data[i];

        if (0u != c)
        {
            UsartWriteData(c);
        }
        else
        {
            i = max;
        }
    }

    return;
}

static void UsartWriteData(uint8_t data)
{
    while (0u == (UCSR0A & (uint8_t)(1u << UDRE0)))
    {
        /* do nothing */
    }

    UDR0 = data;

    return;
}

uint8_t UsartRx(void)
{
    uint8_t done = 0;

    while (0 == done)
    {
        if (0 == (UCSR0A & (uint8_t)(1u << RXC0)))
        {
            done = 0;
        }
        else
        {
            done = 1U;
        }
    }

    return UDR0;
}

uint8_t UsartRxDataAvail(void)
{
    uint8_t avail = 0;

    if (0 == (UCSR0A & (uint8_t)(1u << RXC0)))
    {
        avail = 0;
    }
    else
    {
        avail = 1U;
    }

    return avail;
}

uint8_t UsartRead(uint8_t *data)
{
    uint8_t cnt = 0;

    if (0 == data)
    {
        cnt = 0;
    }
    else
    {
        data[0] = UDR0;
        cnt = 1u;
    }

    return cnt;
}

