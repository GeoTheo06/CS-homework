predicate Asc(a: array<int>)
  reads a
{
  forall i, j :: 0 <= i < j < a.Length ==> a[i] <= a[j]
}

method occursInBoth(a: array<int>, b: array<int>) returns (r: bool)
  requires Asc(a) && Asc(b)
  ensures r == (exists i, j :: 0 <= i < a.Length && 0 <= j < b.Length && a[i] == b[j])
{
  var i := 0;
  var j := 0;
  r := false;
  while i < a.Length && j < b.Length
    decreases a.Length - i + b.Length - j
    invariant 0 <= i <= a.Length
    invariant 0 <= j <= b.Length
	invariant r || (forall k, l :: 0 <= k < i && 0 <= l < b.Length ==> a[k] != b[l])
    invariant r || (forall k, l :: 0 <= k < a.Length && 0 <= l < j ==> a[k] != b[l])
  
  {
    if a[i] == b[j] {
      r := true;
      return;
    } else if a[i] < b[j] {
      i := i + 1;
    } else {
      j := j + 1;
    }
  }
}