predicate AscDesc(a: array2<int>)
  reads a
{
  (forall i, j, k:: 0<=i<=j<a.Length0 && 0<=k<a.Length1 ==> a[i,k]<=a[j,k]) &&
  (forall i, j, k:: 0<=i<a.Length0 && 0<=j<=k<a.Length1 ==> a[i,j]>=a[i,k])
}
predicate F(a: array2<int>, xlo: nat, xhi: nat, ylo: nat, yhi: nat, value: int)
  requires 0<=xlo<=xhi<=a.Length0 && 0<=ylo<=yhi<=a.Length1
  reads a
{
  exists x,y:: xlo<=x<xhi && ylo<=y<yhi && a[x,y]==value
}
method SlopeSearchSE(a: array2<int>, value: int) returns (b: bool)
  requires AscDesc(a)
  ensures b==F(a, 0, a.Length0, 0, a.Length1, value)
{
  var x := 0;
  var y := 0;
  var m := a.Length0;
  var n := a.Length1;
  b := false;
  while x<a.Length0 && y < a.Length1 && !b
    invariant 0<=x<=m && 0<=y<=a.Length1
    invariant (b || F(a, x, m, y, n, value))==F(a, 0, m, 0, n, value)
    decreases a.Length0 + a.Length1 - x - y
  {
    if a[x,y] <= value {
      b := b || (a[x,y] == value);
      x := x + 1;
    } else {
      y := y + 1;
    }
  }
}