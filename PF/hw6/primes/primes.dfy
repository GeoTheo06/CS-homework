/* file: epoch.dfy */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Oct 16 2024 */
/* version: 1.0 */

/* Description:
 * reads number and checks if this number and all the numbers that are generated from it if we remove the last digit are prime
 */

include "io.dfy"

method checkPrime(n: int) returns (res: bool)
{
	if n == 0 || n == 1
	{
		return false;
	}
	//2 is the first prime
	if n == 2
	{
		return true;
	}
    var divisor := 2;
	while divisor * divisor <= n
    {
        if n % divisor == 0
        {
            return false;
        }
        divisor := divisor + 1;
    }
    return true;
}

method Main()
{
	// read input
	var inp : int;
	inp := IO.ReadInt();
	var isPrime : bool;
	isPrime := true;

	if inp == 0
	{
		print "NO\n";
	} else {
		// runs until number becomes 0
		while (inp > 0)
		{
			isPrime := checkPrime(inp);
			if(!isPrime) {
				print "NO\n";
				break;
			}
			inp := inp/10;
		}
	
		if(isPrime)
		{
			print "YES\n";
		}
	}
}