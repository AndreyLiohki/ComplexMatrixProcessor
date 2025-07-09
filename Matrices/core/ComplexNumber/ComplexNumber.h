#pragma once

#include <iostream>
#include <ostream>

namespace LineareAlgebra::Core {

	template<typename T = double>
	class ComplexNumber {
	private:

		static_assert(
			std::is_floating_point_v<T>,
			"ComplexNumber<T> requires T to be a floating-point type"
		);

		T real_;
		T imag_;

	public:

		constexpr ComplexNumber() noexcept:real_(0), imag_(0) {}
		constexpr ComplexNumber(T real, T imag = 0) noexcept: real_(real), imag_(imag) {}
		constexpr ComplexNumber(const std::complex<T>& complexNumber) noexcept : real_(complexNumber.real()), imag_(complexNumber.imag()) {}
		constexpr ComplexNumber(const ComplexNumber&) noexcept = default;
		constexpr ComplexNumber(ComplexNumber&&) noexcept = default;

		constexpr ComplexNumber& operator=(const ComplexNumber&) noexcept = default;
		constexpr ComplexNumber& operator=(ComplexNumber&&) noexcept = default;

		~ComplexNumber() = default;

		[[nodiscard]]constexpr T real() const noexcept { return real_;}
		[[nodiscard]] constexpr T imag() const noexcept { return imag_; }
		constexpr void real(T value) noexcept { real_ = value; }
		constexpr void imag(T value) noexcept { imag_ = value; }

		constexpr ComplexNumber& operator+=(const ComplexNumber& other) noexcept {
			real_ += other.real_;
			imag_ += other.imag_;

			return *this;
		}
		constexpr ComplexNumber& operator-=(const ComplexNumber& other) noexcept {
			real_ -= other.real_;
			imag_ -= other.imag_;

			return *this;
		}
		constexpr ComplexNumber& operator*=(const ComplexNumber& other) noexcept {
			real_ = real_ * other.real_ - imag_ * other.imag_;
			imag_ = real_ * other.imag_ + imag_ * other.real_;

			return *this;
		}
		constexpr ComplexNumber& operator/=(const ComplexNumber& other) {
			if (other.real_ == 0 && other.imag_ == 0) {
				throw std::domain_error("Division by zero");
			}
			T denom = other.real_ * other.real_ + other.imag_ * other.imag_;
			T new_real = (real_ * other.real_ + imag_ * other.imag_) / denom;
			T new_imag = (imag_ * other.real_ - real_ * other.imag_) / denom;
			real_ = new_real;
			imag_ = new_imag;
			return *this;
		}
		[[nodiscard]] constexpr ComplexNumber operator+() const noexcept { return *this; }
		[[nodiscard]] constexpr ComplexNumber operator-() const noexcept { return { -real_, -imag_ }; }
		[[nodiscard]] friend constexpr ComplexNumber operator+(ComplexNumber a, const ComplexNumber& b) noexcept {
			return a += b;
		}
		[[nodiscard]] friend constexpr ComplexNumber operator-(ComplexNumber a, const ComplexNumber& b) noexcept {
			return a -= b;
		}
		[[nodiscard]] friend constexpr ComplexNumber operator*(ComplexNumber a, const ComplexNumber& b) noexcept {
			return a *= b;
		}
		[[nodiscard]] friend constexpr ComplexNumber operator/(ComplexNumber a, const ComplexNumber& b) {
			return a /= b;  
		}
		friend constexpr bool operator==(const ComplexNumber& a, const ComplexNumber& b) noexcept {
			return (a.real() == b.real() && a.imag() == b.imag())
				|| (std::isnan(a.real()) && std::isnan(b.real()))
				|| (std::isnan(a.imag()) && std::isnan(b.imag()));
		}
		friend constexpr bool operator!=(const ComplexNumber& a, const ComplexNumber& b) noexcept {
			return !(a == b);
		}
		friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& z) {
			return os << z.real() << (z.imag() >= 0 ? "+" : "") << z.imag() << "i";
		}
	
		[[nodiscard]] constexpr T abs() const noexcept {
			return std::hypot(real_, imag_);
		}
		[[nodiscard]] constexpr T arg() const noexcept {
			return std::atan2(imag_, real_);
		}
		[[nodiscard]] constexpr ComplexNumber conj() const noexcept {
			return { real_, -imag_ };
		}
		[[nodiscard]] constexpr bool is_zero() const noexcept {
			return real_ == 0 && imag_ == 0;
		}
	};

}//namespace LineareAlgebra::Core