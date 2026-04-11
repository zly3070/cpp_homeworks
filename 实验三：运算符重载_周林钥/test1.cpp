#include <bits/stdc++.h>
using namespace std;

class Complex{
		private:
			double real;
			double imag;

		public:
			Complex() {real = 0;imag = 0;}
			Complex(double r, double i) : real(r), imag(i) {}
			void getComplex();
			Complex operator+(Complex c2) const;
			Complex operator-(Complex c2) const;
			Complex operator*(Complex c2) const;
			Complex operator/(Complex c2) const;
	};
	
void Complex::getComplex(){
	if (real == 0){
		if (imag != 0) cout << imag << "i" << endl;		 
		else cout << "0" << endl;		
	} else {
		if (imag != 0){
			if (imag < 0) cout << real << imag << "i" << endl;
			else cout << real << "+" << imag << "i" << endl;
		} else cout << real << endl;
	}
}

Complex Complex::operator+(const Complex c) const {
	Complex tmp;
	tmp.real = real + c.real;
	tmp.imag = imag + c.imag;
	return tmp;
}

Complex Complex::operator-(const Complex c) const {
	Complex tmp;
	tmp.real = real - c.real;
	tmp.imag = imag - c.imag;
	return tmp;
}

Complex Complex::operator*(const Complex c) const {
	Complex tmp;
	tmp.real = real*c.real - imag*c.imag;
	tmp.imag = real*c.imag + imag*c.real;
	return tmp;
}

Complex Complex::operator/(const Complex c) const {
	double denominator = c.real * c.real + c.imag * c.imag;  // 分母：c²+d²
    // (a+bi)*(c-di) 的展开
    double realPart = (real * c.real + imag * c.imag) / denominator;
    double imagPart = (imag * c.real - real * c.imag) / denominator;
    
    return Complex(realPart, imagPart);
}
	
int main(){
	Complex c1(-1, 1);
	Complex c2(3, 2);
	Complex c3 = c1 + c2;
	Complex c4 = c1 - c2;
	Complex c5 = c1 * c2;
	Complex c6 = c1 / c2;
	c6.getComplex();
	return 0;
}