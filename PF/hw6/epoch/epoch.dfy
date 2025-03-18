/* file: epoch.dfy */
/* author: George Theodoridis (g.theodoridis@rug.nl) */
/* date: Thu Oct 16 2024 */
/* version: 1.0 */

/* Description:
 * reads epoch time and converts to weekdays
 */

include "io.dfy"

method Main()
{
	var day : int;
	var ep : int;
	ep := IO.ReadInt();
	day := (ep/(3600*24))%7;
	if(day == 0) {
		print("Thursday\n");
	} else if(day == 1){
		print("Friday\n");
	} else if (day == 2) {
		print("Saturday\n");
	} else if (day == 3) {
		print("Sunday\n");
	} else if (day == 4) {
		print("Monday\n");
	} else if (day == 5) {
		print("Tuesday\n");
	} else if (day == 6) {
		print("Wednesday\n");
	}
}