#include <stdint.h>
#include <stdio.h>
#include <math.h>

union fp32
{
    uint32_t u32value;
    float fp32;
};

union fp80
{
    uint8_t d[16U];
    long double fp80;
};

int main(int argc, char *argv[])
{
    union fp32 fp32;
    union fp80 fp80;

    typedef char long_double_size_check[sizeof(long double) == 16U ? 1 : -1];

    fp32.fp32 = 3.1415926535897932384626433832795f;
    fp80.fp80 = 3.1415926535897932384626433832795;
    printf("Die Zahl %f ist 0x%08X (32 bit)\n", fp32.fp32, fp32.u32value);
    printf("Die Zahl %Lf ist 0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X (80 bit)\n", (double)fp80.fp80,
            fp80.d[15], fp80.d[14], fp80.d[13], fp80.d[12], fp80.d[11], fp80.d[10],
            fp80.d[9], fp80.d[8], fp80.d[7], fp80.d[6], fp80.d[5], fp80.d[4], fp80.d[3], fp80.d[2], fp80.d[1], fp80.d[0]);

    fp32.fp32 = 0.0f;
    printf("Die Zahl %f ist 0x%08X\n", fp32.fp32, fp32.u32value);

    fp32.fp32 = log2f(10.0f);
    printf("Die Zahl %f (log2f(10)) ist 0x%08X\n", fp32.fp32, fp32.u32value);

    fp32.fp32 = 2.0f;
    printf("Die Zahl %f ist 0x%08X\n", fp32.fp32, fp32.u32value);

    return 0;
}

