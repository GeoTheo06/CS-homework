include "io.dfy"

method SquareCube(n: int) returns (sq: int, cb: int)
  requires n >= 0
  ensures sq == n * n && cb == n * n * n
{
  var i := 0;
  sq := 0;
  cb := 0;

  while i < n
    invariant 0 <= i <= n
    invariant sq == i * n
    decreases n - i
  {
    sq := sq + n;
    i := i + 1;
  }

  i := 0;
  while i < n
    invariant 0 <= i <= n
    invariant cb == i * sq
    decreases n - i
  {
    cb := cb + sq;
    i := i + 1;
  }
}

method Main()
{
  // Do not change the following code. It is used for Themis testing
  var n := IO.ReadNat();
  var square, cube := SquareCube(n);
  print n, "*", n, "=", square, " ", n, "*", n, "*", n, "=", cube, "\n";
}
