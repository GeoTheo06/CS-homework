include "io.dfy"

method GivenHoareTriple(X: int, Y: int) returns (x: int, y: int)
ensures x == y*y + X && y == Y
{
  y := Y - 1;
  x := y*y + X;
  // In the rest of this method, you should consider X and Y
  // to be specification constant. So they are not allowed
  // to appear in statements (apart from assert) after
  // these comment lines.

  // the following annotated program fragment shows the correctness of the Hoare triple:
  //   {x == y*y + X && y + 1 == Y} x:=x + 2*y + 1; y := y + 1; {x == y*y + X && y == Y}

  assert x == y*y + X && y + 1 == Y;
  // the following assertion is wp(x:=x + 2*y + 1, x == y*y + X + 2*y + 1 && y + 1 == Y)
  assert x + 2*y + 1 == y*y + X + 2*y + 1 && y + 1 == Y;
  x := x + 2*y + 1;
  assert x == y*y + X + 2*y + 1 && y + 1 == Y;
  // the following assertion is wp(y:=y+1, x == y*y + X && y == Y);
  assert x == (y+1)*(y+1) + X && y + 1 == Y;
  y := y + 1;
  assert x == y*y + X && y == Y;
}

method ExerciseHoareTriple(X: int, Y: int) returns (x: int, y: int)
ensures x == y*y + X && y == Y
{
  y := Y - 1;
  x := y*y + X;
  // In the rest of this method, you should consider X and Y
  // to be specification constant. So they are not allowed
  // to appear in statements (apart from assert) after
  // these comment lines.

  // the following annotated program fragment shows the correctness of the Hoare triple:
  //   {x == y*y + X && y + 1 == Y} y:= ??; x := ??; {x == y*y + X && y == Y}

  assert x == y*y + X && y + 1 == Y;
  // the following assertion should be a simplification of the next assertion
  assert y == Y-1 && x == y*y + X;
  // the following assertion should be wp(x:=..., y:=....;, x == y*y + X && y == Y);
  assert y == Y - 1; 
  y := y + 1;  // fill in an appropriate expression
  // the following assertion should be wp(x:=..., x == y*y + X && y == Y);
  assert y == Y && x == (y-1)*(y-1) + X;
  x := y*y + X;  // fill in an appropriate expression
  assert x == y*y + X && y == Y;
}


method Main()
{
  // Do not change the following code. It is used for Themis testing
  var X := IO.ReadInt();
  var Y := IO.ReadInt();

  var x, y: int;
  x,y := GivenHoareTriple(X, Y);
  print "x=", x," y=", y, "\n";

  
  var x', y': int;
  x',y' := ExerciseHoareTriple(X, Y);
  print "x'=", x'," y'=", y', "\n";

  if x' != x && y' != y
  {
    print "Houston, we've got a problem\n";
  }
}