complexity
!!!! this is sqrtn because still its adding, not multiplying
```
int i = 0; s = 0;
while(s <= N){
	s += i;
	i++
}

summation s from  0 to N -> O(sqrt(N))
```

logn: ```i%2==0 ? i/2 : i-1```

μπορεις να cheatareis την πρωτη ασκηση. δοκιμασε τις τιμες 100 και 10.000 για να δεις ποσο γρηγορο ειναι το growth rate
```
#include <stdio.h>

#include <stdlib.h>

#include <math.h>

int main() {
    int N = 10000;  

    int sq = sqrt(N);
    printf("sq:%d", sq);

    int log = log2(N);
    printf("log:%d",log);

    int i = 0, s = 0;
    while (s < N) {
     i++;
     s += 2*i + 1;
    }
    printf("%d", i);

}
```


# Dafny

για dafny λυσε prob5, prob6 απο exams

το invariant βρισκεται ευκολα αν σκεφτεις τι πρεπει να βαλεις για να ισχυει πριν ξεκινησει το loop.
ΠΟΛΥ ΣΗΜΑΝΤΙΚΟ ΔΕΣ PROBLEM 5 2023 exams. Για να το λυσεις ετρεξες το recursion στο τετραδιο και παρατηρησες τη μορφη b*f(κατι, κατι) οποτε την εβαλες ως invariant (το b το εκανες r επειδη ειδες οτι το b* αυξανοταν και στο τελος αν το πολλαπλασιαζες με το f(κατι, κατι) εδινε το f(a,b))

παιρνεις το Invariant το ανοιγεις και προσπαθεις να το φερεις στην αρχικη μορφη βημα-βημα

γιατι ξεχνας καθε φορα οτι για τα recursions πρεπει να φτιαχνεις μια μεταβλητη για καθε αριθμο που αλλαζει και σε καθε iteration πρεπει να προσθετεις στην μεταβλητη την καινουρια και την παλια τιμη

για να βρεις το invariant ενος recursive function πρεπει να σκεφτεις τι να βαλεις ωστε να εχεις μια μεβλητη η οποια με καθε iteration να φτάνει ολο και πιο κοντα στο τελικο αποτελεσμα (x) και για να ισχυει το invariant θα πρεπει προφανως να βάλεις και τις υπολοιπες temporary μεταβλητες (pl*f(i) + mu). αν ειναι δυσκολο να βρεις τις υπολοιπες temporary μεταβλητες σκεψου πως θα μοιαζουν αν ανοιξεις το τελικο αποτελεσμα (f(n)) κατα ενα iteration (δλδ θα γινει 2*f(n/2) + 1)
πχ

```
ghost function f(x: nat): nat {
  if x < 2 then 1
  else if x % 2 == 0 then 2*f(x/2) + 1
}

  ensures x == f(n)
{
  var i := n;
  var pl := 1;
  var mu := 0;
  x := 0;

  while(i >= 2)
    invariant x + pl*f(i) + mu == f(n)
```

βαζε τα ορια στα loops γιατι καποιες φορες δεν δουλευει αλλιως (invariant 0 <= y <= b)

καποιες φορες χρειαζεται assert
πχ: χρειαζοταν assert επειδη η dafny δεν μπορουσε να κανει integer division.

    assert x*y + m == a*b;
    if (y%2 == 1) {
    	assert x*(y-1) + x + m == a*b;
    	y := y - 1;
    	assert x*y + x + m == a*b;
    	assert x*y + m + x == a*b;
    	m := m + x;
    	assert x*y + m == a*b;
    }
    !!!!!!!assert y%2==0;
    assert 2*x*y/2 + m == a*b;
    x := 2*x;
    assert x*(y/2) + m == a*b;
    y := y/2;
    assert x*y + m == a*b;
    }

δεν μπορεις να χρησιμοποιησεις ghost variables μεσα σε ενα method.

NOT SURE ABOUT THIS:
when you are given an example function (which you need to implement in another way) you can use it to verify the program. See lab 7 (hw7) exercise: recurrence

επισης δες το mystery (lab 7 exercise 6) αλλα δεν ειμαι σιγουρος αν μπορεις να βγαλεις την ασκηση χωρις να δοκιμασεις 100 τιμες

οταν δεις lemma κανεις εκεινες τις μαλακιες που ειδες στο divBy3, sumOfCubes και exponentiation lab 7. (μπορεσες να τα κανεις χωρις να τα καταλαβεις)

κανε το prob4 απο pleonasm

variant function = decreases

δες την 5 απο lab 8. ειναι καλη επειδη σου δειχνει πως η dafny χρειαζοταν αυτο invariant i%5 == n%5 για να μπορεσει να επιβεβαιωσει στο επομενο βημα οτι i <= n ωστε στο τελος να επιβεβαιωσεις οτι i=n. Δεν μπορουσες να το βρεις με τιποτα.

# C LANGUAGE

didnt understand "arithmetic expressions" lab10. οταν χρειαζεται να κανεις alternate βαζεις calls το ενα πανω απο το αλλο? ολοκληρο το γαμημενο lab 10. (εννοω το parenthesis, arithmetic expressions και updown )

Don't forget the & in scanf. Strings don't take &

//reads digit by digit
scanf("%1d", &grid[i][j]);

STRING

strlen(const char \*str)
Returns the length of a string.

strcat(char *dest, const char *src)
Concatenates two strings by appending src to dest.

strstr(const char *haystack, const char *needle)
Finds the first occurrence of substring needle in string haystack

Dynamic Memory Allocation
int _arr = (int _)malloc(10 _ sizeof(int));
arr = (int _)realloc(arr, 10 \* sizeof(int));
free(arr);

Lexicographic comparison of s1 and s2:
int strcmp(char *s1, char *s2);
Returns a negative value if s1 is less than s2, 0 if the strings are equal,
or a positive value if s1 is greater than s2.
Lexicographic comparison of the first n characters of s1 and s2:
int strncmp(char *s1, char *s2, int n);

# FILES

FILE *file = fopen ("data.in", "r"); // opens the file data.in for reading.
FILE *file = fopen ("result.out", "w"); // opens the file result.out for writing.
fprintf (file, "pi=%f\n", 3.14159);
fclose(file);

int status = fscanf (file, "%d", &n);
while (status != EOF) {} // end of file

ungetc(FILE \*f, int c) // pushes c back to the input file

quick sort σε c:

```
int cmp_int(const void *x, const void *y) {
    int xx = *(int *)x;
    int yy = *(int *)y;
    if (xx < yy) return -1;
    if (xx > yy) return 1;
    return 0;
}


qsort(arr2, n2, sizeof(int), cmp_int);
```
