/* file: prob5.dfy
   author: your name
   description: 2-3rd exam 2024, problem 5
*/

ghost function f(x: nat): nat {
  // you are not allowed to remove 'ghost', so an assignment
  // like x := f(n) is not allowed.
  if x < 2 then 1
  else if x % 2 == 0 then 2*f(x/2) + 1
  else 3 * f(x/2) - 2
}

method problem5(n: nat) returns (x: nat)
  ensures x == f(n)
{
  var i := n;
  var pl := 0;
  var mu := 1;
  x := 0;

  while(i >= 2)
	decreases i
    invariant x + mu*f(i) + pl == f(n)
  {
    if (i % 2 == 0) {
      assert x + mu*(2*f(i/2) + 1) + pl == f(n);
      assert x + mu*2*f(i/2) + mu + pl == f(n);
      mu := mu*2;
      assert x + mu*f(i/2) + mu/2 + pl == f(n);
      pl := mu/2 + pl;
      assert x + mu*f(i/2) + pl == f(n);
    } else {
      assert x + mu*3 * f(i/2) - 2*mu + pl == f(n);
      mu := mu*3;
      assert x + mu* f(i/2) - 2*mu/3 + pl == f(n);
      pl := pl - 2*mu/3;
      assert x + mu* f(i/2) + pl == f(n);
    }

    assert x + mu* f(i/2) + pl == f(n);
    i := i / 2;
	assert x + mu*f(i)+pl == f(n);
	assert x + mu*f(i)+pl == f(n);

  }
  x := mu+pl;

}