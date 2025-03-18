/* file: prob6.dfy
   author: your name
   description: 2-3rd exam 2024, problem 6
*/

ghost function f(n: nat): int {
  if n <= 2 then 2*n else f(n-1) + 2*f(n-2) + 3*f(n-3)
}

ghost function fSum(n: nat): int {
  if n == 0 then 0 else f(n - 1) + fSum(n-1)
}

method problem6(n:nat) returns (a: int)
ensures a == fSum(n)
{
  var k, x, y, z;
  a, k, x, y, z := 0, 0, 0, 2, 4;  // initialize yourself
  while k < n
    invariant 0<=k<=n && x==f(k) && y==f(k+1) && z==f(k+2) && a == fSum(k)
  {
  assert x==f(k) && y==f(k+1) && z==f(k+2) && a == fSum(k);
    k := k + 1;
  assert x==f(k-1) && y==f(k) && z==f(k+1) && a == fSum(k-1);
	
    a := a+x;
  assert x==f(k-1) && y==f(k) && z==f(k+1) && a == fSum(k);
    z := z+2*y+3*x;
  assert x==f(k-1) && y==f(k) && z==f(k+2) && a == fSum(k);
    y := z-2*y-3*x;
  assert x==f(k-1) && y==f(k+1) && z==f(k+2) && a == fSum(k);
    x := (z-y-3*x)/2;
  assert x==f(k) && y==f(k+1) && z==f(k+2) && a == fSum(k);
  }
}