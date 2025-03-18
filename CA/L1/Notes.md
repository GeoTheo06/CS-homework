# Week 1

addition: 
1+1 = 0. carry = 1
1+0=1
1+1 + carry = 1. carry = 1

# signed bit
Just invert the most significant bit to get the negative
## 1s' complement 

Just invert all bits. Inefficient because there are two 0s. (1111111 and 0000000)

**To read negatives**, invert all bits and calculate the positive number. example:
00101 = 5
11010 = -5

## 2s' complement
**conversion:**
invert all bits and add +1 to the result. 
Example:
00101 (5) converts to 11010 + 1 = 11011 (-5)

## IEEE
- Convert the number to binary.
- Normalize it into the form 1.fraction * 2^Exponent (you have to count how many places you will move the dot) (αν ο αριθμος ειναι τυπου 0.κατι τοτε πρεπει να μεταφερεις την τελεια στο τελευταιο 0. οχι στο 1)
- to find the exponent, add the power of the exponent to 127 and convert the number to binary. this number is your exponent.
- Write the **Fraction** (mantissa) and fill up to 23 bits with 0s.
θα το κανεις λαθος: -0.028

If you want to convert something that has 0s in exponent, first try to convert a random decimal "0.something" number to IEEE to see how it works because converting 0.something from IEEE is weird. 

special cases: 

all 0: 0
all values in exponent 1 and in mantissa 0: infinity
all values in exponent 1 and in mantissa not 0: not a number.

## subtraction in binary
just negate the second operand and do addition

## Operation: Sign Extension
when you need to do addition/substraction with two numbers that dont have the same length of bits for positives you pad 0s and for negatives 1s:
To add/subtract, we need both numbers to have the same number of bits. 
What if one number is smaller?
Padding on the left with zero does not work for negatives:
1100 (-4) 
converts to:
00001100 (12, not —4) 

Instead, replicate the most significant bit (the sign bit):

4-bit 8-bit 0100 (+4) converts to: 00000100 (still +4) 
1100 (-4) converts to: 11111100 (still —4) 

## overflow
occurs if the sign is different.

![[Lecture2.pdf#page=32]]

![[Lecture2.pdf#page=]]

## Logic circuits
when you need to create logic circuits, (first of all break the problem into subproblems and then) just think when you need to make the case true. For example:
Design a circuit using logic gates to compare two 2-bit positive numbers. The output should be: (15 points)
• 10 if the first number is greater,
• 01 if the second number is greater,
• 00 if the two numbers are equal.

I split into the first bit and the second bit. the first output bit must be 1 only when the first number is greater. So i create a circuit for when the first number is greater. I start with xor because i split the task into when the first bits are the same and when they are not. If they are not the same then I make the output 1 when the first is the biggest (i just NOT the second bit and then AND both of them). If they are the same then i check for the second bits the same way. In the end I OR the 2 results because in case one of them outputs 1, it means that the above number is bigger. Then the same for the second output bit.