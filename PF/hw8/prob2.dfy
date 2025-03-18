method problem2(p:int, q:int, ghost X:int, ghost Y:int)
returns (r:int, s:int)
requires p == 2*X + Y && q == X + 3
ensures r == X && s == Y
{
	r := q - 3;
	s := p-2*q+6;
}