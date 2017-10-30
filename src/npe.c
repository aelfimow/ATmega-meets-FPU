/**
 * @brief Numeric processor extension (NPE) functions
 */

#include <stdint.h>
#include "npe.h"

#include <avr/io.h>
#include <util/delay.h>

/**
 * @brief Sets reset pin of NPE to reset it
 */
void npe_reset(void)
{
    const uint8_t mask = _BV(PB0);

    DDRB |= mask;
    PORTB |= mask;
}

/**
 * @brief Sets reset pin of NPE to unreset it
 */
void npe_reset_off(void)
{
    const uint8_t mask = _BV(PB0);

    DDRB |= mask;
    PORTB &= (uint8_t)~mask;
}

/**
 * @brief Selects NPE, sets pin NPS2
 */
void npe_select(void)
{
    const uint8_t mask = _BV(PB1);

    DDRB |= mask;
    PORTB |= mask;
}

/**
 * @brief Unselects NPE, resets pin NPS2
 */
void npe_select_off(void)
{
    const uint8_t mask = _BV(PB1);

    DDRB |= mask;
    PORTB &= (uint8_t)~mask;
}

/**
 * @brief Performs write pulse
 */
void npe_write_pulse(void)
{
    const uint8_t mask_rd = _BV(PD4);
    const uint8_t mask_wr = _BV(PD5);

    DDRD |= (mask_wr | mask_rd);

    PORTD &= (uint8_t)~mask_wr;
    _delay_us(1U);
    PORTD |= (mask_wr | mask_rd);
}

/**
 * @brief Activates read pin of NPE
 */
void npe_read(void)
{
    const uint8_t mask_rd = _BV(PD4);
    const uint8_t mask_wr = _BV(PD5);

    DDRD |= (mask_wr | mask_rd);

    PORTD &= (uint8_t)~mask_rd;
    PORTD |= mask_wr;
}

/**
 * @brief Activates write pin of NPE
 */
void npe_write(void)
{
    const uint8_t mask_rd = _BV(PD4);
    const uint8_t mask_wr = _BV(PD5);

    DDRD |= (mask_wr | mask_rd);

    PORTD |= mask_rd;
    PORTD &= (uint8_t)~mask_wr;
}

/**
 * @brief Deactivates read-write pins of NPE
 */
void npe_rw_off(void)
{
    const uint8_t mask_rd = _BV(PD4);
    const uint8_t mask_wr = _BV(PD5);

    DDRD |= (mask_wr | mask_rd);
    PORTD |= (mask_rd | mask_wr);
}

/**
 * @brief Sets CMD0 pin of NPE for instruction
 */
void npe_cmd_instr(void)
{
    const uint8_t mask = _BV(PD6);

    DDRD |= mask;
    PORTD &= (uint8_t)~mask;
}

/**
 * @brief Sets CMD0 pin of NPE for data
 */
void npe_cmd_data(void)
{
    const uint8_t mask = _BV(PD6);

    DDRD |= mask;
    PORTD |= mask;
}

/**
 * @brief Sets data bus to new value
 * @param high High byte to write
 * @param low Low byte to write
 */
void npe_data_write(uint8_t high, uint8_t low)
{
    uint8_t a = 0x00U;
    uint8_t c = 0x00U;

    DDRA = 0xFFU;
    DDRC = 0xFFU;

    a |= (high & 0x80U) ? 0x01U : 0x00U;
    a |= (high & 0x40U) ? 0x02U : 0x00U;
    a |= (high & 0x20U) ? 0x04U : 0x00U;
    a |= (high & 0x10U) ? 0x08U : 0x00U;
    a |= (high & 0x08U) ? 0x10U : 0x00U;
    a |= (high & 0x04U) ? 0x20U : 0x00U;
    a |= (high & 0x02U) ? 0x40U : 0x00U;
    a |= (high & 0x01U) ? 0x80U : 0x00U;

    c |= (low & 0x80U) ? 0x08U : 0x00U;
    c |= (low & 0x40U) ? 0x10U : 0x00U;
    c |= (low & 0x20U) ? 0x20U : 0x00U;
    c |= (low & 0x10U) ? 0x40U : 0x00U;
    c |= (low & 0x08U) ? 0x80U : 0x00U;
    c |= (low & 0x04U) ? 0x04U : 0x00U;
    c |= (low & 0x02U) ? 0x02U : 0x00U;
    c |= (low & 0x01U) ? 0x01U : 0x00U;

    PORTA = a;
    PORTC = c;
}

/**
 * @brief Reads data bus
 * @return uint16_t Data from data bus
 */
uint16_t npe_data_read(void)
{
    uint8_t c = 0x00U;
    uint8_t a = 0x00U;
    uint8_t low_byte = 0x00U;
    uint8_t high_byte = 0x00U;

    npe_data_high_Z();
    npe_read();
    _delay_us(1U);
    a = PINA;
    c = PINC;
    npe_rw_off();

    high_byte |= (a & 0x80U) ? 0x01U : 0x00U;
    high_byte |= (a & 0x40U) ? 0x02U : 0x00U;
    high_byte |= (a & 0x20U) ? 0x04U : 0x00U;
    high_byte |= (a & 0x10U) ? 0x08U : 0x00U;
    high_byte |= (a & 0x08U) ? 0x10U : 0x00U;
    high_byte |= (a & 0x04U) ? 0x20U : 0x00U;
    high_byte |= (a & 0x02U) ? 0x40U : 0x00U;
    high_byte |= (a & 0x01U) ? 0x80U : 0x00U;

    low_byte |= (c & 0x80U) ? 0x08U : 0x00U;
    low_byte |= (c & 0x40U) ? 0x10U : 0x00U;
    low_byte |= (c & 0x20U) ? 0x20U : 0x00U;
    low_byte |= (c & 0x10U) ? 0x40U : 0x00U;
    low_byte |= (c & 0x08U) ? 0x80U : 0x00U;
    low_byte |= (c & 0x04U) ? 0x04U : 0x00U;
    low_byte |= (c & 0x02U) ? 0x02U : 0x00U;
    low_byte |= (c & 0x01U) ? 0x01U : 0x00U;

    return ((((uint16_t)high_byte) << 8U) | (uint16_t)low_byte);
}

void npe_data_high_Z(void)
{
    DDRA = 0x00U;
    DDRC = 0x00U;

    PORTA = 0x00U;
    PORTC = 0x00U;
}

/**
 * @brief Writes instruction to NPE
 * @param high High byte of the instruction
 * @param low Low byte of the instruction
 */
void npe_write_instruction(uint8_t high, uint8_t low)
{
    npe_select();
    npe_cmd_instr();
    npe_data_write(high, low);
    npe_write_pulse();
    npe_select_off();
}

/**
 * @brief Waits for busy pin to be ready
 * @return uint8_t Zero for not ready, else ready
 */
uint8_t npe_wait(void)
{
#if 0
    uint16_t cnt = 0;
    uint8_t ready_flag = 0;
    const uint8_t mask = _BV(PD2);

    DDRD &= (uint8_t)~mask;

    for (cnt = 0U; cnt < 65535U; ++cnt)
    {
        if (mask == (PIND & mask))
        {
            ++ready_flag;
            break;
        }
    }

    return ready_flag;
#else
    const uint8_t mask = _BV(PD2);

    DDRD &= (uint8_t)~mask;

    while (0 == (PIND & mask))
    {
    }

    return 1;
#endif
}

/**
 * @brief Detects error of NPE
 * @return uint8_t Zero for no error, other on error
 */
uint8_t npe_error(void)
{
    const uint8_t mask = _BV(PD3);

    DDRD &= (uint8_t)~mask;

    if (mask == (PIND & mask))
    {
        /* No error */
        return 0U;
    }

    /* Error */
    return 1U;
}

/**
 * @brief Detects NPE request
 * @return uint8_t Zero for no request, other on request
 */
uint8_t npe_request(void)
{
    const uint8_t mask = _BV(PD7);

    DDRD &= (uint8_t)~mask;

    if (mask == (PIND & mask))
    {
        /* request available */
        return 1U;
    }

    /* no request available */
    return 0U;
}

