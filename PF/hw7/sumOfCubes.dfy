function sumCubes(n: nat) : nat {
if n == 0 then 0 else n*n*n + sumCubes(n-1)
}
lemma {:induction false} sumLemma(n: nat)
ensures sumCubes(n) == n*n*(n+1)*(n+1)/4
{
	if (n == 0) {

	} else {
		sumLemma(n-1);
	}
}