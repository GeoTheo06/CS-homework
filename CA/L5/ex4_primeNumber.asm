.ORIG x3000
JSR READ
; input is in R1

AND R6, R6, #0 ; make R6 -1
ADD R6, R6, #1
NOT R6, R6
ADD R6, R6, #1

;!!!!!!!!!!! 4 is not working as input and for exercise 3 the input "500 505" is not working (also "500 520")

ADD R6, R1, R6
BRz one

BR skipOne
one
AND R2, R2, #0
ADD R2, R2, #1
BR Prime
skipOne

AND R6, R6, #0 ; make R6 -2
ADD R6, R6, #2
NOT R6, R6
ADD R6, R6, #1

ADD R6, R1, R6
BRz two

BR skipTwo
two
ADD R4, R4, #1
BR Prime
skipTwo

; check if prime

AND R2, R2, #2; Counter

LOOP1
JSR DIVMOD ;(R1/R2)
;R3 = DIV
;R4 = MOD

ADD R4, R4, #0
BRz notPrime

BR skipNotPrime

notPrime

AND R6, R6, #0 
ADD R6, R2, #0; put R2 into R6
AND R2, R2, #0 ; clear R2
ADD R2, R1, #0 ; put R1 to R2

ST R6, storeR62

JSR PRINT

LD R6, storeR62

LEA R0, PRINTNOTPRIME
PUTS

AND R2, R2, #0
ADD R2, R6, #0 ; put R6 back to R2
JSR PRINT

; print newline
AND R0, R0, #0
ADD R0, R0, #10
PUTC

HALT

skipNotPrime


BR skipPrime
Prime
;first check if this last number is a multiple of R1
ADD R4, R4, #0
BRz notPrime
AND R2, R2, #0
ADD R2, R1, #0
JSR PRINT

LEA R0, PRINTPRIME
PUTS

; print newline
AND R0, R0, #0
ADD R0, R0, #10
PUTC


HALT

skipPrime

ADD R2, R2, #1

BR LOOP1

HALT

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DIVMOD

DIVMOD 
; R3 is div and R4 is mod

; will loop until the divisor reaches the divider

;initialize
AND R3, R3, #0 ; counter (it is the div)
AND R4, R4, #0
AND R5, R5, #0
AND R6, R6, #0

NOT R2, R2
ADD R2, R2, #1
ADD R5, R2, #0 ; R5 holds negative R2 and keeps decrementing until the end

;check starting condition
ADD R6, R1, R5
BRn EXIT1

LOOP7
AND R6, R6, #0

ADD R3, R3, #1
ADD R5, R5, R2
ADD R6, R1, R5 ;R6 only used for the check
BRzp LOOP7

EXIT1

; decrement R5 by one time
NOT R2, R2
ADD R2, R2, #1 ; make R2 positive again
ADD R5, R5, R2

ADD R4, R1, R5 ;now contains the mod

; test if we have reached the root of R1
AND R6, R6, #0
NOT R2, R2
ADD R2, R2, #1 ; make R2 negative
ADD R6, R3, R2 ; R3 (the div) - R2 (the second number). R6 only used for testing
BRnz timeToLeave

BR skipTimeToLeave
timeToLeave

; make R2 positive again
NOT R2, R2
ADD R2, R2, #1
BR prime

skipTimeToLeave

; make R2 positive again
NOT R2, R2
ADD R2, R2, #1

RET

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! READ

READ

;we get at least 1 character no matter what happens
GETC
PUTC
LD R1, asciiZero
ADD R1, R0, R1

LOOP

;get character
GETC
PUTC
LD R2, asciiZero
ADD R2, R0, R2

;check if "enter" is pressed
AND R4, R4, #0
ADD R4, R0, #-10
BRz EXIT

; multiply R1 by 10
AND R5, R5, #0 ; temporarily holds R1 to add it to the updated R1 each time
ADD R5, R1, #0

AND R3, R3, #0 ; counter
ADD R3, R3, #9

mult
ADD R1, R1, R5
ADD R3, R3, #-1
BRp mult

; add current number to total number
ADD R1, R1, R2

AND R2, R2, #0
BR LOOP

EXIT
AND R5, R5, #0
ADD R5, R1, #0
RET

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! PRINT
PRINT

ST R2, INITR2

AND R6, R6, #0
ST R6, digs
ST R6, trailing0s

;REVERSE R2
; last digit of R2 stored in R3. the reverse of R2 is constructed in R4.

AND R4, R4, #0

LOOP3
ST R7, saveR7
JSR MOD10 ;output: R3.
LD R7, saveR7

; multiply R4 by 10
ST R7, saveR7
JSR mult10
LD R7, saveR7

;add the last digit of R2 (R3) into R4
ADD R4, R4, R3

;subtract R3 from R2
NOT R3, R3
ADD R3, R3, #1
ADD R2, R2, R3
ST R7, saveR7
JSR DIV10 ; output: R2. Divides R2 by 10
LD R7, saveR7

ADD R2, R2, #0
BRz EXIT2


BR LOOP3

EXIT2
; END OF REVERSE

AND R2, R2, #0
ADD R2, R4, #0
; now R2 is reversed.

LOOP6
ST R7, saveR7
JSR MOD10
LD R7, saveR7
LD R0, asciiPrintZero
ADD R0, R0, R3
PUTC
;subtract R3 from R2
NOT R3, R3
ADD R3, R3, #1
ADD R2, R2, R3
ST R7, saveR7
JSR DIV10 ; output: R2. Divides R2 by 10
LD R7, saveR7

ADD R2, R2, #0
BRp LOOP6

; print trailing 0s if any
LD R6, trailing0s
LD R5, digs
NOT R6, R6
ADD R6, R6, #1
ADD R5, R5, R6
BRz notLoop
LOOP10
LD R0, asciiPrintZero
PUTC
ADD R5, R5, #-1
BRp LOOP10
notLoop

RET

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DIV10

DIV10
ST R3, div3
ST R4, div4
sT R5, div5

AND R3, R3, #0 ;keeps track of multiples of 10
AND R4, R4, #0 ;counter

AND R5, R5, #0
ADD R5, R2, R3
BRz EXIT3

LOOP5
ADD R3, R3, #-10
ADD R4, R4, #1

AND R5, R5, #0
ADD R5, R2, R3
BRp LOOP5

EXIT3
AND R2, R2, #0
ADD R2, R4, R2

LD R3, div3
LD R4, div4
LD R5, div5
RET

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! mult10

mult10
AND R5, R5, #0
ADD R5, R5, #9 ; counter
AND R6, R6, #0
ADD R6, R4, R6 ; holds the initial value of R4
LOOP4
ADD R4, R4, R6
ADD R5, R5, #-1
BRp LOOP4
RET

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! MOD10

MOD10
ST R4, MOD4
AND R4, R4, #0

LOOP2
ADD R4, R4, #-10

AND R5, R5, #0
ADD R5, R2, R4
BRp LOOP2

;handle special case if multiple of 10
ADD R5, R5, #0
BRz skipMultOf10

; count the trailing 0s
ST R6, storeR6
LD R6, trailing0s
ADD R6, R6, #1
ST R6, trailing0s
LD R6, storeR6

ADD R4, R4, #10
skipMultOf10

;count total digits
ST R6, storeR6
LD R6, digs
ADD R6, R6, #1
ST R6, digs
LD R6, storeR6

AND R3, R3, #0
ADD R3, R2, R4

LD R4, MOD4

RET


asciiPrintZero .FILL x0030
asciiZero .FILL #-48
PRINTNOTPRIME .STRINGZ " is not a prime number as it is divisible by "
PRINTPRIME .STRINGZ " is a prime number"
storeR2 .BLKW #1
digs .BLKW #1
storeR6 .BLKW #1
storeR62 .BLKW #1
MOD4 .BLKW #1
trailing0s .BLKW #1
div3 .BLKW #1
div4 .BLKW #1
div5 .BLKW #1
INITR2 .BLKW #1
saveR7 .BLKW #1
.END