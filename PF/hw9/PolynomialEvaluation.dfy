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
  var sum : int := 0;
  var expon : int := 1;
  var  i : int := 0;
  while (i < a.Length) 
invariant 0 <= i <= a.Length 
invariant expon == exp(x,i)
invariant sum == polynomial(x, i, a)
decreases a.Length - i
  {
	sum := a[i]*expon + sum;
	expon := expon*x;
	i := i + 1;
  }
  assert i == a.Length;
  p := sum;
}
