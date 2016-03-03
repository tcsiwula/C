# File:      hello.s
# Purpose:   hello, world program that uses AT&T syntax
# 
# Assemble:  as -o hello.o hello.s
# Link:      ld -o hello hello.o
# Run:       ./hello
#
# This is from the Linux Assembly Howto:
#
#       http://www.tldp.org/HOWTO/Assembly-HOWTO/

.data					# section declaration

msg:
	.string	"Hello, world!\n"	# our dear string
	len = . - msg			# length of our dear string

.text					# section declaration

			# we must export the entry point to the ELF linker or
    .global _start	# loader. They conventionally recognize _start as their
			# entry point. Use ld -e foo to override the default.

_start:

# write our string to stdout

	movl	$len,%edx	# third argument: message length
	movl	$msg,%ecx	# second argument: pointer to message to write
	movl	$1,%ebx		# first argument: file handle (stdout)
	movl	$4,%eax		# system call number (sys_write)
	int	$0x80		# call kernel

# and exit

	movl	$0,%ebx		# first argument: exit code
	movl	$1,%eax		# system call number (sys_exit)
	int	$0x80		# call kernel
