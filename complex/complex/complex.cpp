#include <iostream>
#include <cmath>
/* for better use I recommend you just start my program and you can see results of testing all my func*/

class complex {
	double real = 0.0; double imag = 0.0; double eps = 1e-5;
public:
	complex() {};
	complex(double a) {
		real = a;
	}
	complex(double a, double b) {
		real = a;
		imag = b;
	}
	void setreal(double a) {
		real = a;
	}
	void setimag(double a) {
		imag = a;
	}
	double getreal() {
		return real;
	}
	double getimag() {
		return imag;
	}
	complex conj() {
		complex res;
		res.real = real;
		res.imag = -imag;
		return res;
	}
	complex operator+ (complex b) {
		complex res;
		res.real = real + b.real;
		res.imag = imag + b.imag;
		return res;
	}
	complex operator+= (complex b) {
		real += b.real;
		imag += b.imag;
		return *this;
	}
	complex operator- (complex b) {
		complex res;
		res.real = real - b.real;
		res.imag = imag - b.imag;
		return res;
	}
	complex operator-= (complex b) {
		real -= b.real;
		imag -= b.imag;
		return *this;
	}
	complex operator* (complex b) {
		complex res;
		res.real = real * b.real - imag * b.imag;
		res.imag = real * b.imag + b.real * imag;
		return res;
	}
	complex& operator*= (const complex& b) {
		double new_real = this->real * b.real - this->imag * b.imag;
		double new_imag = this->real * b.imag + this->imag * b.real;
		this->real = new_real;
		this->imag = new_imag;
		return *this;
	}
	complex operator/ (complex b) {
		complex res;
		res.real = (real * b.real + imag * b.imag) / (b.real * b.real + b.imag * b.imag);
		res.imag = (imag * b.real - real * b.imag) / (b.real * b.real + b.imag * b.imag);
		return res;
	}
	complex& operator/= (const complex& b) {
		double new_real = (this->real * b.real + this->imag * b.imag) / (b.real * b.real + b.imag * b.imag);
		double new_imag = (this->imag * b.real - this->real * b.imag) / (b.real * b.real + b.imag * b.imag);
		this->real = new_real;
		this->imag = new_imag;
		return *this;
	}
	double abs() {
		double res;
		res = std::sqrt(real * real + imag * imag);
		return res;
	}
	double arg() {
		double res;
		res = std::atan2(imag, real);
		return res;
	}
	void setabs(double r) {
		double fi = arg();
		real = r * std::cos(fi);
		imag = r * std::sin(fi);
	}
	double getabs() {
		return abs();
	}
	void setarg(double fi) {
		double r = abs();
		real = r * std::cos(fi);
		imag = r * std::sin(fi);
	}
	double getarg() {
		return arg();
	}
	complex operator+ (double b) {
		complex res;
		res.real = real + b;
		res.imag = imag;
		return res;
	}
	complex operator- (double b) {
		complex res;
		res.real = real - b;
		res.imag = imag;
		return res;
	}
	complex operator* (double b) {
		complex res;
		res.real = real * b;
		res.imag = imag * b;
		return res;
	}
	complex operator/ (double b) {
		complex res;
		res.real = real / b;
		res.imag = imag / b;
		return res;
	}
	complex operator+= (double b) {
		real += b;
		imag = imag;
		return *this;
	}
	complex operator-= (double b) {
		real -= b;
		imag = imag;
		return *this;
	}
	complex operator*= (double b) {
		real *= b;
		imag *= b;
		return *this;
	}
	complex operator/= (double b) {
		real /= b;
		imag /= b;
		return *this;
	}
	bool operator== (complex b) {
		if ((std::fabs(real - b.real) < eps) && (std::fabs(imag - b.imag) < eps)) return true;
		else return false;
	}
	int operator!= (complex b) {
		if ((std::fabs(real - b.real) < eps) && (std::fabs(imag - b.imag) < eps)) return false;
		else return true;
	}
};

int main() {
	complex a;
	complex b(1.0);
	complex c(1.0, 1.0);
	complex d = c.conj();
	std::cout << "c.conj() (" << d.getreal() << ", " << d.getimag() << ")" << '\n';
	complex e = b + c;
	std::cout << "e = b + c (" << e.getreal() << ", " << e.getimag() << ")" << '\n';
	complex f = e - c;
	std::cout << "f = e - c (" << f.getreal() << ", " << f.getimag() << ")" << '\n';
	complex g(5.0, 2.0);
	complex h = g * c;
	std::cout << "h = g * c (" << h.getreal() << ", " << h.getimag() << ")" << '\n';
	double habs = h.abs();
	double harg = h.arg();
	std::cout << "h.abs: " << habs << "\nh.arg: " << harg << '\n';
	complex i = c + 2.8;
	complex j = c - 2.8;
	std::cout << "c + 2.8 (" << i.getreal() << ", " << i.getimag() << ")" << '\n';
	std::cout << "c - 2.8 (" << j.getreal() << ", " << j.getimag() << ")" << '\n';
	complex k = g / c;
	std::cout << "k = g/c (" << k.getreal() << ", " << k.getimag() << ")" << '\n';
	complex l = c * 3.0;
	std::cout << "c * 3.0 (" << l.getreal() << ", " << l.getimag() << ")" << '\n';
	complex m = c / 2.0;
	std::cout << "c / 2.0 (" << m.getreal() << ", " << m.getimag() << ")" << '\n';
	c += 5.0;
	std::cout << "c += 5.0 (" << c.getreal() << ", " << c.getimag() << ")" << '\n';
	c -= 4.0;
	std::cout << "c -= 4.0 (" << c.getreal() << ", " << c.getimag() << ")" << '\n';
	c *= 4.0;
	std::cout << "c *= 4.0 (" << c.getreal() << ", " << c.getimag() << ")" << '\n';
	c /= 2.0;
	std::cout << "c /= 2.0 (" << c.getreal() << ", " << c.getimag() << ")" << '\n';
	complex n(4.000002, 2.0);
	std::cout << "c == n " << (c == n) << '\n';
	n.setreal(5.0);
	std::cout << "n.setreal(5.0) (" << n.getreal() << ", " << n.getimag() << ")" << '\n';
	n.setimag(-2.78);
	std::cout << "n.setimag(-2.78); (" << n.getreal() << ", " << n.getimag() << ")" << '\n';
	std::cout << "c != n " << (c != n) << '\n';
	complex o = (k += c);
	std::cout << "k+=c (" << o.getreal() << ", " << o.getimag() << ")" << '\n';
	complex v = (c -= e);
	std::cout << "c-=e (" << v.getreal() << ", " << v.getimag() << ")" << '\n';
	complex y(5.0, 2.0);
	e.setreal(2.0);
	e.setimag(1.0);
	complex x = (y *= e);
	std::cout << "y*=e (" << x.getreal() << ", " << x.getimag() << ")" << '\n';
	complex z = (o /= d);
	std::cout << "o/=d (" << z.getreal() << ", " << z.getimag() << ")" << '\n';
	complex aa(5.0, 5.0);
	std::cout << "arg:" << (aa.arg()) << " abs: " << (aa.abs()) << "\n";
	aa.setabs(12.041594578792296);
	aa.setarg(0.844153986113171);
	std::cout << "real: " << (aa.getreal()) << " im: " << (aa.getimag()) << "\n";
	complex ab(1.0, 1.0);
	std::cout << "arg:" << (ab.arg()) << " abs: " << (ab.abs()) << "\n";
	ab.setabs(5);
	std::cout << "real: " << (ab.getreal()) << " im: " << (ab.getimag()) << " arg: " << (ab.getarg()) << "\n";
	ab.setarg(1.16);
	std::cout << "real: " << (ab.getreal()) << " im: " << (ab.getimag()) << " arg: " << (ab.getabs()) << "\n";
	// I think that's all, thanks for checking my work! 
}

