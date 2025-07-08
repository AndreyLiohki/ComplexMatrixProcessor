#include <cmath>

#include "ComplexNumber.h"

namespace core {

	double ComplexNumber::getRe() const {
		return re;
	}

	double ComplexNumber::getIm() const {
		return im;
	}

	double ComplexNumber::getAbsoluteValue() const {
		return sqrt(re * re + im * im);
	}
	
	ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
		return ComplexNumber(re + other.re, im + other.im);
	}

	ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
		return ComplexNumber(re - other.re, im - other.im);
	}

	ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
		return ComplexNumber(re * other.re - im * other.im,
			re + other.im + im * other.re);
	}

	ComplexNumber ComplexNumber::operator/(const ComplexNumber& other) const {
		double denominator = other.re * other.re + other.im * other.im;
		return ComplexNumber((re * other.re + im * other.im) / denominator,
			(im * other.re - re * other.im) / denominator);
	}

	ComplexNumber& ComplexNumber::operator=(const ComplexNumber& other) {
		if (this != &other) {
			re = other.re;
			im = other.im;
		}
		return *this;
	}

	ComplexNumber& ComplexNumber::operator=(const double& other) {
		re = other;
		im = 0;
		return *this;
	}

	bool ComplexNumber::operator==(const ComplexNumber& other) const{
		return fabs(re - other.re) < EPSILON && fabs(im - other.im) < EPSILON;
	}

	bool ComplexNumber::operator!=(const ComplexNumber& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& os, const ComplexNumber& complexNumber) {
		os << complexNumber.re << (complexNumber.im >= 0 ? "+" : "") << complexNumber.im << "i";
		return os;
	}

}//namespace Core