# Function       Larger
# Purpose:       Return the larger of two longs
# C prototype:   long Larger(long a, long b)
#
# Assemble:  as -o hello.o hello.s
# Link:      ld -o hello hello.o
# Run:       ./hello
# Notes:
# 1. Linux gcc expects a function called "Larger", not "_Larger"
# 2. This code assumes the x86-64 System V AMD64 calling conventions:
#    - The first six args are passed in registers RDI, RSI, RDX, RCX,
#      R8, and R9, respectively.
#    - Additional arguments are passed on the stack.
#    - Registers rbx, rbp (the frame or base pointer), and r12-r15
#      should be saved by the called function (callee)
#    - The return value is stored in RAX.  A second return value can
#      be returned in rdx

        .section        .text

        .global  Larger

Larger:
        push    %rbp            # Convention requires saving RBP
        mov     %rsp, %rbp      # Now the base and the top of the stack
                                #    frame are the same.


        cmp     %rsi, %rdi      # Set bits in the FLAGS register according to
                                #    the value rdi-rsi.
                                #    Remember ATT reverses operand order
        jge     rdi_big         # Go to rdi_big if rdi >= rsi
        mov     %rsi, %rax      # If we got here rsi is bigger, set ret val
                                #    = rax to rsi
        jmp     done            # Go to done

rdi_big:
        mov     %rdi, %rax      # If we got here rsi is bigger, set ret val
                                #    = rax to rsi

done:
        leave                   # Set stack pointer to frame pointer
                                #    and pop old frame pointer
        ret                     # Pop return address and jump to it
