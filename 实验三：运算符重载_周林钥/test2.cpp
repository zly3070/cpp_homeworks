#include <bits/stdc++.h>
using namespace std;

class Complex{
		private:
			double real;
			double imag;

		public:
			Complex() {real = 0;imag = 0;}
			Complex(double r, double i) : real(r), imag(i) {}
			Complex(double r) : real(r), imag(0) {}
			void getComplex();
			friend Complex operator+(const Complex& jiashu1, const Complex& jiashu2);
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

Complex operator+(const Complex& jiashu1, const Complex& jiashu2){
	return Complex(jiashu1.real+jiashu2.real, jiashu1.imag+jiashu2.imag);
}

int main(){
	Complex c1(-1, 1);
	Complex c2(3, 2);
	int int1 = 4;
	Complex jiahe1 = int1 + c2;
	Complex jiahe2 = c2 + int1;
	Complex jiahe3 = c1 + c2;
	jiahe1.getComplex();
	jiahe2.getComplex();
	jiahe3.getComplex();
	return 0;
}