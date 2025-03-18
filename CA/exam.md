![[Pasted image 20250115142440.png]]
its a multiplexer

μαθε πως να κανεις αυτην
![[Pasted image 20250115143506.png]]![[Pasted image 20250115143509.png]]


!!!!!!!!!!!!!!!!!!!!!!!!!
BRzp #2
ADD R0 R0 #2
ADD R0 R0 #3
TRAP x25

BR #2 will move 3 lines down. starts counting from 0. the BR will move the program to TRAP x25
BR#-1 calls itself

!!! note that if you keep incrementing to overvflow, you eventually get negative number.

registers can fit up to 16 bits (0-15)

adding something by itself means shifting its bits one position to the left. (because you do something * 2)

σε hex μετα το 3009 ειναι το 300A και μετα το 300F ειναι το 3010 και μετα 3011

.FILL will be represented as a plain value (δεν θα μπορεις να το αντιστοιχησεις σε κανενα opcode)

.BLKW is just 0s

MAR will have the instruction

το bit 15 ειναι το πρωτο οχι το 0:
![[Pasted image 20250118204535.png]]

make sure you can do this:
![[Pasted image 20250118232256.png]]
![[Pasted image 20250118232252.png]]

addressability of 1 byte: each memory location has 1 byte

1 KB = 2^10 bytes = 1024

in FSMs, when the input sequence breaks, you fall back to the closest match. for example, if you are on D and  input is T  then you will not start from the beginning (A) but you will continue from B. so now you output 0 and you are on C:
![[Pasted image 20250119005405.png]]