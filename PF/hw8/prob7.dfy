ghost function exp(x: int, e: nat): int
{ // returns x raised to the power e
	if e == 0 then 1 else x*exp(x, e-1)
}

ghost function polynomial(x: int, n: nat, a: array<int>): int
requires n <= a.Length
reads a
{ // returns Sum(i in [0..n):: a[i]*xˆi)
	if n == 0 then 0 else a[n-1]*exp(x, n-1) + polynomial(x, n-1, a)
}

method Polynomial(x: int, a: array<int>) returns (p : int)
ensures p == polynomial(x, a.Length, a)
{
	var sum := 0;
	var i := 0;

	var xExp := 1;

	while(i < a.Length) 
	decreases a.Length - i
	invariant 0 <= i <= a.Length
	invariant xExp == exp(x,i)
	invariant sum == polynomial(x,i,a)
	{
		i:= i + 1;
		sum := sum + a[i-1]*xExp;
		xExp := x*xExp;
	}
	assert i == a.Length;
	assert sum == polynomial(x,i,a);
	p := sum;
}