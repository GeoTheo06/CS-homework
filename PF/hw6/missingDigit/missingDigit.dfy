/* file: missingDigit.dfy */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Oct 16 2024 */
/* version: 1.0 */

/* Description:
 * this program reads an array of 9 numbers and outputs the one that is missing
 */

include "io.dfy"

method Main()
{
	var a : int, i : int, j : int, found : int;
	var arr := new int[9];
	i := 0;
	while i < 9
	{
		arr[i] := IO.ReadInt();
		i := i+1;
	}

	i := 0;

	while i <= 9
	{
		j := 0;
		found := 0;
		while j < 9 
		{
			if(arr[j] == i)
			{
				found := 1;
				break;
			}
			j := j+1;
		}
		if found == 0
		{
			print i, "\n";
			break;
		}
		i := i+1;
	}

}