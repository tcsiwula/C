# File:     MIPS_Code_Class_Example.s
# Purpose:  Read two ints a and b and compute
#              xxx = b - a,  if a < b
#              xxx = a,      if a = b
#              xxx = a + b,  if a > b
# Input:    a and b
# Output:   xxx
# Note:     There is no prompting for input or explanation of output
	.text
	.globl	main
main:
	subu	$sp, $sp, 4 	        # Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address
	
	# Ask the OS to read a 
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t0, $v0                # Put the input value (n) in a safe
                                        #    place
	# Ask the OS to read b 
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t1, $v0                # Put the input value (n) in a safe
                                        #    place

	# Check to see if a > b
	bgt	$t0, $t1, case1		# if positive case1
	beq	$t0, $t1, case2		# if equal case2
					# else case3
	sub 	$t2, $t1, $t0		#   sub b - a
	j	done

case1: 	add	$t2, $t1, $t0		# if a > b calculate b + a
	j 	done

case2: 	addi	$t2, $t0, 0		# if a = b then move a into reg $t1 
					# Note: could also use "add $t2, $t1, $zero
        # Done, print sum
done:   li      $v0, 1                  # Code to print an int
        move    $a0, $t2                # Put the sum in $a0
        syscall                         # Print the sum

	# Restore the values from the stack, and release the stack space.
     	lw	$ra, 0($sp)		# Retrieve the return address
	addu	$sp, $sp, 4 	        # Free up added stack space.

	# Return -- go to the address left by the caller.
	# jr	$ra

        li      $v0, 10
        syscall
