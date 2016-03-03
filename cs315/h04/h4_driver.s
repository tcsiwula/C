        .section        .text
        .globl  Driver
#------------ START copy two numbers to x86 vars -------------#
Driver:
        push    %rbp            # At the start of the function it's
        mov     %rsp, %rbp      #
        add     %rdi, %rsi      # rdi = a
        mov     %rsi, %rax      # rsi = b
#------------ END copy two numbers to x86 vars -------------#

#------------ case 1 ----------------------------------------#
# If a > b, it should compute 0.
#------------ case 1 ----------------------------------------#
A_bigger:
        cmp     %rdi, %rcx
        jg      a_bigger
        je      equal
        jl      a_less


# if a>b return 0.
a_bigger:
        mov     $0, %rax      # If we got here rsi is bigger, set ret val
        jmp     done

# a=b, return a.
equal:
        mov     %rdi, %rax
        jmp     done

# a<b, return sum.
a_less:
        add     $1, %rdi
        jl      a_less
        mov     %rdi, %rax
        jmp     done

done:
        leave                   # Set stack pointer to frame pointer
        ret                     # Pop return address and jump to it
#------------ END copy two numbers to x86 vars -------------#







