.section .text
    fninit
    fnop
    fclex
    fstsw
    fstcw (%eax)
    fldcw (%eax)
    fldz
    fchs
    fstps (%eax)
    fstpl (%eax)
    fstpt (%eax)
    f2xm1

ffree_func:
    ffree %st(0)
    ffree %st(1)
    ffree %st(2)
    ffree %st(3)
    ffree %st(4)
    ffree %st(5)
    ffree %st(6)
    ffree %st(7)

math_functions:
    fsin
    fcos
    faddp

