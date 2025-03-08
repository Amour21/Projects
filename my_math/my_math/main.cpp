#include <stdio.h>
#include "my_math.h"

#define PI 3.14159265358979323846

//tg and ctg just bonus, please don't count them 
//pow is not a full function, but an auxiliary function
//for all full functions it is possible to select epselon ( accuracy ) P.S I know about multi-line comments :)
// for the square root function, the Taylor series takes values of the argument from 0 to two 
// for the same reason, values from zero (not inclusive) to two are allowed for the natural logarithm
int main() {
	printf("%0.10f\n", exp(15)); //3269017.3724721107
	printf("%0.10f\n", sqrt(2)); //1.4142135624
	printf("%0.10f\n", sin(100000)); //0.7071067812
	printf("%0.10f\n", sin(157 * PI / 16)); // -0.5555702330
	printf("%0.10f\n", cos(PI / 4)); //0.7071067812
	printf("%0.10f\n", cos(85 * PI / 8));//-0.3826834324
	printf("%0.10f\n", sh(13,1e-13)); //221206.6960033301
	printf("%0.10f\n", sh(13,1e-13)); //221206.6960033301
	printf("%0.10f\n", ln(0.36, 1e-13));
	printf("%0.19f\n", ln_gr(2, 1e-18));
	printf("%0.10f\n", log(36, 6));
	/*and the logarithmised expression can already represent any positive number
	z = (1+x)/(1-x), for then x = (z - 1)/(z+1) is less than one in absolute value, 
	it satisfies the Mercator series condition*/
}