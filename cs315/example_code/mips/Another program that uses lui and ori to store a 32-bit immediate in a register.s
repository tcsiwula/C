#
# Look at using lui, addi and ori to create the constant 
#    98304 = 2^16 + 2^15
# 
	.text
	.globl	main
main:
        # Put 98304 = 2^16 + 2^15 in $t0 using lui and ori
        lui     $t0, 1                  # Put a 1 in bit 17 of $t0
        ori     $t0, $t0, 32768         # Put a 1 in bit 16 of $t0

	# Print $t0
        la      $a0, first
        move    $a1, $t0
        jal     pr_int

        # Put 98304 = 2^16 + 2^15 in $t0 using lui and addi
	lui	$t0, 1                  # Put 1 in bit 17 of $t0
        addi    $t0, $t0, 32768         # Put 1 in bit 16 of $t0 

	# Print $t0
        la      $a0, secnd
        move    $a1, $t0
        jal     pr_int

	# Return -- go to the address left by the caller.
#	jr	$ra
        li      $v0, 10
        syscall



        #############################################################
        # Function to print a message and an int
        # String to print is in $a0, int is in $a1
pr_int: 
        # Put return address on stack
        addi    $sp, $sp, -4            # Make additional stack space.
        sw      $ra, 0($sp)             # Save the return address

        li      $v0, 4                  # Print string code.
        syscall                         # Print message
        li      $v0, 1                  # Code for print int.
        move    $a0, $a1                # Make int available to syscall
        syscall                         # Print int
        li      $v0, 4                  # Print string code.
        la      $a0, newln              # Make newln avail to syscall
        syscall                         # Print newln

        # Restore the values from the stack, and release the stack space.
        lw      $ra, 0($sp)             # Retrieve return address
        addu    $sp, $sp, 4             # Free stack space.

        # Return -- go to the address left by the caller.
        jr      $ra                     # Return.  


        .data
newln:  .asciiz "\n"
first:  .asciiz "Using lui and ori, 98304 = "
secnd:  .asciiz "Using lui and addi, 98304 = "
