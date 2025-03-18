.ORIG x3000

; will loop until the divisor reaches the divider and R2 is the counter

;initialize
NOT R1, R1
ADD R1, R1, #1
ADD R4, R1, #0

;check starting condition
ADD R5, R0, R4
BRn EXIT

LOOP
AND R5, R5, #0

ADD R2, R2, #1
ADD R4, R4, R1
ADD R5, R0, R4
BRzp LOOP

EXIT

; decrement R4 by one time
NOT R1, R1
ADD R1, R1, #1
ADD R4, R4, R1

ADD R3, R0, R4

HALT

.END