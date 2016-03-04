##  This is an embeded assembly file. Use file fibo.c to compile and run.
##  compile:         clang -arch i386 h_5.s h_5.c -o h_5
##  run              ./h_5
.text

    .globl _fib
_fib:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    pushl %edx  
    movl 8(%ebp),%esi

    cmpl $1,%esi
    jle BASE

    subl $1,%esi
    pushl %esi
    call _fib

    addl $4,%esp
    movl %eax,%edx 

    subl $1,%esi
    pushl %esi
    call _fib

    addl $4,%esp
    addl %edx,%eax

DONE:
    popl %edx  
    popl %esi
    popl %ebp
    ret

BASE:
    movl $1,%eax
    jmp DONE