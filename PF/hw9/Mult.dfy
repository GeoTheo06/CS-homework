method mul(a: int, b: int) returns (m : int)
requires b >= 0
ensures m == a*b
{
var x,y := a,b;
m := 0; // fill in yourself
while y > 0
invariant 0 <= y <= b
invariant x*y + m == a*b // fill in yourself
{
	
	assert x*y + m == a*b;
	if (y%2 == 1) {
		assert x*(y-1) + x + m == a*b;
		y := y - 1;
		assert x*y + x + m == a*b;
		assert x*y + m + x == a*b;
		m := m + x;
		assert x*y + m == a*b;
	}
	assert y%2==0;
	assert 2*x*y/2 + m == a*b;
	x := 2*x;
	assert x*(y/2) + m == a*b;
	y := y/2;
	assert x*y + m == a*b;
	}
}