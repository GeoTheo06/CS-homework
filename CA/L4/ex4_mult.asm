.ORIG x3000

AND R3, R3, #0 ; R3 will indicate whether the result should be negative or positive
; if numbers are negative make them positive
ADD R0, R0, #0
BRz zero

ADD R1, R1, #0
BRz zero

ADD R0, R0, #0
BRp pos1

NOT R0, R0
ADD R0, R0, #1
NOT R3, R3

pos1

ADD R1, R1, #0
BRp pos2

NOT R1, R1
ADD R1, R1, #1
NOT R3, R3

pos2

; making R0 be bigger than R1
NOT R1, R1
ADD R1, R1, #1
ADD R4, R0, R1
BRp bigger

ADD R4, R1, #0
ADD R1, R0, #0
ADD R0, R4, #0

bigger

;do again the same process to change the number back to positive
ADD R0, R0, #0
BRp pos11

NOT R0, R0
ADD R0, R0, #1

pos11

ADD R1, R1, #0
BRp pos22

NOT R1, R1
ADD R1, R1, #1

pos22

mult
ADD R2, R2, R0
ADD R1, R1, #-1
BRp mult

ADD R3, R3, #0
BRz stop

NOT R2, R2
ADD R2, R2, #1

stop
HALT

zero
AND R2, R2, #0
HALT

.END