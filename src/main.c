#include <stdint.h>
#include "npe.h"
#include "fpu_instr.h"
#include "UsartDriver_ifc.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

static char outputStr[256U];

/**
 * @brief Function main
 * @return int Always 0, but normally never returns
 */
int main(void)
{
    uint8_t cnt = 0U;

	/* Disable interrupts */
	cli();

    npe_reset();
    npe_select_off();
    npe_rw_off();
    npe_cmd_instr();
    npe_data_high_Z();

    _delay_ms(10u);

    npe_reset_off();
    _delay_ms(10u);

    UsartInit();

    finit();
    npe_wait();

    while (1)
    {
        union fp32 fp32;
        struct fp80 fp80;

        memset(&fp32, 0, sizeof(fp32));
        memset(&fp80, 0, sizeof(fp80));

        sprintf(&outputStr[0], "%u: Status word: 0x%04X\r\n", cnt, fstsw());
        UsartTxStr(&outputStr[0]);
        sprintf(&outputStr[0], "%u: Control word: 0x%04X\r\n", cnt, fstcw());
        UsartTxStr(&outputStr[0]);

        fld1();
        npe_wait();

        fstps(&fp32);
        sprintf(&outputStr[0], "%u: fld1 = %f\r\n", cnt, fp32.f);
        UsartTxStr(&outputStr[0]);

        fld1();
        npe_wait();
        fchs();
        npe_wait();

        fstps(&fp32);
        sprintf(&outputStr[0], "%u: -fld1 = %f\r\n", cnt, fp32.f);
        UsartTxStr(&outputStr[0]);

        {
            fldpi();
            npe_wait();
            fstps(&fp32);
            sprintf(&outputStr[0], "%u: fldpi (32 bit) = %f\r\n", cnt, fp32.f);
            UsartTxStr(&outputStr[0]);

            fldpi();
            npe_wait();
            fstpt(&fp80);
            npe_wait();
            sprintf(&outputStr[0], "%u: fldpi (80 bit) = 0x%04X%04X%04X%04X%04X\r\n", cnt,
                    fp80.w[4U], fp80.w[3U], fp80.w[2U], fp80.w[1U], fp80.w[0U]);
            UsartTxStr(&outputStr[0]);
        }

        fldz();
        npe_wait();

        fstps(&fp32);
        sprintf(&outputStr[0], "%u: fldz = %f\r\n", cnt, fp32.f);
        UsartTxStr(&outputStr[0]);

        {
            fldl2e();
            npe_wait();

            fldlg2();
            npe_wait();

            fldln2();
            npe_wait();

            fldl2t();
            npe_wait();

            sprintf(&outputStr[0], "%u: Status word: 0x%04X\r\n", cnt, fstsw());
            UsartTxStr(&outputStr[0]);

            fstps(&fp32);
            sprintf(&outputStr[0], "%u: fldl2t = %f\r\n", cnt, fp32.f);
            UsartTxStr(&outputStr[0]);
            fstps(&fp32);
            sprintf(&outputStr[0], "%u: fldln2 = %f\r\n", cnt, fp32.f);
            UsartTxStr(&outputStr[0]);
            fstps(&fp32);
            sprintf(&outputStr[0], "%u: fldlg2 = %f\r\n", cnt, fp32.f);
            UsartTxStr(&outputStr[0]);
            fstps(&fp32);
            sprintf(&outputStr[0], "%u: fldl2e = %f\r\n", cnt, fp32.f);
            UsartTxStr(&outputStr[0]);
        }

        fld1();
        npe_wait();
        fld1();
        npe_wait();
        faddp();
        npe_wait();
        fstps(&fp32);
        sprintf(&outputStr[0], "%u: 1 + 1 = %f\r\n", cnt, fp32.f);
        UsartTxStr(&outputStr[0]);

        _delay_ms(5000U);
        ++cnt;
    }

	return 0;
}

