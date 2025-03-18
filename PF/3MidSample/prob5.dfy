ghost function f(n: nat): int {
// you are not allowed to remove ’ghost’, so an asignment
// like x := f(n) is not allowed.
if n == 0 then 0 else 2*f(n/7) + n%7
}
method problem5(n:nat) returns (x: int)
ensures x == f(n)
{
// implement yourself. You are required to give an invariant!
	var g := n;
	x := 0;

	assert 2 * f(g/7) +g % 7 == f(i);
}