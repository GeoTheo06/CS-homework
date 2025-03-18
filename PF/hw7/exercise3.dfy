method exercise3(y: int, a: int, n:int) returns (x: int)
requires y>=n && (y == 2*a - n || y == 3*n - 2*a + 1)
ensures x == a
{
	if ((y + n) % 2 == 0) {
		x := (y + n) / 2;
	} else {
		x := (3 * n + 1 - y) / 2;
	}
}