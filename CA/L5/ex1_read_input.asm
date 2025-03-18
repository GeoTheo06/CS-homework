.ORIG x3000

AND R1, R1, #0

; initial read character

;we get at least 1 character no matter what happens
GETC
PUTC
LD R2, asciiZero
ADD R2, R0, R2

; add current number to R1
ADD R1, R1, R2

;initialize R2
AND R2, R2, #0

LOOP

;get character
GETC
PUTC
LD R2, asciiZero
ADD R2, R0, R2

;check if its over
AND R4, R4, #0
LD R4, asciiSpace
ADD R4, R4, R0
BRz DONE
AND R4, R4, #0
ADD R4, R0, #-10
BRz DONE

; multiply R1 by 10
AND R5, R5, #0
ADD R5, R1, #0

AND R3, R3, #0
ADD R3, R3, #9

mult
ADD R1, R1, R5
ADD R3, R3, #-1
BRp mult

; add current number to total number
ADD R1, R1, R2

AND R2, R2, #0
BR LOOP

DONE
AND R5, R5, #0
ADD R5, R1, #0
HALT
asciiZero .FILL #-48
asciiSpace .FILL #-32
.END