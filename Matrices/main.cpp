#include <iostream>
#include <complex>

#include "include/matrixlib/core/matrix.h"
#include "include/matrixlib/core/type_traits.h"
#include "include/matrixlib/algebra/matrix_operations.h"
#include "include/matrixlib/algebra/matrix_properties.h"
#include "include/matrixlib/algebra/norms.h"
#include "include/matrixlib/decompositions/lup_decomposition.h"

int main() {
	Core::Matrix<double> matrix_1(2, 2);
	Core::Matrix<double> matrix_2(2, 2);
	matrix_1(0, 0) = 2.3;
	matrix_1(0, 1) = 3.5;
	matrix_1(1, 0) = 9.1;
	matrix_1(1, 1) = 6.3;

	matrix_2(0, 0) = 3.2;
	matrix_2(0, 1) = 5.3;
	matrix_2(1, 0) = 1.9;
	matrix_2(1, 1) = 3.6;

	auto result = (matrix_1 + matrix_2);
	auto result_2 = (matrix_1 * matrix_2);
	auto result_3 = (matrix_1 - matrix_2);
	std::cout << result;
	std::cout << std::endl;
	std::cout << result_2;
	std::cout << std::endl;
	std::cout << result_3;

	Decompositions::LUP_Decomposition::Lup_Decomposition<double> obj(matrix_1);
	std::cout << obj.getL();
}