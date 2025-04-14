![[Pasted image 20250331200219.png]]

στα taylor polynomials οταν δεν ειναι στο 0 τοτε δεν γραφεις x και x^2 αλλα γραφεις x-a και (x-a)^2

για το argz στο 2ο τεταρτημοριο ειναι π + arctanb/a και στο 3ο ειναι -p + arctanb/a

(το λαθος εγινε σε complex numbers) μην ξεχνας οτι το θ ειναι γωνια και οταν θες να βρεις τις λυσεις μιας εξισωσης, δεν βαζεις κατευθειαν x = θ αλλα x =  θ + 2κπ

για καποιο περιεργο λογο κανεις το λαθος οταν εχει trig sub, στην αντικατασταση τιμων παιρνεις τις πρωτς. πχ αν αντικαθιστας cosθ στο 0, θα παρεις την π/2 (ενω ηταν valid και 3π/2 κλπ)

για integration μην ξεχνας να σκεφτεσαι subsitution. αλλα να το σκεφτεσαι οντως σαν πιθανοτητα οπως ολα τα αλλα (πχ προσπαθησε οντως να δεις πως θα εβγαινε με substitution και αν κανουν cancel out)

ξεχνας οτι ποσοτητα^2 = 1 <=> ποσοτητα = +-1

χρησιμο για taylor: μην ξεχνας οτι το $x^a$ με x<1 μικραίνει exponentially όσο μεγαλώνει το α

something like $x/\sqrt{1-x^2}$ could be simple substitution. dont try to do any of that weird stuff without checking first 

((f(x))^-1)' = 1/f'(x) αποδεικνυεται ευκολα


target/codomain: 
the set of all possible values that the function could potentially output, whether or not every value in that set is actually achieved by the function.

Normal Line = κάθετη στην tangent line

Παντού λες continuous on [x1, x2] and differential on (x1,x2)

To find the inverse of a function you solve f(x) = y for x.

![[Pasted image 20250202144210.png]]

if you differentiate distance, you get speed (dx/dt)
when distance gets smaller as time goes on, then the speed obviously has to be negative


καθε συνεχης συναρτηση εχει παραγουσα (δηλ. F)

in differentiation when you have powers of sin,cos,tan,sec you use identities like $tan^2x$ = $sec^2x$ - 1 (lesson VIII γενικα εχει πολλους ανωμαλους κανονες)
/1
$\sqrt{a^2 - x^2}$ substitution: x = asinθ identity: 1-$sin^2θ$ = $cos^2θ$

$\sqrt{a^2 + x^2}$ substitution: x = atanθ identity: 1+$tan^2θ$ = $sec^2θ$

$\sqrt{x^2 - a^2}$ substitution: x = asecθ identity: $sec^2θ$ - 1 = $tan^2θ$

![[Pasted image 20250316222134.png]]



in long division the remainder is the remainder/denominator because it is what's left without being divided

![[Pasted image 20250306194019.png]]
πανω στον αριθμητη δεν ειναι παντα A. μπορει να ειναι Ax+B κλπ αν το x του παρονομαστη του ειναι ^2 κλπ.
Εντωμεταξύ, όταν έχει φτάσει στην εξίσωση, μπορείς να θέσεις το x οποία βολική τιμή θες για να μηδενιστούν κάποιοι άγνωστοι (πχ Β και C) και να μπορείς να βρεις τον καθένα (πχ Α)

convergent integral = An impoproper integral (integral that goes to infinity) if the corresponding limit exists. 
divergent integral = An impoproper integral (integral that goes to infinity) if the corresponding limit doesn't exist.

μπορεις να κανεις derive τις τριγωνομετρικες ταυτοτητες sin(A+B) και cos(A+B) χρησιμοποιώντας imaginary numbers rotation:
https://www.youtube.com/watch?v=5PcpBw5Hbwo
### conversion of Riemman sum to integral and vice versa:
$\int_{a}^{b} f(x)Δx$ = $lim_{n->inf} Σ_{i=1}^{n} f(x_{i^*})Δx$

$Δx_i$ = $b-a\over n$
$x_{i^*}$ = a + $i * Δx_i$ (it is each point) (btw this is the right riemman sum. the left is: instead of i, put i-1)


partitions and riemman sums:
https://chatgpt.com/share/67bf488a-6174-800b-a65e-870205f62be5


![[Pasted image 20250301121828.png]]
προσοχή: μπορει να ειναι απλα το first fundamental theorem αλλα χρειαζεται να θεσεις u και επισης η (f(x^5))' ειναι συνθετη και πρεπει να παραγωγιστει αναλογα (f(x^5)' * 5x^4)

![[Pasted image 20250301181626.png]]

**reduction formulas:**
red. formula of $I_n$ = $\int sin^nx\,dx$:
![[Pasted image 20250306121923.png]]
αυτο βρεθηκε με integration by parts (sin^{n-1}x * sinx) και επιλυση εξισωσης

![[Pasted image 20250306123456.png]]


volume of a revolving solid around x:
$π*outerRadius^2 - π*innerRadius^2$
around a perpendicular line d:
$2π*(x-d)f(x)$


#### arclength:
![[Pasted image 20250319180941.png]]
arclength (or the length of a curve) is $\int_a^b \sqrt{1+f'(x)^2}dx$

which can be derived by pythagorean theorem:
$\sqrt{Δx^2 + Δy^2}$ = $\sqrt{1+(\frac{Δy}{Δx})^2}*Δx$ = $\sqrt{1+f'(x)^2}$


i skipped taylor theorem proof and taylors error

taylor 3ου βαθμου (πχ για sinx) ειναι x - $π^2/2!$

when exercise says to calculate integral with error < a, you can calculate the first values of the taylor polynomyal and stop when they get < a. you dont have to calculate with the error definition:
in taylor polynomials when calculating error term using the definition: when you have substituted n, x then you need to find c so you take the one that gives you the max error. (when E = max) (if E is negative you take the absolute value)

## TRIGONOMETRY:

![[IMG_20250207_125613.jpg]]


c^2 = a^2 + b^2 -2 a * b * cosx

Sinx = sinθ: 
x = 2kπ + θ or 2kπ + (π - θ)

Cosx = cosθ:
X = 2kπ +- θ

Tanx = tanθ  (cotx as well):
X = kπ + θ



sec = secant = 1/cos
csc = co-secant = 1/sin

arcsin(x) = sin^-1(x) != 1/sin(x)
so arsin(x) = y <=> sin(y) = x

sin(π/2 − θ) = cosθ
και γενικα αν μετακινεις την γωνια κατα καποιο πολλαπλασιο του π/2 τοτε αλλαζει το trigonometric function.

1 + (tanθ)^2 = (secθ)^2 απο το πυθαγορειο (διαιρεις με cos^2)


## some theorems and proofs:


![[Pasted image 20250307095134.png]]
![[Pasted image 20250307095136.png]]


![[Pasted image 20250225161924.png]]
![[Pasted image 20250225162145.png]]

![[Pasted image 20250226174906.png]]

![[Pasted image 20250302193020.png]]

![[Pasted image 20250226185027.png]]

![[Pasted image 20250226185159.png]]

![[Pasted image 20250226185551.png]]
![[Pasted image 20250226185601.png]]

ολοκληρωματα:


![[Pasted image 20250218143354.png]]


κοιταζω πρωτα αν το πανω ειναι η παραγωγος του κατω οποτε ειναι ln(...). Μετα κοιταζω αν γινεται καποια απλοποιηση. Μετα βλεπω αν ο βαθμος της πανω ειναι μεγαλυτερος ή  ίσος τους κατω, κανεις διαιρεση. Αν ο βαθμος του κατω ειναι μεγαλυτερος του πανω, κανεις:
![[Pasted image 20250209215329.png]]

![[Pasted image 20250209220402.png]]

![[Pasted image 20250209220520.png]]


![[Pasted image 20250209215549.png]]

![[Pasted image 20250209215732.png]]

![[Pasted image 20250209222458.png]]

![[Pasted image 20250209222717.png]]
