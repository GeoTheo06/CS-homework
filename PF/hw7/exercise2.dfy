method exercise2(a: int, n:int) returns (x: int)
ensures x>=n && (x==2*a - n || x==3*n - 2*a + 1)
{
	if(2*a-n >= n) {
		x := 2*a-n;
	} else if (3*n - 2*a + 1 >= n) {
		x := 3*n - 2*a + 1;
	}
}