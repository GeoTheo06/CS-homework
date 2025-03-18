method mystery(a: nat) returns (q: nat, r: nat)
  ensures q * 3 + r == a
{
  q, r := 0, a + 1;
  while r >= 4
    decreases r
    invariant q * 3 + r == a + 1
	invariant 0 < r
  {
    q := q + r / 4;
    r := r / 4 + r % 4;
  }
  r := r - 1;
}