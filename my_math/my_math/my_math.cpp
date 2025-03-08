#include <stdio.h>
#define PI 3.14159265358979323846


double exp(double x, double eps) {
	double res = 1.0,currEps = 1e16, term = 1.0, count = 1.0;
	while (currEps > eps || currEps < -eps) {
		term = x / count * term;
		currEps = term;
		res += term;
		count += 1.0;
	}
	return res;
}
double pow(double x, int n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2 == 0) {
		return pow(x * x, n / 2);
	}
	else {
		return x * pow(x, n - 1);
	}
}
double ln(double x, double eps) {
	double new_x = x - 1;
	double term = -(new_x * new_x / 2);
	int sign = 2;
	double res = new_x + term, currEps = 1e16, count = 3.0;
	while (currEps > eps || currEps < -eps) {
		term = pow(-1,sign)*pow(new_x,sign+1) / count;
		currEps = pow(-1, sign) * term;
		res += term;
		count += 1.0;
		sign += 1;
	}
	return res;
}
double ln_gr(double x, double eps) {
	double new_x = (x - 1) / (x + 1);
	double term = new_x;
	int degree = 3;
	double res = new_x, currEps = 1e16, count = 3.0;
	while (currEps > eps || currEps < -eps) {
		term = pow(new_x , degree)/count;
		currEps = term;
		res += term;
		degree += 2;
		count += 2.0;
	} 
	res = res * 2;
	return res ;
}
double log(double base, double x, double eps) {
	double denominator = ln_gr(base, eps);
	double numerator = ln_gr(x, eps);
	double res = numerator / denominator;
	return res;
}
double sqrt(double x, double eps ) {
	double new_x = x - 1;
	int sign = 3;
	long long numerator = 1, denumerator = 4, count = 2;
	double term = - 0.125 * new_x * new_x;
	double res = 1 + 0.5 * new_x - 0.125 * new_x * new_x, currEps = 1e16;
	while (currEps > eps || currEps < -eps) {
		numerator += count;
		denumerator += count;
		term = term*new_x * numerator / denumerator;
		res = res + pow(-1, sign)*term;
		currEps = pow(-1, sign)*term;
		sign += 1;
	}
	return res;
}
double sin(double x, double eps) {
	double new_x= x - int(x/2/PI)*2*PI;
	int sign = 3;
	long long denumerator = 5, count = 2;
	double term = pow(-1, sign) * pow(new_x, 3) / 6;
	double res = new_x+term;
	double currEps = 1e16;
	while (currEps > eps || currEps < -eps) {
		term = term * new_x*new_x / (denumerator - 1) / denumerator;
		res += pow(-1, sign)*term;
		currEps = pow(-1, sign) * term;
		sign += 1;
		denumerator += 2;
	}
	return res;
}

double cos(double x, double eps) {
	double new_x = x - int(x / 2 / PI) * 2 * PI;
	int sign = 3;
	long long denumerator = 4, count = 2;
	double term = pow(-1, sign) * pow(new_x, 2) / 2;
	double res = 1 + term;
	double currEps = 1e16;
	while (currEps > eps || currEps < -eps) {
		term = term * new_x * new_x / (denumerator - 1) / denumerator;
		res += pow(-1, sign) * term;
		currEps = pow(-1, sign) * term;
		sign += 1;
		denumerator += 2;
	}
	return res;
}
double tg(double x, double eps) {
	double numerator = sin(x,eps);
	double denumerator = cos(x, eps);
	if (denumerator == 0) {
		printf ("Error cos = 0");
			return 1;
	}
	else {
		return numerator / denumerator;
	}

}
double ctg(double x, double eps) {
	double numerator = cos(x, eps);
	double denumerator = sin(x, eps);
	if (denumerator == 0) {
		printf("Error sin = 0");
		return 1;
	}
	else {
		return numerator / denumerator;
	}
}
double sh(double x, double eps) {
	double new_x = x ;
	long long denumerator = 5, count = 2;
	double term =  pow(new_x, 3) / 6;
	double res = new_x + term;
	double currEps = 1e16;
	while (currEps > eps || currEps < -eps) {
		term = term * new_x * new_x / (denumerator - 1) / denumerator;
		res +=  term;
		currEps = term;
		denumerator += 2;
	}
	return res;
}
double ch(double x, double eps) {
	double new_x = x ;
	long long denumerator = 4, count = 2;
	double term = pow(new_x, 2) / 2;
	double res = 1 + term;
	double currEps = 1e16;
	while (currEps > eps || currEps < -eps) {
		term = term * new_x * new_x / (denumerator - 1) / denumerator;
		res += term;
		currEps = term;
		denumerator += 2;
	}
	return res;
}
