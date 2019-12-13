#     T o p  o f  P i l e
#
#
# This routine finds the color of the part on top of a pile.
#
# Name: Peiqi(Peggy) Zhao
# Date: 10/9/2019

.data
Pile:  .alloc	1024
# Status:	.alloc	7

.text

TopOfPile:	addi	$1, $0, Pile		# point to array base
		swi	545			# generate pile

	        # SWI 547 is useful for debugging. Remove calls to it in
		# final program submission.
		# TEMP: remove the lines between **********
		# addi    $2, $0, 3770		# TEMP: set a random offset into pile
		# swi     547			# TEMP: highlight that position
		# addi    $2, $0, 165		# TEMP: set another offset into pile
		# swi     547			# TEMP: highlight that position
		# addi    $2, $0, 229		# TEMP: set another offset into pile
		# swi     547			# TEMP: highlight that position	
		# *****************************************
                # your code goes here

		addi $4, $0, 0		# $4: arr[]
		addi $5, $0, 1		# $5: 1
		addi $2, $0, 6		# $3: 6
		addi $1, $0, -1


		# outer loop for rows
		addi $6, $0, 60		# $6: rows
OUTLOOP:	addi $6, $6, -1		# rows decrement
		sll $8, $6, 6

		# inner loop
		addi $8, $8, 60
INNERLOOP:	addi $8, $8, -4		# addi $8, $8, -4		# column decrement
		beq $8, $0, OUTLOOP		
		lw $10, Pile($8)
		beq $10, $0, INNERLOOP 
		#j INNERLOOP  #If four pixels are black, go to next set of 4


CHECK:	addi $11, $0, 4		#Counter for each group of 4 pixels
CHECK2: addi $11, $11, -1	#Decrement counter
		beq $11, $1, INNERLOOP				# counter == -1

		add $13, $11, $8		# $13: offset of block of 4---offset of current_pixel
		lb	$9, Pile($13)		# $9: current_pixel
		beq $9, $0, CHECK2		# check current_pixel =? 0
		#j CHECK2

BOTCHECK2:	addi $10, $13, -64 	#	$10: upper--index
			lb $10, Pile($10)		#	$10: upper
			beq $10, $9, LEFTRIGHT				# upper != middle------branch to check left or right



			beq $10, $0, CHECK2			# upper != black--------branch to check left or right

			addi $12, $13, 64		# $12: lower--index
			lb $12, Pile($12)		#	$12: lower
			bne $12, $10, CHECK2		# T: lower==upper

	# check if it's a pixel between two same color horizontal lines(??? not worthy)
			# if left==0 && right==0, ignore
			addi $10, $13, -1		# left != 0, SETUPPER
			lb $10, Pile($10)
			bne $10, $0, SETUPPER
			
			addi $15, $13, 1		# right != left, SETUPPER---$15: right
			lb $15, Pile($15)
			bne $15, $10, SETUPPER
			addi $10, $4, 0		# set current bottom
			sllv $12, $5, $9		# $12: 1 << current pixel
			j SETUPPER2

	#SET	UPPER	as  BOTTOM
SETUPPER:	addi $10, $4, 0
			sllv $12, $5, $12		# $12: 1 << current
SETUPPER2:	or $4, $4, $12
			bne $4, $10, DECREMENT

	# equivalence of DECREMENT
			# addi $2, $2, -1
			# beq $2, $0, FIN
			# j CHECK2
			#j DECREMENT


LEFTRIGHT:	addi $10, $13, -1			# $10: left--index
			lb $10, Pile($10)			# $10: left_pixel
			beq $10, $0, CHECK2

			beq $10, $9, CHECK2				# middel==left, CHECK2

			addi $12, $13, 1			# $12: right---index
			lb $12, Pile($12)			# $12: right_pixel
			bne $10, $12, CHECK2		# left != right, CHECK2

	# Set left as bottom
			addi $10, $4, 0
			sllv $12, $5, $12			# $12: 1 << right
			or $4, $4, $12
			beq $4, $10, CHECK2

DECREMENT:	addi $2, $2, -1
			bne $2, $0, CHECK2
			#j CHECK2

# extract digit from $4
FIN:	addi $2, $2, 1			# $3: counter for how many times shifting
		srl $4, $4, 1			
		or	$11, $5, $4
		beq	$11, $4, FIN

		# TEMP: replace this line to give your answer
     #          add    $2, $0, $3               # TEMP: guess the first color

		swi	546			# submit answer and check
		jr	$31			# return to caller
