ghost function f(n: int): int {
// you are not allowed to remove ’ghost’, so an asignment
// like x := f(n) is not allowed.
	if n < 0 then 0 else 3*f(n-5) + n
	
}
method problem5(n:nat) returns (x: int)
ensures x == f(n)
{
// implement yourself. You are required to give an invariant!
	var i:= n%5;
	var fi:= n%5;
	var fiMin1 := 0;

	while (i < n)
	decreases n - i
	invariant i%5 == n%5
	invariant fi == f(i)
	invariant i <= n
	{
		i:= i+5;
		fiMin1:=fi; 
		fi := 3*fiMin1+i;
		assert fi == f(i);
	}
	assert i == n;
	assert fi == f(i);
	x := fi;
}