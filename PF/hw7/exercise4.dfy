method preserveSum(x: int, y:int, a:int) returns (p: int, q: int)
ensures p + q == x + y
{
p := x + a;
q := y - a;
}
method preserveSumProduct(x: int, y:int) returns (p: int, q: int)
ensures p + q == x + y && p*q < 0
{
	if(x*y < 0) {
		p:=x;
		q:=y;
	} else if (x*y == 0){
		if(x==0 && y == 0) {
			p:=1;
			q:= -1;
		} else if(y == 0) {
			p:=x+x;
			q:= y-x;
		} else if (x == 0) {
			p:=x-y;
			q:= y+y;	
		}
	}else if(x > 0) {
		p:= x - (x+1);
		q:= y + (x+1);
	} else {
		p:= x - (x-1);
		q:= y + (x-1);
	}
}