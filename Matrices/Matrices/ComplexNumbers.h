#pragma once
#include <iostream>

using namespace std;

class ComplexNumber {
private:
	static constexpr double EPSILON = 1e-12;
	double re;
	double im;
public:
	ComplexNumber(double re = 0, double im = 0) :re(re), im(im) {};

	double getRe() const {
		return this->re;
	}
	double getIm() const {
		return this->im;
	}
	double getAbsoluteValue() const {
		return sqrt(re * re + im * im);
	}
	
	ComplexNumber operator+(const ComplexNumber& other) const {
		return ComplexNumber(re + other.re, im + other.im);
	}
	ComplexNumber operator-(const ComplexNumber& other) const {
		return ComplexNumber(re - other.re, im - other.im);
	}
	ComplexNumber operator*(const ComplexNumber& other) const {
		return ComplexNumber(re * other.re - im * other.im, 
								re * other.im + im * other.re);
	}
	ComplexNumber operator/(const ComplexNumber& other) const {
		double denominator = other.re * other.re + other.im * other.im;
		return ComplexNumber((re * other.re + im * other.im) / denominator,
							(im * other.re - re * other.im) / denominator);
	}
	ComplexNumber& operator=(const ComplexNumber& other){
		if (this != &other) {
			re = other.re;
			im = other.im;
		}
		return *this;
	}
	ComplexNumber& operator=(const double& other) {
		re = other;
		im = 0;
		return *this;
	}

	bool operator==(const ComplexNumber& other) const {
		return fabs(re - other.re) < EPSILON && fabs(im - other.im) < EPSILON;
	}
	bool operator!=(const ComplexNumber& other) const {
		return !(*this == other);
	}
	
	friend ostream& operator<<(ostream& os, const ComplexNumber& c) {
		if (fabs(c.im) < EPSILON)
			os << c.re;
		else if (fabs(c.re) < EPSILON)
			os << c.im << "i";
		else
			os << c.re << (c.im > 0 ? "+" : "") << c.im << "i";
		return os;
	}

};