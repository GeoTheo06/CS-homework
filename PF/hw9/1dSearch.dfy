method search(a: array<int>) returns (i : int)
  requires a.Length > 1 && a[0] == a[a.Length-1]
  ensures 0 <= i < a.Length-1 && a[i] >= a[i + 1]
{
  i := 0;
  var j := a.Length - 2;
  while i != j
    invariant 0 <= i <= j <= a.Length - 2 && a[i] >= a[j+1]
  {
    var m := (i + j) / 2;
    if a[m+1] >= a[i] {
      i := m+1;
	} else {
      j := m;
    }
  }
}
