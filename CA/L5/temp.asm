.ORIG x3000

JSR READ
ADD R2, R1, R2
JSR READ

;Now R2 is the small number and R1 is the big

AND R3, R3, #0 ;temp t654evariable used to check 
LOOP1

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! HAHHAAHAH


; takes input R2

AND R6, R6, #0 ; make R6 -1
ADD R6, R6, #1
NOT R6, R6
ADD R6, R6, #1

;!!!!!!!!!!! for exercise 3 the input "500 505" is not working (also "500 520")

ADD R6, R2, R6
BRz one

BR skipOne
one
AND R3, R3, #0
ADD R3, R3, #1
BR Prime
skipOne

AND R6, R6, #0 ; make R6 -2
ADD R6, R6, #2
NOT R6, R6
ADD R6, R6, #1

ADD R6, R2, R6
BRz two

BR skipTwo
two
ADD R5, R5, #1
BR Prime
skipTwo

; check if prime

AND R3, R3, #2; Counter

LOOP12


;swap R2, R3
ST R2, temp
AND R2, R2, #0
ADD R2, R3, #0
AND R3, R3, #0
LD R3, temp

;swap R1, R2
ST R1, temp
AND R1, R1, #0
ADD R1, R2, #0
AND R2, R2, #0
LD R2, temp


JSR DIVMOD ;(R2/R3)
;R4 = DIV
;R5 = MOD

;swap R2, R3
ST R2, temp
AND R2, R2, #0
ADD R2, R3, #0
AND R3, R3, #0
LD R3, temp

;swap R1, R2
ST R1, temp
AND R1, R1, #0
ADD R1, R2, #0
AND R2, R2, #0
LD R2, temp


ADD R5, R5, #0
BRz notPrime

BR skipNotPrime

notPrime

AND R6, R6, #0 
ADD R6, R3, #0; put R3 into R6
AND R3, R3, #0 ; clear R3
ADD R3, R2, #0 ; put R2 to R3

ST R1, everythingR1
ST R2, everythingR2
ST R3, everythingR3
ST R4, everythingR4
ST R5, everythingR5
ST R6, everythingR6

JSR PRINT

LD R1, everythingR1
LD R2, everythingR2
LD R3, everythingR3
LD R4, everythingR4
LD R5, everythingR5
LD R6, everythingR6


LEA R0, PRINTNOTPRIME
PUTS

AND R3, R3, #0
ADD R3, R6, #0 ; put R6 back to R3

ST R1, everythingR1
ST R2, everythingR2
ST R3, everythingR3
ST R4, everythingR4
ST R5, everythingR5
ST R6, everythingR6

JSR PRINT

LD R1, everythingR1
LD R2, everythingR2
LD R3, everythingR3
LD R4, everythingR4
LD R5, everythingR5
LD R6, everythingR6

; print newline
AND R0, R0, #0
ADD R0, R0, #10
PUTC

HALT

skipNotPrime


BR skipPrime
Prime
;first check if this last number is a multiple of R2
ADD R5, R5, #0
BRz notPrime
AND R3, R3, #0
ADD R3, R2, #0

ST R1, everythingR1
ST R2, everythingR2
ST R3, everythingR3
ST R4, everythingR4
ST R5, everythingR5
ST R6, everythingR6

JSR PRINT


LD R1, everythingR1
LD R2, everythingR2
LD R3, everythingR3
LD R4, everythingR4
LD R5, everythingR5
LD R6, everythingR6

LEA R0, PRINTPRIME
PUTS

; print newline
AND R0, R0, #0
ADD R0, R0, #10
PUTC


HALT

skipPrime

ADD R3, R3, #1

BR LOOP12

HALT
; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! END HAHAHAHHAHAH

;condition
NOT R3, R2
ADD R3, R3, #1
ADD R3, R1, R3
BRzp LOOP1

HALT

READ

ST R2, STORER2

AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0

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
LD R2, STORER2
RET

PRINT
; R2 = small, R1 = big
ST R2, INITR2

;new number so reset the number of digits
AND R6, R6, #0
ST R6, digs
ST R6, trailing0s
ST R6, firstNumberDone ; when it becomes 1 it means that we are after the first digit (2nd iteration and above)
ST R6, lastDigIs0 ; when it becomes 1 it means that the last digit of our number is not 0

;REVERSE R2
; last digit of R2 stored in R3. the reverse of R2 is constructed in R4.

AND R4, R4, #0

LOOP3
ST R7, storeR7
JSR MOD10 ;output: R3.
LD R7, storeR7



ST R7, storeR7
; check if this is the first digit of the number
LD R7, firstNumberDone
BRz firstNumberNotDone
BR skipFirstNumberNotDone
firstNumberNotDone

; check if this digit is 0 
AND R7, R7, #0
ADD R7, R3, #0
BRp not0
BR skipNot0
not0
ADD R7, R7, #1 ; not really needed beacuse R7 already positive but whatever
LD R7, lastDigIs0
skipNot0
skipFirstNumberNotDone

LD R7, storeR7


; multiply R4 by 10
ST R7, storeR7
JSR mult10
LD R7, storeR7

;add the last digit of R2 (R3) into R4
ADD R4, R4, R3

;subtract R3 from R2
NOT R3, R3
ADD R3, R3, #1
ADD R2, R2, R3
ST R7, storeR7
JSR DIV10 ; output: R2. Divides R2 by 10
LD R7, storeR7

ADD R2, R2, #0
BRz EXIT2


BR LOOP3

EXIT2
; END OF REVERSE

AND R2, R2, #0
ADD R2, R4, #0
; now R2 is reversed.

LOOP6
ST R7, storeR7
JSR MOD10
LD R7, storeR7
LD R0, asciiPrintZero
ADD R0, R0, R3
PUTC
;subtract R3 from R2
NOT R3, R3
ADD R3, R3, #1
ADD R2, R2, R3
ST R7, storeR7
JSR DIV10 ; output: R2. Divides R2 by 10
LD R7, storeR7

ADD R2, R2, #0
BRp LOOP6

; check if the last digit of the number was 0
ST R7, storeR7
LD R7, lastDigIs0
BRp notLoop

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

LD R7, storeR7

;check if this is the last number and print space or enter accordingly
LD R2, INITR2
NOT R3, R2
ADD R3, R3, #1
ADD R3, R1, R3
BRz DONE1
LD R0, asciiPrintSpace
PUTC

RET

DONE1
AND R0, R0, #0
ADD R0, R0, #10
PUTC

RET

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

;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DIVMOD

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

asciiZero .FILL #-48
asciiSpace .FILL #-32
STORER2 .BLKW #1
asciiPrintZero .FILL x0030 
asciiPrintSpace .FILL x0020
MOD4 .BLKW #1
div3 .BLKW #1
div4 .BLKW #1
div5 .BLKW #1
INITR2 .BLKW #1
storeR7 .BLKW #1
digs .BLKW #1
storeR6 .BLKW #1
trailing0s .BLKW #1
lastDigIs0 .BLKW #1
firstNumberDone .BLKW #1
temp .BLKW #1
everythingR1 .BLKW #1
everythingR2 .BLKW #1
everythingR3 .BLKW #1
everythingR4 .BLKW #1
everythingR5 .BLKW #1
everythingR6 .BLKW #1
.END