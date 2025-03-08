#include <iostream>
#include <cmath>
const int N = 10;


class Vector10 {
	double arr[N] = { 0 }; double eps = 1e-6;
public:
	Vector10() {};
	double& operator[](int index) {
		return arr[index];
	};
	const double& operator[](int index) const {
		return arr[index];
	};
	Vector10(double coord[N]) {
		for (int i = 0; i < N; i++) {
			arr[i] = coord[i];
	}
	};
	void setcoord(int index, double value) {
		arr[index] = value;
	};
	double getcoord(int index) {
		return arr[index];
	};
	double abs() {
		double res = sqrt(arr[0]*arr[0] + arr[1]*arr[1]+ arr[2] * arr[2] + arr[3] * arr[3]+ arr[4] * arr[4] + arr[5] * arr[5]
			+ arr[6] * arr[6] + arr[7] * arr[7] + arr[8] * arr[8] + arr[9] * arr[9]);
		return res;
	};
	double dot(Vector10 b) {
		double res = 0;
		for (int i = 0; i < N; i++) {
			res += (arr[i] * b[i]);
		}
		return res;
	}
	Vector10 operator+ (const Vector10& b) const {
		Vector10 res;
		for (int i = 0; i < N; i++) {
			res[i] = arr[i] + b[i] ;
		}
		return res;
	};
	Vector10 operator+= (const Vector10& b)  {
		for (int i = 0; i < N; i++) {
			arr[i] += b[i];
		}
		return arr;
	};

	Vector10 operator- (const Vector10& b) const {
		Vector10 res;
		for (int i = 0; i < N; i++) {
			res[i] = arr[i] - b[i];
		}
		return res;
	};
	Vector10 operator-= (const Vector10& b) {
		for (int i = 0; i < N; i++) {
			arr[i] -= b[i];
		}
		return arr;
	};
	Vector10 operator* (const double& c) const {
		Vector10 res;
		for (int i = 0; i < N; i++) {
			res[i] = arr[i]* c ;
		}
		return res;
	};
	Vector10 operator/ (const double& c) const {
		Vector10 res;
		for (int i = 0; i < N; i++) {
			res[i] = arr[i] / c;
		}
		return res;
	};
	bool operator== (const Vector10& b) const {
		bool res = true;
		for (int i = 0; i < N; i++) {
			if (std::fabs(arr[i] - b[i]) < eps) {}
			else { res = false; }
		}
		return res;
	};
	bool operator!= (const Vector10& b) const {
		bool res = false;
		for (int i = 0; i < N; i++) {
			if (std::fabs(arr[i] - b[i]) < eps) {}
			else { res = true; }
		}
		return res;
	};
};



int main() {
	double coord_a[N] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0 };
	Vector10 a(coord_a);
	double coord_b[N] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,20.0 };
	Vector10 b(coord_b);
	Vector10 c = a + b;
	for (int i = 0; i < N; i++) {
		std::cout << c[i] << " ";
	}
	int f = (a == b);
	std::cout <<'\n' << f << " \n";
	Vector10 d;
	d = a * 8;
	for (int i = 0; i < N; i++) {
		std::cout << d[i] << " ";
	}
	std::cout << '\n';
	d = d / 4;
	for (int i = 0; i < N; i++) {
		std::cout << d[i] << " ";
	}
	double e = a.abs();
	std::cout << '\n' << e << '\n';
	double k = a.dot(b);
	std::cout << '\n' << k;
	double s = 5.0;
	a.setcoord(1, s);
	std::cout << '\n' << a[1];
	a.setcoord(1, 2);
	double g = a.getcoord(8);
	std::cout << '\n' << g << '\n';
	d += a;
	for (int i = 0; i < N; i++) {
		std::cout << d[i] << " ";
	}
	std::cout << '\n' << '\n';
	a -= b;
	for (int i = 0; i < N; i++) {
		std::cout << a[i] << " ";
	}
}