                .ORIG x3000

; We zero R7 (R1) and load into R1 (R3) the ASCII offset (#-48)

        AND   R7,R7,#0
        LD    R1,OFFSETASCII

GETSIZE
        GETC
        PUTC
        ADD  R0,R0,R1        ; add the ASCII offset
        BRn  SIZEFOUND
        ADD  R7,R7,R7        ; double R7
        ADD  R6,R7,R7        ; R6 = R7 + R7
        ADD  R6,R6,R6        ; R6 <<= 1 again
        ADD  R7,R7,R6        ; R7 += R6
        ADD  R7,R7,R0        ; R7 += last input digit
        BR GETSIZE

SIZEFOUND
        LEA  R6,LENINPUT     ; store the size in LENINPUT
        STR  R7,R6,#0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Read characters into ALLDATA and print digits if numeric.

        LEA  R6,ALLDATA      ; Start pointer to the big input buffer

READALL
        GETC             ; get 1 char
        STR  R0,R6,#0        ; store in ALLDATA
        ADD  R2,R0,R1        ; R2 <- R0 + (#-48) => check if digit
        BRn  COUNTNUM
        PUTC             ; if digit, echo it
        ADD  R6,R6,#1        ; move pointer
        BR READALL

STOPINPUT
        LD   R0,NL
        PUTC
        ; All data is now in ALLDATA
        LEA  R6,ARRAYPOS
        AND  R7,R7,#0
        STR  R7,R6,#0


; Proceed to “prime” checking routine for each numeric entry.

ISPRIME
        LEA  R6,LENINPUT
        LD   R7,LENINPUT
        ADD  R7,R7,#-1
        BRn  ENDPRIME
        STR  R7,R6,#0

        LEA  R7,ALLDATA
        LD   R6,ARRAYPOS
        ADD  R7,R7,R6        ; R7 points at current input character
        LD   R3,OFFSETASCII  ; (previous R5)
        AND  R1,R1,#0        ; (accumulator, or R3)

GETNUMVAL
        LDR  R0,R7,#0
        ADD  R7,R7,#1
        ADD  R4,R0,R3        ; R4 used temporarily (R6=R0+TOINT)
        BRn  NUMVALFOUND
        BR PRINTADD
        RETURN1
        ADD  R1,R1,R4
        ADD  R1,R1,R0
        BR GETNUMVAL

NUMVALFOUND
        LEA  R6,ALLDATA
        NOT  R6,R6
        ADD  R6,R6,#1
        ADD  R7,R7,R6
        LEA  R6,ARRAYPOS
        STR  R7,R6,#0

        ADD  R7,R1,#0        ; R7 has the numeric value
        
; Now check if R7 is prime by checking if R7 == 2, else try dividing

        ADD  R6,R7,#0
        AND  R6,R6,#1
        BRz  CHKTWO
        AND  R6,R6,#0
        ADD  R6,R6,#3

LOOPSQ
        ADD  R1,R6,#0
        ADD  R2,R6,#-1
FIND_SQ
        ADD  R1,R1,R6
        ADD  R2,R2,#-1
        BRp  FIND_SQ
        BR CHECKPRIME
RT

FIND_REST
        ADD  R1,R1,R2
        BRp  FIND_REST
        BRz  DIVISCASE
        ADD  R6,R6,#2
        BR LOOPSQ

ENDPRIME
        HALT

        BR SK
CHECKPRIME
        NOT  R1,R1
        ADD  R1,R1,#1
        ADD  R1,R1,R7
        BRn  PRIMEGOT
        ADD  R1,R7,#0
        ADD  R2,R6,#0
        NOT  R2,R2
        ADD  R2,R2,#1
SK
COUNTNUM
        ADD  R6,R6,#1
        ADD  R7,R7,#-1
        BRnz STOPINPUT
        PUTC
        BR READALL

CHKTWO
        AND  R6,R6,#0
        ADD  R6,R6,#-2
        ADD  R6,R7,R6
        BRz  PRIMEGOT
        AND  R6,R6,#0
        ADD  R6,R6,#2
        BR DIVISCASE

BR SKIP1
PRINTADD
        PUTC
        ADD  R0,R0,R3
        ADD  R1,R1,R1
        ADD  R4,R1,R1
        ADD  R4,R4,R4
        BR RETURN1
SKIP1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; If we find a divisor => not prime

DIVISCASE
        LEA  R0,MSGNOTPRIME
        PUTS
        LEA  R3,FACTOR       ; (previously R5=DIVISOR)
        ADD  R7,R6,#0        ; R7 was divisor
        AND  R6,R6,#0
        AND  R1,R1,#0
        ADD  R1,R1,#-10
        ADD  R2,R6,#10
        AND  R4,R4,#0

DIV_LOOP
        ADD  R7,R7,R1
        BRn  DONE_DIV
        ADD  R6,R6,#1
        BR DIV_LOOP

DONE_DIV
        BR ADD1
        RET2
        BRnz DONE_COPY
        AND  R6,R6,#0
        BR DIV_LOOP

DONE_COPY
        ADD  R3,R3,#-1
        LD   R2,OFFSETA2C
SHOWDIGITS
        ADD  R4,R4,#-1
        BRn  DONEPRINT
        LDR  R0,R3,#0
        ADD  R0,R2,R0
        PUTC
        ADD  R3,R3,#-1
        BR SHOWDIGITS

DONEPRINT
        LD   R0,NL
        PUTC
        BR ISPRIME

PRIMEGOT
        LEA  R0,MSGPRIME
        PUTS
        BR ISPRIME
        
        BR SKIP2
ADD1
        ADD  R4,R4,#1
        ADD  R7,R7,R2
        STR  R7,R3,#0
        ADD  R3,R3,#1
        ADD  R7,R6,#0
        BR RET2
SKIP2


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  DATA SECTION

OFFSETASCII .FILL #-48
OFFSETA2C .FILL #48
FACTOR .BLKW #8
NUMINPUT .BLKW #8
LENINPUT .BLKW #2
TEMP .BLKW #1
ARRAYPOS .BLKW #2
NL .FILL #10
MSGPRIME  .STRINGZ " is a prime number\n"
MSGNOTPRIME .STRINGZ " is not a prime number as it is divisible by "
ALLDATA .BLKW #3000

.END