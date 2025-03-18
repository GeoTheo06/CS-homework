.ORIG x3000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; READS 3x3 ARRAY

LEA R6, arr1 ; R6 is pointer to arr1

AND R5, R5, #0
ADD R5, R5, #9 ; R5 is counter to the elements of the array left

LOOP_READ_ARR

JSR READ_NUM ; R2 holds the current number

;store the number in the array and increment the pointer
STR R2, R6, #0
ADD R6, R6, #1
ADD R5, R5, #-1 ;decrement counter
BRp LOOP_READ_ARR


; now time for arr2
AND R2, R2, #0 ;reset

LEA R6, arr2 ; R6 is pointer to arr2

AND R5, R5, #0
ADD R5, R5, #9 ; R5 is counter to the elements of the array left

LOOP_READ_ARR2

JSR READ_NUM ; R2 holds the current number

;store the number in the array and increment the pointer
STR R2, R6, #0
ADD R6, R6, #1
ADD R5, R5, #-1 ;decrement counter
BRp LOOP_READ_ARR2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; END OF READING ARRAYS

; time to multiply arrayssss less gooo 
AND R0, R0, #0 
ADD R0, R0, #1 ; i

LOOP1

AND R1, R1, #0
ADD R1 R1, #1 ; j


LOOP2

AND R2, R2, #0
ADD R2, R2, #1 ; k

AND R6, R6, #0 ; will be used for adding the multiplications

LOOP3

; i want to convert i, k so i change R1 with R2:
ST R1, temp
AND R1, R1, #0
ADD R1, R1, R2 ; put R2 in R1
LD R2, temp ; put R1 in R2

JSR converter ; converts (i, j) index to row major index using the formula x=(i-1)*3 + j
;input: R0=i, R1=j
;output: R5

ADD R5, R5, #-1 ; making R5 0 based

;change back R1 and R2
ST R1, temp
AND R1, R1, #0
ADD R1, R1, R2 ; put R2 in R1
LD R2, temp ; put R1 in R2


LEA R4, arr1 ; points to array
ADD R4, R4, R5 ; now R4 has the address in the index (i,j)
LDR R4, R4, #0    ; Dereference the address in R4 to get the value
ST R4, ik ; store the value in the (i,k) index




; i want to convert k, j so I need to change R0 with R2:
ST R0, temp
AND R0, R0, #0
ADD R0, R0, R2 ; put R2 in R1
LD R2, temp ; put R1 in R2

JSR converter ; converts (i, j) index to row major index using the formula x=(i-1)*3 + j
;input: R0=i, R1=j
;output: R5

ADD R5, R5, #-1 ; making R5 0 based

;change back R0 and R2
ST R0, temp
AND R0, R0, #0
ADD R0, R0, R2 ; put R2 in R1
LD R2, temp ; put R1 in R2

LEA R4, arr2 ; points to array
ADD R4, R4, R5 ; now R4 has the address of the value in the index (k,j)
LDR R4, R4, #0    ; Dereference the address in R4
ST R4, kj ; store the value in the (k,j) index



; multiply values in i,j and k,j indexes
JSR MULT ; output: R3

ADD R6, R6, R3 ; R6 adds the 3 multiplications of each k.

ADD R2, R2, #1
AND R5, R5, #0
ADD R5, R2, #-3 ; R5 used temporarily
BRnz LOOP3


AND R3, R3, #0
ADD R3, R3, R6 ; just put R6 to R3 to print it

JSR PRINT ; prints R3


ST R0, s0 ; storing R0 (i) to print the space

; if j(R1) == 3 print \n else print space.

AND R5, R5, #0
ADD R5, R1, #-3 ; R5 used temporarily
BRz printEnter

LD R0, space
PUTC

BR skipPrintEnter
printEnter

LD R0, enter
PUTC

skipPrintEnter

LD R0, s0 ; loading back R0

ADD R1, R1, #1
AND R5, R5, #0
ADD R5, R1, #-3
BRnz LOOP2


ADD R0, R0, #1
AND R5, R5, #0
ADD R5, R0, #-3
BRnz LOOP1


HALT












PRINT; input R3
ST R0, s0
ST R1, s1
ST R2, s2
ST R3, s3
ST R4, s4
ST R5, s5
ST R6, s6

LEA R4, digits
AND R6, R6, #0 ; R6 used to count the number of digits to keep track of the index in the digits array

DIGIT_LOOP

; put the number's digits reversed in a buffer


; i will mod 10 the number to get the last digit

AND R2, R2, #0 ; counter which will be used for the div operation
AND R0, R0, #0; will increment by multiples of 10

MOD_LOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    ERROR  HERE
ADD R1, R3, R0 ; R1 used temporarily to check if we have reached the multiple of 10 we want
BRn exit_mod_loop
BRz exit_mod_10mult
ADD R2, R2, #1
ADD R0, R0, #-10

BR MOD_LOOP

exit_mod_loop
; in case last digit is not 0 (not multiple of 10)
ADD R0, R0, #10
ADD R2, R2, #-1
;

exit_mod_10mult

;R0 is already negative
ADD R1, R3, R0 ; R1 holds the last digit of the number

; store last digit to buffer
STR R1, R4, #0
ADD R4, R4, #1

ADD R6, R6, #1 ; adding a digit to R6

AND R3, R3, #0 ; making R3 0 because i will change it
ADD R3, R3, R2 ; R3 div 10 (=R2) so that in the next iteration we get the next digit.
BRp DIGIT_LOOP

ADD R6, R6, #-1 ; decrement R6 by one because it's index

; number has finished. there are no more digits.

; actual print
; now for example number 123 will be in the buffer like 3,2,1 and we have the position of 1 in R4
AND R5, R5, #0 ; R5 used temporarily
LD R5, printAscii0
PRINT_LOOP

LEA R0, digits
ADD R0, R0, R6
LDR R0, R0, #0 ; dereference
ADD R0, R0, R5 ;ascii value
PUTC
ADD R6, R6, #-1
BRzp PRINT_LOOP

LD R0, s0
LD R1, s1
LD R2, s2
LD R3, s3
LD R4, s4
LD R5, s5
LD R6, s6
RET

MULT ;multiplies 2 numbers. output: R3
ST R0, s0
ST R1, s1
ST R2, s2
ST R4, s4
ST R5, s5
ST R6, s6

LD R0, ik
LD R1, kj

; making R0 be bigger than R1
NOT R4, R1 
ADD R4, R1, #1 ; R4 has negative R1
ADD R4, R0, R4
BRzp itsBigger

ST R0, temp
AND R0, R0, #0
ADD R0, R1, #0 ; put R1 to R0
LD R1, temp ; put R0 to R1

itsBigger

AND R3, R3, #0

ADD R1, R1, #0 ; check if R1 is not 0
BRp LOOP_MULT

BR skipLoopMult
LOOP_MULT
ADD R3, R3, R0
ADD R1, R1, #-1
BRp LOOP_MULT
skipLoopMult

LD R0, s0
LD R1, s1
LD R2, s2
LD R4, s4
LD R5, s5
LD R6, s6
RET

converter ; converts (i, j) index to row major index using the formula x=(i-1)*3 + j
;input: R0=i, R1=j
;output: R5

ST R0, s0
ST R1, s1
ST R2, s2
ST R3, s3
ST R4, s4
ST R6, s6

ADD R0, R0, #-1

;multiply R0 by 3
AND R2, R2, #0
ADD R2, R2, #2 ; R2 is temporary counter

AND R3, R3, #0
ADD R3, R3, R0 ; R3 temporarily holds R0
LOOP_3
ADD R0, R0, R3
ADD R2, R2, #-1
BRp LOOP_3

AND R5, R5, #0
ADD R5, R0, R1

LD R0, s0
LD R1, s1
LD R2, s2
LD R3, s3
LD R4, s4
LD R6, s6
RET



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; reads a number and stores it in R2.
READ_NUM

;store registers
ST R0, s0
ST R1, s1
ST R3, s3
ST R4, s4
ST R5, s5
ST R6, s6

GETC
PUTC

;convert number to decimal
LD R1, minFortyEight ; R1 is used temporarily
ADD R0, R0, R1

AND R2, R2, #0 ; R2 will hold the total number
ADD R2, R2, R0

; keep reading until the result is not negative (if its negative it means that it was either enter (10) or space (32) (both are lower than 48))
LOOP_READ_NUM

GETC
PUTC

;convert number to decimal
LD R1, minFortyEight ; R1 is used temporarily
ADD R0, R0, R1
BRn EXIT_LOOP_READ_NUM

; before adding R0 to R2, multiply R2 by 10.
AND R3, R3, #0
ADD R3, R3, #9 ; R3 is counter
ADD R4, R2, #0 ; temporarily holds R2
mult10
ADD R2, R2, R4 ; increment R2 by one time
ADD R3, R3, #-1 ; decrement counter
BRp mult10

; now add R0 to R2
ADD R2, R2, R0

BR LOOP_READ_NUM

EXIT_LOOP_READ_NUM

;load registers
LD R0, s0
LD R1, s1
LD R3, s3
LD R4, s4
LD R5, s5
LD R6, s6

RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


minFortyEight .FILL #-48
arr1 .BLKW #9
arr2 .BLKW #9
s0 .BLKW #1
s1 .BLKW #1
s2 .BLKW #1
s3 .BLKW #1
s4 .BLKW #1
s5 .BLKW #1
s6 .BLKW #1
temp .BLKW #1
ik .BLKW #1
kj .BLKW #1
digits .BLKW 10
space   .FILL x20
enter .FILL x0A
printAscii0 .FILL x0030
.END