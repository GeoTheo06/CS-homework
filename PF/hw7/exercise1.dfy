method exercise1(x:int, y:int, ghost X:int, ghost Y:int)
returns (p:int, q: int)
requires X>Y && ((x==X && y==Y-2*x) || (x==Y && y==X-2*Y))
ensures p==X && q==Y
{
	p := x;
	q := y + (2*x);
	var temp: int;
	if (q > p) {
		temp := p;
		p := q;
		q := temp;
	}
}