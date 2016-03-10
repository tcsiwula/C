#
# Iterative program to read a positive integer n, compute the sum
# 1 + 2 + . . . + n, and print the result
# 
	.text
	.globl	main
main:
	subu	$sp, $sp, 4 	        # Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address
	
	# Ask the OS to read a number and put it in a temporary register
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t0, $v0                # Put the input value (n) in a safe
                                        #    place

	# The loop
        li      $t1, 0                  # Initialize sum (sum) to 0
        li      $t2, 1                  # Initialize counter (i) to 1
lp_tst: bgt     $t2, $t0, done          # If $t2 > $t0 (i >  n), 
                                        #    branch out of loop.
                                        #    Otherwise continue.
        add     $t1, $t1, $t2           # Add $t2 (i) to $t1 (sum)
        addi    $t2, $t2, 1             # Increment $t2 (i++)
        j       lp_tst                  # Go to the loop test

        # Done with the loop, print result
done:   li      $v0, 1                  # Code to print an int
        move    $a0, $t1                # Put the int in $a0
        syscall                         # Print the int

	# Restore the values from the stack, and release the stack space.
     	lw	$ra, 0($sp)		# Retrieve the return address
	addu	$sp, $sp, 4 	        # Free up added stack space.

	# Return -- go to the address left by the caller.
	# jr	$ra

        li      $v0, 10
        syscall
