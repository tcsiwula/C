#
# Program to read two numbers, determine whether the first is > the second
# and print the result.  This uses the pseudoinstruction bgt
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

	# Ask the OS to read another number and put it in a temporary register
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t1, $v0                # Put the input value in a safe
                                        #    place

	# Compare the input values
	bgt     $t0, $t1, gt_lab        # Go to gt_lab if $t0 > $t1

        # Print that first value is <= second
        li      $v0, 4                  # Code to print a string
        la      $a0, le_msg             # Put the string in $a0
        syscall                         # Print the string
        j done                          # Skip next few statements:  go
                                        #    to done

        # Print that first value is > second
gt_lab: li      $v0, 4                  # Code to print a string
        la      $a0, gt_msg             # Put the string in $a0
        syscall                         # Print the string

	# Restore the values from the stack, and release the stack space.
done:	lw	$ra, 0($sp)		# Retrieve the return address
	addu	$sp, $sp, 4 	        # Make additional stack space.

	# Return -- go to the address left by the caller.
	# jr	$ra
        li      $v0, 10
        syscall


        .data
le_msg: .asciiz "The first input value is <= the second\n"
gt_msg: .asciiz "The first input value is > the second\n"
