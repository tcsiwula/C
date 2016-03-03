	.text
	.globl	main
main:
	  subu	$sp, $sp, 16	       		 # why 16 and not 4?
	  sw	$ra, 12($sp)		        # why is it 12 not 0?

      li 	$t0, 0
	  li 	$t1, 0x09					# Why OxO9
	  li 	$t2, 0x42					# Why Ox42
	  move 	$t3, $t1					#temp = y

Loop: ble	$t3, 0, Done			#why ble and not bgt
	  add 	$t0, $t0, $t2
	  sub 	$t3, $t3, 1
      j   	Loop

Done: li	$v0, 1
      move 	$a0, $t0
      syscall

	  lw 	$ra, 0($sp)
      addu  $sp, $sp, 16
	  li 	$v0, 10
	  syscall
