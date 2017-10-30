#include <stdint.h>
#include <util/delay.h>

#include "fpu_instr.h"
#include "npe.h"

/**
 * @brief Writes FINIT instruction
 */
void finit(void)
{
    npe_write_instruction(0xE3, 0xDB);
}

/**
 * @brief Writes FNOP instruction
 */
void fnop(void)
{
    npe_write_instruction(0xD0U, 0xD9U);
}

/**
 * @brief Writes FSTSW instruction and returns status word
 * @return uint16_t Status word
 */
uint16_t fstsw(void)
{
    uint16_t data = 0x0000U;

    npe_select();
    npe_cmd_instr();
    npe_data_write(0xE0U, 0xDFU);
    npe_write_pulse();
    npe_cmd_instr();
    data = npe_data_read();
    npe_select_off();

    return data;
}

/**
 * @brief Writes FSTCW instruction and returns control word
 * @return uint16_t Control word
 */
uint16_t fstcw(void)
{
    uint16_t data = 0x0000U;

    npe_select();
    npe_cmd_instr();
    npe_data_write(0x38U, 0xD9U);
    npe_write_pulse();
    npe_cmd_instr();
    data = npe_data_read();
    npe_select_off();

    return data;
}

/**
 * @brief Writes FLDCW instruction with control word
 * @param cw_high High byte of control word
 * @param cw_low Low byte of control word
 */
void fldcw(uint8_t cw_high, uint8_t cw_low)
{
    npe_select();
    npe_cmd_instr();
    npe_data_write(0x28U, 0xD9U);
    npe_write_pulse();
    while (0 == npe_request());
    npe_cmd_data();
    npe_data_write(cw_high, cw_low);
    npe_write_pulse();
    npe_select_off();
}

/**
 * @brief Writes FCLEX instruction
 */
void fclex(void)
{
    npe_write_instruction(0xE2U, 0xDB);
}

/**
 * @brief Writes F2XM1 instruction
 */
void f2xm1(void)
{
    npe_write_instruction(0xF0U, 0xD9U);
}

/**
 * @brief Writes FDIVP instruction
 */
void fdivp(void)
{
    npe_write_instruction(0xF9U, 0xDEU);
}

/**
 * @brief Writes FCHS instruction
 */
void fchs(void)
{
    npe_write_instruction(0xE0, 0xD9U);
}

/**
 * @brief Writes FLDZ instruction
 */
void fldz(void)
{
    npe_write_instruction(0xEEU, 0xD9U);
}

/**
 * @brief Writes FLD1 instruction
 */
void fld1(void)
{
    npe_write_instruction(0xE8U, 0xD9U);
}

/**
 * @brief Writes FLDPI instruction
 */
void fldpi(void)
{
    npe_write_instruction(0xEBU, 0xD9U);
}

/**
 * @brief Writes FLDL2T instruction
 */
void fldl2t(void)
{
    npe_write_instruction(0xE9U, 0xD9U);
}

/**
 * @brief Writes FLDL2E instruction
 */
void fldl2e(void)
{
    npe_write_instruction(0xEAU, 0xD9U);
}

/**
 * @brief Writes FLDLG2 instruction
 */
void fldlg2(void)
{
    npe_write_instruction(0xECU, 0xD9U);
}

/**
 * @brief Writes FLDLN2 instruction
 */
void fldln2(void)
{
    npe_write_instruction(0xEDU, 0xD9U);
}

/**
 * @brief Writes FSTPS instruction and returns data
 */
void fstps(union fp32 *p)
{
    npe_select();
    npe_cmd_instr();
    npe_data_write(0x18U, 0xD9U);
    npe_write_pulse();
    while (0 == npe_request());
    npe_cmd_data();
    p->w[0U] = npe_data_read();
    npe_cmd_data();
    p->w[1U] = npe_data_read();
    npe_select_off();
}

/**
 * @brief Writes FSTPL instruction and returns data
 */
void fstpl(union fp64 *p)
{
    npe_select();
    npe_cmd_instr();
    npe_data_write(0x18U, 0xDDU);
    npe_write_pulse();
    while (0 == npe_request());
    npe_cmd_data();
    p->w[0U] = npe_data_read();
    npe_cmd_data();
    p->w[1U] = npe_data_read();
    npe_cmd_data();
    p->w[2U] = npe_data_read();
    npe_cmd_data();
    p->w[3U] = npe_data_read();
    npe_select_off();
}

/**
 * @brief Writes FSTPT instruction and returns data
 */
void fstpt(struct fp80 *p)
{
    npe_select();
    npe_cmd_instr();
    npe_data_write(0x38U, 0xDBU);
    npe_write_pulse();
    while (0 == npe_request());
    npe_cmd_data();
    p->w[0U] = npe_data_read();
    npe_cmd_data();
    p->w[1U] = npe_data_read();
    npe_cmd_data();
    p->w[2U] = npe_data_read();
    npe_cmd_data();
    p->w[3U] = npe_data_read();
    npe_cmd_data();
    p->w[4U] = npe_data_read();
    npe_select_off();
}

/**
 * @brief Writes FFREE instruction for st(i) register
 * @param index Index of st(i) register
 */
void ffree(uint8_t index)
{
    const uint8_t instr_byte = (0xC0U | (index & 0x07U));

    npe_write_instruction(instr_byte, 0xDDU);
}

/**
 * @brief Writes FADDP instruction
 */
void faddp(void)
{
    npe_write_instruction(0xC1U, 0xDEU);
}

