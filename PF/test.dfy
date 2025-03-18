/* file: prob4.dfy
   author: your name
   description: 2-3rd exam 2023, problem 4
*/


method problem4(a: int, b: int, c: int) returns (i: int, j: int, k: int)
requires a <= b <= c
ensures i == j == k
{
  i, j, k := a, b, c;
  while i < j || j < k
  invariant a <=i<=j<=k      // choose a suitable invariant
  decreases 3*k-2*i-j      // choose a suitable variant function
  {
    if i < j {
      i := i + 1;
    } else {
      if j < k {
        j := j + 1;
      } else {
        k := k + 1;
      }
    }
  }
}