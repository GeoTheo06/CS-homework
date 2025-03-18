
method problem5(A:int,B:int,x:int,y:int, z:int) returns (X: int, Y: int)
requires x+y+z==A+B && z-y == 3*B - A
ensures X == A + B && Y == 3 * B - A
{
	var Z:int;
	Z, X, Y := x - y, x + y + z, z - y;
}