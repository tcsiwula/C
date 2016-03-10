//-----------------------------------------------------------------
//	hello.s
//
//	This linux program outputs a short message to the screen.
//
//		to assemble:  $ as hello.s -o hello.o
//		and to link:  $ ld hello.o -o hello
//		and execute:  $ ./hello
//
//	programmer: ALLAN CRUSE
//	written on: 27 FEB 2012
//      Edits:      18 Mar 2013 (PSP)
//-----------------------------------------------------------------

	# symbolic constants 
	.equ	sys_write, 1		# system-call ID-number
	.equ	sys_exit, 60		# system-call ID-number
	.equ	dev_stdout, 1		# device-file ID-number
	

	.section	.data
msg:	.ascii 	"Hello, World!\n" 	# message text
len:	.quad	. - msg			# length of the string =
                                        #    current address (.) - 
                                        #    address of message  

	.section	.text
_start:	
	# print the message onscreen
	mov	$sys_write, %rax	# system-call ID-number
	mov	$dev_stdout, %rdi	# device-file ID-number
	lea	msg, %rsi		# address of the string
	mov	len, %rdx		# length of the string
	syscall				# invoke kernel service

	# terminate this program
	mov	$sys_exit, %rax		# system-call ID-number
	mov	$0, %rdi		# zero is the exit-code
	syscall				# invoke kernel service

	.global	_start			# make entry-point visible
	.end
