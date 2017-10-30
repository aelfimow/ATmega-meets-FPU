#ifdef FPU_INSTR_H
#error Already included
#else

typedef char float_size_check[sizeof(float) == 4 ? 1 : -1];
typedef char double_size_check[sizeof(double) == 4 ? 1 : -1];
typedef char long_double_size_check[sizeof(long double) == 4 ? 1 : -1];

union fp32
{
    uint16_t w[2U];
    float f;
};

union fp64
{
    uint16_t w[4U];
    double f;
};

struct fp80
{
    uint16_t w[5U];
};

extern void finit(void);
extern void fnop(void);

extern uint16_t fstsw(void);
extern uint16_t fstcw(void);
extern void fldcw(uint8_t cw_high, uint8_t cw_low);
extern void fclex(void);

extern void f2xm1(void);
extern void fdivp(void);

extern void fchs(void);
extern void fldz(void);
extern void fld1(void);
extern void fldpi(void);
extern void fldl2t(void);
extern void fldl2e(void);
extern void fldlg2(void);
extern void fldln2(void);

extern void fstps(union fp32 *p);
extern void fstpl(union fp64 *p);
extern void fstpt(struct fp80 *p);

extern void faddp(void);

extern void ffree(uint8_t index);

#endif

