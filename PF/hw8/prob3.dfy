method problem3(m:int, X:int) returns (r:int)
requires X >= 0 && (2*m == 1 - X || m == X + 3)
ensures r == X
{
// X is a specification constant and is not allowed to
// appear in the body of this method.
//
// implement yourself
if(m>=3) {
	r:=m-3;
} else {
	r := 1-2*m;
}

}