/* file: prob5.dfy
   author: your name
   description: 2-3rd resit 2023, problem 5
*/

ghost function f(a: nat, b: nat): nat {
  if a == 0
  then 1
  else if a % 2 == 0
    then f(a / 2, b * b)
    else b * f(a - 1, b)
}

method problem5(a: nat, b:nat) returns (r: nat)
  ensures r == f(a, b)
{
  // implement yourself. You are required to give an invariant!
  var i := a;
  var j := b;
  r := 1;

  while (i>0)
    invariant r*f(i,j) == f(a,b)
  {
	assert r*f(i,j) == f(a,b);
	
    if (i%2 == 0) {
	assert r*f(i / 2, j * j) == f(a,b);
	i:=i/2;	
	assert r*f(i, j * j) == f(a,b);
	j:= j*j;
	assert r*f(i, j) == f(a,b);
    } else {
	assert r*j * f(i - 1, j) == f(a,b);
	i:=i-1;
	assert r*j * f(i, j) == f(a,b);
	r:=r*j;
    }
  }
}