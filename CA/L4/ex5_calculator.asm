.ORIG x3000

ADD R3, R3, #0
BRp mult
BRz addit
BRn sub

mult

AND R5, R5, #0
; if numbers are negative make them positive
ADD R1, R1, #0
BRz zero

ADD R2, R2, #0
BRz zero

ADD R1, R1, #0
BRp pos1

NOT R1, R1
ADD R1, R1, #1
NOT R5, R5

pos1

ADD R2, R2, #0
BRp pos2

NOT R2, R2
ADD R2, R2, #1
NOT R5, R5

pos2

; making R0 be bigger than R1
NOT R2, R2
ADD R2, R2, #1
ADD R6, R1, R2
BRp bigger

ADD R6, R2, #0
ADD R2, R1, #0
ADD R1, R6, #0

bigger

;do again the same process to change the number back to positive
ADD R1, R1, #0
BRp pos11

NOT R1, R1
ADD R1, R1, #1

pos11

ADD R2, R2, #0
BRp pos22

NOT R2, R2
ADD R2, R2, #1

pos22

mult1
ADD R4, R4, R1
ADD R2, R2, #-1
BRp mult1

ADD R5, R5, #0
BRz stop

NOT R4, R4
ADD R4, R4, #1

stop
HALT

zero
AND R4, R4, #0
HALT

addit
ADD R4, R1, R2
HALT

sub
NOT R2, R2
ADD R2, R2, #1
ADD R4, R1, R2

HALT
.END