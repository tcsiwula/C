# Function       Sum
# Purpose:       Add two ints
# C prototype:   int Sum(int a, int b)
#
# Notes.
# 1. gcc expects a function called "Sum", not "_Sum"
# 2. The current version of gcc doesn't require an "l", "w", or "b"
#    suffix on instructions.
# 3. This assumes the "C declaration" or "cdecl" calling convention:
#    - Arguments are passed on the stack. (Like MIPS, the stack grows
#      down)
#    - The return value is returned in register eax
#    - Register eax, ecx, and edx are saved by the code calling 
#      the function (caller)
#    - Other registers are saved by the called function  (callee)
#    - Arguments are pushed by the caller in reverse order:  
#      the last argument is pushed first, then the next to the last
#      etc.  The return address is on the top of the stack.
#    This is the default for 32-bit C compilers.
        .section        .text

        .global  Sum

Sum:
        pushl   %ebp            # Save the base or frame pointer.
        movl    %esp, %ebp      # Now the base and the top of the stack 
                                #    frame are the same.
        movl    8(%ebp), %eax   # Top of the stack stores the original ebp
                                #    Next is the return address
                                #    Next is the first arg a
        movl    12(%ebp), %ecx  #    Next is the second arg b
        addl    %ecx, %eax      # Now add ecx to eax
        leave                   # Set stack pointer to frame pointer
                                #    and pop old frame pointer
        ret                     # Pop return address and jump to it
                                #    
