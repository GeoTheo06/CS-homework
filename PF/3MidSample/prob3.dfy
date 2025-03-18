method problem3(n:int,ghost X:int) returns (r:int)
requires X >= 0 && (n == 2*X + 5 || 2*n == 9 - X)
ensures r == X
{
	if n >= 5 {
		assert n == 2 * X + 5;
		r := (n-5)/2;
	} else  {
		assert 2 * n == 9 - X;
		r := 9 - 2*n;
	}
}