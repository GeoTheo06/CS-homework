method problem(n: int, t: int,ghost X:int,ghost Y:int) returns (r:int,s:int)
requires n == Y + 1 && t == X + 2*Y
ensures r == X && s == Y
{
	r := t - 2*n;

	assert r == X-2;
	r := r + 2;

	assert r == X;

	s := t - r;
	assert s == 2*Y;

	s:= s/2;
}