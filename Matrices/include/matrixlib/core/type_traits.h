#pragma once

#include <complex>
#include <type_traits>

namespace Core {
	namespace Traits {

		template<typename T>
		struct is_complex : std::false_type {};

		template<typename T>
		struct is_complex<std::complex<T>> : std::true_type {};

		template<typename T>
		using EpsilonType = typename std::conditional_t<is_complex<T>::value,
			typename T::value_type, T>;

		template<typename T>
		EpsilonType<T> default_epsilon() {
			if constexpr (is_complex<T>::value) {
				return typename T::value_type(1e-10);
			}
			else {
				return T(1e-10);
			}
		}
	
	}
}