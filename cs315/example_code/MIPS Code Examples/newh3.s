	.text
	.globl	main

# +++++++++++++++ Start of main() +++++++++++++++++ #
main:
	  subu	$sp, $sp, 64
	  sw	$ra, 64($sp)

	# Ask the OS to read value
		la      $a0, i_msg              # String prompt
		jal     rd_int                  # Jump to function that prints a msg and reads an int
    	move	$t0, $v0	         	# Copy return value to safe location
	# Print input value with message
        la      $a0, o_msg              # Message to appear with int
        move    $a1, $t0                # The int to print
        jal     pr_int                  # Go to function
	# Call Fib()
#------
        move $a0, $a1
		jal     Fib						# go to Fib function

	# Print Results
        la      $a0, result_msg         # Message to appear with int
        #-----move    $a1, $t0                # The int to print
        move    $a1, $v0                # The int to print
        jal     pr_int                  # Go to function

#result_msg: .asciiz "Reslut value is "

	# Restore the values from the stack, and release the stack space.
		lw	    $ra, 0($sp)		        # Retrieve return address
		addu	$sp, $sp, 64		    # Free stack space.
    # Exit system call:  SPIM or MARS
        li    $v0, 10
        syscall
# +++++++++++++++ End of main() +++++++++++++++++ #

# ***** before calling a function do the following: *****
# 1. put function args in $a0-$a3
# 2. use jal MyFunctionName to jump to your function


# +++++++++++++++ Start Fib() +++++++++++++++++ #
Fib:                              # let n = $a0

    # save args and stack
      addi $sp, $sp, -12           #adjust stack to make room for $s0 and $t0
     #------- sw   $v0, 8($sp)            #save the return address
      sw   $s0, 8($sp)            #save the return address
      sw   $ra, 4($sp)            #save the return address
      sw   $a0, 0($sp)            #save the argument n
    # if (n==0) return 0
      #----------addi $s0, $s0, 0            # put constant 0 into reg $s0
      addi $s0, $0, 0            # put constant 0 into reg $s0
      #-----bne  $a0, $s0, ElseIf        # if (n==0) return 0, else goto ElseIf
      bgt  $a0, $0, ElseIf        # if (n==0) return 0, else goto ElseIf
      addi $v0, $zero, 0        # return 0
      #---------jr    Return                #return to caller
      j    Return                #return to caller
    # ElseIf (n==1) return 1
ElseIf:
     #------addi $s1, $s1, 1            # put constant 1 into reg $s1
     addi $s1, $0, 1            # put constant 1 into reg $s1
     bne  $a0, $s1, Else        # if (n==1) return 1, else go to Else
     addi $v0, $zero, 1            # return 0
     #------jr       Return                #return to caller
     j       Return                #return to caller
    # Else return fib(n-1) + fib(n-2)
Else:
    # fib(n-1)
     addi    $a0, $a0,-1         # $a0 = n - 1
     jal     Fib                 # call Fib(n-1)
     #------add     $v0, $a0, $v0
     add     $s0, $v0, $0
      #------jr       Return                #return to caller
# fib(n-2)
     #--------addi    $a0, $a0,-2         # $a0 = n - 1
     addi    $a0, $a0,-1         # $a0 = n - 1
     jal     Fib                 # call Fib(n-1)
     add     $v0, $s0, $v0
     #------jr       Return                #return to caller

Return:
    # Return - clean pop stack and
    lw      $a0, 0($sp)
    lw         $ra, 4($sp)
    lw      $s0, 8($sp)        #save the return address
    addi    $sp, $sp, 12         # pop 3 items off stack
     jr        $ra                     # return to caller
# +++++++++++++++ End Fib() +++++++++++++++++ #




# ***** BEFORE RETURNING a function do the following: *****
# 1. put results in $v0 and $v1 to save them
# 2. return control to the caller using jr $ra
# +++++++++++++++ Print() +++++++++++++++++ #
        # Function to print a message and an int
        # String to print is in $a0, int is in $a1
pr_int:
        # Put return address on stack
	addi	$sp, $sp, -4		# Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address

        li      $v0, 4                  # Print string code.
        syscall                         # Print message
	li	$v0, 1			# Code for print int.
        move    $a0, $a1                # Make int available to syscall
	syscall				# Print int
        li      $v0, 4                  # Print string code.
        la      $a0, newln              # Make newln avail to syscall
        syscall                         # Print newln

	# Restore the values from the stack, and release the stack space.
	lw	$ra, 0($sp)		# Retrieve return address
	addu	$sp, $sp, 4		# Free stack space.

	# Return -- go to the address left by the caller.
	jr      $ra		        # Return.


# +++++++++++++++ Read() +++++++++++++++++ #
# Function to print a message and read an int
# String to print is in $a0
rd_int:
      # Put return address on stack
        addi	$sp, $sp, -4		# Make additional stack space.
    	sw  	$ra, 0($sp)	    	# Save the return address
	    li      $v0, 4              # Print string code.
	    syscall                     # Print prompt
	  	li	$v0, 5			        # Code for read int.
	  	syscall			        	# Read int, int is in $v0.
	  # Restore the values from the stack, and release the stack space.
	  	lw	$ra, 0($sp)		        # Retrieve return address
	  	addu	$sp, $sp, 4		    # Free stack space.
	  # Return -- go to the address left by the caller.
	  	jr      $ra		            # Return.  Int is in $v0.

# +++++++++++++++ Data Elements +++++++++++++++++ #
        .data
i_msg: .asciiz "Enter int value\n"
o_msg: .asciiz "Input value is "
result_msg: .asciiz "Reslut value is "
newln: .asciiz "\n"
