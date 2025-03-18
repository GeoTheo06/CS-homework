.ORIG x3000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; READS 3x3 ARRAY

LEA R6, arr ; R6 is pointer to arr1

AND R5, R5, #0
ADD R5, R5, #9 ; R5 is counter to the elements of the array left

LOOP_READ_ARR

JSR READ_NUM ; R2 holds the current number

;store the number in the array and increment the pointer
STR R2, R6, #0
ADD R6, R6, #1
ADD R5, R5, #-1 ;decrement counter
BRp LOOP_READ_ARR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;calculate det2erminant

; ------------------------------------------------------------
; det2 = m[0] * (m[4]*m[8] - m[7]*m[5])
; ------------------------------------------------------------

; --- Compute (m[4] * m[8]) ----------------------------------
LEA   R0, arr
ADD   R0, R0, #4   ; R0 -> arr[4]
LDR   R0, R0, #0   ; R0 = m[4]

LEA   R1, arr
ADD   R1, R1, #8   ; R1 -> arr[8]
LDR   R1, R1, #0   ; R1 = m[8]

JSR   MULT         ; R2 = m[4] * m[8]


AND R5, R5, #0;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;ST R2, det2     ; store partial result in det2
ADD R5, R5, R2

; --- Compute (m[7] * m[5]) ----------------------------------
LEA   R0, arr
ADD   R0, R0, #7   ; R0 -> arr[7]
LDR   R0, R0, #0   ; R0 = m[7]

LEA   R1, arr
ADD   R1, R1, #5   ; R1 -> arr[5]
LDR   R1, R1, #0   ; R1 = m[5]

JSR   MULT         ; R2 = m[7] * m[5]

; --- Subtract (m[7]*m[5]) from current partial (stored in 'det2')
NOT   R2, R2       ; negate R2
ADD   R2, R2, #1   ; two’s complement of R2
AND R3, R3, #0;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;LD    R3, det2      ; load det2
ADD R3, R5, #0
ADD   R3, R3, R2   ; (m[4]*m[8]) - (m[7]*m[5])
ST    R3, det2      ; store back into det2

; --- Multiply the above by m[0] -----------------------------
LEA   R0, arr
ADD   R0, R0, #0   ; R0 -> arr[0]
LDR   R0, R0, #0   ; R0 = m[0]

LD    R1, det2      ; R1 = (m[4]*m[8] - m[7]*m[5])

JSR   MULT         ; R2 = m[0] * {...}
ST    R2, det2      ; det2 now holds first part

; ------------------------------------------------------------
; det2 -= m[1] * (m[3]*m[8] - m[5]*m[6])
;      = det2 - m[1] * {...}
; ------------------------------------------------------------

; --- Compute (m[3] * m[8]) ----------------------------------
LEA   R0, arr
ADD   R0, R0, #3   ; R0 -> arr[3]
LDR   R0, R0, #0   ; R0 = m[3]

LEA   R1, arr
ADD   R1, R1, #8   ; R1 -> arr[8]
LDR   R1, R1, #0   ; R1 = m[8]

JSR   MULT         ; R2 = m[3] * m[8]
ST    R2, temp2      ; store intermediate in tmp

; --- Compute (m[5] * m[6]) ----------------------------------
LEA   R0, arr
ADD   R0, R0, #5   ; R0 -> arr[5]
LDR   R0, R0, #0   ; R0 = m[5]

LEA   R1, arr
ADD   R1, R1, #6   ; R1 -> arr[6]
LDR   R1, R1, #0   ; R1 = m[6]

JSR   MULT         ; R2 = m[5] * m[6]

; --- Subtract (m[5]*m[6]) from tmp (which had m[3]*m[8])
LD    R3, temp2
NOT   R2, R2       ; negate R2
ADD   R2, R2, #1   ; two's complement
ADD   R3, R3, R2   ; (m[3]*m[8]) - (m[5]*m[6])
ST    R3, temp2      ; store back into tmp

; --- Multiply by m[1] ---------------------------------------
LEA   R0, arr
ADD   R0, R0, #1   ; R0 -> arr[1]
LDR   R0, R0, #0   ; R0 = m[1]

LD    R1, temp2      ; R1 = (m[3]*m[8] - m[5]*m[6])

JSR   MULT         ; R2 = m[1] * {...}

; --- Subtract from det2 --------------------------------------
; det2 = det2 - R2
NOT   R2, R2
ADD   R2, R2, #1   ; R2 = -R2
LD    R3, det2
ADD   R3, R3, R2
ST    R3, det2      ; updated det2


; ------------------------------------------------------------
; det2 += m[2] * (m[3]*m[7] - m[4]*m[6])
;      = det2 + m[2] * {...}
; ------------------------------------------------------------

; --- Compute (m[3] * m[7]) ----------------------------------
LEA   R0, arr
ADD   R0, R0, #3   ; R0 -> arr[3]
LDR   R0, R0, #0   ; R0 = m[3]

LEA   R1, arr
ADD   R1, R1, #7   ; R1 -> arr[7]
LDR   R1, R1, #0   ; R1 = m[7]

JSR   MULT         ; R2 = m[3] * m[7]
ST    R2, temp2      ; store intermediate in tmp

; --- Compute (m[4] * m[6]) ----------------------------------
LEA   R0, arr
ADD   R0, R0, #4   ; R0 -> arr[4]
LDR   R0, R0, #0   ; R0 = m[4]

LEA   R1, arr
ADD   R1, R1, #6   ; R1 -> arr[6]
LDR   R1, R1, #0   ; R1 = m[6]

JSR   MULT         ; R2 = m[4] * m[6]

; --- Subtract (m[4]*m[6]) from tmp (which had m[3]*m[7])
LD    R3, temp2
NOT   R2, R2
ADD   R2, R2, #1
ADD   R3, R3, R2   ; (m[3]*m[7]) - (m[4]*m[6])
ST    R3, temp2

; --- Multiply by m[2] ---------------------------------------
LEA   R0, arr
ADD   R0, R0, #2   ; R0 -> arr[2]
LDR   R0, R0, #0   ; R0 = m[2]

LD    R1, temp2      ; R1 = (m[3]*m[7] - m[4]*m[6])
JSR   MULT         ; R2 = m[2] * {...}

; --- Add to det2 ---------------------------------------------
LD    R3, det2
ADD   R3, R3, R2   ; det2 + R2
ST    R3, det2

LD R2, det2
ST R2, det

arr .BLKW #9
det2 .BLKW #1
temp2 .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; calculate and print array
; minv[0] = (m[4] * m[8] - m[7] * m[5]) * det
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0


ADD R0, R0, #4
ADD R1, R1, #8
ADD R2, R2, #7
ADD R3, R3, #5

JSR CALC_INV

LD R0, space
PUTC
AND R0, R0, #0
;minv[1] = (m[2] * m[7] - m[1] * m[8]) * invdet;
ADD R0, R0, #2
ADD R1, R1, #7
ADD R2, R2, #1
ADD R3, R3, #8

JSR CALC_INV

LD R0, space
PUTC
AND R0, R0, #0
;minv[2] = (m[1] * m[5] - m[2] * m[4]) * invdet;
ADD R0, R0, #1
ADD R1, R1, #5
ADD R2, R2, #2
ADD R3, R3, #4

JSR CALC_INV

LD R0, enter
PUTC
AND R0, R0, #0
;minv[3] = (m[5] * m[6] - m[3] * m[8]) * invdet;
ADD R0, R0, #5
ADD R1, R1, #6
ADD R2, R2, #3
ADD R3, R3, #8

JSR CALC_INV

LD R0, space
PUTC
AND R0, R0, #0
;minv[4] = (m[0] * m[8] - m[2] * m[6]) * invdet;
ADD R0, R0, #0
ADD R1, R1, #8
ADD R2, R2, #2
ADD R3, R3, #6

JSR CALC_INV

LD R0, space
PUTC
AND R0, R0, #0
;minv[5] = (m[3] * m[2] - m[0] * m[5]) * invdet;
ADD R0, R0, #3
ADD R1, R1, #2
ADD R2, R2, #0
ADD R3, R3, #5

JSR CALC_INV

LD R0, enter
PUTC
AND R0, R0, #0
;minv[6] = (m[3] * m[7] - m[6] * m[4]) * invdet;
ADD R0, R0, #3
ADD R1, R1, #7
ADD R2, R2, #6
ADD R3, R3, #4

JSR CALC_INV

LD R0, space
PUTC
AND R0, R0, #0
;minv[7] = (m[6] * m[1] - m[0] * m[7]) * invdet;
ADD R0, R0, #6
ADD R1, R1, #1
ADD R2, R2, #0
ADD R3, R3, #7

JSR CALC_INV

LD R0, space
PUTC
AND R0, R0, #0
;minv[8] = (m[0] * m[4] - m[3] * m[1]) * invdet;
ADD R0, R0, #0
ADD R1, R1, #4
ADD R2, R2, #3
ADD R3, R3, #1

JSR CALC_INV

LD R0, enter
PUTC

HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;input: one, two, three, four
CALC_INV
ST R7, storeR7

ST R0, one
ST R1, two
ST R2, three
ST R3, four

; R3 will be used to load the values from the BLKWs
LD R3, one

LEA   R0, arr
ADD   R0, R0, R3   ; R0 -> arr[R3]
LDR   R0, R0, #0   ; dereference R0

LD R3, two

LEA   R1, arr
ADD   R1, R1, R3   ; R1 -> arr[R3]
LDR   R1, R1, #0   ; dereference R1

JSR   MULT         ; input: R0, R1. output: R2

ST R2, inv ; stores partial output to inv

LD R3, three

LEA   R0, arr
ADD   R0, R0, R3   ; R0 -> arr[R3]
LDR   R0, R0, #0   ; dereference R0

LD R3, four

LEA   R1, arr
ADD   R1, R1, R3   ; R1 -> arr[R3]
LDR   R1, R1, #0   ; dereference R1

JSR   MULT         ; input: R0, R1. output: R2

LD R0, inv ; get the current value of inv

NOT R2, R2
ADD R2, R2, #1 ; negate R2

ADD R0, R0, R2 ; subtract R2 from R0

LD R1, det ; load det

JSR   MULT         ; input: R0, R1. output: R2
AND R3, R3, #0
ADD R3, R3, R2
JSR PRINT ; prints R3

AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0

LD R7, storeR7
RET


one .BLKW #1
two .BLKW #1
three .BLKW #1
four .BLKW #1
storeR7 .BLKW #1
det .BLKW #1

inv .BLKW #1
space   .FILL x20
enter .FILL x0A








PRINT; input R3
ST R0, s0
ST R1, s1
ST R2, s2
ST R3, s3
ST R4, s4
ST R5, s5
ST R6, s6

; check if R3 negative:
ADD R3, R3, #0
BRn nigative

BR skipNigative
nigative
NOT R3, R3
ADD R3, R3, #1

LD R0, DASH    ; Load ASCII value of dash into R0
PUTC
skipNigative

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

DASH .FILL x2D


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


MULT ;multiplies 2 numbers. input R0, R1, output: R2
ST R0, s0
ST R1, s1
ST R3, s3
ST R4, s4
ST R5, s5
ST R6, s6


AND R3, R3, #0 ; will indicate whether result is positive or negative (-1 positive, 0 negative, 1 positive)

; check if R0 negative, and make it positive if so:

AND R2, R2, #0  ; R2 used temporarily
ADD R2, R2, R0
BRn negativeR0

BR skipNegativeR0
negativeR0
NOT R0, R0
ADD R0, R0, #1
ADD R3, R3, #1
skipNegativeR0


; check if R1 negative, and make positive if so:

AND R2, R2, #0  ; R2 used temporarily
ADD R2, R2, R1
BRn negativeR1

BR skipNegativeR1
negativeR1
NOT R1, R1
ADD R1, R1, #1
ADD R3, R3, #1
skipNegativeR1


; making R0 be bigger than R1
NOT R2, R1 
ADD R2, R1, #1 ; R2 is negative R1
ADD R2, R0, R2
BRzp itsBigger

ST R0, temp
AND R0, R0, #0
ADD R0, R1, #0 ; put R1 to R0
LD R1, temp ; put R0 to R1

itsBigger

AND R2, R2, #0

ADD R1, R1, #0 ; check if R1 is not 0
BRp LOOP_MULT

BR skipLoopMult
LOOP_MULT
ADD R2, R2, R0
ADD R1, R1, #-1
BRp LOOP_MULT
skipLoopMult

;check if result is positive or nagative:
ADD R3, R3, #0
BRz resNegative

BR skipResNegative
resNegative
NOT R2, R2
ADD R2, R2, #1
skipResNegative

LD R0, s0
LD R1, s1
LD R3, s3
LD R4, s4
LD R5, s5
LD R6, s6
RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; reads a number and stores it in R2.
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

s0 .BLKW #1
s1 .BLKW #1
s2 .BLKW #1
s3 .BLKW #1
s4 .BLKW #1
s5 .BLKW #1
s6 .BLKW #1
temp .BLKW #1
digits .BLKW 10
printAscii0 .FILL x0030
.END