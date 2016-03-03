# Function:     Fact
# Purpose:      Compute n!
# C prototype:  long Fact(long n)
#
# Notes:
# 1. Linux gcc expects a function called "Fact", not "_Fact"
# 2. This code assumes the x86-64 System V AMD64 calling conventions:
#    - The first six args are passed in registers RDI, RSI, RDX, RCX, 
#      R8, and R9, respectively.
#    - Additional arguments are passed on the stack.
#    - Registers rbx, rbp (the frame or base pointer), and r12-r15
#      should be saved by the called function (callee)
#    - The return value is stored in RAX.  A second return value can
#      be returned in rdx
#
#  n = rdi

        .section        .text
        .global Fact

Fact:
        push    %rbp
        mov     %rsp, %rbp
        mov     $1, %rcx        # Loop variable rcx = i = 1
        mov     $1, %rdx        # rdx = nfact = 1

loop:
        # Check whether rcx = i > n = rdi
        #     In Intel syntax cmp rcx, rdi
        #     So in ATT syntax cmp rdi, rcx
        cmp     %rdi, %rcx      # Is rcx = i > n = rdi?
        jg      done            # If so, we're done

        # Get here when i <= n
        imul    %rcx, %rdx      # rdx = nfact = nfact*i = rcx
        add     $1, %rcx        # rcx = i++
        jmp     loop            # Go back to loop

done:   
        mov     %rdx, %rax      # Set return value
        leave
        ret
