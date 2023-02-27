section .text
global f1
f1:
    push   ebp
    mov    ebp, esp
    fld    qword[ebp + 8]
    fldl2e
    fmulp  st1, st0
    fld1
    fld    st1
    fprem
    f2xm1
    faddp
    fscale
    fld1
    fadd   st0, st0
    fadd   st1, st0
    fxch   st1
    fxch   st2
    fstp   st0
    fstp   st0
            
    leave
    ret
 
global f2
f2:
    push   ebp
    mov    ebp, esp
    fld1
    fchs
    fld    qword[ebp + 8]
    fdivp  st1, st0
    
    leave
    ret
 
global f3
f3:
    push   ebp
    mov    ebp, esp
    fld1
    fld    st0
    fadd   st0, st0
    fchs
    fld    st0
    fchs
    fadd   st0, st2
    fld    qword[ebp + 8]
    faddp  st3, st0
    fdivp  st1, st0
    fmulp  st1, st0
    
    leave
    ret
 
global f_1
f_1:
    push   ebp
    mov    ebp, esp
    fld    qword[ebp + 8]
    fldl2e
    fmulp  st1, st0
    fld1
    fld    st1
    fprem
    f2xm1
    faddp
    fscale
    fxch   st2
    fstp   st0
    fstp   st0
    
    leave
    ret
 
global f_2
f_2:
    push   ebp
    mov    ebp, esp
    fld1
    fld    qword[ebp + 8]
    fmul   st0, st0
    fdivp   st1, st0
    
    leave
    ret
 
global f_3
f_3:
    push   ebp
    mov    ebp, esp
    fld1
    fadd   st0, st0
    fchs
    fld    st0
    fchs
    fld1
    faddp  st1, st0
    fdivp  st1, st0
    
    leave
    ret
