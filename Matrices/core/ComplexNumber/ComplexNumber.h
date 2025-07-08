#pragma once

#include <iostream>

namespace core {

	class ComplexNumber {
	private:
		static constexpr double EPSILON = 1e-12;
		double re;
		double im;
	public:
		ComplexNumber(double re = 0, double im = 0) : re(re), im(im) {};

		double getRe() const;
		double getIm() const;
		double getAbsoluteValue() const;

		ComplexNumber operator+(const ComplexNumber& other) const;
		ComplexNumber operator-(const ComplexNumber& other) const;
		ComplexNumber operator*(const ComplexNumber& other) const;
		ComplexNumber operator/(const ComplexNumber& other) const;
		ComplexNumber& operator=(const ComplexNumber& other);
		ComplexNumber& operator=(const double& other);

		bool operator==(const ComplexNumber& other) const;
		bool operator!=(const ComplexNumber& other) const;

		friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& c);
	};

	ComplexNumber getConjugated(const ComplexNumber& number) {
		core::ComplexNumber conjugatedNumber(number.getRe(), -1 * number.getIm());
		return conjugatedNumber;
	}

}//namespace Core

