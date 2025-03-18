function f(n: nat):int
{
	if n <= 1 then 1-n else 2*f(n-1) + f(n-2)
}

method computeF(n: nat) returns (a: int)
ensures a == f(n)
{
	if(n<=0) {
		a := 1;
	} else if (n==1) {
		a := 0;
	} else {
		assert n >= 2;
		var i := 2;
		var fiMin1 := 0;
		a := 1;
		while(i < n) 
		invariant f(i-1) == fiMin1 && a == f(i)
		invariant 2 <= i <= n
		decreases n - i
		{
			assert f(i-1) == fiMin1 && a == f(i);
			i:= i + 1;
			fiMin1, a := a, 2*a+fiMin1;
		}
		assert i == n;
		assert a == f(n);
	}
}