method problem4(a: nat, b: nat)
{
	var i,j: int;
	i,j := a,b;
	while i > 0 && j > 0
	decreases j, i // choose a suitable variant function
	{
		if i < j {
			i,j := j,i;
		} else {
			i := i - 1;
		}
	}
}