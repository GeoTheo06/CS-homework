function sumDigits(n: nat) : nat {

	if n < 10 then n else n%10 + sumDigits(n/10)

}


lemma {:induction false} div3Lemma(n: nat)
ensures sumDigits(n)%3 == n%3
{
	if (n < 10) {
	
	} else {
		div3Lemma(n/10);
	}
}