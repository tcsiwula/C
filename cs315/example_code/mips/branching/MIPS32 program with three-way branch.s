#
# Program to read two numbers, print whether the first is greater, they're
# equal or the first is smaller.
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
	beq     $t0, $t1, eq_lab        # Go to eq_lab if $t0 == $t1
        blt     $t0, $t1, lt_lab        # Go to lt_lab if $t0 < $t1

        # Print that first value is > second
        li      $v0, 4                  # Code to print a string
        la      $a0, gt_msg             # Put the string in $a0
        syscall                         # Print the string
        j done                          # Skip to done

        # Print that they're equal
eq_lab: li      $v0, 4                  # Code to print a string
        la      $a0, eq_msg             # Put the string in $a0
        syscall                         # Print the string
        j done                          # Skip to done

        # Print that first value is < second
lt_lab: li      $v0, 4                  # Code to print a string
        la      $a0, lt_msg             # Put the string in $a0
        syscall                         # Print the string

	# Restore the values from the stack, and release the stack space.
done:	lw	$ra, 0($sp)		# Retrieve the return address
	addu	$sp, $sp, 4 	        # Make additional stack space.

	# Return -- go to the address left by the caller.
	# jr	$ra
        li      $v0, 10
        syscall


        .data
gt_msg: .asciiz "First is greater than second\n"
eq_msg: .asciiz "They're equal\n"
lt_msg: .asciiz "First is less than second\n"
