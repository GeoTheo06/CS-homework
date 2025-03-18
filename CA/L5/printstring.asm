.ORIG x3000
;input 
ADD R3, R3, #5

LD R0, asciiZero
ADD R0, R0, R3
PUTC
LEA R0, PRINTNOTPRIME
PUTS 

HALT
asciiZero .FILL x0030 
PRINTNOTPRIME .STRINGZ " is not prime because of "
.END
