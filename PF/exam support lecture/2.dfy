ghost function f(n: int): int {
  if n <= 0 then 1 else n + f(n-1)*f(n-2)
}

ghost function fSum(n: nat): int {
 // give the body of this function
  // it should return Sum(i: 0<=i<n: f(i))
  if n ==0 then 1 else fSum(n-1)+f(n-1)
}

method problem6(n:nat) returns (a: int)
ensures a == fSum(n)
{
  var k, x, y;
  a,k,x,y := 1,0,1,2;  // initialize yourself
  while k < n
    invariant 0<=k<=n && x==f(k) && y==f(k+1) && a == fSum(k)
  {
  assert x==f(k) && y==f(k+1) && a == fSum(k);
    k := k + 1;
  assert x==f(k-1) && y==f(k) && a == fSum(k-1);
  
    // complete the rest of this method
    a := a+x;
    x,y := y, k+1+x*y;
  }
}