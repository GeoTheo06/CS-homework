method problem4(a: int, b:int, c:int) returns (i: int, j: int, k: int)
requires a <= b <= c
ensures i == j == k
{
	i,j,k:=a,b,c;
	while i<j || j < k
	invariant i <= j <= k
	decreases k-j
	decreases j-i // choose a suitable variant function
	{
		if i < j {
			i := i + 1;
		} else {
			if j < k {
				j := j + 1;
			} else {
				k := k + 1;
			}
		}
	}
}