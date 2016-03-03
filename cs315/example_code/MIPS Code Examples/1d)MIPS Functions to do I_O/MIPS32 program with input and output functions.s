#
# Read int from input with a function, print result with a function
 	.text
	.globl	main
main:
	addi	$sp, $sp, -4		# Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address
	
	# Ask the OS to read value
        la      $a0, i_msg              # String prompt
        jal     rd_int                  # Jump to function that prints a msg
                                        #   and reads an int
	move	$t0, $v0		# Copy return value to safe location

	# Print input value with message
        la      $a0, o_msg              # Message to appear with int
        move    $a1, $t0                # The int to print
        jal     pr_int                  # Go to function

	# Restore the values from the stack, and release the stack space.
	lw	$ra, 0($sp)		# Retrieve return address
	addu	$sp, $sp, 4		# Free stack space.

	# Return -- go to the address left by the caller.  OK for SPIM
	# jr	$ra

        # Exit system call:  SPIM or MARS
        li    $v0, 10
        syscall


        # Function to print a message and read an int
        # String to print is in $a0
rd_int: 
        # Put return address on stack
	addi	$sp, $sp, -4		# Make additional stack space.
	sw	$ra, 0($sp)		# Save the return address

        li      $v0, 4                  # Print string code.
        syscall                         # Print prompt
	li	$v0, 5			# Code for read int.
	syscall				# Read int, int is in $v0.

	# Restore the values from the stack, and release the stack space.
	lw	$ra, 0($sp)		# Retrieve return address
	addu	$sp, $sp, 4		# Free stack space.

	# Return -- go to the address left by the caller.
	jr      $ra		        # Return.  Int is in $v0.


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


        .data
i_msg: .asciiz "Enter int value\n"
o_msg: .asciiz "Input value is "         
newln: .asciiz "\n"

