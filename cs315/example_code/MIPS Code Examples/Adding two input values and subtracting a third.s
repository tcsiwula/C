#
# Program to read three numbers, find the sum of the first two and
# subtract the third from the sum:
#
#       (x+y)-z
#
# Note that it's not necessary to store the input values in memory
# (although it's fine to do so).
# 
	.text
	.globl	main
main:
	subu	$sp, $sp, 4 	        # Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address
	
	# Get x
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t0, $v0		# Copy to memory (this is x).

	# Get y
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t1, $v0		# Copy to memory (this is y).

	# Get z
	li	$v0, 5			# Code for read int.
	syscall				# Ask the system for service.
	move    $t2, $v0		# Copy to memory (this is z).

	# Add x + y
	add	$t0, $t0, $t1           # x = x + y

        # Subtract
        sub     $t0, $t0,$t2            # x = x - z

	# Print the result
        move    $a0, $t0
	li	$v0, 1			# Code for print int.
	syscall

	# Clean up and return
	lw	$ra, 0($sp)		# Retrieve the return address
	addu	$sp, $sp, 4 	        # Make additional stack space.
	# jr	$ra
        li      $v0, 10
        syscall
