#
# Program to read a number, determine whether it's >= 0 and
# print the result
# 
	.text
	.globl	main
main:
	subu	$sp, $sp, 4 	        # Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address
	
	# Ask the OS to read a number and put it in a temporary register
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t0, $v0                # Put the input value in a safe
                                        #    place
	# Compare input value to zero
	slt     $t1, $t0, $zero         # $t1 = 1 if $t0 < 0.  Otherwise
                                        #    $t1 = 0

        # Branch to appropriate print statement
        beq     $t1, $zero, ge0         # if $t1 == 0, go to ge0

        # Print that input value is < 0
        li      $v0, 4                  # Code to print a string
        la      $a0, lt_msg             # Put the string in $a0
        syscall                         # Print the string
        j done                          # Skip next few statements:  go
                                        #    to done

        # Print that input value is >= 0
ge0:    li      $v0, 4                  # Code to print a string
        la      $a0, ge_msg             # Put the string in $a0
        syscall                         # Print the string

	# Restore the values from the stack, and release the stack space.
done:	lw	$ra, 0($sp)		# Retrieve the return address
	addu	$sp, $sp, 4 	        # Free added stack space.

	# Return -- go to the address left by the caller.  SPIM
	# jr	$ra

        # Exit system call:  SPIM and MARS
        li      $v0, 10
        syscall

        .data
lt_msg: .asciiz "The input value is negative\n"
ge_msg: .asciiz "The input value is >= 0\n"
