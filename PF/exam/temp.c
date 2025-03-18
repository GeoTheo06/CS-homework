; Store the program at memory location 3000.
.ORIG x3000
AND R0 R0 #0
AND R2 R2 #0
AND R1 R1 #0
AND R3 R3 #0
AND R4 R4 #0
AND R5 R5 #0
AND R6 R6 #0
AND R7 R7 #0
JSR readNum1
JSR readNum2

JSR addNumbers

JSR print

HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;readNum1
readNum1
ST R7 s7
AND R2 R2 #0


readLoop
GETC
OUT

; exit if space
LD R2 min32
ADD R2 R0 R2
BRz readExit

LD R2 min48
ADD R0 R0 R2
BRz readLoop ;skip if 0

LEA R2 numLkw ; Rs is pointer

; pushes number to stack
LD R1 num1
JSR pushToStack
ST R1 num1

skip4
BR readLoop
readExit

LD R7 s7
RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;readNum2
readNum2
ST R7 s7

readLoop2

GETC
OUT

LD R2 negEnter
ADD R2 R0 R2
BRz exit ; exit if enter

LD R2 min48
ADD R0 R0 R2
BRz readLoop2 ; skip if 0

LEA R2 numLkw ; R2 is pointer
LD R3 k10
ADD R2 R2 R3
; Push the number to stack
LD R1 num2
JSR pushToStack
ST R1 num2
skip5
BR readLoop2
exit

LD R7 s7
RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;addNumbers
addNumbers
ST R7 s7

LD R0 num1
LD R2 num2
NOT R2 R2
ADD R2 R2 #1
ADD R0 R0 R2 ; R0 - R2
BRn smaller
BR bigger

bigger ; puts num1 in sumSize
LD R0 num1
ST R0 sumSize
BR sumLoop

smaller ; puts num2 in sumSize
LD R0 num2
ST R0 sumSize

sumLoop

LEA R2 numLkw ; Get the last digit of the first number
LD R1 num1
BRp getDig1

; pointer negative so dig becomes 0
AND R0 R0 #0
ST R0 dig1
BR getDig2

; in case that pointer is positive, get digit from array
getDig1
JSR pop
ST R0 dig1
ST R1 num1

getDig2
LEA R2 numLkw ; Get the last digit of the second number
LD R1 k10
ADD R2 R2 R1
LD R1 num2 ; load values
BRp getDig11

; pointer negative so dig becomes 0
AND R0 R0 #0
ST R0 dig2
BR addDigs

; in case that pointer is positive, get digit from array
getDig11
JSR pop
ST R0 dig2
ST R1 num2

addDigs
;initialize R1,2,3
LD R2 dig1
LD R1 dig2
LD R3 carry

skipAdd
ADD R0 R2 R1
ADD R0 R0 R3


LEA R2 numLkw ; R2 is the array pointer
LD R1 k10
ADD R2 R2 R1
ADD R2 R2 R1
LD R1 sum

ADD R3 R0 #-10 ; if bigger than 10 then we need carry
BRn notCarry
BR yCarry

notCarry
JSR pushToStack
AND R0 R0 #0
BR skip2

yCarry
ADD R0 R3 #0
JSR pushToStack
AND R0 R0 #0
ADD R0 R0 #1

skip2
; store sum and carry
ST R1 sum
ST R0 carry

LD R0 sumSize
ADD R0 R0 #-1
ST R0 sumSize
BRz exit1 ; check if we reached the beginning
BR sumLoop

exit1
LD R7 s7
RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;print
print
ST R7 s7

LD R2 asciiZero
LD R0 carry
BRz printLoop
ADD R0 R0 R2
OUT

printLoop

LEA R2 numLkw ; R2 is pointer
LD R1 k10

skipAdd
ADD R2 R2 R1
ADD R2 R2 R1

LD R1 sum ; get values
JSR pop ; get the digit

LD R2 asciiZero
ADD R0 R0 R2
OUT

ST R1 sum
ADD R1 R1 #0
BRz exit3 ;check if done
BR printLoop

exit3
LD R0 asciiEnter
OUT

LD R7 s7
RET



pushToStack ; input R0

ADD R2 R2 R1 ; go to end of array

STR R0 R2 #0 ; Push R0 to stack

ADD R1 R1 #1 ; update num
RET


pop ; output R0

; last element
ADD R2 R2 R1
ADD R2 R2 #-1

LDR R0 R2 #0

ADD R1 R1 #-1 ; update num
RET

s7 .BLKW #1
dig1 .FILL #0
dig2 .FILL #0
k10 .FILL #10000
carry .FILL #0
sumSize .FILL #0
num1 .FILL #0
num2 .FILL #0
sum .FILL #0
asciiZero .FILL #48
asciiEnter .FILL #10
min48 .FILL #-48
min32 .FILL #-32
negEnter .FILL #-10
numLkw .BLKW #10000

.END