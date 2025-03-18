function f(n: nat): int
{
	if n <= 1 then 1-n else 2*f(n-1) + f(n-2)
}

method computeF(n: nat) returns (a: int)
ensures a == f(n)
{
	var i: nat;
	var fiMinus1: nat;
	var fiMinus2: nat;
	var fi: nat;

	if n == 0 {
        a := 1;
        return;
    }
    if n == 1 {
        a := 0;
        return;
    }

	fiMinus1 := 0;
	fiMinus2 := 1;
	fi := 1;
	i := 2;
	while (i <= n) 
	decreases n-i
	invariant 2 <= i <= n+1
	invariant fiMinus2 == f(i-2)
	invariant fiMinus1 == f(i-1)
	{
		fi := 2*fiMinus1 + fiMinus2;
		fiMinus2 := fiMinus1;
		fiMinus1 := fi;
		i:= i+1;
	}
	a := fiMinus1;
}